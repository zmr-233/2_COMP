#include<bits/stdc++.h>
using namespace std;
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
#define DEB1
struct node{
    #ifdef DEB1
    int x=0;
    #endif
    int i=0;
    int p = -1;
    bool a[6][6]={};
};
int ctt = 0;
#ifdef DEB1
node rev(node t,int x,int y,int p){
    t.x = ctt++;
    t.p = p;
    t.a[x][y] = t.a[x][y] ? 0:1;
    t.a[x+1][y] = t.a[x+1][y]  ? 0:1;
    t.a[x][y+1] = t.a[x][y+1] ? 0:1;
    t.a[x-1][y] = t.a[x-1][y] ? 0:1;
    t.a[x][y-1] = t.a[x][y-1] ? 0:1;
    t.i+=1;
    return t;
}
#endif
bool check(node t){
    bool is_0 = true,is_1 = true;
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++){
            if(t.a[i][j]==1){
                is_0 = false;
            }else{
                is_1 = false;
            }
            if(!is_1 && !is_0){
                return 0;
            }
        }
    return 1;
}

#ifdef DEB1
void print(node& t){
    cout << "------------------------------"<<endl;
    cout <<"index="<< t.x << " i=" << t.i << " p=" << t.p <<endl;
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            cout << t.a[i][j];
        }
        cout <<endl;
    }
    cout << "------------------------------"<<endl;

}
#endif
int main(){
    yyj("njupt_2_4");
    node t;
    for(int i=1;i<=4;i++){
        string s; cin >> s;
        for(int j=1;j<=4;j++){
            if(s[j-1]=='w') t.a[i][j]=1;
            else t.a[i][j]=0;
        }
    }
    queue<node> q; q.push(t);
    while(!q.empty()){
        node tmp = q.front(); q.pop();
        #ifdef DEB1
        print(tmp);
        #endif
        if(check(tmp)){
            cout << tmp.i;
            return 0;
        }
        for(int i=1;i<=4;i++)
            for(int j=1;j<=4;j++)
                    q.push(rev(tmp,i,j,tmp.x));
    }
    return 0; 
}
