#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    pid_t childpid[2], w;
    int status;
    char ch;
    int pipefd[2];
    // char *messages[] = {"123\n", "123456789\n"};
    if (pipe(pipefd) == -1)
    {
        perror("Can't pipe.\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < 2; ++i)
    {
        childpid[i] = fork();
        if (childpid[i] == -1)
        {
            perror("Can't fork.\n");
            exit(EXIT_FAILURE);
        }
        else if (childpid[i] == 0)
        {
            printf("Child process: PID = %d, PPID = %d, PGRP = %d\n", getpid(), getppid(), getpgrp());
            char *messages[] = { "ffffffff", "sssss" };
            printf("--------%s\n",messages[i]);
            close(pipefd[0]);
            write(pipefd[1], messages[i], strlen(messages[i]));
            close(pipefd[1]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("Parent process: PID = %d, PGRP = %d\n", getpid(), getpgrp());
        }
	}
	for (int i = 0; i < 2; i++) 
    {
        w = waitpid(childpid[i], &status, WUNTRACED);
        if (w == -1)
        {
            perror("Can't wait.\n");
            exit(1);
        }
        printf("Child #%d has finished: PID = %ls\n", i + 1, childpid);
        if (WIFEXITED(status))
        {
            printf("Child #%d exited with code %d\n", i + 1, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child #%d terminated, recieved signal %d\n", i + 1, WTERMSIG(status));
        }
        else if (WIFSTOPPED(status))
        {
            printf("Child #%d stopped, recieved signal %d\n", i + 1, WSTOPSIG(status));
        }
    }
    close(pipefd[1]);
    while (read(pipefd[0], &ch, 1) > 0)
        printf("%c", ch);
    printf("\n");
    close(pipefd[0]);
    return 0;
}
