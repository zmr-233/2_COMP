#ifdef USEERROR1
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


const int MAXN = 100010;
llg nums[MAXN];
int n;
llg dp[MAXN];
int main(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> nums[i];
    llg max_m=1;
    for(int i=1;i<=n;i++){
        llg max_n = 0;
        for(int j=1;j<i;j++){
            if(nums[i] & nums[j]!=0)
                max_n=max(max_n,dp[j]); 
        }
        dp[i]=max_n+1;
        max_m=max(max_m,dp[i]);
    }
    cout << max_m;
    return 0;
}
#endif
#ifndef USEERROR1
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canBeAdded(const vector<int>& sequence, int number) {
    for (int num : sequence) {
        if ((num & number) == 0) return false;
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end(), greater<int>());

    vector<int> sequence;
    for (int i = 0; i < n; ++i) {
        if (canBeAdded(sequence, a[i])) {
            sequence.push_back(a[i]);
        }
    }

    cout << sequence.size() << endl;
    return 0;
}











#endif