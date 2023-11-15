#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
typedef char HFelem;
#define HFelemNULL '\0'
struct HFnode{
	HFelem data;
	int weight;	
	struct HFnode* Left;
	struct HFnode* Right;
};
typedef struct HFnode HFnode_;
typedef struct HFnode* HFnode;
typedef struct{
	HFnode head;
	int size;
}HFtree_;
typedef HFtree_* HFtree;
//------------------------------------
typedef HFnode HeapType;
int HeapCMP(HeapType e1,HeapType e2){
	return e1->weight - e2->weight;
}
//------------------------------------
#define MINHeapElem -1
typedef struct {
	HeapType* data;
	int size;
	int capacity;
}PriHeap_;
typedef PriHeap_* PriHeap;

PriHeap create_priheap(int capacity){
	PriHeap  tmp = (PriHeap) malloc (sizeof(PriHeap_));
	tmp->data = (HeapType*) malloc (sizeof(HeapType) * (capacity+1));
	tmp->data[0] = getHFnode();
	tmp->data[0]->weight = MINHeapElem;	
	tmp->size = 0;
	tmp->capacity = capacity;
	return tmp;
}

HFnode getHFnode(){
	HFnode tmp = (HFnode) malloc(sizeof(HFnode_));
	tmp->data = HFelemNULL;
	tmp->weight = 0;
	tmp->Left = tmp->Right = NULL;
	return tmp;
}

void h_swap(HeapType* e1,HeapType* e2){
	HeapType tmp = *e1;
	*e1 = *e2, *e2 = tmp;
}

bool h_size(PriHeap ph){return ph->size;}
bool h_top(PriHeap ph) {return ph->data[1];}

bool h_push(PriHeap ph,HeapType e){
	if(h_size(ph) > ph->capacity) return -1;
	ph->data[++ph->size] = e;
	int child = ph->size, parent = child / 2;
	while(parent > 0 && HeapCMP(ph->data[child],ph->data[parent]<0)){
		h_swap(&ph->data[child],&ph->data[parent]);
		child = parent;
		parent /=2;
	}
	return 0;
}

	






	
