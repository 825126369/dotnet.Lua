<h1>dotnet运行时, 知识备注</h1>

1: 什么是 bundleProbe?
.NET Core 3.0 之后支持“单文件发布”（PublishSingleFile）。
单文件运行时，所有托管 DLL 都被打包进一个巨大的 exe，原生代码启动后需要知道“怎么在内存里把某个托管 DLL 抠出来”。
