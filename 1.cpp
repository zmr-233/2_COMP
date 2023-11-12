#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int inf = 0x3f3f3f3f; 
const ll INF=0x3f3f3f3f3f3f3f3f;
int main(){
    int N;
    cin >> N;
    for(int i=0;i<N;i++){
        int  n;
        cin >> n;
        vector<ll> x;
        ll _sum = 0,min_val = inf,max_val = 0;
        bool judge = false;
        for(int i=0;i<n;i++){   
            ll num;
            cin >> num;
            x.push_back(num);
            _sum +=num;
            if(num < min_val) min_val = num;
            if(num > max_val) max_val = num;
        }
        int cnt = 0;
        for(auto i : x){
            if(i == min_val) cnt++;
            if(cnt >= 2){
                judge = true;
                break;
            }
        }
        if (judge == false) cout << _sum - min_val - max_val +1 << endl;
        else cout << _sum - min_val - max_val << endl;
    }
}

