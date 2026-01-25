#include <iostream>

int main() {
    long standard = __cplusplus;

    std::cout << "当前标准宏的值: " << standard << std::endl;

    if (standard == 202302L) std::cout << "当前版本: C++23" << std::endl;
    else if (standard == 202002L) std::cout << "当前版本: C++20" << std::endl;
    else if (standard == 201703L) std::cout << "当前版本: C++17" << std::endl;
    else if (standard == 201402L) std::cout << "当前版本: C++14" << std::endl;
    else if (standard == 201103L) std::cout << "当前版本: C++11" << std::endl;
    else if (standard == 199711L) std::cout << "当前版本: C++98" << std::endl;
    else std::cout << "可能是 C++98 或者未知的预览版本" << std::endl;
    return 0;
}