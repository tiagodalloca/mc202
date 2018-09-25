#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/************************************* Estruturas *************************************/
/* Declara estrutura da Database, com espaço extra para as strings.                   */
typedef struct{
  char CPF[12];
  char Name[41];
  char Email[31];
  int Age;
} Database;

/************************************* Funções ***************************************/
int biggerCPF(char CPF1[11], char CPF2[11]){
  int w;
  for(w = 0; w < 11; w++){
    if(CPF1[w] > CPF2[w])
      return 1;
    else if(CPF1[w] < CPF2[w])
      return 0;
	}
  return 0;
}

/* A função de ordenação é um insertion sort que é chamado conforme a database é pre-*/
/* enchida, isso a tornará mais eficiente uma vez que a cada item adicionado a lista */
/* anterior já estará ordenada                                                       */
void sortDatabase(int n,Database v[]){
  int i,j;
  Database Temporary;
  for(i = 0; i < n; i++){
    Temporary = v[i];
    j = i - 1;
    while(j >= 0 && v[j].Age == Temporary.Age && biggerCPF(v[j].CPF,Temporary.CPF)){
			v[j+1] = v[j];
			j = j - 1;
		}
    v[j+1] = Temporary;
  }
}


/* A função que recebe a database irá receber os n valores da dabatabase e os ordenará */
/* conforme eles são adicionados na Database                                           */
int receiveDatabase(Database v[]){
  int i = 0;
  while(scanf("%[^,],%[^,],%[^,],%d\n", v[i].CPF, v[i].Name, v[i].Email, &v[i].Age)!=EOF){
    i++;
  }
  return i;
}

/* Essa função irá apenas escrever a database no arquivo de saída                     */
void writeDatabase(int n, Database v[]){
  int i;
  for(i = 0; i < n; i++)
    printf("%s, %s, %s, %i \n",v[i].CPF,v[i].Name,v[i].Email,v[i].Age);
}

/************************************** Main ****************************************/
int main(){
  int n = 500;
  Database *v;
  v = malloc(500*sizeof(Database));
  n = receiveDatabase(v);
  sortDatabase(n,v);
  writeDatabase(n, v);
  free(v);
  return 0;
}
