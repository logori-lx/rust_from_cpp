#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int min_val = INT_MAX;
        for(int i = 0; i < arr.size() - 1; i++){
            int tmp = abs(arr[i] - arr[i + 1]);
            if(min_val > tmp){
                min_val = tmp;
            }
        }
        vector<vector<int>> res;
        for(int i = 0; i < arr.size() - 1; i++){
            int tmp = abs(arr[i] - arr[i + 1]);
            if(min_val == tmp){
                res.push_back(vector<int>(arr[i], arr[i+1]));
            }
        }
        return res;
    }
};


int main(){
    Solution s;
    vector<int> input = {3,8,-10,23,19,-4,-14,27};
    s.minimumAbsDifference(input);

}