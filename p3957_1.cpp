#include<bits/stdc++.h>
using namespace std;
const int N = 500005;
int s[N], l[N];
int main(){
    int n,d,k;cin >> n >> d >> k;
    int max_dl = d;
    s[0] = l[0] = 0;
    int top_k = 0,max_d_l = 0;
    for(int i=1;i<=n;i++){
        cin >> l[i] >> s[i];
        top_k += s[i]<0?0:s[i];
        if(l[i]-l[i-1] > max_d_l) max_d_l = l[i]-l[i-1];
    }
    if(top_k < k) {cout << -1; return 0;}
    int nd = 0; //现在的金币
    while(nd <= 2000 - d){
        int max_k = -10e5-10,now_k = 0,min_d = 0;
        for(int i=0/*这里从原点开始*/;i < n /*这里只到倒数第一个*/;i++){ 
            int j = i+1; deque<int> q;
            while(j<=n && l[j]-l[i] >= d-nd && l[j]-l[i] <= d+nd){
                while(!q.empty() && s[j] > s[q.back()] && s[q.back()] < 0) q.pop_back();
                q.push_back(j);
                j += 1;
            }
            if(q.empty()){min_d = abs(l[i+1] - l[i]-d);break;}
            else{
                now_k += s[q.front()]; i = q.front();
                if(now_k > max_k ){max_k = now_k;}
            }
        }
        if(max_k >= k){cout << nd; return 0;}
        if(min_d <= max_d_l) nd = min_d;
        else nd +=1;
    }
    return 0;
}