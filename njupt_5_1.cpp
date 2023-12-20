//特别简单的WSL，基本没有价值
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

priority_queue<llg, vector<llg>, greater<llg>> pq;
llg WSL; int N;
void generateWSL() {
  llg t1, t2; WSL = 0;
  while (pq.size() > 1) {
    t1 = pq.top(); pq.pop();
    t2 = pq.top(); pq.pop();
    WSL += t1 + t2;
    pq.push(t1 + t2);
  }
}
int main()
{
  cin >> N;
  if(N==1){
    llg a;cin>>a;
    cout << a;
    return 0;
  }
  for (int i = 0; i < N; i++) {
    llg a;cin>>a;
    pq.push(a);
  }
  generateWSL();
  cout << WSL;
  return 0;
}