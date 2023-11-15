/**给你一个整数数组 nums 
 * 请你找出一个具有最大和的连续子数组（子数组最少包含一个元素）
 * 返回其最大和。*/
#include<bits/stdc++.h>
using namespace std;

//A-贪心算法
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max_sum = -1e4-10;
        int sum = 0,start = 0, end = 0, p = 0;
        for(int i=0;i < nums.size();i++){
            sum += nums[i];
            if(sum > max_sum){max_sum = sum; start = p;end = i;}
            if(sum<0){sum = 0; p = i+1;}
        }
        return max_sum;
    }
};
//B-动态规划
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max_sum = nums[0];
        vector<int> dp(nums);
        int start = 0,end = 0, p =0;
        for(int i=1;i<dp.size();i++){
            if(dp[i-1]+dp[i]>dp[i])
                dp[i] = dp[i-1] + dp[i];
            else
                p = i;
            if(dp[i]>max_sum){max_sum = dp[i];start = p;end = i;}
        }
        return max_sum;
        
    }
};

//C-分治方法:
class Solution{
public:
    struct Status{
        int lsum,rsum,isum,msum;
    };
    Status pushUp(Status l, Status r){
        int lsum = max(l.isum+r.lsum,l.lsum);
        int rsum = max(r.isum+l.rsum,r.rsum);
        int isum = l.isum + r.isum;
        //BUG:int msum = max(max(lsum,rsum),l.rsum+r.lsum);
        //```````````````````````^^^^^^^^^``````
        //这里已经抛弃了边界，只使用左右区间的最大值即可
        int msum = max(max(l.msum,r.msum),l.rsum + r.lsum);
        return (Status){lsum,rsum,isum,msum};
    }
    Status get(vector<int>& nums,int l,int r){
        if(l == r) return (Status){nums[l],nums[l],nums[l],nums[l]};
        int mid = (l + r)>>1;
        Status ls = get(nums,l,mid);
        Status rs = get(nums,mid+1,r);
        return pushUp(ls,rs);
    }
    int maxSubArray(vector<int>& nums){
        return get(nums,0,nums.size()-1).msum;
    }

};
