//https://leetcode.cn/problems/russian-doll-envelopes/description/
//lt354.俄罗斯套娃信封问题

/**
 * 解题思路：
 * 基本上算是LIS最长递增子序列的二维版本
 * 首先LIS只能适用于单维序列，那么就构造单维序列：
 * 先对宽度升序，再对同一宽度的长度降序
 * 
 * 详细题解:
 * https://labuladong.github.io/algo/di-er-zhan-a01c6/dong-tai-g-a223e/dong-tai-g-6ea57/
 * (扩展到二维)
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long llg;
const llg INF = 2147483647;

//#define yyj(a) freopen("0_in/"a".in","r",stdin),freopen("0_out/"a".out","w",stdout);
#define yyj(a) freopen(("0_in/" + string(a) + ".in").c_str(),"r",stdin),freopen(("0_out/" + string(a) + ".out").c_str(),"w",stdout)
inline llg getint()
{
    llg w=0,q=0; char c=getchar();
    while((c<'0' || c>'9') && c!='-') c=getchar();
    if (c=='-')  q=1, c=getchar(); while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
    return q ?  -w : w;
}
const int MAXN = 1000010;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& env) {
        sort(env.begin(),env.end(),[](vector<int>& a,vector<int>& b){
            return a[0] < b[0] || (a[0]==b[0] && a[1]>b[1] );
        });
        vector<int> p(env.size());
        int p_n=1; p[0]=env[0][1];
        for(int i=1;i<env.size();i++){
            int l=0,r=p_n;
            while(l<r){
                int mid=(l+r)>>1;
                if(p[mid]>=env[i][1]) r=mid;
                else l=mid+1;
            }
            if(l==p_n) p_n++;
            p[l]=env[i][1];
        }
        return p_n;
    }
};