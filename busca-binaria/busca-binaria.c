#include <stdio.h>

char busca_binaria(int* vetor, int key, int size){
	int inicio = 0;
	int fim = size - 1;
	int meio = 0;
	while (inicio <= fim){
		meio =  (fim - inicio) / 2 + inicio;
		if (vetor[meio] == key)
			break;
		else if (vetor[meio] < key)
			inicio = ++meio;
		else
			fim = --meio;
		meio++;
	}
	return meio;
}
	

int main(){
	int v[] = {0, 2, 3, 4, 6, 7};
	int k = busca_binaria(v, -1, 6);
	printf("%d\n", k);
}
