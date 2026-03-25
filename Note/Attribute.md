# 概念
在rust中属性与C++11中的属性概念类似，都是开发者对代码所做的一些编译过程中的指令，也与C中的__attribute__类似。
在C中我们可以使用__attribute__修饰结构体，告诉编译器一些编译过程中需要遵循的指令
```cpp
// 告诉编译器取消内存对齐优化 
struct MyPacket { 
	char a; // 1 字节 
	int b; // 4 字节 
} __attribute__((packed)); // 加上 packed 后，这个结构体大小严格是 5 字节；不加的话通常是 8 字节。
// 强制要求这个数组的内存地址是 16 的倍数
int my_array[4] __attribute__((aligned(16)));
```
在C++中我们可以使用\[\[...\]\]语法来对编译器下一些指令
```cpp
// 告诉编译器和阅读者，这个函数一旦调用，程序/线程就不会往下走了
[[noreturn]] void fatal_error(const char* msg) {
    throw std::runtime_error(msg);
    // 或者 std::exit(1);
}

int do_something(int x) {
    if (x < 0) {
        fatal_error("Negative value not allowed!");
    }
    return x * 2; // 编译器知道 fatal_error 不会返回，所以这里不需要考虑 x < 0 时的 return 问题
}
```
C++中我们有如下属性

而在rust中，我们则使用#\[...\]来对编译器下一些指令
比如
```rust
#[derive(Deserialize, Debug)]
struct InputPayload {
    user_prompt: String,
    file_content: String,
    file_extension: String,
}
```
有了derive派生的Deserialize和Debug 这两个trait, InputPayload这个struct就能够在编译期间产生对应的反序列化代码，能够正确的转化成json格式而不用自己去写反序列化代码，同时Debug trait则能够在调用println!({:?})时能格式化打印结构体。

# 类型
## derive
rust中唯一能够派生出trait修饰结构体或者其他数据结构的属性,其会在编译过程中生成一系列的代码，以便在运行时能够执行，比如下面的代码,derive就在编译过程中生成了反序列化代码和用于debug格式化打印的函数
```rust
#[derive(Deserialize, Debug)]
struct InputPayload {
    user_prompt: String,
    file_content: String,
    file_extension: String,
}
```
有了Deserialize 这个trait, 就不必要人工写像下面这样的反序列化函数以供serde_json::from_str函数反序列化
```rust
// 类似于在 C++ 类外实现接口函数
impl Deserialize for InputPayload {
    fn deserialize(...) -> ... {
        // 你手写的解析逻辑
    }
}
let input: InputPayload = match serde_json::from_str(&input_json){
	...
}
```