#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 2147483647;
const int N = 100010;
ll a[N],s[N],n;
int main(){
    cin >> n;
    s[0] = 0;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        s[i] = s[i-1] + a[i];
    }
    deque<ll> q;
    ll start = 0,end = 0,p=0;
    ll max_k = - INF;
    for(int i=1;i<=n ;i++){
        while(!q.empty() && a[i] < a[q.back()]) q.pop_back();
        q.push_back(i);
        while(q.front() <= p) q.pop_front();
        ll k = a[q.front()] * (s[i]-s[p]);
        if( k < a[i]*a[i]) {p = i-1; k = a[i] * a[i];}
        if(k > max_k){max_k = k;start = p;end = i;}
    }
    cout << max_k;
    return 0;
}
//目前尚未解决，只有50分