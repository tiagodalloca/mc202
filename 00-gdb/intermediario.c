#include <stdio.h>

/* ESTE PROGRAMA POSSUI UM ERRO! Voce deve conserta-lo como um exercicio */

int main() {
  int   i, j, auxiliar;
  int   numero[10]; 

	for( i = 0; i < 10; i++ ) {
		scanf("%d", numero + i);
		/* Troquei essa linha primeiro porque estava tendo problemas com a leitura.*/
	}

  for( i = 0; i < 10; i++ ) {
		for( j = i + 1; j < 10; j++ ) {
			if( numero[j] < numero[i] ) {
				auxiliar = numero[i];
				numero[i] = numero[j];
				numero[j] = auxiliar;
				/* antes mesmo de conseguir executar o gdb com a leitura do teclado, 
					 já percebi que o problema era aqui, na troca errada das variáveis */
			}
		}
  }

  printf( "Os numeros ordenados ficam assim: \n" );

  for( i = 0; i < 10; i++ ) {
    printf( "%d ", numero[i] );
  }

  /* sem a quebra de linha, o prompt do terminal sairia na mesma linha
   * da saida do nosso programa */
  printf( "\n" );

  return 0;

}


/* Ajuda! */

/* Objetivo do programa: ordenar um array de inteiros usando o algoritmo
 * selection-sort */

/* Metodo: descobrir o elemento que deve ocupar cada posicao do array,
 *         um de cada vez. O loop em i controla a posicao que estamos
 *         resolvendo e o loop em j controla os possiveis candidatos a
 *         ocuparem a posicao indicada por i. Quando um candidato em j
 *         eh mais apto do aquele que esta na posicao i, eles trocam de
 *         lugar. */
