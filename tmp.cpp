#include<stdio.h>
#include<string.h>
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

