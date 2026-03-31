rust中cfg与C++中的ifdef有点相像，是用于**编译器预处理阶段的编译配置**，主要承担了条件编译（类似于C++中的#ifdef win32 xxx ）以及编译参数的传入（类似于C++中 g++ -o test.exe中的-o test.exe这部分就是由rust所处理的）
# 条件编译
我们可以用如下格式的代码在rust中实现条件编译，在部分平台中不编译特定的代码实现跨平台环境适配，比如，对于一段需要在win32上运行的程序，我们可以使用如下指令进行编译
```rust
cargo build --release --target "i686-pc-windows-msvc"
```
同时，为什么需要写成--target "i686-pc-windows-msvc" 则可以参考[跨平台编译选项](#跨平台编译选项)

然后我们就可以确保下面的函数call_win32_api仅在win32时才会被编译
```rust
#[cfg(all(target_arch="x86", target_pointer_width="32", target_os="windows"))]
fn call_win32_api() { ... }
```
# 条件判别
我们可以使用如下格式的代码来实现判别是否处于debug模式
```rust
if cfg!(debug_assertions) {
	println!...	
}
```
同时需要注意的是，这种写法并不会像ifdef一样在release模式下不把代码编译进来，而是无论release还是debug模式都会保留代码。至于如何区分debug模式，参考[编译运行代码](编译运行代码)
