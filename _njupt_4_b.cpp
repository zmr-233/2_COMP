#include<bits/stdc++.h>
using namespace std;
typedef long long llg;
const int MAXN = 100005; 
bool is_prime[MAXN];
int prime[MAXN], cnt[MAXN];

void init(){
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < MAXN; ++i){
        if(is_prime[i]){
            for(llg j = (llg)i * i; j < MAXN; j += i)
                is_prime[j] = false;
        }
    }
    for(int i = 3; i < MAXN; i += 2){
        if(is_prime[i] && is_prime[(i+1)/2])
            cnt[i] = cnt[i-2] + 1;
        else
            cnt[i] = cnt[i-2];
    }
}

int solve(){
    int Q; cin >> Q;
    while(Q--){
        int l, r; cin >> l >> r;
        if(r % 2 == 0) r--;
        if(l % 2 == 0) l++;
        cout << cnt[r] - cnt[l-2] << endl;
    }
    return 0;
}

int main(){
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); cout.tie(nullptr);
    init();
    solve();
    return 0;
}
