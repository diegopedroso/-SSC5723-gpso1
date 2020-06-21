#include <stdio.h>

#define MAX 8000000

int main(int argc, char * argv[]){
	FILE * f = fopen("teste.dat", "wb");
	char vet[MAX];
	
	// writes each byte at once
	for(int i = 0; i < MAX; ++i){
		vet[i] = (char) i;
		fwrite(vet + i, sizeof(char), 1, f);
	}

	// write the whole vector at once
	fwrite(vet, sizeof(char), MAX, f);

	fclose(f);
}