#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
const int MAXM = 25010;
int a[MAXN];
int b[MAXM];
int n, m, s;
int as[MAXN][30];
int bs[MAXM][30];


// Initializes prefix sums for frequency of each character up to index i in a[] and b[]
void init() {
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            for (int j = 1; j <= 25; j++) as[i][j] = 0;
        } else {
            for (int j = 1; j <= 25; j++) as[i][j] = as[i - 1][j];
        }
        as[i][a[i]]++;
    }
    for (int i = 0; i < m; i++) {
        if (i == 0) {
            for (int j = 1; j <= 25; j++) bs[i][j] = 0;
        } else {
            for (int j = 1; j <= 25; j++) bs[i][j] = bs[i - 1][j];
        }
        bs[i][b[i]]++;
    }
}
int Next[MAXM];

void kmp_pre() {
    int i,j;
    j = Next[0]=-1;
    i=0;
    while(i<m){
        int t11=0,t12=0,t21=0,t22=0;
        /**
         * t11：在 b[i-j] 到 b[i] 区间内，所有小于 b[i] 的字符的出现频率总和
         * t12：在 b[i-j] 到 b[i] 区间内，与 b[i] 相同的字符的出现频率。
         * t21：在 b[0] 到 b[j] 区间内，所有小于 b[j] 的字符的出现频率总和
         * t22：在 b[0] 到 b[j] 区间内，与 b[j] 相同的字符的出现频率
         * 方法:使用是一种相对关系，满足相对关系的频率之和相同
        */
        for(int k=1;k<b[i];k++){
            if(i-j>0)t11+=bs[i][k]-bs[i-j-1][k]; 
            else t11+=bs[i][k];
        }
        if(i-j>0)t12=bs[i][b[i]]-bs[i-j-1][b[i]];
        else t12=bs[i][b[i]];
        for(int k=1;k<b[j];k++){
            t21+=bs[j][k];
        }
        t22=bs[j][b[j]];
        if(j==-1 || (t11==t21 && t12==t22)){
            Next[++i]=++j;
        }
        else j=Next[j];
    }
}
vector<int> ans;
void kmp() {
    ans.clear(); //最大的失误
    int i, j;
    kmp_pre();
    i = j = 0; //千万别写成j=Next[0]=-1;
    while(i < n) {
        int t11 = 0, t12 = 0, t21 = 0, t22 = 0;
        for(int k = 1; k < a[i]; k++) {
            if(i - j > 0) t11 += as[i][k] - as[i - j - 1][k];
            else t11 += as[i][k];
        }
        if(i - j > 0) t12 = as[i][a[i]] - as[i - j - 1][a[i]];
        else t12 = as[i][a[i]];
        for(int k = 1; k < b[j]; k++) {
            t21 += bs[j][k];
        }
        t22 = bs[j][b[j]]; 
        
        if(j == -1 || (t11 == t21 && t12 == t22)) {
            i++; j++;
            if(j >= m) {
                ans.push_back(i - m + 1);
                j = Next[j]; 
            }
        } else {
            j = Next[j];
        }
    }
}

int main() {
    while(scanf("%d%d%d", &n, &m, &s) == 3) {
        
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        for(int i = 0; i < m; i++) scanf("%d", &b[i]);
        init();
        kmp();
        printf("%d\n", ans.size());
        for(size_t i = 0; i < ans.size(); i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}