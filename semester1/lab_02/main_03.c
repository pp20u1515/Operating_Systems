#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define N 2 

int main(void)
{
    char *param[2] = { "./lab_01/app.exe", "./lab_04/app.exe" };
    pid_t childpid[N];
    int status;
       
    for (size_t index = 0; index < N; index++)
    {
        childpid[index] = fork();
	    if (childpid[index] == -1)
	    {
	        perror("Can't fork.\n");
	        exit(1);
	    }
	    else if (childpid[index] == 0)
	    {
	        printf("Child process: ID = %d, PPID = %d, GROUP = %d\n",getpid(), getppid(), getpgrp());     
	        int rc = execl(param[index], param[index], NULL);
	        if (rc == -1)
	        {
	           	perror("Can't exec.\n");
	           	exit(1);
	        }
	    }
	    else 
	    {
	        printf("Parent process: PID = %d, GROUP = %d, child's ID = %d\n", getpid(), getpgrp(), childpid[index]);
          }
    }
    for (int i = 0; i < 2; i++)
    {
        pid_t w = waitpid(childpid[i], &status, WUNTRACED);
        if (w == -1)
        {
        	perror("Can't wait.\n");
        	exit(1);
        }
        
        printf("Child #%d has finished: PID = %d\n", i + 1, w);
    
        if (WIFEXITED(status))
          printf("Child #%d exited with code %d\n", i + 1, WEXITSTATUS(status));
        else if(WIFSIGNALED(status))
          printf("Child #%d terminated, recieved signal %d\n", i + 1, WTERMSIG(status));
        else if (WIFSTOPPED(status))
          printf("Child #%d stopped, recieved signal %d\n", i + 1, WSTOPSIG(status));   
     }
  	
    return 0;
}
