#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX 256

int main(int argc, char * argv[]) {
	char buffer[MAX];
	// Get current working directory
	getcwd(buffer, MAX);
	printf("cwd is %s\n", buffer);
	
	// chdir changes the cwd
	printf("%s\n", chdir("..") == 0 ? "cwd successfully changed to parent folder" : "error trying to change cwd");
	
	// a file called teste.txt must exist in cwd so it is created if it doesn't
	FILE * f = fopen("teste.txt", "wa");
	fclose(f);
	
	// 0777 is octal code for release all permissions of a file to user, its group and others
	int success = chmod("teste.txt", 0777);
	if (success == 0)
		printf("Permissions of file successfully changed\n");
	else
		printf("Could not change permissions of file\n");
		
	return 0;
}