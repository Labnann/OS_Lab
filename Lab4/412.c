#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int count;
int sequence[1000] = {0};


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
    return NULL;
    
}



void main(){
    pthread_t newthread;

     printf("Fibonacci count?\n");
    scanf("%d", &count);
    pthread_create(&newthread,NULL,buildFibonacci,NULL);
    
    pthread_join(newthread,NULL);



    for(int i = 0; i<count; i++){
        printf("%d ",sequence[i]);
    }

    

    
}