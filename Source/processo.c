#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
	// Create a process
	int pid = fork();
	// fork returns child's pid in parent's run
	if (pid != 0) {
		printf("I am parent and my child pid is %d\n", pid);
		printf("Parent process waiting for child to terminate...\n");
		// parent gets blocked until pid process terminates
		waitpid(pid, NULL, 0);
		printf("Parent process done!\n");
	} else {
		// getpid returns the pid of runing process
		printf("I am child and my pid is %d\n", getpid());
		printf("Child process executing...\n");
		printf("Child process done!\n");
	}
	return 0;
}