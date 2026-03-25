#include<vector>
#include<iostream>
using namespace std;

class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int left = 0, right = letters.size() - 1;
        // 预处理：如果目标比所有字符都大，按题目要求通常返回第一个
        if (target >= letters.back()) return letters[0];

        while(left <= right){
            int mid = left + (right - left) / 2;
            if(letters[mid] <= target){
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return letters[left];
    }
};

int main(void){
    Solution s;
    vector<char> input = {'c','f','j'}; // 使用 LeetCode 的标准测试用例
    char res = s.nextGreatestLetter(input, 'a');
    
    cout << "Result: " << res << endl; // 必须要有这一行
    return 0;
}