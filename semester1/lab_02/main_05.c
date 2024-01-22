#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>

#define N 2
#define LEN 64

_Bool flag = false;

void signal_handler(int sig_num)
{
    flag = true;
    printf(" SIGNAL: %d\n", sig_num);
}

int main() {
    int child[N];
    int fd[N];
    char text[LEN] = {0};
    char *mes[N] = {"AAA\n", "BBB\n"};

    if (pipe(fd) == -1) {
        perror("Can't pipe!");
        exit(EXIT_FAILURE);
    }

    printf("Parent process start. PID: %d, GROUP: %d\n", getpid(), getpgrp());
    if (signal(SIGINT, signal_handler) == SIG_ERR)
    {
        perror("Can't signal!");
        exit(EXIT_FAILURE);
    }

    sleep(2);

    for (int i = 0; i < N; i++)
    {
        int child_pid = fork();

        if (child_pid == -1)
        {
            perror("Can\'t fork()\n");
            exit(EXIT_FAILURE);
        }
        else if (!child_pid)
        {
            if (flag)
            {
                close(fd[0]);
                write(fd[1], mes[i], strlen(mes[i]));
                printf("Message %d sent to parent. %s", i + 1, mes[i]);
            }

            return EXIT_SUCCESS;
        }
        else
        {
            child[i] = child_pid;
        }
    }

    for (int i = 0; i < N; i++)
    {
        int status;
        int statval = 0;

        pid_t child_pid = wait(&status);

        printf("Child process %d finished. Status: %d\n", child_pid, status);

        if (WIFEXITED(statval))
        {
            printf("Child process %d finished. Code: %d\n", i + 1, WEXITSTATUS(statval));
        }
        else if (WIFSIGNALED(statval))
        {
            printf("Child process %d finished from signal with code: %d\n", i + 1, WTERMSIG(statval));
        }
        else if (WIFSTOPPED(statval))
        {
            printf("Child process %d finished stopped. Number signal: %d\n", i + 1, WSTOPSIG(statval));
        }
    }

    printf("\nMessage:\n");
    close(fd[1]);
    read(fd[0], text, LEN);
    printf("%s\n", text);

    printf("Parent process finished. Children: %d, %d! \nParent: PID: %d, GROUP: %d\n", child[0], child[1], getpid(), getpgrp());

    return EXIT_SUCCESS;
}
