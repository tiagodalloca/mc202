#include<stdio.h>
#include <stdlib.h>

typedef struct No {
	int info ;
	struct No * prox ;
} No ;

No * criar_no ( int val ) {
	No * no = ( No *) malloc ( sizeof ( No )) ;
	if ( no == NULL )
		exit (1) ;
	no -> info = val ;
	no -> prox = NULL ;
	return no ;
}

void remover_lista ( No *lista , int val ) {
	if(lista->prox != NULL){
		if ( (lista -> prox)->info == val ){
			No* aux = lista->prox;
			lista->prox = lista->prox->prox;
			free (aux);
		}
		else{
			remover_lista ( lista->prox , val );
		}
	}
}

No * buscar_lista ( No * lista , int val ) {
	if(lista == NULL)
		return NULL;
	if ( lista -> info == val )
		return lista ;
	return buscar_lista ( lista -> prox, val );
}

void insercao (No * lista,int l){
	No *novo = criar_no(l);
	if (lista->prox == NULL){
		lista->prox = novo;
		return;
	}
	if (lista->prox->info > l){
		novo->prox = lista->prox;
		lista->prox = novo;
	}
	else{
		insercao(lista->prox, l);
	}
}

void uniao (No *lista1, No *lista2){
	if (buscar_lista(lista1, lista2->info) != NULL)
		insercao(lista1, lista2->info);
	if (lista2->prox != NULL)
		uniao(lista1, lista2->prox);
}

void interseccao(No *lista1, No *lista2){
	if (lista1->prox != NULL){
		if (buscar_lista(lista2, lista1->prox->info) == NULL)
			remover_lista(lista1, lista1->prox->info);
		if (lista1->prox->prox != NULL)
			interseccao(lista1->prox, lista2);
	}
}

void subtracao(No *lista1, No *lista2){
	if(lista2->prox != NULL){
		if (buscar_lista(lista1, lista2->prox->info) != NULL)
			remover_lista(lista1, lista2->prox->info);
		if (lista2->prox->prox != NULL)
			subtracao(lista1, lista2->prox);
	}
}
void pertence (No *lista , int val){
	if (buscar_lista(lista, val) != NULL)
		printf ("SIM\n");
	else
		printf ("NAO\n");
}

void imprimir_lista ( No * lista ) {
	if ( lista->prox != NULL ) {
		printf ("% d ", lista -> prox ->info );
		imprimir_lista ( lista -> prox );
	}
}

int main(){
	char v = 'o';
	int n, l;

	No * lista1 ;
	lista1 = ( No *) malloc ( sizeof ( No ));
	lista1 -> prox = NULL ;

	No * lista2 ;
	lista2 = ( No *) malloc ( sizeof ( No ));
	lista2 -> prox = NULL ;

	while (v != 's'){
		if (v == 'i' ){
			scanf("%d", &n);
			scanf("%d", &l);
			if(l==1)
				insercao(lista1,n);
			else
				insercao(lista2,n);
			printf ("{");
			imprimir_lista(lista1);
			printf ("}\n");
			printf ("{");
			imprimir_lista(lista2);
			printf ("}\n");
		}
		if (v== 'p'){
			scanf("%d", &n);
			scanf("%d", &l);
			if(l==1)
				pertence(lista1,n);
			else
				pertence(lista2,n);
			printf ("{");
			imprimir_lista(lista1);
			printf ("}\n");
			printf ("{");
			imprimir_lista(lista2);
			printf ("}\n");
		}
		if (v== 'r'){
			scanf("%d", &n);
			scanf("%d", &l);
			if(l==1)
				remover_lista(lista1,n);
			else
				remover_lista(lista2,n);
			printf ("{");
			imprimir_lista(lista1);
			printf ("}\n");
			printf ("{");
			imprimir_lista(lista2);
			printf ("}\n");
		}
		if (v== 'u'){
			uniao(lista1,lista2);
			printf ("{");
			imprimir_lista(lista1);
			printf ("}\n");
			printf ("{");
			imprimir_lista(lista2);
			printf ("}\n");
		}
		if (v== 'x'){
			interseccao(lista1,lista2);
			printf ("{");
			imprimir_lista(lista1);
			printf ("}\n");
			printf ("{");
			imprimir_lista(lista2);
			printf ("}\n");
		}
		if (v== 'b'){
			subtracao(lista1,lista2);
			printf ("{");
			imprimir_lista(lista1);
			printf ("}\n");
			printf ("{");
			imprimir_lista(lista2);
			printf ("}\n");
		}
		scanf("%s", &v);
	}
	printf ("{");
	imprimir_lista(lista1);
	printf ("}\n");
	printf ("{");
	imprimir_lista(lista2);
	printf ("}\n");

	return 0;
}
