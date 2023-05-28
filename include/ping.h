#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void executePing(const char *hostname)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        // Child process
        execlp("ping", "ping", "-c", "4", hostname, NULL);
        perror("exec");
        exit(1);
    }
    else
    {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}