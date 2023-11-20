//P3045--优惠劵买奶牛
#include<bits/stdc++.h>
using namespace std;

typedef long long llg;
const llg INF = 2147483647;

#define yyj(a) freopen("0_in/"a".in","r",stdin),freopen("0_out/"a".out","w",stdout);

inline llg getint()
{
    llg w=0,q=0; char c=getchar();
    while((c<'0' || c>'9') && c!='-') c=getchar();
    if (c=='-')  q=1, c=getchar(); while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
    return q ? -w : w;
}


struct cow{
    int index;
    llg cost;
    cow(){}
    cow(llg i_,llg c_):index(i_),cost(c_){}
};
struct cowCMP{
    bool operator()(cow& c1,cow& c2){
        return c1.cost > c2.cost;
    }
};
priority_queue<cow,vector<cow>,cowCMP> p;
priority_queue<cow,vector<cow>,cowCMP> c;
llg n,k,m;

bool hasBUY[50010];
/**如下用的方法是完全贪心的策略，但是却会出现一种问题:
 * 输入:
 * 2 1 5
 * 2 1
 * 1000 3
 * 
 * 理论输出:2
 * 实际输出:1
 * 
 * 由于贪心，把优惠劵给了2的奶牛，导致无法购买1000块的奶牛
*/
int main(){
    cin >> n >> k >> m;
    for(int i = 1;i<=n;i++) {
        llg tmp1,tmp2; cin >> tmp1 >> tmp2;
        p.push(cow(i,tmp1));c.push(cow(i,tmp2));
    }
    llg n_cow = 0;
    while(m >= 0){
        while(!c.empty() && hasBUY[c.top().index]) c.pop();
        while(!p.empty() && hasBUY[p.top().index]) p.pop();
        if(c.empty() || p.empty()) break;
        cow min_cow; bool isC = false;
        if(k>=1){
            if(c.top().cost < p.top().cost) {min_cow = c.top();isC = true;}
            else min_cow = p.top();
        }else
            min_cow = p.top();
        if(min_cow.cost > m) break;
        else{
            m -= min_cow.cost; hasBUY[min_cow.index] = true;
            if(isC){
                c.pop(); k-=1;
            }else p.pop();
            n_cow +=1;
        }
    }
    cout << n_cow;
    return 0;
}
