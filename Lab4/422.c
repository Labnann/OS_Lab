#include <pthread.h>
#include <stdio.h>
#include<semaphore.h>

int count;
int sequence[1000] = {0};

sem_t semaphore;


int fibonacci(int n){
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}




void* buildFibonacci(void *arg){

    for(int i = 0; i<count; i++)
    {
      sequence[i] = fibonacci(i);
    }
    sem_post(&semaphore);
    return NULL;
    
}

void outputByParent(){
    sem_wait(&semaphore);
      for(int i = 0; i<count; i++){
        printf("%d ",sequence[i]);
    }
    sem_destroy(&semaphore);
}



void main(){
    pthread_t newthread;

    sem_init(&semaphore,0,0);

     printf("Fibonacci count?\n");
    scanf("%d", &count);
    pthread_create(&newthread,NULL,buildFibonacci,NULL);

    
    // pthread_join(newthread,NULL);

    outputByParent();
    
}