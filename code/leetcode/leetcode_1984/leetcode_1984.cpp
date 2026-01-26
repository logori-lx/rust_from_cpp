#include<vector>
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        if(k == 1){
            return 0;
        }
        sort(nums.begin(), nums.end());
        int min = INT_MAX;
        for(int i = 0; i <= nums.size() - k; i++){
            if(min > nums[i + k - 1] - nums[i]){
                min = nums[i + k - 1] - nums[i];
            }
        }
        return min;
    }
};