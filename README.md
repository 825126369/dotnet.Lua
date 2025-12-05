<h1>dotnet运行时, 知识备注</h1>

官方运行时库: https://github.com/dotnet/runtime

<h1>1: 基础知识：</h1>

(1) 什么是 bundleProbe?  .NET Core 3.0 之后支持“单文件发布”（PublishSingleFile）。
单文件运行时，所有托管 DLL 都被打包进一个巨大的 exe，原生代码启动后需要知道“怎么在内存里把某个托管 DLL 抠出来”。

(2) FEATURE_GDBJIT: 是 Mono 和 .NET 运行时内部的一个编译开关，用来“把刚刚 JIT 编译出来的机器码同步告诉 GDB/LLDB”，从而在调试器里能看到函数名、能下断点、能打印堆栈——它本身并不是给生产环境用的，也不是热更新方案的一部分。运行时每 JIT 编译一块新代码，就把这块内存的地址、大小、函数名打包成一个 __jit_debug_descriptor 结构体，插到全局链表上。
GDB 里内置了 __jit_debug_register_code 钩子，一旦发现链表有新节点，就把这段机器码当成“临时 ELF 文件”加载到调试符号表里。
结果：你在 GDB 里 bt 能看到 MyCompany.MyClass.Foo() 而不是 ??+0xabcd

(3) FEATURE_INTERPRETER 是 .NET Runtime（CoreCLR）内部的一个 条件编译宏（conditional-compile flag），用来控制“解释执行”代码路径是否被编译进运行时。
作用. 当在 CoreCLR 源码里定义了 FEATURE_INTERPRETER 后，运行时会在启动阶段初始化一套 解释器（Interpreter）逻辑，使得部分或全部 IL 指令不经过 JIT 编译，而是直接解释执行 。

(4) "unwind info" 是一组描述“函数在入口处把哪些寄存器压栈、栈帧大小如何变化”的元数据，供操作系统或运行时做栈回溯（stack unwinding）、异常传播和调试器堆栈遍历。它跟普通符号表不同：符号表只告诉你“函数入口地址”，而 unwind info 进一步告诉你“为了回到调用者，需要把哪些寄存器从栈里弹出、如何恢复 RSP/PC”。在 Windows PE/COFF 中，它表现为 .pdata 段里的 RUNTIME_FUNCTION → UNWIND_INFO 结构；

<h1>2: CLR 启动，和执行程序集是分开的:  exports.cpp 提供了2个重要的方法</h1>

(1) coreclr_initialize: 启动CLR虚拟机

(2) coreclr_execute_assembly: 负责执行程序集

<h1>3: 看过源码后，看不懂，原因是 宏太多太长了，但C++有输出宏处理后文件的功能，所以重新编译运行时</h1>

1： 选择 github Release 8.0 版本, 其他版本Build 全部失败。 使用 VS 内置 x64 命令行工具

2：build-runtime.cmd -msbuild //默认无参数选项，只输出生成库Lib/dll文件, -msbuild选项 会输出VS工程。生成的VS工程目录路径: \runtime\artifacts\obj\coreclr\windows.x64.Debug\ide\

3: 通过在 VS工程中， 右键工程->属性->C/C++选项->预处理到文件：设置为true, 就可以输出 预处理文件，这样我们就可以看到完整的代码了

<h1>4: JIT 详解：</h1>

```
PCODE MethodDesc::GetNativeCode()
{
    WRAPPER_NO_CONTRACT;
    SUPPORTS_DAC;
    _ASSERTE(!IsDefaultInterfaceMethod() || HasNativeCodeSlot());
    if (HasNativeCodeSlot())
    {
        // When profiler is enabled, profiler may ask to rejit a code even though we
        // we have ngen code for this MethodDesc.  (See MethodDesc::DoPrestub).
        // This means that *ppCode is not stable. It can turn from non-zero to zero.
        PTR_PCODE ppCode = GetAddrOfNativeCodeSlot();
        PCODE pCode = *ppCode;

#ifdef TARGET_ARM
        if (pCode != NULL)
            pCode |= THUMB_CODE;
#endif
        return pCode; //此时函数要么已经由 NGen 编译好，要么由 ReJIT 重新编译过，不需要再走 JIT。
    }

    if (!HasStableEntryPoint() || HasPrecode())
        return NULL; //告诉调用者“我现在没有稳定入口，你必须走 precode”。 这正对应“第一次调用”或“方法尚未编译”的场景。

    return GetStableEntryPoint(); //方法已经由 JIT 编译过，且没有 NativeCodeSlot（最常见的热路径），直接返回 GetStableEntryPoint()，也就是上次 JIT 生成的机器码址。
}
```

FEATURE_MULTICOREJIT（又称 Multicore JIT）是 .NET Framework 4.5 引入、CoreCLR 继续保留的一项启动加速技术：
利用多核 CPU，在应用启动阶段把“接下来大概率要编译的方法”提前放到后台线程并行编译，从而削掉主线程的 JIT 时间，让程序更快进入稳定状态。它不改变 prestub → JIT 的基本流程，只是提前把活干完，让主线程走到 prestub 时常常能“捡现成”。
基本思想
第一次运行（Recording）
CLR 把启动路径上所有触发的 MethodDesc 按顺序写进 %LocalAppData%\<yourapp>\*.profile 文件。
后续运行（Playback）
进程一启动就 StartProfile，CLR 在后台线程里按 profile 顺序批量调用 MakeJitWorker(..., CORJIT_FLG_MCJIT_BACKGROUND)，
把方法先编译好并塞进 MulticoreJitCodeStorage。
主线程真正调用到某个方法时，prestub → PreStubWorker → GetNativeCode() 会优先去 MulticoreJitCodeStorage 里查，
如果已有现成代码，直接 SetNativeCodeInterlocked 并返回，几乎 0 等待；
若还没轮到后台编，就走常规 JIT，只是现在编译队列已被“预热”，等待时间也大大缩短。

FEATURE_READYTORON（简称 R2R）是 .NET Core 3.0 正式引入、.NET 5+ 默认开启的预编译（AOT）技术：
在 build 阶段就把 IL 编译成目标平台的机器码，并嵌入同一 PE 文件（.dll/.exe）的专用区域；
运行时跳过 JIT，直接映射到 ReadyToRun 代码，从而把启动时间和JIT 内存占用都压到最低。
它与 prestub 和 Multicore JIT 是互补关系：有 R2R 就用 R2R，没有才回退到 prestub → JIT。
基本思想
编译期（Crossgen2）
把 IL + 元数据 → 目标平台机器码，生成 .r2r section 和 READYTORUN_HEADER。
运行期（CoreCLR）
加载模块时，ReadyToRunInfo::Initialize 把 .r2r section 映射到内存；
方法第一次被调用，prestub → PreStubWorker → MethodDesc::DoPrestub
会优先去 R2R 哈希表里查，命中就直接返回机器码地址，不再调用 JIT；
若缺失（泛型特化、版本 bubble 外等）才回退到传统 JIT。

CallDescrWorkerInternal 是纯原生汇编辅助例程，它的唯一职责是：
按预先填好的 TransitionBlock（参数槽、返回地址、寄存器镜像）把线程从协作模式切到抢占模式；
用一段非常精简的 calling-convention 胶水直接跳转到目标机器码地址；
目标函数返回后，再把返回值搬回 TransitionBlock，切回协作模式，返回到托管 caller。
——它本身既不会解释 IL，也不会触发 JIT，只是“帮你把参数、返回、GC 模式、栈对齐”全部铺好，然后一条 jmp/blr 把 PC 交给那个地址。
