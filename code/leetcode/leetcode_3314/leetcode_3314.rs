impl Solution {
    pub fn min_bitwise_array(nums: Vec<i32>) -> Vec<i32> {
        let mut return_val = Vec::new();
        for x in  nums{
            let mut res = -1;
            let mut d = 1;
            while((x&d) != 0){
                res = x - d;
                d <<= 1;
            }
            return_val.push(res);
        }
        return_val
    }
}