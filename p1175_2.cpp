//中缀转后缀
//C语言实现--表达式树方法
#include<bits/stdc++.h>
#define N 114514
using namespace std;
string op;
char ch[N];int num[N],lf[N],rf[N],cnt=0;// ch是运算符，num是值，cnt是节点个数，lf,rf左右儿子
void build(int l,int r){//建表达式树
	if(l==r){
		num[++cnt]=op[l]-'0';
		ch[cnt]=' ';
		return;
	}//叶子结点存好
	if(op[l]=='('){//判断是否为(xxxxx)型
		int go=1;
		for(int i=l+1;i<=r;++i){
			if(op[i]=='(') ++go;
			else if(op[i]==')') --go;
			if(go==0){//找到对应的')'了
				if(i==r) ++l,--r;//判断是否为首尾
				break;
			}
		}
	}
	int p,typo=5;//p为根的坐标
    //typo:+1-1*2/2^3
	for(int i=r;i>=l;--i){
		if(op[i]==')'){//跳过括号
			int go=1,j;
			for(j=i-1;j>=l;--j){
				if(op[j]==')') ++go;
				else if(op[j]=='(') --go;
				if(go==0) break;
			}
			i=j;continue;
		}else if(op[i]<='9'&&op[i]>='0') continue;//跳过数字
		else{//对符号分类讨论
			if((op[i]=='+'||op[i]=='-')&&typo>1) p=i,typo=1;//有加减就加减
			else if((op[i]=='*'||op[i]=='/')&&typo>2) p=i,typo=2;//有乘除就乘除
			else if(op[i]=='^'&&typo>3) p=i,typo=4;//找幂
		}
	}
	int x=++cnt;
	ch[x]=op[p];//更新自己
	lf[x]=cnt+1;
	build(l,p-1);//向左子树递归
	rf[x]=cnt+1;
	build(p+1,r);//向右子树递归
}
int calc(int a,int b,char gk){
	switch(gk){
		case '+':return a+b;
		case '-':return a-b;
		case '*':return a*b;
		case '/':return a/b;
		case '^':return pow(a,b);
	}
}//武则天计算器
void print(int u){//后序遍历输出
	if(ch[u]==' '){
		cout<<num[u]<<" ";
		return;
	}
	print(lf[u]);print(rf[u]);
	cout<<ch[u]<<" ";
}
void dfs(int x){//递归计算
	if(ch[x]==' ') return;
	dfs(lf[x]);dfs(rf[x]);//算左右子树
	num[x]=calc(num[lf[x]],num[rf[x]],ch[x]);//计算本节点
	ch[x]=' ';//复位叶子
	print(1);cout<<endl;//输出运算过程
}
int main(){
	cin>>op;
	build(0,op.size()-1);
	print(1);cout<<endl;
	dfs(1);
	return 0;
}