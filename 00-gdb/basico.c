#include <stdio.h>

int main() {
  int   i, j;

  for( i = 0; i < 10; i++ ) {
    for( j = 0; j < 10; j++ ) {
      printf( "(%d, %d) ", i, j );
    }
    printf( "\n" );
  }

  return 0;

}

/* Ajuda! */

/* Objetivo do programa: imprimir pares ordenados da forma (linha,coluna) */

/* As linhas sao contadas como 0, 1, 2, ..., 8, 9 */
/* As colunas sao contadas como 0, 1, 2, ..., 8, 9 */

/* Metodo: Um loop para repetir comandos para cada uma das linhas */
/*         Um loop para repetir comandos para cada uma das colunas */
