// TIAGO DALL'OCA RA 206341
// o código contem alguns comentários, mas é bem direto

#include <stdio.h>
#include <stdlib.h>
#include "07-race-game.h"

Node* create_node(float f, unsigned int* indexes){
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
		// It's needed to update the reference of the index of this node
		// as we're switching it
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
			// Similar line is seen in goup_heap
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
	// update index reference
	last->indexes[heap_index] = godown_heap(h, heap_index, 0);
	return n;
}


/* This method is used to bring a node from any location of the heap */
/* to the very first index. This is done for post removal to keep the */
/* heap's balance */
unsigned int artificially_goup_heap(MaxHeap* h,
																		unsigned char heap_index,
																		unsigned int k) {
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
			artificially_goup_heap(&h[hi], hi, n->indexes[hi]);
			free(extract_max(&h[hi], hi));
		}
	free(n->indexes);
	free(n);
}

int main(int argc, char** args){
	unsigned int IT, MC;
	MaxHeap h[3];
	scanf("%u %u", &IT, &MC);
	for(unsigned char i = 0; i < 3; i++){
		h[i].max = MC;
		h[i].n = 0;
		h[i].v = (Node**) malloc(sizeof(Node*)*MC);		
	}
	for(unsigned int i = 0; i < IT; i++){
		unsigned int C, P;
		scanf("%u %u", &C, &P);

		for(unsigned int j = 0; j < C; j++){
			float atrs[3];
			scanf("%f %f %f", atrs, atrs + 1, atrs + 2);
			unsigned int* indexes = (unsigned int*) malloc(sizeof(unsigned int)*3);
			for(unsigned char k = 0; k < 3; k++)
					insert_heap(h + k, k, create_node(atrs[k], indexes));
		}

		for(unsigned int j = 0; j < P; j++){
			unsigned char k;
			float f[3];
			scanf("%hhu", &k);
			extract_node(h, k, f);
			printf("%.2f %.2f %.2f\n", f[0], f[1], f[2]);
		}
	}

	// free up the memory
	float f[3];
	while(h[0].n > 0) extract_node(h, 0, f);
	for(unsigned char i = 0; i < 3; i++) free(h[i].v);
	return 0;	
}

