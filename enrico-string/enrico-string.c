#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[argc]){
	char string1[100], string2[100];
	char frequencia[128];

	scanf("%s %s", string1, string2);
	
	if (strlen(string1) != strlen(string2)){
		printf("false\n");
		return 0;
	}

	for (unsigned int i = 0; i < strlen(string1); ++i) 
		frequencia[(int) string1[i]]++;

	for (unsigned int i = 0; i < strlen(string2); ++i){
		if (frequencia[(int) string2[i]] == 0) {
			printf("false\n");
			return 0;
		}
		else
			frequencia[(int) string2[i]]--;
	}

	printf("true\n");

	return 0;
}
