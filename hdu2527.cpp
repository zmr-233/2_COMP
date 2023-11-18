#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;cin >> n;
    for(int ii=1;ii<=n;ii++){
        int safe; cin >> safe;
        string s; cin >> s;
        sort(s.begin(),s.end());
        priority_queue<int,vector<int>,greater<int>> pq;
        //统计个数:
        int n_ch = 1;
        for(int i=1;i<=s.size()/*这里使用包含空字符的方法*/;i++){
            if(s[i]!=s[i-1]){pq.push(n_ch);n_ch = 1;}
            else n_ch +=1;
        }
        int ans = 0;
        /*-------陷阱A:只有一种字符的情况*/
        if(pq.size() == 1) ans= s.size();
        while(pq.size() > 1 /*陷阱B:注意哈夫曼树的根结点是不算进去的*/){
            int a = pq.top(); pq.pop();
            int b = pq.top(); pq.pop();
            pq.push(a+b);
            ans += a+b;
        }
        pq.pop();
        if(ans <= safe) cout << "yes"<<endl;
        else cout << "no" << endl;
    }
    return 0;

}
