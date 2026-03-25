# 所有权
在rust，中所谓的所有权，全称应该为分配在堆内存上的变量的所有权，其有3条规则：
1. 每个值都有一个变量，称为其 **owner**
2. 任意时刻，一个段被分配的内存只能有一个 **owner**。
3. 当 owner 离开作用域，这个值将被 **dropped**。

这三条规则看着可能比较难记，但如果将其看成**对于rust中所有分配在堆内存上的变量，rust都采用类似于C++中std::move的方式来处理函数传参以及赋值等时候的内存分配，且同一作用域下一段被分配的内存只能为一个变量所有**，就会好理解很多。
对于赋值操作，下面的rust代码和C++代码可以进行对比
```rust
fn main(){
    let book1: String = String::from("Yello book");
    let book2: String = book1;
    println!("{}",book2)
    // println!("{}",book1) //会编译报错，因为book1的所有权已经转移给book2了
}
```
相当于C++中的
```C++
int main() {
    std::string book1 = "Yello book";
	std::string book2 = std::move(book1);
	std::cout << book2 << std::endl;
	std::cout << book1 << std::endl; //不会报错，因为即使内存被转给了book2，book1仍能被访
                                     //问，只是指向的内存的内容未知，访问这块内存为未定义
                                     //的危险行为
}
```
之所以rust代码中打印book1变量会报错，从根本上是因为book1对于指向"Yello book"这块内存的所有权已经std::move转移给了book2，且book1与book2都处于同一块作用域(指fn main(){}这个大括号括住的作用域)，所以book1就会失效，再想访问book1所指向的内存，就会报错，而因为在C++中即使变量被std::move了也可以继续访存，所以并不会报错。

同样的对于函数传参，也有相似的规律
```rust
fn take_book(input : String){
    println!("{}", input)
}
fn main(){
    let book1: String = "Yello book".to_string();
    take_book(book1);
    // println!("{}",book1) //会报错，因为book1的所有权给了take_book的函数参数变量input
}
```
而其等价的C++实现如下:
```C++
void take_book(const std::string input){
    std::cout << input << std::endl;
}

int main() {
    std::string book1 = "Yello book";
    take_book(std::move(book1));
    std::cout << book1 << std::endl; //不会报错，但因访问未知内存为未定义行为
}
```
而有些人可能会产生一个问题，**book1和take_book的函数参数作用域也不同，并不满足之前提到的rust对于所有权规则中定义的第二条即*2. 任意时刻，一个段被分配的内存只能有一个 owner。* 但为什么在执行完take_book函数后还是不能访问book1的内存呢？**

这需要深入take_book传入book1后的整个流程，当调用*take_book(book1);* 时, rust会
1. **建立新的栈帧**: 为take_book函数开辟一块新空间
2. **位拷贝**:把book1在栈上的三个字段(ptr, len, cap)复制到take_book的参数变量input的位置
3. **所有权变更**:编译器认定现在这块内存归input关了，给book1打上Moved的标签
4. **函数执行，直至执行结束**
5. **Drop input**: 编译器插入代码，释放input指向的堆内存
6. **弹出栈帧**: take_book的栈空间被回收
7. **回到main继续执行**: book1还是有Moved的标签
8. **执行book1的println!打印**:编译器发现book1有Moved的标签，代表其原有内存已经被别的变量拿走了，还没分配新的给他，所以报错。
这也是为什么虽然book1和take_book函数的传入参数input不在同一个作用域但仍会报错的原因，因为book1的内存所有权已经转移给input了。

# 引用
之前也提到过，rust中的引用与其说是“引用”，其概念上更像是C/C++中的指针，而想要理解rust中有关引用的代码也很容易。我们都知道，在C++中我们对一个变量是通过&(取址运算符)实现对一个变量的内存取址的，同时在C++中我们想声明一个变量是指针，我们需要使用\*， 而在rust中者两个功能我们都可以通过&运算符实现，但对于rust中的解引用操作，还是会跟C++一样用
\* 符号实现。比如:
rust中声明一个函数传入变量的是引用，代码像这样
```rust
fn backtrace(candidates: &i32){ //用&声明这是一个指针
	let val = *candidates + 1;  // 用*访问内存取出对应的值
	...
}
let candidates = 0;
backtrace(&candidates);  //用&声明传入的变量是一个引用
```
相当于
```c++
void backtrace(const int32_t *candidates){ 
	int32_t val = *candidates + 1;
	...
}
const int32_t candidates = 0;
backtrace(&candidates); 
```
不过将rust中的引用用法也有两点跟C++中的指针不一样的地方， 比如对于rust中的引用来说，其值不能为空，而C++中的指针允许为空(nullptr)， 另外， rust中的引用用的是 **\.** 来访问引用的成员变量或方法，而C++中的指针则是用的是 **\-\>** 来访问一个指针的成员或方法，如下面的代码
```rust
    struct Mystruct{
        username: String,
        active: bool,
    }
    let mut mystruct : Mystruct = Mystruct{username: String::from("Bob"), active: true};
    let ptr: &mut Mystruct = &mut mystruct;
    ptr.active = false;
```
对应C++中的
```c++
	typedef struct{
        std::string username;
        bool active;
    } Mystruct;
    Mystruct mystruct = Mystruct{
        username: "Bob",
        active: true,
    };
    Mystruct *ptr = &mystruct;
    ptr->active =false;
```
然后我们就可以有下面这张总结对比表

| 操作场景         | C++指针(比如int \*) | C++引用(比如int &) | rust 引用(比如&i32) | 结论            |
| ------------ | --------------- | -------------- | --------------- | ------------- |
| 解引用（访问内存的内容) | \*ptr           | ptr(编译器隐藏)     | &ptr            | rust 更像C++指针  |
| 变量声明         | \*ptr           | &ptr           | &ptr            | rust更像C++中的引用 |
| 取址(获取内存地址)   | &val            | val(编译器隐藏)     | &val            | rust 更像C++指针  |
| 判空           | 可以nullptr       | 不可以为空          | 不可以为空           | rust更像C++中的引用 |
| 访问成员         | val->member     | val.member     | val.member      | rust更像C++中的引用 |


其实实话说rust book中下面的这张图是有点误导人的，因为这张图我一度认为rust中的引用应该算是C/C++中的二级指针，但实际上并不是这个意思。
![](assets/Pasted%20image%2020260120131104.png)

这张图之所以看着这么像二级指针，是因为s这个引用指向的s1为string, 其在rust中的实现是以上图中的一个包含指向堆内存的指针和内存长度的结构体来实现的，所以这也是为啥这张图中s看着这么像二级指针。
## 可变与不可变引用
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

## 悬垂引用
rust中也不可能存在悬垂引用，rust中使用了生命周期这一特性去确保这一特性，一个引用的生命周期一定小于等于其指向变量的生命周期，如果其指向变量的生命结束时，则其引用生命必然结束，后面再使用引用必然会报错。
# 切片

rust中的切片在概念上实际上类似于**C/C++中的指针**，只是这个指针拥有长度（也即**胖指针**， 前前8个字节存储内存地址，后8个字节存储指针所指向内存占多少个字节数），规定了指针的起始。在字符串处理上，相比C用'\0'去标明一个字符串的结尾，一方面避免了'\0'被错误覆盖时导致的访问越界内存问题，另一方面省下了计算字符串长度（strlen）的开销。
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