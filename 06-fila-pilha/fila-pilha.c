/* TIAGO PEREIRA DALL'OCA */
/* RA 206341 */

/* O programa contem alguns comentários mas no geral é bem autoexplicativo */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	void* info;
	struct Node* next;
	struct Node* prev;
	size_t size_info;
} Node;

typedef struct Register{
	unsigned short id;
	char cpf[12];
	char name[31];
} Register;

struct Stack{
	unsigned int max;
	long current;
	void** stack;
	size_t size_info;
} stack_default = {30, 0, NULL, sizeof(Register)};

typedef struct Stack Stack;

void _insert_before(Node** n, void* v, size_t s){
	Node* nn = (Node*) malloc(sizeof(Node));
	nn->info = malloc(s);
	memcpy(nn->info, v, s);
	nn->size_info = s;
	nn->prev = n[0]->prev;
	nn->next = n[0];
	n[0] = nn;
}

void _insert_after(Node** n, void* v, size_t s){
	Node* nn = (Node*) malloc(sizeof(Node));
	nn->info = malloc(s);
	memcpy(nn->info, v, s);
	nn->size_info = s;
	nn->next = n[0]->next;
	nn->prev = n[0];
	n[0]->next = nn;
}

void _remove_node(Node** n){
	Node* next =  n[0]->next;
	Node* prev = n[0]->prev;
	free(n[0]->info);
	free(n[0]);
	next->prev = prev;
	prev->next = next;
	n[0] = next;
}


void _remove(Node** n, Node* f, void* r, int (*compar)(void*, void*)){
	if(n[0] == NULL)
		return;

	if (!compar(n[0]->info, r)){
		_remove_node(n);
	}
	
	else if (n[0]->next != f)
		_remove(&(n[0]->next), f, r, compar);
}

Node* free_nodes(Node* n) {
	if (n != NULL) {
		free_nodes(n->next);
		free(n->info);
		free(n);
	}
	return NULL;
}

void* _stack_peek(Stack s){
	return s.stack[s.current];
}

char _is_stack_empty(Stack s){
	return s.current < 0;
}

void* _stack_pop(Stack s){
	if (! _is_stack_empty(s)){
		void* ret = _stack_peek(s);
		s.current--;
		return ret;
	}
	return NULL;
};

void _stack_push(Stack s, void* v){
	s.stack[s.current++] = v;
}

void _print(void* v){
	Register* r = ((Register*) v);
	printf("%hu,%s,%s", r->id, r->cpf, r->name);
}

void _insert_queue(unsigned short n, Node** q, Node** db, Stack s){
	Register* p = (Register*) malloc(sizeof(Register)); 
	for(int i = n; i > 0; i--, scanf("%11s,%30s\n",
																	 p->cpf, p->name)){
		Register* aux = ((Register*) (q[0] == NULL? _stack_peek(s):q[0]->info));
		p->id = (aux == NULL? 0:aux->id) + 1;
		_insert_before(q, p, sizeof(Register));
		_insert_before(db, p, sizeof(Register));
	}
}

void _remove_queue(unsigned short n, Node** q, Stack s){
	for(unsigned short i = n; i > 0; i--){
		Register p = *((Register*) q[0]->prev->info);
		Register* pp = (Register*) malloc(sizeof(Register));
		*pp = p;
		_stack_push(s, pp);
		q[0] = q[0]->prev;
		_remove_node(q);
		if (q[0] != NULL)
			q[0] = q[0]->next;
	}
}

void _make_it_so(Node** q, Stack s){
	Node* aux = q[0]->prev;
	printf("[Q]");
	for(; aux != q[0]->prev; aux = aux->prev)
		printf("%d", ((Register*) aux->info)->id);

	for(unsigned char sc = 1; sc <= 6; sc++){
		printf("\n[S%d]", sc);
		for(unsigned char cs = 1; cs <= 5 && sc*cs - 1 <= s.current; cs++)
			printf("%d", ((Register*) s.stack[sc*cs - 1])->id);
	}
}

void _show(Node* n, Node* e){
	_print(n->info);
	if (n != e)
		_show(n->next, e);
}

void _remove_stack(unsigned short n, Stack s){
	for(; n > 0; n--)
		_stack_pop(s);
}

int main(){
	char c1;
	unsigned short d;
	Node* list, backup;
	Stack s = stack_default;
	s.stack = malloc(sizeof(Register*)*30);

	scanf("%c", &c1);
	if(c1 == 'S'){
		scanf("%c", &c1);
		scanf("%hu", &d);
		if(c1 == 'R')
			_remove_stack(d, s);
	}
	/* else if() */
}
