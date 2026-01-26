impl Solution {
    pub fn minimum_difference(mut nums: Vec<i32>, k: i32) -> i32 {
        if k == 1 {
            return 0;
        }
        nums.sort_unstable();
        let mut min_diff = i32::MAX;
        let window_len: usize = k as usize;
        for window in nums.windows(window_len){
            let diff = window[window_len - 1] - window[0];
            if diff < min_diff{
                min_diff = diff;
            }
        }
        min_diff
    }
}