#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

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

void runParentProcess()
{

    int readData[100];
    read(fd[0], readData, sizeof(int) * inputSize);
    if(binarySearch(readData,0,inputSize-1,toSearch)!=-1){
        printf("true");
    }
    else
    {
        printf("false");
    }
    
}

void runChildProcess()
{
    bubbleSort(inputs, inputSize);
    write(fd[1], inputs, inputSize * sizeof(int));

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
    scanf("%d",&toSearch);

    pipe(fd);

    if ((childpid = fork()) == -1)
    {
        perror("fork");
        exit(1001);
    }

    decideProcess(childpid);
}