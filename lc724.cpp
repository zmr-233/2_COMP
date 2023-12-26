#include<bits/stdc++.h>
using namespace std;

/**
 * 题解：
 * 目的是数据只会有两个部分：
 * 在A组和不在A组-->成为0/1背包问题
 * 为了让sum(A)-sum(B)更加贴近，
 * A组背包的最大值应该尽量接近sum(nums)/2
*/
class Solution {
public:
    /**
     * @param nums: the given array
     * @return: the minimum difference between their sums 
     */
    int findMin(vector<int> &nums) {
        int n=nums.size(),sum_=accumulate(nums.begin(),nums.end(),0),C=sum_>>1;
        vector<vector<int>> dp(2,vector<int>(C+1,0));
        int cur=1,old=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=C;j++){
                if(nums[i-1] <= j)
                    dp[cur][j]=max(dp[old][j],dp[old][j-nums[i-1]]+nums[i-1]);
                else    
                    dp[cur][j]=dp[old][j]; 
            }
            swap(cur,old);
        } 
        return abs(sum_-2*dp[old][C]); //这里把dp[old][C]写成dp[old][n]
    }
};
/** 
 * 0/1背包问题必要分析：
 * n=? C=?
 * i| (w) c (m)
 * -|----------
 * 1| 
 * 2| 
 * 3| 
 * 4| 
 * 
 * a.若无明确w，则w为c
 * b.若有m，使用二进制拆分优化
*/