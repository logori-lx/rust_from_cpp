impl Solution {
    pub fn climb_stairs(n: i32) -> i32 {
        if n <= 2{
            return n;
        }
        let mut dp1 = 1;
        let mut dp2 = 2;
        let mut dp3 = dp1 + dp2;
        for i in 3..n {
            dp1 = dp2;
            dp2 = dp3;
            dp3 = dp1 + dp2;
        }
        return dp3;
    }
}