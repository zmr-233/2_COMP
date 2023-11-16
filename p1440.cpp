#include<bits/stdc++.h>
using namespace std;
const int INF = 0x7fffffff;

//给定限制长度k，找出一段不超过k的连续子数列，使其子序列和最大
class Solution {
public:
    int maxSubArray(vector<int>& nums,int k) {
        //int k = nums.size();
        deque<int> q;
        for(int i=1;i < nums.size();i++)
            nums[i] = nums[i] + nums[i-1];
        int max_sum = -1e4-10, start = 0, end = 0;
        for(int i=0;i < nums.size();i++){
            while(!q.empty() && q.front() < i-k) q.pop_front();
            if(q.empty()) max_sum = max(max_sum,nums[i]);
            else max_sum = max(max_sum,nums[i] - nums[q.front()]);
            while(!q.empty() && nums[q.back()] >= nums[i]) q.pop_back();
            q.push_back(i);
        }
        return max_sum;
    }
};
/*一个含有n项的数列，求出每一项前的m个数到它这个区间内的最小值。
若前面的数不足m 项则从第1 个数开始，若前面没有数则输出 0
*/

/**
 * 第一行两个整数，分别表示n,m
 * 第二行,n 个正整数，为所给定的数列 a_i
 * n 行，每行一个整数，第 i 个数为序列中a_i之前 m 个数的最小值
*/
const int N = 2000005;
int a[N];
int main(){
    int n,m; cin >> n >> m;
    deque<int> dq;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++){
        cout << (dq.empty() ? 0 : a[dq.front()] ) << endl;
        while(!dq.empty() && dq.front() <= i-m) dq.pop_front();
        while(!dq.empty() && a[dq.back()] > a[i]) dq.pop_back();
        dq.push_back(i);
    }

}
