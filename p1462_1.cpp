#include<bits/stdc++.h>
using namespace std;
typedef long long llg;
const llg INF = 2147483647;

//用于从重定向0_in/a.in和0_out/a.out读取文件
#define yyj(a) freopen("0_in/"a".in","r",stdin),freopen("0_out/"a".out","w",stdout);

//读取一个整数
inline llg getint()
{
    llg w=0,q=0; char c=getchar();
    while((c<'0' || c>'9') && c!='-') c=getchar();
    if (c=='-')  q=1, c=getchar(); while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
    return q ? -w : w;
}
const int MAXN = 10010;
vector<pair<int,llg>> vec[MAXN];
priority_queue<pair<llg,int>> que;
llg f[MAXN];
bool vis[MAXN];
llg dis[MAXN];
int n,m; llg b;
bool check(llg mid){
    if(f[1]>mid) return 0;
    for(int i=1;i<=n;i++)
        vis[i]=false, dis[i]= INF;
    dis[1]=0; que.push(make_pair(0,1));
    while(!que.empty()){
        int cur = que.top().second; que.pop();
        if(vis[cur]) continue;
        else vis[cur]=true;
        for(int i=0;i<vec[cur].size();i++){
            int v=vec[cur][i].first;
            /*这里为什么不用考虑v是否已经访问过？？？*/
            if(f[v] > mid) continue;
            llg w = vec[cur][i].second;
            if(dis[cur]+w < dis[v]){
                dis[v] = dis[cur]+w;
                que.push(make_pair(dis[v], v));
                if(v==n){
                    if(dis[v] >= b) return 0;
                    else return 1; 
                }
            }            

        }
        
    }
    //cout << " #" << endl;
    return 0;
}
int main(){
    cin >> n >> m >> b;
    llg max_m = -INF;
    for(int i=1;i<=n;i++){cin >> f[i]; max_m = max(max_m,f[i]);}
    for(int i=1;i<=m;i++){
        int tmp1,tmp2; llg tmp3;
        cin >> tmp1 >> tmp2 >> tmp3;
        vec[tmp1].push_back(make_pair(tmp2,tmp3));
        vec[tmp2].push_back(make_pair(tmp1,tmp3));
    }
    llg l=0,r=max_m,ans = -1;
    while(l<=r){
        llg mid = l + (r-l)/2;
        if(check(mid)) ans=mid,r=r-1;
        else l=l+1;
    }
    if(ans==-1) puts("AFK");
    else cout << ans;
    return 0;
}