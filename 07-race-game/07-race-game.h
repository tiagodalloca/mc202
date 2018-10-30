#ifndef HEADER_FILE
#define HEADER_FILE

#define PARENT(i) ((i-1)/2)
#define LT(i) (2*i+1) /* left node of i */
#define RT(i) (2*i+2) /* right node of i */

typedef struct{
	float val;
	unsigned int* indexes;
} Node;

typedef struct{
	Node** v;
	unsigned int n, max;
} MaxHeap;

Node* create_node(float f, unsigned int* indexes);
void switch_adr(void** a, void** b);
unsigned int goup_heap(MaxHeap *h, unsigned char heap_index, unsigned int k);
void  insert_heap(MaxHeap *h, unsigned char heap_index, Node *p);
unsigned int godown_heap(MaxHeap *h, unsigned char heap_index, unsigned int k);
Node* extract_max(MaxHeap *h, unsigned char heap_index);
unsigned int artificially_goup_heap(MaxHeap* h,
																		unsigned char heap_index,
																		unsigned int k);
void extract_node(MaxHeap h[3], unsigned char heap_index, float vals[3]);
#endif
