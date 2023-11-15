#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
typedef char ElemType;
#define ElemNull '\0'
#define MINWEIGHT -1
struct Node_{
	ElemType data;
	int weight;
	struct Node_* Left;
	struct Node_* Right;
};
typedef struct Node_ Node_;
typedef struct Node_* Node;
typedef struct{
	Node head;
	int size;
}Tree_;
typedef Tree_* Tree;

bool CMP(int  e1,int  e2){
	return e1 < e2;
}

Node getNode(){
	Node tmp =  (Node) malloc(sizeof(Node_));
	tmp->Left = tmp->Right = NULL;
	tmp->weight = 0;
	tmp->data = ElemNull;
	return tmp;
}
Tree create_tree(){
	Tree tmp = (Tree) malloc(sizeof(Tree_));
	tmp->size = 0, tmp->head = NULL;
	return tmp;
}

Tree create_heap(){
	Tree tmp = create_tree();
	tmp->head = getNode();
	tmp->head->weight = MINWEIGHT;
	return tmp;
}	


Tree insert_heap(Tree t, ElemType e, int weight){
	Node tmp = getNode();:
	tmp->data = e, tmp->weight = weight;
	
	
		

















	
