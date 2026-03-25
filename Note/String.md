在rust中存在有两种类型的字符串，&str以及String
## &str
为什么说是&str和String而不是str和String，是因为我们不能声明一个变量为str类型，这是因为rust中并**不存在**C++中的以'\0'为结束字符，当读到'\0'时也不能确定这个字符串是否结束，所以**str类型只能以&str这种切片（胖指针）的形式存在**，因为切片中还存储了所指向内存的大小，可以让程序知道读到哪里为终点，而单纯的str只是一个指向连绵不断内存的指针而已。

&str在C++中的对照是string_view，让我们复习一下C++中string_view的用法
在C++中存在一个尴尬的问题，即对于const char * 和const string & 这两种用法有
- const char \*虽然轻量但是不记录字符串长度，缺少string的一些成员方法和高级用法
- const string& 作为函数参数接收字面量比如"hello"时，需要在堆上产生一次临时分配，将字面量包装成string类型的对象。
而string_view很好地解决了这个疼点，其本质上是一个**既指向内存又存储了内存有效长度的胖指针**，其不拥有内存，而只是观察一段已经存在了的字符串序列
```cpp
#include <string_view>
#include <string>
#include <iostream>

void process_string(std::string_view sv) {
    // 1. 获取长度是 O(1) 的，不需要找 \0
    std::cout << "Length: " << sv.length() << std::endl;
    
    // 2. 像 string 一样访问
    if (!sv.empty()) {
        std::cout << "First char: " << sv[0] << std::endl;
    }
}

int main() {
    std::string s = "Hello World";
    
    process_string(s);             // 支持 std::string
    process_string("Literal");      // 支持字面量（无堆分配！）
    
    char arr[] = {'H', 'i'};
    process_string({arr, 2});       // 支持字符数组+长度
}
```
而rust 中的&str与string_view的用法基本一致
