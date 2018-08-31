#include <stdio.h>

int main(){
	char p2[3];
	int h,w,maxg;
	scanf("%2s %d %d %d", p2, &h, &w, &maxg);
	unsigned char frase[100000];
	unsigned char letra = 0x0;
	int k = 1;
	for(int i = 0; i < h; ++i)
		for(int j = 0; j < w; ++j){
			unsigned int u;
			scanf("%u", &u);
			unsigned char last_bits = 0x03 & u;
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
