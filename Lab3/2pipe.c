#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int fd[2];
int count;
int sequence[1000] = {0};

int fibonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}



void runParentProcess()
{

    int readData[100];
    read(fd[0], readData, sizeof(int) *count);
    for(int i = 0; i<count; i++){
        printf("%d ",readData[i]);
    }
    
}

void runChildProcess()
{
    for(int i =0; i<count;i++){
        sequence[i] = fibonacci(i);
    }
    write(fd[1], sequence, count * sizeof(int));

}

void decideProcess(pid_t pid)
{
    if (pid == 0)
    {
        runChildProcess();
    }
    else
    {
        runParentProcess();
    }
}

void main()
{

    pid_t childpid;

    printf("Fibonacci count?\n");
    scanf("%d", &count);

    pipe(fd);

    if ((childpid = fork()) == -1)
    {
        perror("fork");
        exit(1001);
    }

    decideProcess(childpid);
}