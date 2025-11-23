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

<h1>2: CLR 启动，和执行程序集是分开的:  exports.cpp 提供了2个重要的方法</h1>

(1) coreclr_initialize: 启动CLR虚拟机

(2) coreclr_execute_assembly: 负责执行程序集

<h1>3: 看过源码后，看不懂，原因是 宏太多太长了，但C++有输出宏处理后文件的功能，所以重新编译运行时</h1>

1： 选择 github Release 8.0 版本, 其他版本Build 全部失败。

2：build-runtime.cmd -msbuild //默认无参数选项，只输出生成库Lib/dll文件, -msbuild选项 会输出VS工程。生成的VS工程目录路径: \runtime\artifacts\obj\coreclr\windows.x64.Debug\ide\

3: 通过在 VS工程中， 右键工程->属性->C/C++选项->预处理到文件：设置为true, 就可以输出 预处理文件，这样我们就可以看到完整的代码了
