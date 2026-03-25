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

#include<iostream>
#include<vector>
#include<stack>
#include<bitset>
#include<set>
#include<string_view>
using namespace std;
// int partition(vector<int> &arr, int low, int high){
//     int pivot = arr[high];
//     int i = low - 1;
//     for(int j = low; j < high; j++){
//         if(arr[j] <= pivot){
//             i++;
//             swap(arr[i], arr[j]);
//         }
//     }
//     swap(arr[i + 1], arr[high]);
//     return i + 1;
// }

// void quick_sort(vector<int> &arr){
//     if(arr.empty()) return;
//     stack<pair<int, int>> st;
//     st.emplace(0, arr.size() - 1);
//     while(!st.empty()){
//         auto [low, high] = st.top();
//         st.pop();
//         int mid = partition(arr, low, high);
//         if(mid - 1 > low){
//             st.emplace(low, mid - 1);
//         }
//         if(mid + 1 < high){
//             st.emplace(mid + 1, high);
//         }
//     }
// }
// int main(void){
//     vector<int> res = {0,0,0};
//     quick_sort(res);
//     for(auto &iter : res){
//         cout << iter << " ";
//     }
//     cout << endl;
// }

// char findKthBit(int n, int k) {
//     int len = (1 << n) - 1;
//     if(k == len / 2) return 1;
//     vector<bool> check(1, false);
//     for(int i = 1; i < n; i++){
//         int n = 2 * check.size() + 1;
//         vector<bool> tmp(n, false);
//         tmp[n / 2] = true;
//         for(int j = 0; j < n / 2; j++){
//             tmp[j] = check[j];
//             tmp[n - j - 1] = !check[j];
//         }
//         check = tmp;
//     }
//     return check[k] ? '1' : '0'; 
// }
// int main(void){
//     findKthBit(3, 1);
// }

// int gcd(int a, int b){
//     while(b != 0){
//         int tmp = b;
//         b = a % b;
//         a = tmp;
//     }
//     return a;
// }

// double pow(double a, int n){
//     if(n == 0) return 1;
//     if(n < 0) {
//         n = -1 * n;
//         a = 1 / a;
//     }
//     double res = pow(a, n / 2);
//     res *= res;
//     return n % 2 ? res * a : res;
// }

// int main(){
//     // bitset<32> a(0), b(0);
//     // a.set(1);
//     // b.set();
//     // std::cout << a << std::endl;
//     // std::cout << b << std::endl;
//     vector<int> a = {3,3,4,1,5};
//     set<int> b(a.begin(), a.end());
//     for(auto elem : b){
//         std::cout << elem << " ";
//     }
//     std::cout << std::endl;

void funct(string_view input){
    std::cout << input << std::endl;
}
int main(){
    string test = "hello world";
    funct(test);
}