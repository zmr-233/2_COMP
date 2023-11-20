//这道题找奶牛，属于-->反悔贪心 的算法
/**
 * 首先只会有两种情况:
 * 1.全部使用优惠劵购买
 * 2.一部分使用优惠劵，另一部分则是原价购买
 * 
 * 情况1：只需要确保j<k的情况下，/sum{C_j} > m 此时答案就是 j-1
 * 情况2：首先针对k个全买c，计算tut，接着处理k-n，有两种情况:
 *        a.从k+1只选出一只min P的奶牛m
 *        b.从前k只奶牛中选出一只P与C之差最小的奶牛x,再从k+1选出一只C最小的奶牛y
 *          -->将x的优惠劵给y使用，此时增加为Px-Cx+Cy
*      这样，增加的总钱数为min(P_m,Px-Cx+Cy)就是最终的答案

    更新方式:
    开三个优先队列：
    1.前k只奶牛的P与C之差
    2.从k+1到n的C值
    3.从k+1到第n的P值
*/

//P3045--优惠劵买奶牛
#include<bits/stdc++.h>
using namespace std;
#define DEB0_
#define DEB1_

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

const int MAXN = 5*10e4+10;

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
    cin >> n >> k >> m;
    int sum_i = 0;
    for(int i=1;i<=n;i++){
        llg p,c; cin >> p >> c;
        cow[i] = cow_(p,c);
    }
    sort(cow+1,cow+n+1,cmpSORT());
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





