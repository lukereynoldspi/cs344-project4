// Luke Reynolds
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	// Pipe and fork initiation
	int pfd[2];
	pipe(pfd);
	pid_t pid = fork();

	// Child
	if(pid) {
		dup2(pfd[0], 0); 
		close(pfd[1]);
		execlp("wc", "wc", "-l", (char *) NULL);
	}

	// Parent
	dup2(pfd[1], 1);
	close(pfd[0]);
	execlp("ls", "ls", "-1a", argv[1], (char *) NULL);

}
