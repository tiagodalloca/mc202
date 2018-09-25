#include <stdio.h>

void quicksort(int* vet, int len){
	if (len <= 1)
		return;
	int pivo = vet[len / 2];
	int i, j, aux;
	for(i = 0, j = len - 1; ; i++, j--){
		while(vet[i] < pivo) i++;
		while(vet[j] > pivo) j--;
		if (i >= j) break;
		aux = vet[i];
		vet[i] = vet[j];
		vet[j] = aux;
	}
	quicksort(vet, i);
	quicksort(vet + i, len - i);
}

int main(int argc, char** args){
	int vet[] = {5, 3, 4, 1, 2, 6};
	quicksort(vet, 6);
	for(int i = 0; i < 6; i++)
		printf("%d\n", vet[i]);
	return 0; 
}
