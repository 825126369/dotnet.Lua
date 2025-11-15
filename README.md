<h1>dotnet运行时, 知识备注</h1>

1: 基础知识：
(1) 什么是 bundleProbe?  .NET Core 3.0 之后支持“单文件发布”（PublishSingleFile）。
单文件运行时，所有托管 DLL 都被打包进一个巨大的 exe，原生代码启动后需要知道“怎么在内存里把某个托管 DLL 抠出来”。

(2) FEATURE_GDBJIT: 是 Mono 和 .NET 运行时内部的一个编译开关，用来“把刚刚 JIT 编译出来的机器码同步告诉 GDB/LLDB”，从而在调试器里能看到函数名、能下断点、能打印堆栈——它本身并不是给生产环境用的，也不是热更新方案的一部分。运行时每 JIT 编译一块新代码，就把这块内存的地址、大小、函数名打包成一个 __jit_debug_descriptor 结构体，插到全局链表上。
GDB 里内置了 __jit_debug_register_code 钩子，一旦发现链表有新节点，就把这段机器码当成“临时 ELF 文件”加载到调试符号表里。
结果：你在 GDB 里 bt 能看到 MyCompany.MyClass.Foo() 而不是 ??+0xabcd

2: CLR 启动，和执行程序集是分开的:  exports.cpp 提供了2个重要的方法

(1) coreclr_initialize: 启动CLR虚拟机

(2) coreclr_execute_assembly: 负责执行程序集