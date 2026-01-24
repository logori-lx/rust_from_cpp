

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

以C++作为参照，我们可以得到如下的一张表：

| rust 语法           | C++ 语法              | 核心语义        | 初始化时机  |
| ----------------- | ------------------- | ----------- | ------ |
| let mut x = ...   | auto x = ...        | 类型自动推导的可变变量 | 运行时    |
| let x = ...       | const auto x = ...  | 不可变变量（只读）   | 运行时    |
| const x = ...     | constexpr T x = ... | 真 常量（编译期写死） | 编译时    |
| static X: T = ... | static T X = ...    | 全局变量 (固定地址) | 编译/加载时 |
但rust 和C++还是会存在一些不同
### 类型推导的可变变量
首先对于可变变量，其存在以下几点不同
#### 初始化要求不同
C++中用auto定义变量要求一定要赋值，而rust中let mut则不一定要赋值，比如在C++中, 用auto声明一个变量是不允许的
```C++
  auto a
```
但是，rust中允许用let mut 像下面这样对变量先进行声明，后面再对其进行赋值
```rust
 let mut a;
 a = 10;
 println!("{a}") 
```
#### auto存在**类型退化**现像
所谓类型退化即用auto定义变量时，如果用一个const或者引用给其赋值，其常常会剥离const以及引用，如像下面的C++代码
```C++
int a = 10;
const int& a_ref = a;
auto b = a_ref;
b = 11;
std::cout << a << std::endl;
```
输出如下：
![](assets/Pasted%20image%2020260114203809.png)
可以发现auto 定义的变量b只是一个单纯的int类型变量，既不const也不是引用（a的值没变）。这是因为auto 在定义变量的时候，将const 和引用都剥离了。
而对于rust， 严格上说，其也会有const的剥离，因为如下面的代码

```rust
let a = 10;
let mut b = a;
b = 11;
println!("{b}");
```
可以看到b也并没有继承a的“const”属性（虽然这在rust中并不能称为const），其数值仍可以变更。
另一方面，对于引用来说，rust中的引用其实更像是C语言中的指针，所以也并不存在类似C++中的引用剥离这一说（因为rust中并不存在像C++中引用一样的类型）
```rust
let mut a = 10;
let mut b =  & mut a;
*b = 11;
println!("a (original): {}", a);
```
其输出为：
![](assets/Pasted%20image%2020260114211028.png)
#### 编译器敏感程度不同
在rust中，如果你定义了一个let mut变量却不修改其值，那么编译器会报一个warning，而C++中，编译器则司空见惯，根本不会作任何反应
```rust
let mut a = 10;
println!("a (original): {}", a);
```

![](assets/Pasted%20image%2020260114212329.png)

## 标准库引入
与C++相同，rust中也有许多标准库，我们可以用类似C++中using的use进行引入
```rust
use std::io
...
io::stdin().read_line(&mut guess)
...
```
### 不可变变量
对于rust而言，其不可变变量为真·不可变变量，想要改变不可变变量唯有通过unsafe去修改，并且rust官方也说明了这种修改结果是未定义的，编译器可以将修改的语句优化掉。
而对于C++而言，const 更像是一种君子协定，可以通过很多种方式绕开
#### 通过mutable修改不可变变量
如下面的代码
```C++
class Data {
  mutable int a = 0;
  public:
    void do_something() const{
        a++;
    }  
    int get_value() const{
        return a;
    }
};
int main(){
    const Data data;
    data.do_something();
    std::cout << data.get_value() << std::endl;
}
```
可以发现，虽然data是const声明的，但是还是能够通过mutable修改其中的值
#### 强制类型转换
开发者可以很轻松地通过const_cast 来将一个const指针改成一个可以被变更的指针，如下面的代码
```c++
int a = 10; 
const int* p = &a; 
int* ptr = const_cast<int*>(p); 
*ptr = 20;
```
另外，强制类型转换也可能导致未定义行为:
如下面的代码:
```C++
    const int a = 10;  // a 是真正的常量
    int* p = (int*)&a; // 强行获取地址并强转
    *p = 20;           // 试图修改
    std::cout << "a = " << a << std::endl;
    std::cout << "*p = " << *p << std::endl;
    std::cout << "&a = " << &a << std::endl;
    std::cout << "p  = " << p << std::endl;
    return 0;
```
其输出为:
![](assets/Pasted%20image%2020260114220119.png)
可以发现，p指针确实修改了a地址的内存，打印出来的a的值却没变，这是因为编译器看到这是一个const变量，就认为其值不可能更改，所以在要输出a的值时就直接将a寄存器中a原来的值直接填进去了，而没有读内存，但是p也的确修改了a地址所存储的值。
而这在rust中，只有unsafe才能够实现
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
![](assets/Pasted%20image%2020260114122149.png)
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
## 引用
之前也提到过，rust中的引用与其说是“引用”，其概念上更像是C/C++中的二级指针（即\*\*ptr）
如rust book中画的下面这张图所示
![](assets/Pasted%20image%2020260120131104.png)
可以看到s是变量s1的引用，但在rust中其角色，更像是C/C++中的二级指针，对一个变量创建引用的行为被称为是**借用**。而既然是二级指针，那就很好理解为什么对一个变量进行借用，并不影响其所有权(Ownership)了，因为我们并不能通过修改二级指针的方式实现对一级指针所指向的内容进行修改，自然也谈不上对变量拥有所有权。
### 可变与不可变引用
rust为了避免**数据竞争**，对引用的定义有如下规则，这些规则确保了rust在通过编译后，没有数据竞争的代码
对于同一变量:
1. 同一作用域下可以有任意个不可变引用
2. 同一作用域下只能有一个不可变引用
3. 同一作用域下不可变引用和可变引用不能共存

为什么这三项规则可以让rust避免数据竞争，让我们复习一下数据竞争产生的三个必需条件
1. 多个内存访问操作同时进行
2. 至少有一个访问操作是写访问
3. 没有互斥锁进行保护
rust对于引用的三项规则确保了rust即使没有互斥锁的保护，rust也不可能有数据竞争，因为满足条件1在rust中仅当定义多个不可变引用时才可满足，而由于rust中同一变量不可变引用和可变引用在同一作用域下不能共存，所以条件2必不满足；同样，满足条件2在rust中仅当定义了一个可变引用时才可满足，也由于rust中同一变量不可变引用和可变引用在同一作用域下不能共存，条件1必不满足。条件1与条件2的互斥确保了rust中的引用不可能存在数据安全问题。

### 悬垂引用
rust中也不可能存在悬垂引用，rust中使用了生命周期这一特性去确保这一特性，一个引用的生命周期一定小于等于其指向变量的生命周期，如果其指向变量的生命结束时，则其引用生命必然结束，后面再使用引用必然会报错。
### 切片
rust中的切片在概念上实际上类似于**C/C++中的指针**，只是这个指针拥有长度，规定了指针的起始。在字符串处理上，相比C用'\0'去标明一个字符串的结尾，一方面避免了'\0'被错误覆盖时导致的访问越界内存问题，另一方面省下了计算字符串长度（strlen）的开销。
同时切片在rust中本质上是一个**指向原始数据里特定位置的引用**，利用这一特性，rust很轻松的实现了避免切片在原始数据内存被回收时没有被及时回收导致切片指向一块未定义内存区域的机制，如下面的这段代码
```rust
fn first_word(s: &String) -> &str {
   ...
}

fn main() {
    let mut s = String::from("hello world");

    let word = first_word(&s);

    s.clear(); // error!

    println!("the first word is: {}", word);
}

```
word是s的一个切片，也是一个s的一个不可变引用，当s调用clear时，其会创建一个可变引用来进行回收，而由于可变引用和不可变引用的不可兼容性，其能够在编译到s.clear()时就报错，避免了切片在原始数据被回收后仍继续使用的问题。
同时我们也要注意到一点，由于切片本质上是一个引用，所以我们是否能通过切片更改原始数据的内容，需要确定原始数据是定义在堆栈还是静态数据区，比如对于以下代码
```rust
let s = "hello"; // s 是 &str
let s_mut = &mut s; // ❌ 编译报错！无法从不可变数据创建可变引用
```
因为s是创建于静态数据区的字符串字面量，所以不可以定义一个可变引用修改变量，而对于创建于堆栈中的变量则是合法的
```rust
let s = String::from("hello"); 
let s_mut = &mut s;
```
## 结构体
与C++中的结构体类似，但是有一些不同需要注意
### 成员变量可变性不可控制
在C++中我们可以通过给结构体中的成员变量加const修饰的方式实现对成员变量的可变性控制如：
```C++
   struct Mystruct{
	   const int value;
	   string str;
	}
```
但在rust中我们只能控制结构体实例整体的可变性，而不能控制结构体中某个成员变量的可变性，比如
```rust
struct Mystruct{
	mut username: String, // 让结构体中的成员变量可变是非法的
	active: bool,
}

struct Mystruct{
	username: String,
	active: bool,
}
// 让结构体实例整体可变是合法的。
let mut instance = Mystruct{username: String::from("hello world!"), active: false};
```
### 结构体快捷赋值方式
在rust中，支持用如下方式用同一结构体实例快捷的对另一结构体变量进行赋值
```rust
struct Struct1{
	username: String,
	active: bool，
	...
}
let var1 = Struct1{username: String::from("var1"), active: false ...}
let var2 = Struct1{username: String::from("var2"), ..user1} //采用这种方式快捷赋值
```
但是用这种方式，要注意所有权的借用可能产生的问题, 比如下面
```rust
struct Struct1{
	username: String,
	active: bool，
	...
}
let var1 = Struct1{username: String::from("var1"), active: false ...}
let var2 = Struct1{active: true, ..user1} //将var1的username所有权夺走
println!("username: {0}，active: {1}",user1.username, user1.active) //会报错

```
因为在..user对username进行拷贝赋值时，对于像active这种创建于栈上的基本类型的成员变量来说会简单的拷贝，并创建一块内存将拷贝的内容贴上去，但是对于想username这种需要创建在堆上的成员变量来说，则只是会将所有权夺走（浅拷贝，想象一下只把指针拷贝过去，但是指针还是会指向原来的堆内存）这样原本var1中的username就会因为没有相应的堆内存所有权而失效

正确的方式是，在采用..user进行快捷赋值之前，先将会夺走所有权的部分手动clone给予内存，而不是简单的浅拷贝：
```rust
struct Struct1{
	username: String,
	active: bool，
	...
}
let var1 = Struct1{username: String::from("var1"), active: false ...}
let var2 = Struct1{username: var1.username.clone(), active: true, ..user1} //将var1的username深拷贝一下，而不仅仅是浅拷贝
```
### 不同结构体间的不可覆盖性
在C++中typedef一个结构体，更像是给结构体起一个别名，而并不是定义一个结构体类型，不同结构体间可以相互覆盖。比如：
```C++
typedef int Weight;
typedef int Height;
Weight h = 100;
Height w = h; //不同结构体间覆盖是合法的
```
但rust中与其说是别名，则更应该说是定义了一个类型，不同结构体间即使成员变量完全一样也不可相互覆盖
```rust
struct Mystruct1 {
    height: i32,
    weight: i32,
}
struct Mystruct2 {
    height: i32,
    weight: i32,
}
fn main(){
    let instance1 = Mystruct1{height: 1, weight:2};
    let instance2 = Mystruct2{height: 2, weight:3};
    instance1 = instance2     //报错，因为instance1 和instance2的结构体类型不一样
}
```
### 元组结构体
由于在rust中定义结构体类型是真的定义了一个类型，所以我们也可以将元组定义成结构体，即元组结构体，来实现对相同类型间不同含义类型的区分，比如:
```rust
// Rust
struct Height(i32);
struct Weight(i32);

let h = Height(180);
let w: Weight = h; // ❌ 编译报错！类型不匹配。
```
### 类单元结构体
rust中允许定义没有任何字段的结构体以实现别的语言中类似接口的功能，如:
```rust
struct AlwaysEqual;
```
![](assets/Pasted%20image%2020260124124353.png)