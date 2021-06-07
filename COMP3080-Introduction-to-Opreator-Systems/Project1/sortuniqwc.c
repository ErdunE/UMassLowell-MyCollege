/*
 * team members: Erdun E & Chenghai Cao
 * email: Erdun_E@student.uml.edu
 * email: Chenghai_Cao@student.uml.edu
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>


#define READ_END 0
#define WRITE_END 1


int main(int argc, char *arv[])
{
	int fd1[2];
	int fd2[2];

	//create pipe fd1
	if (pipe(fd1))
    {
		fprintf(stderr, "pipe error\n");
		exit(1);
	}
	//fork first child to run sort
	pid_t pid = fork();
	if (pid < 0)
    {
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	if (pid == 0)
    {
		printf("The child process running sort is %d\n", getpid());
		// tie write end of pipe fd1 to standard output (file descriptor 1)
		dup2(fd1[WRITE_END], 1);
		// close read end of pipe fd1
		close(fd1[READ_END]);
		// start the sort command using execlp
		execlp("/usr/bin/sort", "sort", NULL);
		//should not get here
		printf("Should not be here after execlp to sort.\n");
		exit(1);
	}


	//create second pipe fd2
	if (pipe(fd2))
    {
		fprintf(stderr, "pipe error\n");
		exit(1);
	}
	// fork second child
	pid = fork();

	if (pid < 0)
    {
		fprintf(stderr, "fork error\n");
		exit(1);
	}

	if (pid == 0)
    {
		printf("The child process running uniq is %d\n", getpid());
		// second child process, run uniq
		// tie read end of fd1 to standard input (file descriptor 0)
		dup2(fd1[READ_END], 0);
		// tie write end of fd2 to standard output (file descriptor 1)
		dup2(fd2[WRITE_END], 1);
		// close write end of pipe fd1
		close(fd1[WRITE_END]);
		// close read end of pipe fd2
		close(fd2[READ_END]);
		// start the uniq command using execlp
		execlp("/usr/bin/uniq", "uniq", NULL);
		//should not get here
		printf("Should not be here after execlp to uniq.\n");
		exit(1);// should not get here
	}

	//fork third child process
	pid = fork();
	if (pid < 0)
    {
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	if (pid == 0)
    {
		printf("The child process running wc is %d\n", getpid());
		// third child process, run wc -l
		// tie read end of fd2 to standard input (file descriptor 0)
		dup2(fd2[READ_END], 0);
		// close write end of pipe fd2
		close(fd2[WRITE_END]);
		// close read end of pipe fd1
		close(fd1[READ_END]);
		// close write end of pipe fd1
		close(fd1[WRITE_END]);
		// start the wc -l command using execlp
		execlp("/usr/bin/wc", "wc", "-l", NULL);
		//should not get here
		printf("Should not be here after execlp to wc -l.\n");
		exit(1);// should not get here
	}
	// parent process code
	// close both ends of pipes fd1 and fd2
	close(fd1[READ_END]);
	close(fd1[WRITE_END]);
	close(fd2[READ_END]);
	close(fd2[WRITE_END]);
	// wait for third process to end.
	wait(NULL);
}
