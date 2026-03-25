#include<vector>
#include<iostream>
using namespace std;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int len = nums.size();
        int left = -1, right = len;
        int ret_left, ret_right;
        while(left + 1 < right){
            int mid = left + (right - left) / 2;
            if(target > nums[mid]){
                left = mid;
            }else{
                right = mid;
            }
        }

        ret_left = left + 1;
        left = -1;
        right = len;
        while(left + 1 < right){
            int mid = left + (right - left) / 2;
            if(target < nums[mid]){
                right = mid;
            }else{
                left = mid;
            }
        }
        ret_right = right - 1;
        if(right == 0 || left == len - 1 || ret_right < ret_left){
            return vector<int> {-1,-1};
        }
        return vector<int> {ret_left, ret_right};
        
    }
};

int main(void){
    Solution s;
    vector<int> input = {1}; // 使用 LeetCode 的标准测试用例
    vector<int> res = s.searchRange(input, 1);
    
    cout << "Result: " << res << endl; // 必须要有这一行
    return 0;
}