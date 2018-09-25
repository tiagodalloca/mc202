// TIAGO PEREIRA DALL'OCA
// RA 206341

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char cpf[12];
	char nome[41];
	char email[31];
	unsigned char idade;
} Person;


/*
	Função de comparação de duas pessoas.
	Retorna > 0 se p1 > p2, 0 de p1 == p2 e < 0 se p1 < p2
*/
char compare_persons(Person p1, Person p2){
	if (p1.idade > p2.idade)
		return 1;
	else if (p1.idade < p2.idade)
		return -1;
	return strcmp(p1.cpf, p2.cpf);
}

/*
	Faz leitura das linhas e retrona uma ponteiro de ponteiros de void.
	Na primeira posição do array está o ponteiro com o número de linhas,
	na segunda está os ponteiro de ponteiros de pessoas.
*/
void** read_rows(){
	Person** persons = (Person**) malloc(500 * sizeof(Person*)); 
	unsigned short rows_count = -1;
	Person* p;
	do {
		rows_count++; 
		persons[rows_count] = (Person*) malloc(sizeof(Person));
		p = persons[rows_count];
	} while(scanf("%[^,],%[^,],%[^,],%u\n",
								p->cpf, p->nome, p->email, (unsigned int*) &p->idade) != -1);

	void** ret = (void**) malloc(sizeof(unsigned short*) + sizeof(Person**));
	ret[0] = (int*) malloc(sizeof(int)); 
	*((unsigned short*) ret[0]) = rows_count;
	ret[1] = (void*) persons; 
	return ret;
}


/*
	Implementação do quicksort para pessoas
*/
void sort(Person** persons, unsigned short len){
	if (len <= 1)
		return;

	Person* pivot = persons[len / 2];
	unsigned short i, j;
	for (i = 0, j = len - 1; ; i++, j--) {
		while (compare_persons(*persons[i], *pivot) < 0)
			i++;
		while (compare_persons(*persons[j], *pivot) > 0)
			j--;
 
		if (i >= j)
			break;
 
		Person* aux = persons[i];
		persons[i] = persons[j];
		persons[j] = aux;
	}
 
	sort(persons, i);
	sort(persons + i, len - i);
}

int main(){
	// lê as pessoas
	void** rows_count_and_persons = read_rows();

	unsigned short rows_count = *((unsigned short*) rows_count_and_persons[0]);
	Person** persons = (Person**) rows_count_and_persons[1];

	// ordena
	sort(persons, rows_count);

	// printa no stdout
	for(unsigned int i = 0; i < rows_count; i++){
		printf("%s, %s, %s, %u\n",
					 persons[i]->cpf,
					 persons[i]->nome,
					 persons[i]->email,
					 (unsigned int) persons[i]->idade);
		free(persons[i]);
	} 

	free((unsigned short *) rows_count_and_persons[0]);
	free(persons);
	free(rows_count_and_persons);
	return 0;
}
