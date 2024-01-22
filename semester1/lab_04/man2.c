#include <signal.h>
#include <fcntl.h>
#include <syslog.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 
#include <errno.h> 
#include <pthread.h>

#define LOCKFILE "/var/run/daemon.pid"
#define PERMS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
#define SLEEP_TIME 10

sigset_t mask;

int lockfile(int fd) {
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    return fcntl(fd, F_SETLK, &fl);
}

void daemonize(const char *cmd) {
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    // * Сбросить маску режима создания файла чтобы обеспечить нужные права доступа при создании файлов.
    umask(0);
    
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        syslog(LOG_ERR, "возможно получить максимальный номер дескрипто \n");
    }
    
    if ((pid = fork()) == -1) {
        syslog(LOG_ERR, "ошибка вызова функции for\n");
    } else if (pid != 0) {
        exit(0);
    }
    
    if (setsid() == -1) {
        syslog(LOG_ERR, "ошибка setsid\n");
        exit(1);
    }
    
    sa.sa_handler = SIG_IGN; 
    sigemptyset(&sa.sa_mask); 
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) == -1) {
        syslog(LOG_ERR, "Невозможно игнорировать сигнал SIGHUB");
    }
    
    if (chdir("/") == -1) {
        syslog(LOG_ERR, "Невозможно сделать текущим рабочим каталогом ");
    }
    
    if (rl.rlim_max == RLIM_INFINITY) {
        rl.rlim_max = 1024; 
    }
    for (i = 0; i < rl.rlim_max; i++) {
        close(i);
    }
    
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
    /*
    *    Инициализировать файл журнала.
    */
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "Ошибочные файловые дескрипторы %d, %d, %d\n", fd0, fd1, fd2);
        exit(1);
    }
}

int already_running(void) {
    int fd;
    char buf[16];

    fd = open(LOCKFILE, O_RDWR | O_CREAT, PERMS);
    if (fd == -1) {
        syslog(LOG_ERR, "невозможно открыть %s : %s\n", LOCKFILE, strerror(errno));
        exit(1);
    }
    if (lockfile(fd) == -1) {
        if (errno == EACCES || errno == EAGAIN) {
            close(fd);
            return 1;
        }
        syslog(LOG_ERR, "невозможно установить блокировк %s: %s\n", LOCKFILE, strerror(errno));
        exit(1);
    }
    
    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long) getpid());
    write(fd, buf, strlen(buf) + 1);
    return 0;
}

void reread(void)
{
}

void* thr_fn(void *arg)
{
    int i = 0;
    while(i < 5)
    { 
        syslog(LOG_INFO, "%s", (char*)arg);
        sleep(1);
        i++;
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    int err;
    int status;
    pthread_t tid1, tid2;
    char *a_str = "xxxxxx";
    char *b_str = "yyyyyy";
    char *cmd;
    struct sigaction sa;

    if ((cmd = strrchr(argv[0], '/')) == NULL) {
        cmd = argv[0];
    } else {
        cmd++;
    }
    daemonize(cmd);
    
    if (already_running()) {
        syslog(LOG_ERR, "демон уже запущен\n");
        exit(1);
    }
    //* Восстановить 
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGHUP, &sa, NULL) == -1) {
        syslog(LOG_ERR, "возможно восстановить действие SIG_DFL для SIGHUB\n");
    }
    sigfillset(&mask);
    if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) == -1) {
        syslog(LOG_ERR, "Ошибка выполнения операции SIG_BLOC");
    }
    //* Создать поток для обработки SIGHUP и SIGTERM
    err = pthread_create(&tid1, NULL, thr_fn, (void*)(a_str));
    if (err == -1) {
        syslog(LOG_ERR, "невозможно создать поток\n");
    } else {
        syslog(LOG_INFO, "Новый поток создан\n");
    }
    err = pthread_create(&tid2, NULL, thr_fn, (void*)(b_str));
    if (err == -1) {
        syslog(LOG_ERR, "невозможно создать поток\n");
    } else {
        syslog(LOG_INFO, "Новый поток создан\n");
    }
    void* res;
    int s;
    s = pthread_join(tid1, &res);
    s = pthread_join(tid2, &res);
    if (s == -1)
    {
      syslog(LOG_ERR, "can`t thread join\n");
      exit(1);
    }
    free(res);

    time_t timestamp;
    struct tm *time_info;
    for (;;)
    {
        sleep(SLEEP_TIME);
        time(&timestamp);
        time_info = localtime(&timestamp);
        syslog(LOG_DAEMON, "%s", asctime(time_info));  
        exit(0);
    }
}
