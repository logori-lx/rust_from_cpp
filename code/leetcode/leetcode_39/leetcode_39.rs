impl Solution {
    pub fn backtrace(candidates: &Vec<i32>, target: i32, start_idx: usize, mid:  &mut Vec<i32>, res:  & mut Vec<Vec<i32>>){
        if target == 0{
            res.push(mid.to_vec());
            return;
        }

        for i in start_idx..candidates.len(){
            if target >= candidates[i]{
                mid.push(candidates[i]);
                Self::backtrace(candidates, target - candidates[i], i, mid, res);
                mid.pop();
            }else{
                return;
            }
        }
    }
    pub fn combination_sum(mut candidates: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
        candidates.sort();
        let mut res =  Vec::new();
        Self::backtrace(&candidates, target, 0, &mut vec![], &mut res);
        return res;
    }
}