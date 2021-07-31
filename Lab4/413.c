#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define MAT_A_ROW 2
#define MAT_A_COL 3

#define MAT_B_ROW 3
#define MAT_B_COL 4

struct Dimension {
   int row;
   int column;
};


int matrixA[MAT_A_ROW][MAT_A_COL];
int matrixB[MAT_B_ROW][MAT_B_COL];
int matrixC[MAT_A_ROW][MAT_B_COL];



void* fillColumnAt(void* args){
    struct Dimension* dimension = (struct Dimension*)args;
        int row = dimension->row;
        int column = dimension->column;

    int k = MAT_B_ROW;
    for(int i =0; i<k; i++){
      matrixC[row][column]= matrixA[row][i]*matrixB[i][column];
    }


   
   
}


void  fillMatrixA(){
    //2x3
    matrixA[0][0] =3;
    matrixA[0][1] =7;
    matrixA[0][2] =4 ;
    matrixA[1][0] =1 ;
    matrixA[1][1] =6 ;
    matrixA[1][2] =5 ;
}


void  fillMatrixB(){
    //3x4
    matrixB[0][0] =3;
    matrixB[0][1] =7;
    matrixB[0][2] =4 ;
    matrixB[0][3] =23;
    matrixB[1][0] =1 ;
    matrixB[1][1] =6 ;
    matrixB[1][2] =5 ;
    matrixB[1][3] =13 ;
    matrixB[2][0] =12 ;
    matrixB[2][1] =26 ;
    matrixB[2][2] =15 ;
    matrixB[2][3] =32 ;
}

void main(){

    
    
     fillMatrixA();
     fillMatrixB();

 pthread_t thread;


 for(int i = 0; i<MAT_A_ROW; i++){
      for(int j = 0; j<MAT_B_COL; j++){
         struct Dimension matrixCDimension;
         matrixCDimension.row= i;
         matrixCDimension.column = j;
         pthread_create(&thread,NULL,fillColumnAt,&matrixCDimension);
        // fillColumnAt(&matrixCDimension)
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