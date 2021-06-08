#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/resource.h>

#include <string.h>


int main(void)
{



        pid_t   pid, ppid;
        int     ruid, rgid, euid, egid;
        int     priority;
        char    msg_buf[100];
        int     msg_pipe[2];



        if(pipe(msg_pipe) == -1){
                perror("failed in Parent pipe creation:");
                exit(7);
        }


        printf("\nThis is the Parent process report:\n");
        pid  = getpid();
        ppid = getppid();
        ruid = getuid();
        euid = geteuid();
        rgid = getgid();
        egid = getegid();
        priority = getpriority(PRIO_PROCESS, 0);

        printf("\nPARENT PROG:  Process ID is:\t\t%d\n\
PARENT PROC:  Process parent ID is:\t%d\n\
PARENT PROC:  Real UID is:\t\t%d\n\
PARENT PROC:  Real GID is:\t\t%d\n\
PARENT PROC:  Effective UID is:\t\t%d\n\
PARENT PROC:  Effective GID is:\t\t%d\n\
PARENT PROC:  Process priority is:\t%d\n",
	pid, ppid, ruid, rgid, euid, egid, priority);

	printf("\nPARENT PROC: will now create child, write pipe,\n \
and do a normal termination\n");

        pid_t fork_pid;

        fork_pid = fork();

        if(fork_pid==-1){
                perror("Fork error.");
                exit(7);
        }
        else if(fork_pid>0){
                close(msg_pipe[0]);
                msg_buf[0] = (char)0;
                strcat(msg_buf, "\n===================\na formatted text string\n===================\n");
                write(msg_pipe[1], msg_buf, 100);
                close(msg_pipe[1]);
                exit(0);
        }
        else if(fork_pid==0){

                pid  = getpid();
                ppid = getppid();
                ruid = getuid();
                euid = geteuid();
                rgid = getgid();
                egid = getegid();
                priority = getpriority(PRIO_PROCESS, 0);

                printf("\nCHILD PROG:  Process ID is:\t\t%d\n\
        CHILD PROC:  Process parent ID is:\t%d\n\
        CHILD PROC:  Real UID is:\t\t%d\n\
        CHILD PROC:  Real GID is:\t\t%d\n\
        CHILD PROC:  Effective UID is:\t\t%d\n\
        CHILD PROC:  Effective GID is:\t\t%d\n\
        CHILD PROC:  Process priority is:\t%d\n",
                pid, ppid, ruid, rgid, euid, egid, priority);
                
                close(msg_pipe[1]);
                read(msg_pipe[0], msg_buf, 100);
		
		printf("CHILD PROC: parent's msg is %s\n", msg_buf);
		printf("CHILD PROC: Process parent ID now is:   %d\n",
                                                            getppid());
		printf("CHILD PROC: ### Goodbye ###\n");
		exit(0);
        }

