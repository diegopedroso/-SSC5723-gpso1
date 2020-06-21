#include <stdio.h>

int main(int argc, char * argv[]) {
	// open a file "teste.txt" for writing at the end of it or create a new one if it does not exist
	FILE * f = fopen("teste.txt", "wa");
	// write some content into the file
	fputs("Hello world!", f);
	// close the file
	fclose(f);

	return 0;
}
