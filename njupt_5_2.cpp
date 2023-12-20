
/**
 * 题解：贪心+作业调度问题
 * 
*/
/**
 * ## 玩游戏

## 题目描述

某游戏中有 $n$ 个任务，第 $i$ 个任务将在 $T_i$ 时间后截止，做第 $i$ 个任务要耗费 $t_i$ 时间。最多能完成多少个任务？

## 输入格式
共 $n+1$ 行，第一行一个正整数 $n$，$1\le n\le 10^6$

接下来 $n$ 行，每行两个正整数 $t_i$，$T_i$

$1\le t_i,T_i \le 10^9$

## 输出格式
一行，一个整数表示最多能完成的任务数量

### 输入#1

```
4
100 200
200 1300
1000 1250
2000 3200
```
### 输出#1
```
3
```
*/
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

const int MAXN = 1000010;

struct cow_{
    llg p,c;
    bool b = false;
    cow_(){}
    cow_(llg p_,llg c_):p(p_),c(c_){}
}cow[MAXN];


struct cmpPC{
    bool operator()(int m,int n){
        return cow[m].p-cow[m].c > cow[n].p-cow[n].c;
    }
};
struct cmpP{
    bool operator()(int m,int n){
        return cow[m].p > cow[n].p;
    }
};
struct cmpC{
    bool operator()(int m,int n){
        return cow[m].c > cow[n].c;
    }
};
struct cmpSORT{
    bool operator()(cow_& m,cow_& n){
        return m.c < n.c;
    }
};

priority_queue<int,vector<int>,cmpPC> pc_k;
priority_queue<int,vector<int>,cmpP> p_n;
priority_queue<int,vector<int>,cmpC> c_n;


llg n,k,m,tut;
int main(){
    cin >> n;
    int sum_i = 0;
    for(int i=1;i<=n;i++){
        llg p,c; cin >> p >> c;
        cow[i] = cow_(p,c);
    }
    sort(cow+1,cow+n+1,cmpSORT());
    while(1){
        
    }
    for(int i=1;i<=n;i++){
        if(i<=k){
            pc_k.push(i);
            tut += cow[i].c; cow[i].b = true;sum_i +=1;
            if(tut > m) {
                cout << i - 1;
                return 0;
            }
        }
        else{p_n.push(i); c_n.push(i);}
    }
    for(int i=1;i<=n-k;i++){
        int min_i; bool isPC = false;
        while(!p_n.empty() && cow[p_n.top()].b) p_n.pop();
        while(!c_n.empty() && cow[c_n.top()].b) c_n.pop();
        if( !pc_k.empty() &&
        cow[p_n.top()].p 
        < 
        cow[c_n.top()].c + cow[pc_k.top()].p - cow[pc_k.top()].c)
            isPC = false;   
        else{
            min_i = c_n.top(); cow[min_i].b = true;
            tut += cow[min_i].c + cow[pc_k.top()].p - cow[pc_k.top()].c;
            c_n.pop(); pc_k.pop();
            pc_k.push(min_i);
            isPC = true;
            #ifdef DEB1
            cout << "@" << cow[min_i].p << " "<< cow[min_i].c << endl;
            #endif
        }
        if(isPC == false){
            min_i = p_n.top(); cow[min_i].b = true;
            tut += cow[min_i].p; 
            p_n.pop();
            #ifdef DEB1
            cout << "#" << cow[min_i].p << " "<< cow[min_i].c << endl;
            #endif
        }
        if(tut > m) break; //这里有一个小陷阱，刚好等于m的时候，其实还是要+=1的
        sum_i +=1;
    }
    cout << sum_i;
    return 0;
}
