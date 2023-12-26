//https://leetcode.cn/problems/longest-increasing-subsequence/description/
//300. 最长递增子序列

//具体讲解：见
//https://labuladong.github.io/algo/di-er-zhan-a01c6/dong-tai-g-a223e/dong-tai-g-6ea57/
#include<bits/stdc++.h>
using namespace std;
//常规方法：DP问题
//转移方程:dp[i]=max(dp[j])+1
//需要遍历所有的比nums[i]小的nums[j],然后挑出一个最大的+1
int lengthOfLIS(vector<int>& nums) {
    vector<int> dp(nums.size());
    int max_m=1;
    for(int i=0;i<nums.size();i++){
        int max_n = 0;
        for(int j=0;j<i;j++){
            if(nums[j]<nums[i])
                max_n=max(max_n,dp[j]); 
        }
        dp[i]=max_n+1;
        max_m=max(max_m,dp[i]);
    }
    return max_m;
}
//特殊方法：二分法
//扑克问题
//具体过程见https://labuladong.github.io/algo/di-er-zhan-a01c6/dong-tai-g-a223e/dong-tai-g-6ea57/
int lengthOfLIS(vector<int>& nums) {
        vector<int> p(nums.size());
        int p_n=1; p[0]=nums[0];
        for(int i=1;i<nums.size();i++){
            int l=0,r=p_n;
            while(l<r){
                int mid=(l+r)>>1;
                if(p[mid]>=nums[i]) r=mid;
                else l=mid+1;
            }
            if(l==p_n) p_n++;
            p[l]=nums[i];
        }
    return p_n;
}
#define yyj(a) freopen(("0_in/" + string(a) + ".in").c_str(),"r",stdin),freopen(("0_out/" + string(a) + ".out").c_str(),"w",stdout)

int main() {
    yyj("lt300");
    std::vector<int> nums;
    std::string line, token;

    std::getline(std::cin, line);
    std::istringstream ss(line);

    while (std::getline(ss, token, ',')) {
        nums.push_back(std::stoi(token));
    }

    cout << lengthOfLIS(nums);

    return 0;
}