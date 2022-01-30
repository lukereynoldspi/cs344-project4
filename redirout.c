// Luke Reynolds
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	// argc check
	if(argc < 3) {
		perror(":( Minimum number of arguments not reached (3)");
		exit(0);
	}

	// Opens/creates file, pipes and forks child
	int fd = open(argv[1], O_RDWR | O_CREAT);
	int pfd[2];
	pipe(pfd);
	pid_t pid = fork();

	// Child
	if(pid) {
		dup2(pfd[1], 1); 
		close(pfd[0]);
		execvp(argv[2], argv + 2);
	}

	// Parent
	close(pfd[1]);
	char *buf[2048];

	// Reads from pipe, writes to output file
	int final_bytes = read(pfd[0], buf, sizeof buf);
	while (final_bytes) {
		write(fd, buf, final_bytes);
		break;
	}
	
	// Closes pipe and output file
	close(pfd[0]);
	close(fd);

}
