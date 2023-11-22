//这道题只是了解了做法，没有实际做过
#pragma GCC optimize(2)
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long ul;
typedef unsigned long long ull;
#define pi acos(-1.0)
#define e exp(1.0)
#define pb push_back
#define mk make_pair
#define fir first
#define sec second
#define scf scanf
#define prf printf
typedef pair<ll,ll> pa;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAX_N=1e5+7;
ll N,T,a[MAX_N],pre[MAX_N],L[50],R[50];
void do_() {
	ll i,j;
	for(i=2;i<=35;i++){//求二进制是i位的十进制数范围
		L[i]=1ll<<(i-1);//这里要强制的将int 常量转换为long long 
		R[i]=(1ll<<i)-1;
	}
	L[1]=0;
	R[1]=1;//要特别注意1位数的取值范围，题中说了log0=1 
	return ;
}
int main()
{
//  freopen(".../.txt","w",stdout);
//  freopen(".../.txt","r",stdin);
	ios::sync_with_stdio(false);
	ll i,j,k,b,l,r;
	do_();
	cin>>T;
	while(T--){
		cin>>N;
		pre[0]=0;
		for(i=1;i<=N;i++){
			cin>>a[i];
			pre[i]=pre[i-1]+a[i];
		}
		ll sum=0;
		for(i=0;i<35;i++){//枚举位数 
			if(pre[N]<L[i])//如果所有的值都小于L[i],那数列的子区间就更不可能满足条件了，后面的高位数也不可能了 
			break;
			ll tmp=0;
			l=1,r=0;
			for(j=1;j<=N;j++){//指定区间的左端点j ,下面是找区间右端点的可选范围l,r
			 	if(pre[N]-pre[j-1]<L[i])//从j开始到最后这个大的区间都不行的话，后面就不用想了 
			 	    break;
			 	l=(l>j?l:j);
				while(l<=N&&pre[l]-pre[j-1]<L[i])
				    l++;
				r=(r>l?r:l);
				while(r<=N&&pre[r]-pre[j-1]>=L[i]&&pre[r]-pre[j-1]<=R[i])
				    r++;
				r--;//最后要退一下
				if(r>=l)
				tmp+=((r-l+1)*j+(l+r)*(r-l+1)/2);//区间[j~j+l],[j~j+l+1],[j~j+l+2]……[j~j+r]的区间和都是满足位数是i 
			}
			sum+=(i*tmp);
		}
		cout<<sum<<endl;
	}
	return 0;
}


