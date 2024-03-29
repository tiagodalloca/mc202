/* TIAGO PEREIRA DALL'OCA */
/* RA 206341 */

/* O programa contem alguns comentários mas no geral é bem autoexplicativo */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _compare_int(void* v1, void* v2){
	return *((int*) v1) - *((int*) v2);
}

typedef struct Node {
	void* info;
	struct Node* next;
	size_t size_info; 
} Node;

void _insert_before(Node** n, void* v, size_t s){
	Node* nn = (Node*) malloc(sizeof(Node));
	nn->info = malloc(s);
	memcpy(nn->info, v, s);
	nn->size_info = s;
	nn->next = n[0];
	n[0] = nn;
}

void _insert_after(Node** n, void* v, size_t s){
	Node* nn = (Node*) malloc(sizeof(Node));
	nn->info = malloc(s);
	memcpy(nn->info, v, s);
	nn->size_info = s;
	nn->next = n[0]->next;
	n[0]->next = nn;
}

void _ordered_insert(Node** n, void* v, size_t s, int (*compar)(void*, void*)){
 int c;
 if(n[0] == NULL)
	 _insert_before(n, v, s);
 else if ((c = compar(n[0]->info, v)) > 0)  // n->info > v
	 _insert_before(n, v, s);
 else // n->info <= v
	 if (c == 0)
		 return;

	 else if (n[0]->next == NULL)
		 _insert_after(n, v, s);
	 else
		 _ordered_insert(&(n[0]->next), v, s, compar); 
}


int _has(Node* n, void* r, int (*compar)(void*, void*)){
	if(n == NULL)
		return 0;
	if(!compar(n->info, r)) // equal
		return 1;
	return _has(n->next, r, compar);
}

void _remove(Node** n, void* r, int (*compar)(void*, void*)){
	if(n[0] == NULL)
		return;

	if(n[0]->next == NULL){
		if(!compar(n[0]->info, r)){
			free(n[0]->info);
			free(n[0]);
			n[0] = NULL;
		}
	}

	else if (!compar(n[0]->info, r)){
		Node* aux =  n[0]->next;
		free(n[0]->info);
		free(n[0]);
		n[0] = aux;
	} 
	
	else if(!compar(n[0]->next->info, r)){
		Node* aux = n[0]->next->next;
		free(n[0]->next->info);
		free(n[0]->next);
		n[0]->next = aux;
	}
		else if (n[0]->next != NULL)
		_remove(&(n[0]->next), r, compar);
}


int _is_in(Node* n, void* v, int (*compar)(void*, void*)){
	if (n == NULL)
		return 0;
	if (!compar(n->info, v))
		return 1;
	return _is_in(n->next, v, compar);
}

void _union(Node** a, Node* na, Node* nb, int (*compar)(void*, void*)){
	if (nb == NULL)
		return;
	else if (na == NULL){
		_ordered_insert(a, nb->info, nb->size_info, &_compare_int);
		_union(a, a[0], nb->next, compar);
	} 
	else if (compar(na->info, nb->info)) // if different
		_union(a, na->next, nb, compar);
	else // if equal
		_union(a, a[0], nb->next, compar);
}

void _intersection(Node** a, Node* na, Node* b, Node* nb, int (*compar)(void*, void*)){
	if (na == NULL)
		return;
	else if (nb == NULL){
		Node* aux = na->next;
		_remove(a, na->info, compar);
		_intersection(a, aux, b, b, compar);
	} 
	else if (compar(na->info, nb->info)) // if different
		_intersection(a, na, b, nb->next, compar);
	else // if equal
		_intersection(a, na->next, b, b, compar);
}

void _subtraction(Node** a, Node* na, Node* nb, int (*compar)(void*, void*)){
	if (nb == NULL)
		return;
	else if (na == NULL){
		_subtraction(a, a[0], nb->next, compar);
	} 
	else if (compar(na->info, nb->info)) // if different
		_subtraction(a, na->next, nb, compar);
	else { // if equal
		_remove(a, nb->info, compar);
		_subtraction(a, a[0], nb->next, compar); 
	}
}

void _show(Node* n, void (*_print)(void*)){
	printf("{");
	if (n != NULL){
		for(; n->next != NULL; n = n->next){
			_print(n->info);
			printf(",");
		}
		_print(n->info);
	}
	printf("}\n");
}

Node* free_nodes(Node* n) {
	if (n != NULL) {
		free_nodes(n->next);
		free(n->info);
		free(n);
	}
	return NULL;
}

void _print_int(void* v){
	printf("%d", *((int*) v));
}

int main(){
	unsigned char c;
	Node *c1, *c2;
	char s = 1;
	c1 = c2 = NULL; 
	while(s){
		char d = scanf("%c", &c);
		
		if (d == EOF){
			s = 0;
			goto terminar;	
		}

		int e, x;
		switch(c){
		case 'i': 
			scanf("%d %d", &e, &x); 
			if (x == 1)
				_ordered_insert(&c1, &e, sizeof(int), &_compare_int);
			else
				_ordered_insert(&c2, &e, sizeof(int), &_compare_int);
			break;
		case 'p': 
			scanf("%d %d", &e, &x);
			if (x == 1)
				if (_has(c1, &e, &_compare_int))
					printf("SIM\n");
				else
					printf("NAO\n");
			else
				if (_has(c2, &e, &_compare_int))
					printf("SIM\n");
				else
					printf("NAO\n");
			break;
		case 'r': 
			scanf("%d %d", &e, &x);
			if (x == 1)
				_remove(&c1, &e, &_compare_int);
			else
				_remove(&c2, &e, &_compare_int);
			break;
		case 'u':
			_union(&c1, c1, c2, &_compare_int);
			break;
		case 'x':
			_intersection(&c1, c1, c2, c2, &_compare_int);
			break;
		case 'b':
			_subtraction(&c1, c1, c2, &_compare_int);
			break;
		case 's':
			s = 0;
			break;
		default:
			continue;
		}

	terminar:
		_show(c1, &_print_int);
		_show(c2, &_print_int);
	}

	free_nodes(c1);
	free_nodes(c2);

	return 0;
}
