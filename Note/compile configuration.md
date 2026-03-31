# 跨平台编译选项
rust中如果想要跨平台编译，需要确定如下几个参数
```
<架构 (Arch)> - <供应商 (Vendor)> - <操作系统 (OS)> - <环境/ABI (Environment)>
```
比如，像下面的指令：
```bash
cargo build --release --target "i686-pc-windows-msvc"
```
i686-pc-windows-msvc 分别代表
- **第 1 部分：`i686` (架构)** 这就对应了你刚才写的 `target_arch="x86"`。它决定了编译器生成哪种 CPU 指令集。
- **第 2 部分：`pc` (供应商)** 这代表硬件供应商。在通用电脑上通常是 `pc`，如果是苹果设备可能会看到 `apple`，如果是通用的 Linux 经常会写 `unknown`。
- **第 3 部分：`windows` (操作系统)** 这就对应了 `target_os="windows"`。它决定了编译器如何处理系统调用（Syscalls）和操作系统 API。
- **第 4 部分：`msvc` (环境 / ABI)** 这是后来加上的第四部分，用来指定应用程序二进制接口（ABI）或具体的工具链环境。

具体的参数设置可以查看[官方文档](https://doc.rust-lang.org/reference/conditional-compilation.html) 



