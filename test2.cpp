#include <stdio.h>
#include <stdlib.h>
using namespace std;
typedef struct Info{
    int x, y, distance;
};
/*------------------------------PriStack---------------------------------------------*/
typedef struct Info HeapType; // 定义堆元素类型
int HeapCMP(HeapType a, HeapType b) {// 比较函数，返回值大于0表示a的优先级大于b
    return b.distance-a.distance;
}
/*--------------------------------------------------------------------------------*/
typedef struct { HeapType* data; int size; int capacity; } PriHeap;
void initialize(PriHeap* heap, int capacity) {
    heap->data = (HeapType*)malloc(sizeof(HeapType) * (capacity + 1));
    heap->size = 0; heap->capacity = capacity;
}
int empty(PriHeap* heap) { return heap->size == 0; }
int size(PriHeap* heap) { return heap->size; }
HeapType top(PriHeap* heap) { return heap->data[1]; }
void clear(PriHeap* heap) { heap->size = 0; }
void swap(HeapType* a, HeapType* b) { HeapType temp = *a; *a = *b; *b = temp; }
void push(PriHeap* heap, HeapType value) {
    if (heap->size == heap->capacity) return; // 堆已满
    heap->data[++heap->size] = value;
    int child = heap->size, parent = child / 2;
    while (parent > 0 && HeapCMP(heap->data[child], heap->data[parent]) > 0) {
        swap(&heap->data[child], &heap->data[parent]);
        child = parent;
        parent /= 2;
    }
}
void pop(PriHeap* heap) {
    if (empty(heap)) return; heap->data[1] = heap->data[heap->size--];
    int parent = 1, child = 2; while (child <= heap->size) {
        if (child + 1 <= heap->size && HeapCMP(heap->data[child + 1], heap->data[child]) > 0) {
            child++;
        }if (HeapCMP(heap->data[parent], heap->data[child]) >= 0) break;
        swap(&heap->data[parent], &heap->data[child]); parent = child; child = 2 * parent;
    }
}
/*--------------------------------------------------------------------------------*/