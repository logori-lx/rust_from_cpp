struct Solution;
impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        for (i, &num1) in nums.iter().enumerate(){
            for(j, &num2) in nums.iter().enumerate().skip(i+1){
                if num1 + num2 == target{
                    return vec![i as i32, j as i32]
                }
            }
        }
        return vec![];
    }
}


fn main() {
    let nums = vec![3,2,4];
    let target = 6;
    let result = Solution::two_sum(nums, target);
    println!("result is {:?}",result)
}
