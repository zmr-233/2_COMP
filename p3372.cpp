/**
 * 题解：
 * 线段树模板代码-- 区间查询+区间修改
*/


#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5+10;
ll a[N];
ll tree[N<<2];
ll tag[N<<2];
ll ls(ll p){return p<<1;}
ll rs(ll p){return p<<1|1;}

void push_up(ll p){
    //区间求和
    tree[p]=tree[ls(p)]+tree[rs(p)];
    //tree[p]=max(tree[ls(p)],tree[rs(p)]); 最大值
}
void build(ll p,ll pl,ll pr){
    if(pl==pr){tree[p]=a[pl];return;}
    ll mid=(pl+pr)>>1;
    build(ls(p),pl,mid);
    build(rs(p),mid+1,pr);
    push_up(p);
}
void addtag(ll p,ll pl,ll pr,ll d){
    tag[p]+=d;
    tree[p]+=d*(pr-pl+1);
}
void push_down(ll p,ll pl,ll pr){
    if(tag[p]){
        ll mid=(pl+pr)>>1;
        addtag(ls(p),pl,mid,tag[p]);
        addtag(rs(p),mid+1,pr,tag[p]);
        tag[p]=0;
    }
}
void update(ll L,ll R,ll p,ll pl,ll pr,ll d){
    if(L<=pl && pr<=R){
        addtag(p,pl,pr,d); //情况：完全覆盖--只需打上tag就走
        return;
    }
    push_down(p,pl,pr); //向下传递tag
    ll mid=(pl+pr)>>1; 
    //情况:无法完全覆盖--用tag对左右子树update
    if(L<=mid) update(L,R,ls(p),pl,mid,d);
    if(R>mid) update(L,R,rs(p),mid+1,pr,d);
    push_up(p);//更新
}

ll query(ll L,ll R,ll p,ll pl,ll pr){
    if(L<=pl && pr<=R) return tree[p];
    push_down(p,pl,pr);
    ll mid=(pl+pr)>>1;
    ll ans{};
    /**
     * 区间最大值
     *  if(L<=mid) ans=max(ans,query(L,R,ls(p),pl,mid));
        if(R>mid) ans=max(ans,query(L,R,rs(p),mid+1,pr));
    */
    if(L<=mid) ans+=query(L,R,ls(p),pl,mid);
    if(R>mid) ans+=query(L,R,rs(p),mid+1,pr);
    return ans;
}

int main(){
    ll n,m; scanf("%lld %lld",&n,&m);
    for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
    build(1,1,n);
    while(m--){
        ll q,L,R,d;scanf("%lld",&q);
        if(q==1){
            scanf("%lld %lld %lld",&L,&R,&d);
            update(L,R,1,1,n,d);
        }else{
            scanf("%lld %lld",&L,&R);
            printf("%lld\n",query(L,R,1,1,n));
        }
    }
    return 0;
}

