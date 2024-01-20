#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType;
typedef int KeyType;

typedef struct entry{
    KeyType key;
    DataType data;
} Entry;

#define MAXN 1000000

typedef long long llg;

typedef struct list{
    int n;
    Entry D[MAXN];
} List;

void swap_(Entry* a, Entry* b){
    Entry tmp = *a;
    *a = *b, *b = tmp;
    return;
}

int cmp(const void* a, const void* b){
    return ((Entry*)a)->key - ((Entry*)b)->key;
}

DataType generateDataFromKey(KeyType key){
    return key;  // 直接返回键作为数据
}

// 生成包含随机整数键的列表
List* generateRandomList(int N, KeyType min, KeyType max){
    List* newList = (List*)malloc(sizeof(List));
    newList->n = N;
    for (int i = 0; i < N; i++) {
        newList->D[i].key = min + rand() % (max - min + 1);
        newList->D[i].data = generateDataFromKey(newList->D[i].key);
    }
    return newList;
}

// 冒泡排序算法
void Bubble_Sort(List* A_, int N){
    Entry* A = A_->D;
    for(int p=N-1;p>=0;p++){
        bool flag = false;
        for(int i=0;i<p;i++){
            if(cmp(&A[i+1],&A[i])<=0) {swap_(&A[i+1],&A[i]);flag=true; }
            if(flag==false) break;
        }
    }
}

// 插入排序算法
void Insert_Sort(List* A_, int N){
    Entry* A=A_->D;
    for(int p=1;p<N;p++){
        Entry tmp = A[p];
        int i=p;
        for(;i>0 && cmp(&tmp,&A[i-1])<=0;i--){
            A[i]=A[i-1];
        }
        A[i]=tmp;
    }
}
// 希尔排序算法--原始希尔排序
void Shell_Sort(List* A_, int N){
    Entry* A=A_->D;
    for(int D=N/2;D>0;D/=2){
        for(int p=D;p<N;p+=D){
            Entry tmp = A[p];
            int i=p;
            for(;i>=D && cmp(&tmp,&A[i-D])<=0;i-=D){
                A[i]=A[i-D];
            }
            A[i]=tmp;
        }
    }
}
void PercDown_(List* A_, int p, int N) {
    int Parent, Child;
    Entry X = A_->D[p];  // 取出根节点

    for (Parent = p; (Parent * 2 + 1) < N; Parent = Child) {
        Child = Parent * 2 + 1;
        if ((Child != N - 1) && (A_->D[Child].key < A_->D[Child + 1].key))
            Child++;  // Child指向左右子节点的较大者
        if (X.key >= A_->D[Child].key) break;
        else  // 下滤X
            A_->D[Parent] = A_->D[Child];
    }
    A_->D[Parent] = X;
}

// 堆排序算法
void Heap_Sort(List* A_, int N) {
    // 建立最大堆
    for (int i = N / 2 - 1; i >= 0; i--)
        PercDown_(A_, i, N);
    // 删除堆顶元素并执行下滤
    for (int i = N - 1; i > 0; i--) {
        swap_(&A_->D[0], &A_->D[i]);  // 交换堆顶与堆的最后一个元素
        PercDown_(A_, 0, i);
    }
}

// 归并排序的合并函数（第一种实现）
void Merge1_(List* A, Entry* temp, int L, int R, int RightEnd) {
    int LeftEnd = R - 1;
    int TempPos = L;
    int NumElements = RightEnd - L + 1;

    while (L <= LeftEnd && R <= RightEnd) {
        if (A->D[L].key <= A->D[R].key)
            temp[TempPos++] = A->D[L++];
        else
            temp[TempPos++] = A->D[R++];
    }

    while (L <= LeftEnd)
        temp[TempPos++] = A->D[L++];
    while (R <= RightEnd)
        temp[TempPos++] = A->D[R++];

    for (int i = 0; i < NumElements; i++, RightEnd--)
        A->D[RightEnd] = temp[RightEnd];
}


// 归并排序（第一种实现）
void MSort1_(List* A, Entry* temp, int L, int RightEnd) {
    if (L < RightEnd) {
        int Center = (L + RightEnd) / 2;
        MSort1_(A, temp, L, Center);
        MSort1_(A, temp, Center + 1, RightEnd);
        Merge1_(A, temp, L, Center + 1, RightEnd);
    }
}
void Merge_Sort1(List* A, int N) {
    Entry* temp = (Entry*)malloc(N * sizeof(Entry));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    MSort1_(A, temp, 0, N - 1);

    free(temp);
}


// 归并排序的合并函数（第二种实现）
void Merge2_(List* A, List* temp, int L, int R, int RightEnd) {
    int LeftEnd = R - 1;
    int TempPos = L;
    int NumElements = RightEnd - L + 1;

    while (L <= LeftEnd && R <= RightEnd) {
        if (A->D[L].key <= A->D[R].key)
            temp->D[TempPos++] = A->D[L++];
        else
            temp->D[TempPos++] = A->D[R++];
    }

    while (L <= LeftEnd)
        temp->D[TempPos++] = A->D[L++];
    while (R <= RightEnd)
        temp->D[TempPos++] = A->D[R++];

    for (int i = 0; i < NumElements; i++, RightEnd--)
        A->D[RightEnd] = temp->D[RightEnd];
}


// 归并排序（第二种实现）
void MSort2_(List* A, List* temp, int L, int RightEnd) {
    if (L < RightEnd) {
        int Center = (L + RightEnd) / 2;
        MSort2_(A, temp, L, Center);
        MSort2_(A, temp, Center + 1, RightEnd);
        Merge2_(A, temp, L, Center + 1, RightEnd);
    }
}


void Merge_Sort2(List* A, int N) {
    List* temp = (List*)malloc(sizeof(List));
    MSort2_(A, temp, 0, N - 1);
    free(temp);
}


// 快速排序算法
void QSort(List* A_, int L, int R) {
    if (L < R) {
        int i = L, j = R;
        Entry X = A_->D[L];
        while (i < j) {
            while (i < j && A_->D[j].key >= X.key) j--;
            if (i < j) A_->D[i++] = A_->D[j];
            while (i < j && A_->D[i].key < X.key) i++;
            if (i < j) A_->D[j--] = A_->D[i];
        }
        A_->D[i] = X;
        QSort(A_, L, i - 1);
        QSort(A_, i + 1, R);
    }
}


double getTime(llg (*fun)(List*, int), List* A, int N){
    clock_t begin = clock();
    fun(A, N);
    clock_t end = clock();
    return 1.0 * (end - begin) / CLOCKS_PER_SEC;
}

#define FUNN 7
//#define DEB
int main(){
    #ifndef DEB
    llg (*fun[FUNN])(List*, int) = {
        Bubble_Sort, Insert_Sort, Shell_Sort, Heap_Sort,
        Merge_Sort1, Merge_Sort2, QSort
    };

    int N; KeyType min, max;
    puts("Input N / min / max\n");
    scanf("%d %d %d", &N, &min, &max);
    List* A = generateRandomList(N, min, max);

    for(int i = 0; i < FUNN; i++){
        printf("#%d--调用时间:\n", i + 1);
        double t = getTime(fun[i], A, N);
        printf("    %f\n", t);
    }

    free(A);
    #endif
    #ifdef DEB

    #endif
    return 0;
}

