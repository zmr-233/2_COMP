
//P5018-检验是否是对称二叉树
#include<bits/stdc++.h>
using namespace std;
#define llg long long
#define maxn 1000100
#define V1 (llg)(999999751) 
#define V2 (llg)(299999827) 
#define V3 (llg)(100000007)
#define md (llg)(89999794200117649)
#define mdd (llg)(999999786000011449)
#define yyj(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout);

inline llg getint()
{
    llg w=0,q=0; char c=getchar();
    while((c<'0' || c>'9') && c!='-') c=getchar();
    if (c=='-')  q=1, c=getchar(); while (c>='0' && c<='9') w=w*10+c-'0', c=getchar();
    return q ? -w : w;
}

//A-使用散列值检验
/**
 * 这里使用的方法是散列值检验
 * 分别为左右子树计算散列值，如果对称相等，就判定为相同
 * 这里使用了两种散列值的计算
*/
unsigned long long hal[maxn],har[maxn],Har[maxn],Hal[maxn];
llg val[maxn],n,ans,he[maxn],lson[maxn],rson[maxn];

void dfs(llg x,llg fa)
{
	if (lson[x]) dfs(lson[x],x);
	if (rson[x]) dfs(rson[x],x);
	he[x]=he[lson[x]]+he[rson[x]]+1; //这里是节点个数
	if (he[lson[x]]==he[rson[x]] && hal[lson[x]]==har[rson[x]] &&  Hal[lson[x]]==Har[rson[x]])
		{
			ans=max(ans,he[x]);
		}
    hal[x] = (hal[lson[x]] * V1 + val[x] * V2 + hal[rson[x]] * V3) % md;
    Hal[x] = (Hal[lson[x]] * V1 + val[x] * V2 + Hal[rson[x]] * V3) % mdd;


    har[x] = (har[rson[x]] * V1 + val[x] * V2 + har[lson[x]] * V3) % md;
    Har[x] = (Har[rson[x]] * V1 + val[x] * V2 + Har[lson[x]] * V3) % mdd;
}

int main()
{
	yyj("D");
	cin>>n;
	for (llg i=1;i<=n;i++) val[i]=getint();
	for (llg i=1;i<=n;i++)
		{
			llg x=getint(),y=getint();
			if (x!=-1) lson[i]=x; //这里使用了一个默认行为:全局变量自动初始化为0
			if (y!=-1) rson[i]=y;
		}
	dfs(1,-1);
	cout<<ans;
	return 0;
}

//B-枚举判断，不属于任何遍历
/**
 * 第一感是搞镜像。
 * 但其实只要枚举每棵子树，判断递归的判断左右子树分别相等。
 * 相等就记数，更新答案即可,总结为三个步骤:
 * 
 * 1.以二叉树的每一个节点为根节点，寻找对称二叉树
 * 2.将找到的二叉树统计节点数
 * 3.比较最大的节点数
*/
struct node{long long l,r,val;}bt[1000002];
bool same(long long now1,long long now2){//判断是否对称
	if(now1==-1&&now2==-1) return true;
	if(now2==-1||now1==-1) return false;//小技巧
	if(bt[now1].val!=bt[now2].val) return false;
	return same(bt[now1].l,bt[now2].r)&&same(bt[now1].r,bt[now2].l);//递归的判断左右子树相等
}
int count(long long now){//递归的对左右子树计数
	return now==-1?0:count(bt[now].l)+count(bt[now].r)+1;
}
int main(){
	int n,ans=0;cin>>n;
	for(int i=1;i<=n;i++) cin>>bt[i].val;
	for(int i=1;i<=n;i++) cin>>bt[i].l>>bt[i].r;
	for(int i=1;i<=n;i++)/*枚举每棵子树*/ if(same(i,i)) ans=max(ans,count(i));
	return 0&printf("%d",ans);
}