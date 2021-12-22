#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
	int rc = fork();
	if (rc < 0) {
		// fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		// child process
		printf("Child: start to write in q2.log\n");
		close(STDOUT_FILENO);
		// if printf goes after close(), it will not show up on the screen
		// since the standard output has been turned off
		open("./q2.log", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		
		// print hello world to q2.log
		char *myargs[3];
		myargs[0] = strdup("echo");
		myargs[1] = strdup("Hello World from child");
		myargs[2] = NULL;
		execvp(myargs[0], myargs);
	} else {
		// parent process
		//int rc_wait = wait(NULL);
		printf("Parent: start to write in q2.log\n");
		close(STDOUT_FILENO);
		open("./q2.log", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		
		// print hello world to q2.log
		char *myargs[3];
		myargs[0] = strdup("echo");
		myargs[1] = strdup("Hello World from parent");
		myargs[2] = NULL;
		execvp(myargs[0], myargs);
	}

	return 0;


}
