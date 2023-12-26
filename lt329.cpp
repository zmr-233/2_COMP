#include<bits/stdc++.h>
using namespace std;

//A-记忆化DFS(但是没有优化，时长较长)
class Solution {
public:
    vector<vector<int>> dp;
    vector<vector<int>> mat;
    int s_i,s_j;
    int solve(int i,int j){
        if(i<=0 || i>=s_i+1 || j<=0 || j>=s_j+1) return 0;
        if(dp[i][j]!=0) return dp[i][j];
        //ERROR:
        //dp[i][j]=max({dp[i][j],solve(i+1,j),solve(i-1,j),solve(i,j+1),solve(i,j-1)})+1;
        //ERROR:只有当路径是递增的时候才进行递归调用
        auto f=[=](int i,int j){
            return i>=0 && i<=s_i-1 && j>=0 && j<=s_j-1;
        };
        if(f(i-1-1,j-1) && mat[i-1-1][j-1]<mat[i-1][j-1])
            dp[i][j]=max(dp[i][j],solve(i-1,j));
        if(f(i-1+1,j-1) && mat[i-1+1][j-1]<mat[i-1][j-1])
            dp[i][j]=max(dp[i][j],solve(i+1,j));
        if(f(i-1,j-1-1) && mat[i-1][j-1-1]<mat[i-1][j-1])
            dp[i][j]=max(dp[i][j],solve(i,j-1));
        if(f(i-1,j-1+1) && mat[i-1][j-1+1]<mat[i-1][j-1])
            dp[i][j]=max(dp[i][j],solve(i,j+1));
        return ++dp[i][j];
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        mat = move(matrix);
        s_i=mat.size(),s_j=mat[0].size(); //size
        dp = vector<vector<int>>(s_i+2,vector<int>(s_j+2,0));
        int max_dp = -1;
        for(int i=1;i<=s_i;i++)
            for(int j=1;j<=s_j;j++)
                max_dp=max(max_dp,solve(i,j));
        return max_dp;
    }
}; 