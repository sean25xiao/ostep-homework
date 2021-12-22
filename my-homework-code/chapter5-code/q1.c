#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
	int x = 100;
	int rc = fork();
	if (rc < 0) {
		// fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		// child process
		// When both parent and child process change the value of x, there is no conflict
		// Because child process create a new address space and copy the data to the copied AS. So it changes the variable x in its own AS instead of the parent process's
		printf("child: before change, x = %d\n", x);
		x = 200;
		printf("child: after  change, x = %d\n", x);
	} else {
		// parent process
		//int rc_wait = wait(NULL);
		printf("parent: before change, x = %d\n", x);
		x = 300;
		printf("parent: after  change, x = %d\n", x);
	}

	return 0;
}
