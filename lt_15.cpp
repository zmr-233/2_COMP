#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums){
        vector<vector<int>> ans;
        sort(nums.begin(),nums.end());
        int n = nums.size();
        for(int i=0;i<n;i++){
            if(i>0 && nums[i]==nums[i-1] )continue;
            //优化1:跳过大循环重复
            int l=i+1,r=n-1;
            while(l<r){
                int sum = nums[i]+nums[l] + nums[r];
                if(sum>0) r--;
                else if(sum<0) l++;
                else if(sum==0){
                    ans.push_back({nums[i], nums[l], nums[r]});
                    //优化2:跳过左右指针重复元素
                    while(l<r && nums[l]==nums[l+1]) l++;
                    while(l<r && nums[r]==nums[r-1]) r--;
                    l++; //小小陷阱，易错-->是否有更多的选择？
                    r--; //优化3：其实还可以再减一
                }
            }
        }
        return ans;
    }
};