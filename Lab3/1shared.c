#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int fd[2];
int inputSize;
int inputs[1000];
int toSearch;

int binarySearch(int arr[], int left, int right, int searchFor)
{
    if (right >= left)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == searchFor)
            return mid;

        if (arr[mid] > searchFor)
            return binarySearch(arr, left, mid - 1, searchFor);
        return binarySearch(arr, mid + 1, right, searchFor);
    }
    return -1;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{

    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

int main()
{
    // ftok to generate unique key
    //key_t key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    int sharedMemoryId = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    int *sharedMemory = (int *)shmat(sharedMemoryId, NULL, 0);
    

    printf("Input Size\n");
    scanf("%d", &inputSize);
    printf("Inputs:\n");
    for (int i = 0; i < inputSize; i++)
    {
        scanf("%d", &inputs[i]);
        if (inputs[i] < 0)
            i--;
    }
    printf("Search for:\n");
    scanf("%d", &toSearch);

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
        int readData[inputSize];

        for (int i = 0; i < inputSize; i++)
        {
            readData[i] = sharedMemory[i];
        }

        if(binarySearch(readData,0,inputSize,toSearch)==-1){
            printf("false");
        }
        else
        {
            printf("true");
        }
        


         // destroy the shared memory
        shmctl(sharedMemoryId, IPC_RMID, NULL);
       
    }

    // child process
    else
    {
        bubbleSort(inputs, inputSize);

        for (int i = 0; i < inputSize; i++)
        {
            sharedMemory[i] = inputs[i];
        }

         //detach from shared memory
        shmdt(sharedMemory);

       

        exit(0);
    }
}