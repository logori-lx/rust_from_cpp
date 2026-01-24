// #include<stdio.h>
// #include<string.h>
// struct MyResult {
//     union {
//         int value;
//         char* error_msg;
//     } data;
// };

// int main(){
//     MyResult my_result;
//     my_result.data.error_msg = "hello world";
//     // 存在安全隐患，可以不进行类型判断就直接输出
//     printf("%d", my_result.data.value);
// }

#include <iostream>

int main() {
    const int a = 10;  // a 是真正的常量
    int* p = (int*)&a; // 强行获取地址并强转
    *p = 20;           // 试图修改

    std::cout << "a = " << a << std::endl;
    std::cout << "*p = " << *p << std::endl;
    std::cout << "&a = " << &a << std::endl;
    std::cout << "p  = " << p << std::endl;
    
    return 0;
}
