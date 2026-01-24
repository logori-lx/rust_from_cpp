#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int get_bit_width(int n){
    if(n == 0) return 0;
    int count = 0;
    while(n != 0){
        n >>= 1;
        count++;
    }
    return count;
}

class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> res{};
        bool flag = false;
        for(auto &num : nums){
            if(num % 2 == 1){
                for(int i = num / 2; i <= num - 1; i++){
                    if((i | (i + 1)) == num){
                        res.push_back(i);
                        flag = true;
                        break;
                    }
                }
                
            }
            if(!flag){
                res.push_back(-1);
            }else{
                flag = false;
            }
        }
        return res;
    }
};



int main(){
    Solution solution;
    vector<int> input = {2,3,5,7};
    auto res = solution.minBitwiseArray(input);
    for(auto iter : res){
        cout << iter << " ";
    } 
    cout << endl;
}
