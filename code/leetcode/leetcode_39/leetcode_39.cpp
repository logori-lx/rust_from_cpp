class Solution {
public:
    void backtrace(vector<int> & candidates, int target, int start_index, vector<int> &mid, vector<vector<int>> &res){
        if(target == 0){
            res.push_back(mid);
            return;
        }
        for(int i = start_index; i < candidates.size(); i++){
            if(target >=  candidates[i]){
                mid.push_back(candidates[i]);
                backtrace(candidates, target - candidates[i], i, mid, res);
                mid.pop_back();
            }else{
                return;
            }
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res = {};
        vector<int> mid = {};
        backtrace(candidates, target, 0, mid, res);
        return res;
    }
};