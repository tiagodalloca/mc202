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
} stack_default = {30, -1, NULL, sizeof(Register)};

typedef struct Stack Stack;

void _insert_before(Node** n, void* v, size_t s){
	Node* nn = (Node*) malloc(sizeof(Node));
	nn->info = malloc(s);
	memcpy(nn->info, v, s);
	nn->size_info = s;
	if(n[0] == NULL){
		n[0] = nn;
		nn->next = nn;
		nn->prev = nn;
	}
	else{
		nn->prev = n[0]->prev;
		nn->next = n[0];
		n[0]->prev->next = nn;
		n[0]->prev = nn; 
		n[0] = nn;
	}
}

void _insert_after(Node** n, void* v, size_t s){
	Node* nn = (Node*) malloc(sizeof(Node));
	nn->info = malloc(s);
	memcpy(nn->info, v, s);
	nn->size_info = s;
	if(n[0] == NULL)
		n[0] = nn;
	nn->next = n[0]->next;
	nn->prev = n[0];
	n[0]->next = nn;
}

void _remove_node(Node** n){
	if(n[0]->next == n[0]){
		free(n[0]->info);
		free(n[0]);
		n[0] = NULL;
		return;
	}

	Node* next =  n[0]->next;
	Node* prev = n[0]->prev;
	free(n[0]->info);
	free(n[0]);
	next->prev = prev;
	prev->next = next;
	n[0] = next;
}

void* _stack_peek(Stack s){
	return s.stack[s.current];
}

char _is_stack_empty(Stack s){
	return s.current < 0;
}

void* _stack_pop(Stack* s){
	if (! _is_stack_empty(*s)){
		void* ret = _stack_peek(*s);
		s->current--;
		return ret;
	}
	return NULL;
};

void _stack_push(Stack* s, void* v){
	s->stack[++s->current] = v;
}

void _print(void* v){
	Register* r = ((Register*) v);
	printf("%hu,%s,%s\n", r->id, r->cpf, r->name);
}

void _insert_queue(unsigned short n, Node** q, Node** db){
	Register* p = (Register*) malloc(sizeof(Register));
	
	for(int i = n; i > 0; i--){
		scanf("%11s,%30[^\n]s", p->cpf, p->name);
		if (!p->cpf[0]){i++; continue;} // garante que está sendo lido alguma coisa

		p->id = (db[0] == NULL? 0:((Register*)db[0]->info)->id) + 1;
		_insert_before(q, p, sizeof(Register));
		_insert_before(db, p, sizeof(Register));
	}

	free(p);
}

void _remove_queue(unsigned short n, Node** q, Stack* s){
	for(unsigned short i = n; i > 0; i--){
		Register p = *((Register*) q[0]->prev->info);
		Register* pp = (Register*) malloc(sizeof(Register));
		*pp = p;
		_stack_push(s, pp);
		q[0] = q[0]->prev;
		_remove_node(q);
	}
}

void _make_it_so(Node** q, Stack s){
	printf("[Q]");
	if (q[0] != NULL){
		// printa queue
		Node* aux = q[0]->prev;
		for(; aux != q[0]; aux = aux->prev)
			printf("%d,", ((Register*) aux->info)->id);
		unsigned short id =	((Register*) aux->info)->id;
		if(id) printf("%d,", id);
	}
	printf("\n");

	// printa as stacks
	for(unsigned char sc = 1; sc <= 6; sc++){
		printf("[S%d]", sc);
		unsigned char n = (sc - 1)*5;
		for(unsigned char cs = 1; cs <= 5 && n <= s.current;
				cs++, n = (sc - 1)*5 + cs - 1)
			// umas contas loucas pra printar as stacks corretamente
			printf("%d,", ((Register*) s.stack[n])->id);
		printf("\n");
	}
}

void _remove_stack(unsigned short n, Stack* s){
	// remove os rolês da stack
	for(; n > 0; n--)
		free(_stack_pop(s));
}

void _show(Node* n, Node* last){
	// mostra tudo
	_print(n->info);
	if(n != last)
		_show(n->prev, last);
}


int main(){
  unsigned short n;
	char c;
	
	Node *q, *db; 
	q = db = NULL;
	Stack s = stack_default;
	s.stack = malloc(sizeof(Register*)*30);

	while(1){
		scanf("%c", &c);
		if(c == 'S'){
			scanf("%c", &c);
			scanf("%hu", &n);
			_remove_stack(n, &s); 
		}
 
		else if(c == 'Q'){
			scanf("%c", &c);
			scanf("%hu", &n);
			if(c == 'R')
				_remove_queue(n, &q, &s);
			else
				_insert_queue(n, &q, &db);
		}

		else if(c == 'P')
			_make_it_so(&q, s);

		else if(c == 'D')
			break;
	}
	
	_show(db->prev, db);
	fflush(stdout);

	// limpeza dos rolês do baragauê
	free(s.stack);
	while(db != NULL) _remove_node(&db);
	while(q  != NULL) _remove_node(&q); 

	return 0;
}
