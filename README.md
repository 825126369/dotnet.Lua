<h1>dotnet运行时, 知识备注</h1>

官方运行时库: https://github.com/dotnet/runtime

本地安装目录: C:\Program Files\dotnet\shared\Microsoft.NETCore.App\

<h1>编译runtime，产生VS工程</h1>

1： 选择 github Release 8.0 版本, 其他版本Build 全部失败。 使用 VS 内置 x64 命令行工具

2：build-runtime.cmd -msbuild //默认无参数选项，只输出生成库Lib/dll文件, -msbuild选项 会输出VS工程。生成的VS工程目录路径: \runtime\artifacts\obj\coreclr\windows.x64.Debug\ide\

3: 通过在 VS工程中， 右键工程->属性->C/C++选项->预处理到文件：设置为true, 就可以输出 预处理文件，这样我们就可以看到完整的代码了

<h1>CLR虚拟机 核心入口方法： exports.cpp 提供了2个重要的方法</h1>

(1) coreclr_initialize: 启动CLR虚拟机

(2) coreclr_execute_assembly: 负责执行程序集


<h1> 基础知识：</h1>

(1) 什么是 bundleProbe?  .NET Core 3.0 之后支持“单文件发布”（PublishSingleFile）。
单文件运行时，所有托管 DLL 都被打包进一个巨大的 exe，原生代码启动后需要知道“怎么在内存里把某个托管 DLL 抠出来”。

(2) FEATURE_GDBJIT: 是 Mono 和 .NET 运行时内部的一个编译开关，用来“把刚刚 JIT 编译出来的机器码同步告诉 GDB/LLDB”，从而在调试器里能看到函数名、能下断点、能打印堆栈——它本身并不是给生产环境用的，也不是热更新方案的一部分。运行时每 JIT 编译一块新代码，就把这块内存的地址、大小、函数名打包成一个 __jit_debug_descriptor 结构体，插到全局链表上。
GDB 里内置了 __jit_debug_register_code 钩子，一旦发现链表有新节点，就把这段机器码当成“临时 ELF 文件”加载到调试符号表里。
结果：你在 GDB 里 bt 能看到 MyCompany.MyClass.Foo() 而不是 ??+0xabcd

(3) FEATURE_INTERPRETER 是 .NET Runtime（CoreCLR）内部的一个 条件编译宏（conditional-compile flag），用来控制“解释执行”代码路径是否被编译进运行时。
作用. 当在 CoreCLR 源码里定义了 FEATURE_INTERPRETER 后，运行时会在启动阶段初始化一套 解释器（Interpreter）逻辑，使得部分或全部 IL 指令不经过 JIT 编译，而是直接解释执行 。

(4) "unwind info" 是一组描述“函数在入口处把哪些寄存器压栈、栈帧大小如何变化”的元数据，供操作系统或运行时做栈回溯（stack unwinding）、异常传播和调试器堆栈遍历。它跟普通符号表不同：符号表只告诉你“函数入口地址”，而 unwind info 进一步告诉你“为了回到调用者，需要把哪些寄存器从栈里弹出、如何恢复 RSP/PC”。在 Windows PE/COFF 中，它表现为 .pdata 段里的 RUNTIME_FUNCTION → UNWIND_INFO 结构；

(5) EN_C_SUPPORTED（注意：正确宏名是 ENC_SUPPORTED，全大写，常写作 #define ENC_SUPPORTED 1）是 .NET 运行时（CoreCLR / .NET Runtime）中一个编译期开关宏（build-time feature flag），用于控制是否启用 Edit and Continue（EnC）—— 即“编辑并继续”调试功能 的底层支持。


<h1>汇编 *.S *.asm 详解</h1>

(1) *.S：对应 GCC 汇编语法：AT&T / ARM 统一汇编。  *.asm： 对应 MSVC 汇编语法: Intel MASM

(2) LEAF_ENTRY	叶子函数： 会生成 尾部标签(类似 StubPrecodeCode_End), 供 C++ 侧计算桩长度;   NESTED_ENTRY	非叶子函数	需要标准 prolog/epilog

<h1>JIT [clrjit.dll] 详解</h1>

<h2>一些宏定义的意思</h2>

FEATURE_MULTICOREJIT（又称 Multicore JIT）是 .NET Framework 4.5 引入、CoreCLR 继续保留的一项启动加速技术：
利用多核 CPU，在应用启动阶段把“接下来大概率要编译的方法”提前放到后台线程并行编译，从而削掉主线程的 JIT 时间，让程序更快进入稳定状态。它不改变 prestub → JIT 的基本流程，只是提前把活干完，让主线程走到 prestub 时常常能“捡现成”。

FEATURE_MULTIREG_RET 并不是某条汇编指令，而是 CoreCLR-JIT 在 编译期 使用的一个 条件编译宏（feature flag），用来区分“当前目标平台是否支持把结构体或长整型拆到多个寄存器返回”。

FEATURE_READYTORON（简称 R2R）是 .NET Core 3.0 正式引入、.NET 5+ 默认开启的预编译（AOT）技术：
在 build 阶段就把 IL 编译成目标平台的机器码，并嵌入同一 PE 文件（.dll/.exe）的专用区域；
运行时跳过 JIT，直接映射到 ReadyToRun 代码，从而把启动时间和JIT 内存占用都压到最低。
它与 prestub 和 Multicore JIT 是互补关系：有 R2R 就用 R2R，没有才回退到 prestub → JIT。

CallDescrWorkerInternal 是纯原生汇编辅助例程，它的唯一职责是：
按预先填好的 TransitionBlock（参数槽、返回地址、寄存器镜像）把线程从协作模式切到抢占模式；
用一段非常精简的 calling-convention 胶水直接跳转到目标机器码地址；
目标函数返回后，再把返回值搬回 TransitionBlock，切回协作模式，返回到托管 caller。

StubManager: 在 .NET 运行时（.NET Runtime）中，StubManager 是一个内部（internal）、非公开的运行时组件，主要存在于 CoreCLR（即 .NET Core / .NET 5+ 的运行时实现）中，用于管理调用桩（stubs）的生成、缓存与生命周期。Stub 缓存管理：维护 MethodDesc/StubSig → stub 地址 的映射（哈希表或类似结构），避免重复生成。
内存分配与释放：	在专用内存区域（如 CodeHeap 或 JitCodeHeap）中申请可执行内存，并在卸载 Assembly 或 AssemblyLoadContext 时安全回收。
Stub 生命周期跟踪：	关联 stub 与所属模块/上下文，支持 ALC 卸载时自动清理（防止内存泄漏或悬空跳转）。
调试与诊断支持：	提供调试器接口（如 ICorDebug）查询 stub 信息，用于断点、堆栈展开等

ThePreStubManager:StubManager ：

预分配 & 复用 PreStub 模板:	 在启动时为不同架构（x64/arm64）预生成少量固定格式的 stub 模板（如 PrecodeFixupThunk, DynamicHelperFixupThunk），避免每次分配都写入可执行内存  按需生成 PreStub 实例	当某个 MethodDesc 尚未 JIT，且其入口点（m_pEntry）被设为 PreStub 地址时，ThePreStubManager::GetPreStub() 返回一个指向该方法专属 prestub 的指针。
Patch（热补丁）机制:  JIT 完成后，运行时通过 ThePreStubManager::ReplacePreStubWithRealCode() 将 prestub 内存中的跳转指令原子地修改为直接跳向 JIT 后的代码地址（例如 jmp [rip + offset] → jmp <real_method_addr>）。这是 .NET “冷启动优化”的关键一环。
支持多种 prestub 类型:	根据方法特性选择不同 stub：
• PRESTUB：普通非泛型方法
• DYNAMICHELPERFIXUPPRESTUB：泛型/动态方法（需运行时解析类型）
• IL_STUB_PRESTUB：IL stub（如委托调用封装）
• UNMANAGED_EXPORT_PRESTUB：[UnmanagedCallersOnly] 导出函数的前置入口
与 GC / 卸载协同:	确保 prestub 所占内存在其所属 Module 或 AssemblyLoadContext 卸载时被安全释放（尤其在 ALC 卸载场景下防止悬挂 stub）。

PrecodeStubManager:StubManager  是创建/缓存/释放所有 Precode 实例的管理者。

StubLinkStubManager:StubManager 为每个需“懒解析”的方法分配一个 StubLinkStub（桩链接桩），由 StubLinkStubManager 统一管理。

ThunkHeapStubManager:StubManager 就是 .NET CoreCLR 为“动态生成小段可执行跳板”量身定做的内存池：按需分配 32/64 字节可执行槽位，用完即还，既快又不漏，是托管代码无缝调用原生世界的幕后功臣。

JumpStubStubManager：StubManager  x64/IA64 的 jmp 指令只有 32-bit 相对偏移（±2 GB）。 CoreCLR 的代码段（JIT 后的机器码、NGEN 镜像、预编译 stub）可能被地址空间随机化（ASLR）放到 >2 GB 之外。这时如果 A 方法里要直接跳转到 B 方法，而两者相距 >2 GB，就必须在中间插一段“跳板”——先把绝对地址放进寄存器再 jmp reg。这段跳板就是 jump stub，由ExecutionManager::jumpStub() 在运行期实时生成，并由 JumpStubStubManager 统一分配、回收、识别。

RangeSectionStubManager : StubManager 解决的问题： “给定一个指针，它是不是某类 stub？ 如果是，下一步该往哪走？” 如果每个查询都线性遍历所有 StubManager，性能不可接受；于是 CLR 把“地址→StubManager”做成一张范围表（RangeSection），并让一个统一的 RangeSectionStubManager 坐镇调度。

ILStubManager : StubManager 它的作用可以一句话概括为：“让调试器、profiler 能认出‘这片代码是运行期动态生成的 IL stub’，并告诉它们下一步该怎么走。”

InteropDispatchStubManager : StubManager 是 .NET CoreCLR 里专门负责 “通用互操作分发桩” 的 StubManager。 它只干三件事：认出 GenericComPlusCallStub、VarargPInvokeStub 和 GenericPInvokeCalliHelper 这三段手写汇编桩，然后告诉调试器 “这是互操作分发桩，下一步请走到 unmanaged 目标” 。

TailCallStubManager  尾调用指的是函数的最后一条语句是“调用另一个函数”并且“直接用它的返回值作为自己的返回值”。
此时调用者（caller）的栈帧已经不再有用，可以被被调用者（callee）的栈帧立即复用，从而省掉一次压栈 / 弹栈的开销。
如果编译器 / 运行时真的这么做了，就叫 尾调用优化（Tail Call Optimization，TCO） 或 尾递归优化（当 callee 正是 caller 自身时）

VirtualCallStubManager : StubManager（简称 VCSM）是 CoreCLR 中 “虚派发 + 接口派发” 的 专属 StubManager。它只为 virtual 方法 和 interface 方法 调用服务，核心目标：
把“对象运行时类型 → 目标方法地址”的映射做成可缓存的桩（stub）；让后续调用走最快路径（一条 cmp + jmp），失败才回退到运行时解析；对调试器、profiler 提供“这是虚桩”的身份识别与单步支持。

<h2>Precode 类型</h2>

StubPrecode：基础类型，加载 MethodDesc 并跳转

FixupPrecode：用于 NGen 映像中的方法修复，省略加载 MethodDesc 以提升性能

NDirectImportPrecode：用于 P/Invoke 的延迟绑定
 
ThisPtrRetBufPrecode：处理返回值类型的开放实例委托的调用约定转换

<h2>MethodTableBuilder</h2>
MethodTableBuilder 的唯一使命就是“把元数据里的一堆 TypeDef/MethodDef 记录变成一块真正可运行的 MethodTable 内存。可以把整个构建过程看成一条流水线：
拿到待建类型的元数据 token、父类句柄、接口列表、泛型实参等原料；

<h2>JIT 外围调用 流程图</h2>

(1) 设置 PCode 指向 ThePreStub 方法

Assembly::GetEntryPoint() => 

ClassLoader::LoadTypeHandleForTypeKey => 

ClassLoader::CreateTypeHandleForTypeDefThrowing => 

MethodTableBuilder::BuildMethodTableThrowing => 

Precode::Init => 

GetPreStubEntryPoint 返回代码点 ThePreStubAMD64.asm[ThePreStub] 

(2) 调用 ThePreStub 方法,进行执行 JIT/解释器

callhelpers.h[CallTargetWorker] => 

CallDescrWorkerAMD64.asm[CallDescrWorkerInternal] (没有JIT的时候)=> 

ThePreStubAMD64.asm[ThePreStub] => 

prestub.cpp[PreStubWorker] => 

prestub.cpp[MethodDesc::DoPrestub] => 

prestub.cpp[MethodDesc::PrepareInitialCode] => 

jitinterface.cpp[UnsafeJitFunction]

<h2>JIT [clrjit.dll] 内部调用 流程图</h2>

ee_il_dll.cpp[jitStartup] => ee_il_dll.cpp[CILJit::compileMethod] => [compiler.cpp]Compiler::compCompile => [codegencommon.cpp]CodeGen::genGenerateCode

<h2>ClrJit DoPhase各个阶段</h2>

fgTransformPatchpoints : 就是 Tier-1 编译把占位块换成真正“逃生跳板” 的局部改写阶段，确保 OSR 既能热替换，也能安全回退。

fgTransformIndirectCalls ：把看不见目标的 call [reg] 变成 if-else 双路径：热路径直调用，冷路径保持间接，既提速又保正确，是 PGO/静态启发式落地的关键一步。

fgMorphInit = “Morph 大循环前的全局缓存与开关集中初始化”，本身不改 IR，只负责把后面高频访问的常量/掩码/缓存一次性填好，让几十万次递归 fgMorphTree 跑得更快、分支更少。

fgInline = “在 Morph 期把符合条件的 call 整个展开成调用方 IR 子图”，彻底消除调用开销，为后续所有全局优化打开更大空间，是 .NET JIT 拿到 “零调用开销 + 跨过程常量折叠” 最关键的一刀。


<h2> 苹果 IOS 禁止JIT 的窍门</h2>

VirtualAlloc = Windows 内核级“整页内存”分配器，64 KB 对齐，可赋 RX/RWX，专为 JIT、大对象、Guard Page 设计；日常小对象请继续用 malloc/new。

Compiler::eeAllocMem 拿到的内存页已被内核标成可执行，所以JIT 往里写入机器码后 CPU 能直接跳转过去。

普通 new/malloc 只给 RW 权限，往里写指令会立即触发 DEP/权限错误——这是二者最本质的区别。

这也是苹果禁止JIT的关键: 在进程内让内核 不再标记任何内存为：RWX(可执行内存)，JIT也就堵死了。


<h2>JIT的心脏：RWX内存</h2>

insGroup 是 RyuJIT emitter 里最底层的 代码块 单位：它把连续发射的指令归成一组，挂到链表上，用来解决“热代码/冷代码分裂”和“地址重定位”问题。
emit 阶段把指令攒进组 → 输出阶段按组复制到最终可执行内存 → 重定位时按组修正跳转偏移。

emitSavIG：本质就是往可执行内存里现场写机器码——JIT 的核心动作。

<h1>GC [clrgc.dll] 详解</h1>

GC初始化方法: ceemain.cpp[InitializeGarbageCollector] => gcload.cpp[GC_Initialize]




