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

#define DEB2_
#define DEB3_
const int MAXN = 100010;
llg** c;
llg* f,*f_s;
llg* dist;
int* path;
bool* collected;
int n,m; llg b;
struct cmp{
    bool operator()(int m,int n){
        return dist[m] > dist[n];
    }
};
bool check_(llg mid){
    for(int i=1;i<=n;i++){
        dist[i] = INF; path[i] = -1; collected[i]=false;
    }
    dist[1] = 0;
    priority_queue<int,vector<int>,cmp> vi; vi.push(1);
    while(true){
        if(vi.empty()) break;
        int v = vi.top(); vi.pop();
        collected[v]=true;
        for(int i=1;i<=n;i++)
            if(f[i] <=mid && c[v][i] !=0 && collected[i]==false)
                if(dist[v]+c[v][i] < dist[i]){
                    dist[i] = dist[v]+c[v][i];
                    path[i] = v;
                    vi.push(i);
                }        
    }
    if(path[n]==-1) {
        #ifdef DEB2
        cout << "path[n]==-1"<<endl;
        #endif
        return false;
    }
    else{
        int p = path[n];
        llg b_cur = c[n][p]; 
        while(path[p]!=-1){
            #ifdef DEB3
            cout << "p=" << p<<" path[p]=" << path[p] << endl;
            #endif
            b_cur += c[p][path[p]];
            #ifdef DEB2
            cout << "p-"<< p << " ";
            #endif
            p = path[p];
        }
        b_cur +=c[p][1];
        #ifdef DEB2
        cout << endl << "cur_b="<<b_cur<<endl;
        #endif
        if(b_cur > b){
            #ifdef DEB2
            cout << "b_cur > b"<<endl;
            #endif
            return false;
        }
        else{
            #ifdef DEB2
            cout << "b_cur < b"<<endl;
            #endif
            return true;
        }
    }
    return false;
}
int main(){
    cin >> n >> m >> b;
    c = new llg*[n+5];
    f=new llg[n+5],f_s=new llg[n+5];
    dist =new llg[n+5];
    path =new int[n+5];
    collected=new bool[n+5];
    for (int i = 0; i < n+5; i++)
        c[i] = new llg[n+5];
    for(int i=1;i<=n;i++) {cin >> f[i];f_s[i]=f[i];}
    for(int i=1;i<=m;i++){
        int a,b,k; cin >> a >> b >> k;
        c[a][b] = c[b][a] = k;
    }
    #ifdef DEB3
    cout << "check_(10)"<<check_(f_s[4]) << endl;
    #endif
    sort(f_s+1,f_s+1+n);
    int l=1,r=n+1,ans=-1;
    while(l<r){
        int mid = l + (r-l)/2;
        #ifdef DEB3
        cout << "#"<< l<<" " << mid << " "<< r <<" " << f_s[mid]<< endl;
        #endif
        if(check_(f_s[mid])) {
            r = mid;
            ans = mid;
        }
        else l=mid+1;
    }
    #ifdef DEB3
    cout << "ans=" <<ans <<endl;
    #endif 
    if(ans != -1) cout << f_s[ans]; // 检查 ans 是否有效
    else cout << "AFK";
    return 0;
}
