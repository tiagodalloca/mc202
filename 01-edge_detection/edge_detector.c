/* RA 206341 */
/* TIAGO PEREIRA DALL'OCA */

/* O codigo eh bem autoexplicativo */

#include <math.h>   /*Biblioteca com a funcao de raiz quadrada*/
#include <stdio.h>  /*Biblioteca para input e output*/

#define WIDTH 128
#define HEIGHT 96

#define W WIDTH + 2
#define H HEIGHT + 2

char fx[3][3] = {
	{1, 0, -1},
	{2, 0, -2},
	{1, 0, -1}
};

char fy[3][3] = {
	{1, 2, 1},
	{0, 0, 0},
	{-1, -2, -1}
};


int apply_fliter(char filter[3][3], int matrix[H][W], unsigned int i, unsigned int j){
	int ret = 0;
	for (int c = 0; c < 3; ++c)
		for (int d = 0; d < 3; ++d)
			ret += filter[c][d]*matrix[i + c][j + d];
	return ret;
}

void convolute(char filter[3][3], int i_matrix[H][W], int o_matrix[HEIGHT][WIDTH]){
	for (int i = 0; i + 3 <= H; ++i)
		for (int j = 0; j + 3 <= W; ++j)
			o_matrix[i][j] = apply_fliter(filter, i_matrix, i, j); 
}

void apply_padding(int i_matrix[HEIGHT][WIDTH], int o_matrix[H][W]){
	for(int i = 0; i < W; ++i)
		o_matrix[0][i] = o_matrix[H - 1][i] = 0;
	
	for(int i = 1; i <= HEIGHT; ++i){
		o_matrix[i][0] = o_matrix[i][W - 1] = 0;
		for(int j = 1; j <= WIDTH; ++j)
			o_matrix[i][j] = i_matrix[i - 1][j - 1];
	}
}

void combine(int x[HEIGHT][WIDTH], int y[HEIGHT][WIDTH], int z[HEIGHT][WIDTH]){
	for(int i = 0; i < H; ++i)
		for(int j = 0; j < W; ++j)
			z[i][j] = floor(sqrt(pow(x[i][j], 2) + pow(y[i][j], 2)));
}

int main() {
	int A[HEIGHT][WIDTH];
	int B[H][W];
	int X[HEIGHT][WIDTH], Y[HEIGHT][WIDTH], Z[HEIGHT][WIDTH];

	for(int i = 0; i < HEIGHT; ++i)
		for(int j = 0; j < WIDTH; ++j)
			scanf("%d", &A[i][j]);
	
	apply_padding(A, B);
	convolute(fx, B, X);
	convolute(fy, B, Y);
	combine(X, Y, Z);

	for(int i = 0; i < HEIGHT; ++i){
		for(int j = 0; j < WIDTH; ++j)
			printf("%d ", Z[i][j]);
		printf("\n");
	}
	return 0;
}
