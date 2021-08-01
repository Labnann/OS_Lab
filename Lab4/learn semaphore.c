#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>

#define THREAD_NUM 4

sem_t semaphore;


void * routine(void* args){
    sem_wait(&semaphore);
    sleep(1);
    printf("HELLO WORLD %d\n",*(int*)args);
    sem_post(&semaphore);
    free(args);
}

int main(int argc, char* argv[]){
    pthread_t th[THREAD_NUM];

    sem_init(&semaphore,0,1);

    for(int i =0; i<THREAD_NUM; i++){
        int *a = malloc(sizeof(int));
        *a=i;
        if(pthread_create(&th[i],NULL,&routine,a)!=0){
            perror("FAILED THREAD CREATION");
        }
    }

    for(int i =0; i<THREAD_NUM; i++){
       if(pthread_join(th[i],NULL)!=0){
           perror("FAILED JOINING");
       }
    }

    

    return 0;

}