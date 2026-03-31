#include<iostream>
#include<vector>
#include<mutex>
using namespace std;

void test_function(int a, int b){
    return;
}

class Singleton{
    static Singleton& getInstance(){
        //C++11规定，局部静态变量的初始化在多线程下是原子性的
        static Singleton instance;
        return instance;
    }
    //禁用拷贝构造和赋值运算符，防止单例被拷贝
    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton) = delete;

    private:
        Singleton(){};
};
int fact(int n){
    int max_n = 10000; // 假设阶乘最多计算到n
    int mod = 1e9 + 7;
    static vector<long long> storage(max_n + 1, 1);
    static std::once_flag flag;
    call_once(flag, [&](){
        for(int i = 2; i < max_n + 1; i++){
            storage[i] = (static_cast<long long>(i) * static_cast<long long>(storage[i - 1])) % mod;
        }
    });
    return storage[n];
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
