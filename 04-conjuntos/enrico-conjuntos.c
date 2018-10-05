/* Enrico Delbuono - RA 196439 */

#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int info;
	struct no *prox;
} no;

/* Funcao que adiciona um novo no na lista analisada*/
no *novo_final(int elemento){
	no *novo = (no*) malloc(sizeof(no));
	novo->info = elemento;
	novo->prox = NULL;
	return novo;
}

no *novo_meio(int elemento,no *aux){
	no *novo = (no*) malloc(sizeof(no));
	novo->info = elemento;
	novo->prox = aux;
	return novo;
}

/* Funcao que imprime a lista inserida*/
void imprime(no *lista){
	if (lista != NULL && lista->prox != NULL){
		printf("%d,", lista->info);
		imprime(lista->prox);
	}
	else if (lista != NULL)
		printf("%d",lista->info);
}

no *insere(int elemento, no *lista){
	no *aux = lista->prox;
	if (lista->prox == NULL){
		no *novo = novo_final(elemento);
		lista->prox = novo;
		return lista;
	}
	else if (aux->info == elemento)
		return lista;
	else if (aux->info > elemento){
		no *novo = novo_meio(elemento,aux);
		lista->prox = novo;
		return lista;
	}
	else
		lista->prox = insere(elemento, lista->prox);
	return lista;
}

int pertence(int elemento, no *lista){
	if (lista->prox != NULL){
		if(lista->prox->info==elemento)
			return 1;
		else
			pertence(elemento,lista->prox);
	}
	else
		return 0;
}

no *remover(int elemento, no *lista){
	no *aux = lista->prox;
	if (lista->prox == NULL)
		return lista;
	else{
		if (aux->info == elemento){
			lista->prox = aux->prox;
			aux = NULL;
			return lista;
		}
		lista->prox = remover(elemento, lista->prox);
	}
	return lista;
}

no *uniao(no *lista1, no *lista2){
	no *aux = lista2->prox;
	if (lista2->prox == NULL)
		return lista1;
	else{
		lista1 = insere(aux->info, lista1);		
		uniao(lista1, lista2->prox);	
	}
	return lista1;
}

no *intersec(no *lista1, no *lista2){
	no *aux1 = lista1->prox, *aux2 = lista2->prox;
	if (lista1->prox == NULL && lista2->prox == NULL)
		return lista1;
	else if (lista1->prox == NULL)
		return lista1;
	else if (lista2->prox == NULL){
		lista1 = remover(aux1->info, lista1);
		intersec(lista1,lista2);
	}
	else if (aux1->info > aux2->info)
		intersec(lista1,lista2->prox);
	else if (aux1->info < aux2->info){
		lista1 = remover(aux1->info, lista1);
		intersec(lista1,lista2);
	}
	else
		intersec(lista1->prox,lista2->prox);
	return lista1;
}

no *subtracao(no *lista1, no *lista2){
	no *aux1 = lista1->prox, *aux2 = lista2->prox;
	if (lista1->prox == NULL || lista2->prox == NULL)
		return lista1;
	else if (aux1->info > aux2->info)
		subtracao(lista1, lista2->prox);
	else if (aux1->info < aux2->info)
		subtracao(lista1->prox,lista2);
	else{
		lista1 = remover(aux1->info,lista1);
		subtracao(lista1,lista2->prox);
	}
	return lista1;
}

int main(){
	int elemento, conjunto;
	no *v1, *v2;
	char comando;

	v1 = (no*) malloc(sizeof(no));
	v2 = (no*) malloc(sizeof(no));
	v1->prox = NULL;
	v2->prox = NULL;

	while (comando != 's'){
		scanf("%c",&comando);
		if (comando=='i'||comando=='p'||comando=='r'){
			scanf("%d %d",&elemento,&conjunto);
			if (comando=='i'){
				if (conjunto==1){
					v1 = insere(elemento,v1);
				}
				else{
					v2 = insere(elemento,v2);
				}
			}
			else if (comando=='p'){
				if (conjunto==1){
					if (pertence(elemento,v1)==1)
						printf("SIM\n");
					else
						printf("NAO\n");
				}
				else
					if (pertence(elemento,v2)==1)
						printf("SIM\n");
					else
						printf("NAO\n");
			}
			else if (comando=='r'){
				if (conjunto==1){
					v1 = remover(elemento,v1);
				}
				else{
					v2 = remover(elemento,v2);
				}
			}	
		}
		else if (comando=='u'){
			v1 = uniao(v1,v2);
		}
		else if (comando=='x'){
			v1 = intersec(v1,v2);
		}
		else if (comando=='b'){
			v1 = subtracao(v1,v2);
		}
		printf("{");
		imprime(v1->prox);
		printf("}\n");
		printf("{");
		imprime(v2->prox);
		printf("}\n");
		scanf(" ");
	}
	free(v1);
	free(v2);
	return 0;
}
