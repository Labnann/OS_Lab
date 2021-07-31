#include<stdio.h>
#include<pthread.h>




void * test(){
    
}
void* fillColumnAt(void* args){
    printf("T");
    int *row = (int) args;
    int *column =  row++;
    
    printf("%d ",row);

    int k = MAT_B_ROW;
    for(int i =0; i<k; i++){
      matrixC[*row][*column]= matrixA[*row][k]*matrixB[k][*column];
    }
   
   
}

void main(){
    printf("T3");
pthread_t thread; //s[MAT_A_ROW*MAT_B_COL];

int threadInProgress=0;

int ij[2];
printf("T2");

for(int i = 0; i<MAT_A_ROW; i++){
    for(int j = 0; j<MAT_B_COL; j++){
        ij[0]=i;
        ij[1]=j;
        printf("T1");
        pthread_create(&thread,NULL,fillColumnAt,ij);
        threadInProgress++;
    }
}



pthread_join(thread,NULL);

for(int i =0; i<MAT_A_ROW;i++){
    for(int j=0; j<MAT_B_COL; j++){
        printf("%d ",matrixC[i][j]);
    }
    printf("\n");
}

}