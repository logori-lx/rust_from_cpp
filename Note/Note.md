

# 基础概念

## Cargo

### 创建新项目

```sql
cargo new {project_name}
```

### 编译运行代码

编译项目，默认为**debug模式**，cargo会以最快的速度编译项目，但不会对其进行任何优化，所以编译速度虽然快，但运行速度会相对慢些，同时会在${project}/target/debug下创建${project_name}.exe可执行文件

```sql
cargo build
```

**release模式**，编译慢，但会对其进行优化，运行速度快

```sql
cargo build --release
```

运行对应的项目，相当于cargo build + ./xxx.exe

```sql
cargo run （--release）
```

创建cargo.toml (适用于将原本不是由cargo管理的代码)

``````bash
cargo init
``````
#### 编译
如果在cargo.toml中增加了dependencies的库，在编译时，与C/C++类似cargo会下载对应的库并且将其编译，并且在已经编译完毕且没有代码和新增dependencies的情况下，再次调用cargo编译会不做任何事情，直接退出。



### 代码检查

由于rust需要做很多复杂的编译优化和语言特性解析，所以其编译速度也会变慢，我们可以通过cargo内置的check指令快速的检查代码是否能够通过编译，节省编译时间

```sql
cargo check
```

### Cargo.toml

Cargo.toml指定了项目依赖的package名称和对应的能运行的版本范围，类似于python中的requirements.txt

以下面的Cargo.toml作为示例:

```sql
[package]
name = "hello_world"
version = "0.1.0"
edition = "2024"

[dependencies]
rand = "0.3"
hammer = { version = "0.5.0"}
color = { git = "https://github.com/bjz/color-rs" }
geometry = { path = "crates/geometry" }
```

其中package中描述了项目的描述信息，name定义项目名称，version定义了项目的版本，edition定义了rust的大版本，此处为2024说明为Rust edition 2024的版本。

dependencies定义了项目依赖，其有几种写法

```sql
# 引入rust 标准库，其中0.3表示0.3.1 0.3.2 ...
# 都可以作为依赖
rand = "0.3"
# 也为引入rust 标准库，但这种方式可以使用feature功能
# 只引入必要的库，或者额外引入一些这个库的其他功能
hammer = { version = "0.5.0"}
# 从github引入库
color = { git = "https://github.com/bjz/color-rs" }
# 用相对路劲引入本地的库
geometry = { path = "crates/geometry" }
```
其中对于版本号来说
```rust
rand = "0.3.5"
```
等价于
```rust
rand = "^0.3.5"
```
其含义为可以安装0.3.5极以上的版本，比如0.3.5, 0.3.6, 0.3.7... 0.3.20...。但不可以安装0.4极其以上的版本
### Cargo.lock
用于追踪编译时实际使用的不同依赖库是什么版本
## 变量定义

在rust 中我们使用let去定义一个变量，如

```sql
let a = 10;
```

但rust中默认定义的变量是一个常量，其值不可更改，如果想要更改变量中的值需要这样定义

```sql
let mut a = 10;
```
## 标准库引入
与C++相同，rust中也有许多标准库，我们可以用类似C++中using的use进行引入
```rust
use std::io
...
io::stdin().read_line(&mut guess)
...
```

## 输入
```rust
std::io::stdin().read_line(&mut guess).expect("Failed to read line");
```
stdin()会返回一个std::io::Stdin实例，其用于处理终端的标准输入，其有成员方法read_line()

而readline函数中之所以传入guess参数前面要加&，其实是与C++类似，标明传入的是个变量的引用，而不是变量本身，但同时与C++不同的是，如果传入的变量没有加mut则代表这个变量是const的，不能被read_line函数所变更，所以需要加mut

而readline函数执行完后会返回一个类型的enum，其值为Ok和Err，在rust中定义如下
```rust
enum Result<T, E> {
    Ok(T),   // 变体 1：包含成功的数据 T
    Err(E),  // 变体 2：包含错误的数据 E
}
```
当read_line函数失败时，会返回Err，调用expect会直接让程序崩溃，并且输出"Failed to read line"
如果成功，则会返回Ok，调用expect会返回一个数值，即成功读取的字符数。
```rust
let bytes = io::stdin()
    .read_line(&mut guess)
    .expect("读取失败")
println!("成功读取了{}个字节",bytes)
```
同时要注意rust 中的read_line与C++中的不同，其是用append模式追加到变量当中的，所以如果要每次读入新行，记得需要对变量进行clear()
```rust
let mut bytes = String::new();
loop{
	bytes.clear();
	let bytes = io::stdin().read_line(&mut bytes).expect("读取失败")
	....
}
```
## 输出
有两种方式，一种是直接用"{}"括住你要输出的变量，另一种则与python中输出方式类似，在要输出变量的地方加"{}"，然后在字符串后面以","连接要输出的变量
```rust
let x = 12
let y = 15
println!("x = {x}, y = {}",y)
```

## 数值比较
在rust 中一方面支持C/C++中的< > = 的比较表达式，如
```rust
if guess < secret_number{
	println!("Too small");
}else if guess == secret_number{
	println!("Equal");
}else{
	println!("Too large");
}
```
另一方面，与C/C++不同，其基本类型i32, u32等也具备成员方法，其提供了相比if else更优雅的数值比较方法cmp
```rust
match guess.cmp(&secret_number){
	Ordering::Less => println!("Too Small"),
	Ordering::Equal => println!("Equal"),
	Ordering::Greater => println!("Too large"),
}
```
但使用这种方法，强制需要将大于小于等于三种情况
比如如果少了greater的情况就会报如下错误:
![[Pasted image 20260114122149.png]]
## 字符串类型
### 去除空白字符串
string有成员方法trim来去除字符串中前后的空白字符串，包括"\n", " ", "\t"等
```rust
let mut a = String::from(" hello ");
let a = a.trim();
```
### 字符串转数值
```rust
let mut a = String::from(" 12 ");
let a : u32 = a.trim().parse().expect("isn't a number");
```
## 错误处理
### Result<T, E>
其与C/C++中的std::variant<T, E>几乎相同，为完全安全的union。对于C/C++中一般的union
```c++
struct MyResult {
    union {
        int value;
        char* error_msg;
    } data;
};

int main(){
    MyResult my_result;
    my_result.data.error_msg = "hello world";
    // 存在安全隐患，可以不进行类型判断就直接输出
    printf("%d", my_result.data.value);
}
```
而Result<T, E>可以视作一个带标签的union，在内存上虽然跟union原理一致，只分配占用空间最大的类型所占的空间大小，但在使用上，其只有在被正确解包时才会将数据当成对应的类型数据进行返回，比如
```rust
let guess : u32 = match guess.trim().parse(){
	Ok(num) => num,
	Err(_) => continue,
}
```
其中如果是Ok类型，其会根据guess的类型u32将union变为u32进行返回，如果是Err类型，因为Result的类型为Result<u32, ParseIntError>，其解包后返回的是ParseIntError，这里会用_忽略拆包出来的ParseIntError，因为有continue而继续
