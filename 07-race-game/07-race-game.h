#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>

#define PARENT(i) ((i-1)/2)
#define LT(i) (2*i+1) /* left node of i */
#define RT(i) (2*i+2) /* right node of i */

typedef struct{
	float val;
	unsigned char* indexes;
} Node;

typedef struct{
	Node** v;
	unsigned int n, max;
} MaxHeap;

Node* create_node(float f, unsigned char* indexes){
	Node* n = (Node*) malloc(sizeof(Node));
	n->val = f;
	n->indexes = indexes;
	return n;
}

void switch_adr(void** a, void** b){
	void* aux = *a;
	*a = *b;
	*b = aux;
}

unsigned int goup_heap(MaxHeap *h, unsigned char heap_index, unsigned int k) {
	if (k > 0 && h->v[PARENT(k)]->val < h->v[k]->val) {
		unsigned int k_parent_index = PARENT(k);
		h->v[k_parent_index]->indexes[heap_index] = k;
		switch_adr((void **) &h->v[k], (void **) &h->v[k_parent_index]);
		return goup_heap(h, heap_index, k_parent_index);
	}
	return k;
}

void  insert_heap(MaxHeap *h, unsigned char heap_index, Node *p) {
	h->v[h->n] = p; 
	h->n++; 
	p->indexes[heap_index] = goup_heap(h, heap_index, h->n - 1);
}

unsigned int godown_heap(MaxHeap *h, unsigned char heap_index, unsigned int k) {
	if (LT(k) < h->n) { // has any descendant
		unsigned int greater_descendant =
			// chooses greater descendant
			(RT(k) < h->n && h->v[LT(k)]->val < h->v[RT(k)]->val)?RT(k):LT(k);
		if (h->v[k]->val < h->v[greater_descendant]->val) {
			h->v[greater_descendant]->indexes[heap_index] = k; 
			switch_adr((void*)&h->v[k], (void*)&h->v[greater_descendant]);
			return godown_heap(h, heap_index, greater_descendant);
		}
	}
	return k;
}

Node* extract_max(MaxHeap *h, unsigned char heap_index) {
	Node* n = h->v[0];
	Node* last = h->v[h->n - 1];
	switch_adr((void **) &h->v[0],(void **) &h->v[h->n - 1]);
	h->n--;
	last->indexes[heap_index] = godown_heap(h, heap_index, 0);
	return n;
}

unsigned int artificially_goup_heap(MaxHeap* h, unsigned char heap_index, unsigned int k) {
	if (k > 0) {
		unsigned int k_parent_index = PARENT(k);
		h->v[k_parent_index]->indexes[heap_index] = k;
		switch_adr((void **) &h->v[k], (void **) &h->v[k_parent_index]);
		return artificially_goup_heap(h, heap_index, k_parent_index);
	}
	return k;
}

void extract_node(MaxHeap h[3], unsigned char heap_index, float vals[3]){
	Node* n	= extract_max(&h[heap_index], heap_index);
	vals[heap_index] = n->val;
	for(unsigned char hi = 0; hi < 3; hi++)
		if(hi != heap_index){
			vals[hi] = h[hi].v[n->indexes[hi]]->val;
			n->indexes[hi] = artificially_goup_heap(&h[hi], hi, n->indexes[hi]);
			extract_max(&h[hi], hi);
		}
}

#endif
