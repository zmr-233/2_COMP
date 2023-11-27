#include<bits/stdc++.h>
using namespace std;
const int N = 10010;
long long f[N];//点的费用 
vector< pair< int , long long> >vec[N];//这里使用向量数组，相当于邻接表
priority_queue< pair< long long, int > >que; //这里实际上存的dist和节点
int vis[N];
long long dis[N];
long long b, v;
int n, m, x, y;
int check(int x)
{
	if(f[1] > x) return 0;//如果第一个点就不能走,直接返回不行 
	for(int i = 1; i <= n; ++ i){
		dis[i] = 1e18;//必备的初始化,没有会致错 
		vis[i] = 0;
	}
	dis[1] = 0;
	que.push(make_pair(0, 1));//修改的dijk 
	while(!que.empty()){
		int u = que.top().second;
		que.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = 0; i < vec[u].size(); ++ i){
			int v = vec[u][i].first;
			if(f[v] > x) continue;//如果新拓展的点不符合要求,继续寻找 
			long long w = vec[u][i].second;
			if(dis[u] + w < dis[v]){
				dis[v] = dis[u] + w;
				que.push(make_pair(-dis[v], v));
                if(v == n){//如果已经到达,判断是否生命值有剩余 
                    if(dis[n] >= b) return 0;
                    else return 1;
                }	
            }
        }
    }
	return 0;//如果没有到达,直接返回不行 
}
int main()
{
	long long mxx = -1;
	scanf("%d%d%lld", &n, &m, &b);
	for(int i = 1; i <= n; ++ i){
		scanf("%lld", &f[i]);
		mxx = max(mxx, f[i]);//寻找上边界 
	}
	for(int i = 1; i <= m; ++ i){
		scanf("%d%d%lld", &x, &y, &v);
		vec[x].push_back(make_pair(y, v));
		vec[y].push_back(make_pair(x, v));
	}
	long long ans = -1, l = 1, r = mxx;
	while(l <= r){
		long long mid = (l + r) / 2;
		if(check(mid)) ans = mid, r = mid - 1;//更形ans，要使r=mid-1的条件，必须是l<=r
		else	l = mid + 1;
	}
	if(ans == -1) puts("AFK");//如果每次都没有扩展成功说明不能到达 
	else printf("%lld\n", ans);
	return 0;
}