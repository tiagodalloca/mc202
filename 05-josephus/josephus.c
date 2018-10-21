/* TIAGO PEREIRA DALL'OCA */
/* RA 206341 */

/* O programa contem alguns comentários mas no geral é bem autoexplicativo */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _compare_str(void* v1, void* v2){
	return strcmp((char*) v1, (char*) v2);
}

typedef struct Node {
	void* info;
	struct Node* next;
	struct Node* prev;
	size_t size_info; 
} Node;

Node* _insert_before(Node* n, void* v, size_t s){
	Node* nn = (Node*) malloc(sizeof(Node));
	nn->info = malloc(s);
	memcpy(nn->info, v, s);
	nn->size_info = s;
	if(n == NULL)
		n = nn;
	n->prev = nn;
	nn->next = n;
	nn->prev = n->prev;
	n->prev = nn;
	return nn;
}

Node* _remove_node(Node* n){
	if(n == NULL)
		return n;
	n->prev->next = n->next;
	n->next->prev = n->prev;
	Node* aux = n->next;
	free(n);
	return aux;
}


Node* _walk(Node* n, unsigned int pos){
	if(!pos) // pos == 0
		return n;
	return _walk(n->next, --pos);
}

int _has(Node* n, void* r, int (*compar)(void*, void*)){
	if(n == NULL)
		return 0;
	if(!compar(n->info, r)) // equal
		return 1;
	return _has(n->next, r, compar);
}

Node* _insert(Node* n, void* v, size_t s, unsigned int pos){
	n = _walk(n, pos);
	return _insert_before(n, v, s);
}



Node* _remove(Node* n, unsigned int pos){
	n = _walk(n, pos);
	return _remove_node(n);
}

Node* _find(Node* n, Node* f, void* v1, int (*compar)(void*, void*)){
	if(n == f || ! compar(n->info, v1)) // if equal
		return NULL;
	return _find(n->next, f, v1, compar);
}

Node* _swap(Node* n, void* v1, void* v2, int (*compar)(void*, void*)){
	Node* n1 = _find(n, n, v1, compar);
	Node* n2 = _find(n, n, v2, compar);
	if (n1 == NULL || n2 == NULL)
		return n;
	void* aux = n1->info;
	n1->info = n2->info;
	n2->info = aux;
	return n;
}

void _show(Node* n, void (*_print)(void*)){
	Node* aux = n;

	if (n != NULL){
		for(; n != aux; n = n->next){
			_print(n->info);
			printf(" ");
		}
		_print(n->info);
	}
}

Node* free_nodes(Node* n, Node* f) {
	if (n != f) {
		free_nodes(n->next, f);
		free(n->info);
		free(n);
	}
	return NULL;
}

void _print_str(void* v){
	printf("%s", ((char*) v));
}

int main(){
  char a1[21], a2[21], a3[21], nome[21], *ptr, c;
  Node* n = NULL;

  while (scanf("%20s%c", nome, &c), c != '\n'){
		n = _insert_before(n, nome, sizeof(char*));
	}

  while(1){
		scanf("%20s", a1);

		/* if(! strcmp(a1, "mudar")){ */
		/* 	scanf("%20s", a2); */
		/* 	n = _change_direction(n); */
		/* } */

		/* else */
		if (! strcmp(a1, "sair")) // if equal
			break;

		else{
			scanf("%20s", a2);

			if(! strcmp(a1,"troca")){
				scanf("%20s\n", a3);
				n = _swap(n, a2, a3, _compare_str);
			}

			else if(! strcmp(a2,"+")){
				scanf("%20s\n", a3);
				n = _insert(n, a3, sizeof(char*), strtoul(a1, &ptr, 10));
			}
			else if(! strcmp(a2,"-")){
				scanf("%20s\n", a3);
				n = _remove(n, strtoul(a1, &ptr, 10));
			}
			else if(! strcmp(a2, "!")){
				Node* n1 = _walk(n, strtoul(a1, &ptr, 10));
				_print_str(n1->info);
			}
		}
	}
	_show(n, _print_str);
	free_nodes(n, n);	
}
