#include <stdio.h>

int main(){
	char p2[3];
	int h,w,maxg;
	scanf("%2s %d %d %d", p2, &h, &w, &maxg);

	unsigned int M[h][w];
	unsigned char mask = 0x03; // 00000011
	for(int i = 0; i < h; ++i)
		for(int j = 0; j < w; ++j)
			scanf("%u", &M[i][j]);
	
	unsigned char frase[1000];
	unsigned char letra = 0x0;
	int k = 1;
	for(int i = 0; i < h; ++i)
		for(int j = 0; j < w; ++j){
			unsigned char last_bits = mask & M[i][j];
			if (k <= 4){
				letra <<= 2;
				letra |= last_bits;
				k++;
			}
			else {
				frase[(i*w + j)/4 - 1] = letra;
				if (letra == '\0'){
					i = h; j = w; break;
				}
				k = 2;
				letra = last_bits;
			}
		}
	printf("%s", frase);
}
