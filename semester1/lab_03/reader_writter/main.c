#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include<unistd.h>
#include <time.h>
#define ACTIVE_READERS  0
#define ACTIVE_WRITER   1
#define WRITERS_QUEUE   2
#define READERS_QUEUE   3
#define BIN_WRITER      4
int fl=1;
struct sembuf start_read[] = {{READERS_QUEUE, 1, 0}, {BIN_WRITER, 0, 0}, {WRITERS_QUEUE, 0, 0}, {ACTIVE_READERS, 1, 0}, {READERS_QUEUE, -1, 0}};
struct sembuf stop_read[] = {{ACTIVE_READERS, -1, 0}};
struct sembuf start_write[] = {{WRITERS_QUEUE, 1, 0}, {ACTIVE_READERS, 0, 0}, {BIN_WRITER, 0, 0}, {ACTIVE_WRITER, -1, 0}, {BIN_WRITER, 1, 0}, {WRITERS_QUEUE, -1, 0}};
struct sembuf stop_write[] = {{BIN_WRITER, -1, 0}, {ACTIVE_WRITER, 1, 0}};
void sig_handler(int sig_num)
{
    if (getpid() != getpgrp())
    {
        fl=0;
       // sleep(10);
        printf("\n --Child %d - catch sig_num: %d\n", getpid(), sig_num);
    }
}
void reader(int *shm, int semid, int pid)
{
    srand(time(NULL));
    while (fl)
    {
        sleep(rand() % 3 + 1);
        if (semop(semid, start_read, 5) == -1)
        {
            perror("Can't start_read.\n");
            exit(1);
        }
        printf("Reader %d read: %5d\n", pid, *shm);
        if (semop(semid, stop_read, 1) == -1)
        {
            perror("Can't stop_read.\n\n");
            exit(1);
        }
       // sleep(2);
    }
    exit(0);
}
void writer(int *shm, int semid, int pid)
{
    srand(time(NULL));
    while (fl)
    {
        sleep(rand() % 3 + 1);
        if (semop(semid, start_write, 6) == -1)
        {
            perror("Can't start write\n");
            exit(1);
        }
        printf("Writer %d wrote:  %5d\n", pid, ++(*shm));
        if (semop(semid, stop_write, 2) == -1)
        {
            perror("Can't stop_write.\n");
            exit(1);
        }
        // sleep(2);
    }
    exit(0);
}
int main()
{
    pid_t childpid[8];
    int perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int fd, semid;
    void *handler = NULL;
    if ((handler = signal(SIGINT, sig_handler)) == SIG_ERR)
    {
        perror("Can't signal.\n");
        exit(1);
    }
    fd = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | perms);
    if (fd == -1)
    {
        perror("Can't shmget\n");
        exit(1);
    }
    int *shm = (int*) (shmat(fd, 0, 0));
    if (shm == (int*) -1)
    {
        perror("Can't shmat\n");
        exit(1);
    }
    *shm = 0;
    semid = semget(IPC_PRIVATE, 5, IPC_CREAT | perms);
    if (semid == -1)
    {
        perror("Can't semget\n");
        exit(1);
    }
    if (semctl(semid, ACTIVE_READERS, SETVAL, 0) == -1)
    {
        perror("Can't semctl active_readers\n");
        exit(1);
    }
    if (semctl(semid, ACTIVE_WRITER, SETVAL, 1) == -1)
    {
        perror("Can't semctl active_writer\n");
        exit(1);
    }
    if (semctl(semid, WRITERS_QUEUE, SETVAL, 0) == -1)
    {
        perror("Can't semctl write_queue\n");
        exit(1);
    }
    if (semctl(semid, READERS_QUEUE, SETVAL, 0) == -1)
    {
        perror("Can't semctl read_queue\n");
        exit(1);
    }
    if (semctl(semid, BIN_WRITER, SETVAL, 0) == -1)
    {
        perror("Can't semctl bin_writer\n");
        exit(1);
    }
    for (int i = 0; i < 3; i++)
    {
        if ((childpid[i] = fork()) == -1)
        {
            perror("Can't fork writer\n");
            exit(1);
        }
        else if (childpid[i] == 0)
        {
            writer(shm, semid, getpid());
            exit(0);
        }
    }
    for (int i = 3; i < 8; i++)
    {
        if ((childpid[i] = fork()) == -1)
        {
            perror("Can't fork consumer\n");
            exit(1);
        }
        else if (childpid[i] == 0)

        {
            reader(shm, semid, getpid());
            exit(0);
        }
    }
    for (int i = 0; i < 8; i++)
    {
        int status;
        pid_t w_pid = waitpid(childpid[i], &status, WUNTRACED);
        if (w_pid == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status))
        {
            printf("exited, status=%d, PID = %d\n", WEXITSTATUS(status), w_pid);
        }
        else if (WIFSIGNALED(status))
        {
            printf("kill signal = %d, PID = %d\n", WTERMSIG(status), w_pid);
        }
        else if (WIFSTOPPED(status))
        {
            printf("stop signal = %d, PID = %d\n", WSTOPSIG(status), w_pid);
        }
    }
    if (shmdt(shm) == -1)
    {
        perror("Can't shmdt\n");
        exit(1);
    }
    if (semctl(semid, IPC_RMID, 0) == -1)
    {
        perror("Can't delete semaphore\n");
        exit(1);
    }
    if (shmctl(fd, IPC_RMID, NULL))
    {
        perror("Can't mark a segment as deleted.\n");
        exit(1);
    }
}
