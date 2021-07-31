#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

int count;

int isPrime(int n)
{
    if (n <= 1)
        return 0;
    for (int i = 2; i <n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}


void* printPrimaryNumbers(void *arg){
    for(int i = 0; i<count+1; i++)
    {
       if(isPrime(i)) printf("%d ",i);
    }
    return NULL;
    
}



void main(){
    scanf("%d",&count);
    pthread_t secondThread;
    pthread_create(&secondThread,NULL,printPrimaryNumbers,NULL);
 
    pthread_join(secondThread,NULL);
}