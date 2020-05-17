#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h"

struct Page {
	char address[9];
	Page *next;	
};

char *algoritmo, *filePath, line[20], tmpAddress[9];
int tampag, tammem, numpag, operacoes=0, leituras=0, escritas=0, writebacks=0;
FILE *file;
Page *first, *last;

void AddNewPage(char value[9]){
	Page *current = (Page*)malloc(sizeof(Page));
	strcpy(current->address, value);
	current->next = NULL;
	
	if(paginasused == 0){
		first = current;
		last = first;
	}
	else {
		last->next = current;
		last = current;
	}
	
	if(paginasused < numpag)
		paginasused++;
	
	escritas++;
}
// algoritmo de substituição a ser utilizado
void LRU(char value[9]){
	AddNewPage(value);
	if(paginasused == numpag)
		first = first->next;
}

void FIFO(char value[9]){
	AddNewPage(value);
	if(paginasused == numpag)
		first = first->next;
}

void Random(char value[9]){
	escritas++;
	srand(time(NULL));	
	int index = rand() % paginasused;
	Page *tmp = first;
	for(int i = 0; i < index; i++){
		tmp = tmp->next;
	}
	strcpy(tmp->address, value);
}

bool Find(char value[9]){
	Page *tmp = first, *prev = NULL;
	while(tmp != NULL){
		if(strcmp(tmp->address, value)==0){
			if(strcmp(algoritmo, "lru") == 0){
				if(prev != NULL){
					if(tmp->next != NULL)
						prev->next = tmp->next;							
				}
				else {
					first = first->next;
				}
				last->next = tmp;
				last = tmp;
				tmp->next = NULL;
			}

			return true;
		}
		prev = tmp;	
		tmp = tmp->next;
	}
	return false;
}

void ReplacePage(char value[9]){
	if(strcmp(algoritmo, "lru") == 0){
		LRU(value);
	}
	else if(strcmp(algoritmo, "random") == 0){
		Random(value);
	}
	else if(strcmp(algoritmo, "fifo") == 0){
		FIFO(value);
	}
	writebacks++;
}

void WriteAddress(char value[9]){
	if(paginasused < numpag){
		AddNewPage(tmpAddress);
	}
	else{
		faults++;
		ReplacePage(tmpAddress);
	}
}

void FreeMemory(){
	Page *tmp = first;
	while(tmp != NULL){
		free(tmp);
		tmp = tmp->next;
	}
	fclose(file);
}

int main(int argc, char *argv[]){
	algoritmo = argv[1];
	filePath = argv[2];
	tampag = atoi(argv[3]);
	tammem = atoi(argv[4]);

	if(tampag < 2 || tampag > 64){	
		printf("O tamanho de cada pagina precisa estar entre 2 e 64.");
		return 0;
	}
		
	if(tammem < 128 || tammem > 16384){
		printf("O tamanho da memoria precisa estar entre 128 e 16384.");
		return 0;
	}	
	
	if(strcmp(algoritmo, "lru") && strcmp(algoritmo, "fifo") && strcmp(algoritmo,"random")){
		printf("O algoritmo precisa ser LRU, FIFO ou Random.");
		return 0;	
	}
	
	numpag = tammem/tampag;
		
	if(strlen(filePath) > 0){
		file = fopen(filePath, "r");
		while(fgets(line, 20, file) != NULL){
			operacoes++;
			strncpy(tmpAddress, line, 8);
			tmpAddress[8] = '\0';
			if(line[9] == 'W' || line[9] == 'w'){
				WriteAddress(tmpAddress)
			}
			else{
				printf("ERRO: formato de dados incorreto.");
				return 0;	
			}	
		}
	}
	else{
		printf("ERRO: Arquivo de entrada inválido.");
		return 0;
	}
	
	printf("\nExecutando o Simulador\n");
	printf("Memoria: %iKB\n", tammem);
	printf("Paginas: %iKB\n", tampag);
	printf("Tecnica de Reposicao: %s\n", algoritmo);
	printf("Numero de Paginas: %i\n", numpag);
	printf("Operacoes no Arquivo de Entrada: %i\n", operacoes);
	printf("Operacoes de Leitura: %i\n", leituras);
	printf("Operacoes de Escrita: %i\n", escritas);
	
	FreeMemory();
	return 0;
}