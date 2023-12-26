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
    return q ? -w : w;
}

const int MAXN = 35010;
int dp[MAXN];
int pre[MAXN];
int nums[MAXN];
int s_nums[MAXN];
int n,pre_n,ans,max_i=1;

/**
 * 题解：
 * 见https://www.luogu.com.cn/problem/solution/P2501
 * 这道题还是比较难
*/
int main(){
    cin >> n;
    for(int i=1;i<=n;i++) {
        cin >>nums[i];
        s_nums[i]=nums[i]+s_nums[i-1];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(nums[i]-nums[j]>=i-j){
                if(dp[j]>dp[i]){
                    dp[i]=dp[j];
                    pre[i]=j;
                }
            }
        }
        dp[i]++;
        if(dp[i]>ans){
            ans = dp[i];
            max_i=i;
        }
    }
    ///*
    for(int i=0;i<=n;i++)
        cout << pre[i]<<" ";
    //*/
    //cout << ans;
    /**
     * 
     * 后面就枚举k了
    */
    return 0;
}
