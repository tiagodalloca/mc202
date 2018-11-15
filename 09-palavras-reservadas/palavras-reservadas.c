// TIAGO PEREIRA DALL'OCA RA 206341
// Código  da árvore é bem simples semelhante ao do Hélio
// Nem tem muito o que comentar na real
// Gente, desculpa. Comentar é muito difícil.
// Por favor não peguem pesado na correção
// Amo vocês <3 FELIZ 2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* RESERVED_WORDS[32] = {
	"auto",
	"double", 
	"int", 
	"struct",
	"break",
	"else", 
	"long",
	"switch", 
	"case",
	"enum",
	"register",
	"typedef",
	"char",
	"extern",
	"return",
	"union", 
	"continue",
	"for",
	"signed",
	"void",
	"do",
	"if",
	"static",
	"while",
	"default",
	"goto",
	"sizeof",
	"volatile",
	"const",
	"float",
	"short",
	"unsigned"
};

typedef struct Tree{
	char* val;
	struct Tree* lt;
	struct Tree* rt; 
} Tree;

struct Stack{
	unsigned int max;
	long current;
	void** stack;
	size_t size_info;
} stack_default = {50, -1, NULL, sizeof(char*)};

typedef struct Stack Stack;

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
}

void _stack_push(Stack* s, void* v){
	s->stack[++s->current] = v;
}

void _stack_copy(Stack* s1, Stack* s2){
	if(_is_stack_empty(*s1)){
		s2->current = -1;
		return;
	}
	
	for(int i = 0; i <= s1->current; i++){
		s2->stack[i] = s1->stack[i];
	}
	s2->current = s1->current;
	s2->max = s1->max;
	s2->size_info = s1->size_info;
}

int max(int a, int b){
  return a >= b? a:b;
}

Tree* node(char* val){
  Tree* t = (Tree*) malloc(sizeof(Tree));
  t->val = val;
  t->rt = NULL;
  t->lt = NULL;
  return t;
}

int height ( Tree* t ) {
  if ( t == NULL ) return 0;
  int h_lt = 1 + height( t->lt );
  int h_rt = 1 + height( t->rt );
  return h_lt > h_rt? h_lt:h_rt;
}

Tree *rotate_right(Tree *y) 
{ 
	Tree *x = y->lt; 
	Tree *aux = x->rt;
  
	x->rt = y; 
	y->lt = aux;

	return x; 
} 
  
Tree *rotate_left(Tree *x) 
{ 
	Tree *y = x->rt;
	Tree *aux = y->lt;

	y->lt = x;
	x->rt = aux;
  
	return y;
}

int balance(Tree* t) { 
	if (t == NULL) 
		return 0; 
	return height(t->lt) - height(t->rt);  
} 

Tree* insert_tree(Tree* t, char* val){
  if (t == NULL) return node(val);

  if (strcmp(val, t->val) < 0) 
    t->lt  = insert_tree(t->lt, val); 
  else if (strcmp(val, t->val) > 0)
		t->rt = insert_tree(t->rt, val);
  else
    return t;

	int b = balance(t); 
  
	if (b > 1 && strcmp(val, t->lt->val) < 0) 
		return rotate_right(t); 

	if (b < -1 && strcmp(val, t->rt->val) > 0 )
		return rotate_left(t);
  
	if (b > 1 && strcmp(val, t->lt->val) > 0) { 
		t->lt = rotate_left(t->lt); 
			return rotate_right(t);
	} 

	if (b < -1 && strcmp(val, t->rt->val) < 0) {
		t->rt = rotate_right(t->rt); 
		return rotate_left(t); 
	} 
	
	return t;
}

void free_tree(Tree* t){
  if (t == NULL) return;
  free_tree(t->lt);
  free_tree(t->rt);
	free(t);
}

void print_node(Tree* t){
	if(t != NULL)
		printf("%s ", t->val);
}

void print_zig_zag(Tree* t){
	printf("O percurso da árvore é:\n");
	
	if(t == NULL)
		return;

	char left = 0;

	Stack s1 = stack_default;
	Stack s2 = stack_default;
	s1.stack = (void**) malloc(sizeof(char*) * s1.max);
	s2.stack = (void**) malloc(sizeof(char*) * s2.max);

	_stack_push(&s1, t);
	do{
		printf("[ ");
		for(t = (Tree*) _stack_pop(&s1); t != NULL; t = _stack_pop(&s1)){
			print_node(t);
			if (left) {
				if(t->lt != NULL)
					_stack_push(&s2, t->lt);
				if(t->rt != NULL)
					_stack_push(&s2, t->rt);
			}
			else {
				if(t->rt != NULL)
					_stack_push(&s2, t->rt);
				if(t->lt != NULL)
					_stack_push(&s2, t->lt);
			}
		}
		printf("]\n");
		_stack_copy(&s2, &s1);
		s2.current = -1;
		left = ! left; // essa flag cuida de que o zig-zag seja obedecido
	} while(!_is_stack_empty(s1));

	free(s1.stack);
	free(s2.stack);
}

char is_ok_char(char c){
	static char OK_CHARS[] = {
		'{', '}', '(', ')', '[', ']', ' ', '\n', '\t', ';', ':'
	};
	static unsigned char ok_len = 11;
	for(unsigned short s = 0; s < ok_len; s++)
		if(c == OK_CHARS[s])
			return 1;
	return 0;
}

char* is_reserved_word(char* word){
	for(unsigned char i = 0; i < 32; i++) {
		char* s = strstr(word, RESERVED_WORDS[i]);
		if (s != NULL){
			unsigned short word_pos = s - word;
			unsigned short len_rw = strlen(RESERVED_WORDS[i]);
			if((word_pos == 0 || is_ok_char(s[-1]))
				 && (word_pos + len_rw == strlen(word)
						 || is_ok_char(s[len_rw])))
				return RESERVED_WORDS[i];
		}
	}
	return NULL;
}

int main(){
	
	Tree* t = NULL;

	char word[201];
	
	while(scanf("%100s", word) != EOF){
		char* w = is_reserved_word(word);
		if(w != NULL)
			t = insert_tree(t, w);
	}

	print_zig_zag(t);

	free_tree(t);

  return 0;
}
