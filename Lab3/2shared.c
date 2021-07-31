#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int fd[2];
int count;
int sequence[1000] = {0};

int fibonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return (n - 1) + (n - 2);
}

int main()
{
    // ftok to generate unique key
    //key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    int sharedMemoryId = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    int *sharedMemory = (int *)shmat(sharedMemoryId, NULL, 0);

    printf("Fibonacci count?\n");
    scanf("%d", &count);

    pid_t p = fork();

    if (p < 0)
    {
        printf("fork Failed");
        return 1;
    }

    // Parent process
    else if (p > 0)
    {
        wait(NULL);
        int readData[count];

        for (int i = 0; i < count; i++)
        {
            printf("%d ",sharedMemory[i]);
        }

      

        // destroy the shared memory
        shmctl(sharedMemoryId, IPC_RMID, NULL);
    }

    // child process
    else
    {
        for (int i = 0; i < count; i++)
        {
            sharedMemory[i] = fibonacci(i);
        }

        //detach from shared memory
        shmdt(sharedMemory);

        exit(0);
    }
}