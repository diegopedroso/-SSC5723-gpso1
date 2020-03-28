#define MAX 1000

int main(int argc, char * argv[]) {
	int matrix[MAX][MAX];
	for(int i = 0; i < MAX; ++i)
		for(int j = 0; j < MAX; ++j)
			matrix[i][j] = i * j;
}