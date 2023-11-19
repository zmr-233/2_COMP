#ifdef __cplusplus
#include<bits/stdc++.h>
#endif
#ifndef __cplusplus
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include<limits.h>
#include<stdlib.h>
#endif

#define DEB0_
#define DEB1_
#define DEB2_
#define DEB3_

#define MAXN 10000
/*-------------------------hfm节点部分-----------------------------------*/
typedef char ElemType;
#define ElemNull '@'
typedef struct hfmNode_{
    ElemType elem;
    int w;
    struct hfmNode_ * l;
    struct hfmNode_ * r;
}hfmNode_;
typedef hfmNode_* hfmNode;

typedef hfmNode HeapType;	

hfmNode getNode(ElemType elem,int w){
    hfmNode tmp = (hfmNode)malloc(sizeof(hfmNode_));
    tmp->elem = elem,tmp->w = w;
    tmp->l = tmp->r = NULL;
    return tmp;
}
hfmNode buildNode(hfmNode l,hfmNode r){
    hfmNode f = getNode(ElemNull,l->w + r->w);
    f->l = l, f->r = r;
    return f;
}
void node_swap(hfmNode* m,hfmNode* n){hfmNode tmp = *m; *m = *n; *n = tmp;}
#ifdef DEB0
void print_hfmNode(hfmNode elem){
    cout << "hfmNode:" << elem->elem 
        << " " << elem->w << " " << ((elem->l==NULL)?"*":"^") << " " << ((elem->r==NULL)?"*":"^") << endl;
}
#endif
/*-------------------------优先队列(最小堆)-----------------------------------*/
#ifdef __cplusplus
struct tmpCMP /*重写仿函数*/{bool operator() (HeapType a, HeapType b) {return a->w > b->w;}};

typedef struct Heap_ {
    priority_queue<HeapType, vector<HeapType>, tmpCMP> pq;
    int size;
    int capacity;
} Heap_;
typedef Heap_* Heap;

Heap iniHeap(int capacity){
    Heap tmp = (Heap)malloc(sizeof(Heap_));
    tmp->capacity = capacity;
    tmp->size = 0;
    return tmp;
}
bool h_empty(Heap h){return h->pq.empty();}
int h_size(Heap h){/*return h->size;*/return h->pq.size();}
HeapType h_top(Heap h){ return h->pq.top();}
void h_push(Heap h,HeapType elem){ 
    assert(h!=NULL); 
    #ifdef DEB1
    print_hfmNode(elem);
    #endif
    #ifdef DEB3
    cout << "h is empty" << h->pq.empty() << endl;
    #endif
    h->pq.push(elem);
}
void h_pop(Heap h){h->pq.pop();}
#endif
#ifndef __cplusplus
bool heapCMP(HeapType a, HeapType b) {return a->w > b->w;} // 1--> b优先 0-->a优先
typedef struct Heap_ {
	HeapType* data;
	int size;
	int capacity;
} Heap_;
typedef Heap_* Heap;
Heap iniHeap(int capacity){
	Heap tmp = (Heap)malloc(sizeof(Heap_));
	tmp->capacity = capacity;
	tmp->size = 0;
	tmp->data = (HeapType*)malloc(sizeof(HeapType)*(capacity+1));
	tmp->data[0] = getNode(ElemNull,INT_MIN);
	return tmp;
}
bool h_empty(Heap h){return h->size == 0;}
int h_size(Heap h){return h->size;}
HeapType h_top(Heap h){
	assert(!h_empty(h));
	return h->data[1];
}
void h_push(Heap h,HeapType elem){
	assert(h_size(h) < h->capacity);
	int i = ++h->size;
	for(;heapCMP(elem,h->data[i/2]) == 0;i/=2)
		h->data[i] = h->data[i/2];
	h->data[i] = elem;
};
void h_pop(Heap h){
	HeapType top = h_top(h);
	HeapType tmp = h->data[h->size--];
	int parent = 1,child = 2;
	for(;2*parent <= h->size;parent = child){
		child = 2*parent;
		if(child + 1 <= h->size && heapCMP(h->data[child],h->data[child+1])==1)
			child +=1;
		if(heapCMP(h->data[child],tmp)==1) break;
		else h->data[parent] = h->data[child];
	}
	h->data[parent] = tmp;
	return top;
}
#endif
/*-------------------------encoder编码器-------------------------------------*/
/*-----hfmTree哈夫曼树-------*/
typedef struct hfmTree_{
    hfmNode root;
}hfmTree_;
typedef hfmTree_* hfmTree;

/*------数据传递结构-------*/
typedef struct Info_{
    hfmTree tree;
    int* data;
    int n;
}Info_;
typedef Info_* Info;
#ifdef DEB0
void print_info(Info info){
    for(int i=0;i<info->n;i++)
        cout << (char)info->data[i];
    cout << endl;
}
#endif
#ifdef __cplusplus
Info cppInput(string& s){
    Info info = (Info)malloc(sizeof(Info_));
    info->tree = NULL, info->n = s.size();
    info->data = (int*)malloc(sizeof(int)*(s.size()+1));
    for(int i=0;i <= s.size();i++) info->data[i] = s[i]; //这里结尾是'\0'
    return info;
}
#endif
Info cInput(){
    char input[MAXN + 1];
    fgets(input, MAXN, stdin); //读取一整行

	Info info = (Info)malloc(sizeof(Info_));
	info->tree = NULL;
    info->n = strlen(input); // 更新n为实际读取的长度
	info->data = (int*)malloc(sizeof(int)*(info->n+1));

    if (input[info->n - 1] == '\n') { /*陷阱:换行符*/
		input[info->n - 1] = '\0';
		info->n--; 
	}
    for (int i = 0; i <= info->n; i++) // 将字符转换为整数并存储
        info->data[i] = input[i];
    return info;
}
Info copyInfo(Info info) {
    if (info == NULL) return NULL;
    Info infoCopy = (Info)malloc(sizeof(Info_));
    infoCopy->n = info->n;
    if (info->n > 0) {
        infoCopy->data = (int*)malloc(sizeof(int) * info->n);
        memcpy(infoCopy->data, info->data, sizeof(int) * info->n);
    } else infoCopy->data = NULL;
    return infoCopy;
}

int intCMP(const void* a, const void* b) {
    const int* x = (const int*)a;const int* y = (const int*)b;
    return *x - *y;
}

Heap countLen(Info info) {
    qsort(info->data, info->n, sizeof(int), intCMP); //对字符排序
    #ifdef DEB1
    print_info(info);
    #endif
    Heap h = iniHeap(info->n + 1);
    int n_ch = 1;
    for(int i=1;i <= info->n;i++){
        if(info->data[i] != info->data[i-1]) { 
            hfmNode tmp = getNode(info->data[i-1],n_ch);
            h_push(h,tmp); n_ch = 1;
        }
        else n_ch +=1;
    }
    return h;
}
void createMapping(hfmNode node,char* code,int top,char mapping[256][256]){
    //如果是叶节点
    if(node->l == NULL && node->r == NULL){
        code[top] = '\0';
        strcpy(mapping[node->elem],code);
    }else{
        if(node->l != NULL){ //左为0
            code[top] = '0';
            createMapping(node->l,code,top+1,mapping);
        }
        if(node->r != NULL){ //右为1
            code[top] = '1';
            createMapping(node->r,code,top+1,mapping);
        }
    }
}

void encodeInfo(Info info,Info output,char mapping[256][256]){
    int top = 0; //此处是output编码的顶端
    for(int i=0;i < info->n;i++){
        char *code = mapping[info->data[i]];
        for(int j=0; code[j] != '\0' ;j++)
            output->data[top++] = code[j];
    }
    output->data[top] = '\0'; //添加结束标志
}
Info encoder(Info info){ /*info中包含传入的原始字符，而output则生成*/
    #ifdef DEB1
    print_info(info);
    #endif
    Info ini_info = copyInfo(info); /*创建一个原始信息副本*/
    Heap h = countLen(info); //统计字符长度
    Info output = (Info)malloc(sizeof(Info_));
    output->tree = (hfmTree)malloc(sizeof(hfmTree_));
    int wpl = 0;
    //陷阱:只有一种字符的时候
    if(h_size(h) == 1) wpl = h_top(h)->w;
    while(h_size(h) > 1){
        hfmNode a = h_top(h); h_pop(h);
        hfmNode b = h_top(h); h_pop(h);
        hfmNode root= buildNode(a,b);
        h_push(h,root); wpl += a->w + b->w;
    }
    output->tree->root = h_top(h); h_pop(h);

    /*下方是生成编码的部分*/
    output->n = wpl;
    #ifdef DEB2
    cout << output->n << endl;
    #endif
    output->data = (int*)malloc(sizeof(int)*(wpl+1));
    memset(output->data,0,sizeof(output->data));

    /*生成映射表，并进行编码*/
    char mapping[256][256];
    char code[256];

    createMapping(output->tree->root,code,0,mapping);

    encodeInfo(ini_info,output,mapping); /*注意：这里要使用没有排序过的ini_info来编码*/

    return output;
}
/*-------------------------decoder解码器-------------------------------------*/
Info decoder(Info output){
    Info info = (Info)malloc(sizeof(Info_));
    info->n = output->n;
    info->data = (int*)malloc(sizeof(int)*(info->n+1));
    info->data[info->n] = '\0';
    //处理只有一种字符的时候,重复这个字符
    if(output->tree->root->l == NULL && output->tree->root->r == NULL) {
        // 只有一个节点，
        int singleChar = output->tree->root->elem;
        for(int i = 0; i < info->n; i++) {
            info->data[i] = singleChar;
        }
        info->data[info->n] = '\0';
        return info;
    } 
    int top = 0; hfmNode cur = output->tree->root;
    for(int i=0;output->data[i] != '\0';i++){
        if(output->data[i] == '0') cur = cur->l;
        else cur = cur->r;

        if(cur->l == NULL && cur->r == NULL){
            info->data[top++] = cur->elem;
            cur = output->tree->root;
        }
    }
    info->data[top] = '\0';
    return info;
}
int main(){
	#ifdef __cplusplus
	string s; cin >> s;
    Info input =  cppInput(s);
	#endif
	#ifndef __cplusplus
	Info input = cInput();
	#endif
    Info output = encoder(input);
    Info info = decoder(output);
    #ifdef DEB2
    cout << "######"<<endl;
    #endif
	#ifdef __cplusplus
    for(int i=0;info->data[i] != '\0';i++) cout << (char)info->data[i];
	#endif
	#ifndef __cplusplus
	for(int i=0;info->data[i] != '\0';i++) printf("%c",(char)info->data[i]);
	#endif
    return 0;
}
	
	
		

















	
