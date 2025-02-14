#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

int matrice1[MAX][MAX], r1,c1;
int matrice2[MAX][MAX], r2, c2;

void init();
void sorting1();
void sorting2();
void rigXcol();
void swap(int x1, int x2);
void printMatrix();
void parseValue();

int main(void){
    init();
    sorting1();
    sorting2();
    printMatrix();
    rigXcol();
     
    return 1;
}
void init(){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    printf("Matrice 1:\n");
    fscanf(input, "%d %d\n", &r1, &c1);
    for(int y=0; y<r1; y++){
        for(int x=0; x<c1; x++){
            fscanf(input, "%d", &matrice1[y][x]);
            printf("%d ", matrice1[y][x]);
        }
        printf("\n");
    }
    printf("Matrice 2:\n");
    fscanf(input, "%d %d\n", &r2, &c2);
    for(int y=0; y<r2; y++){
        for(int x=0; x<c2; x++){
            fscanf(input, "%d", &matrice2[y][x]);
            printf("%d ", matrice2[y][x]);
        }
        printf("\n");
    }
    fclose(input);

}
void sorting1(){
    bool sorted;
    for(int y=0; y<r1; y++){
        do{
            sorted=true;

            for(int x=0; x<c1-1; x++){
                if(matrice1[y][x]>matrice1[y][x+1]){
                    int tmp=matrice1[y][x];
                    matrice1[y][x]=matrice1[y][x+1];
                    matrice1[y][x+1]=tmp;
                    sorted=false;
                }
            }
            
        }while(!sorted);
    }
}
void sorting2(){
    bool sorted;
    int sums[MAX];
    for(int x=0; x<c2; x++){
        sums[x]=0;
        for(int y=0; y<r2; y++){
            sums[x]+=matrice2[y][x];
        }
    }
    do{
        sorted=true;

        for(int x=0; x<c2-1; x++){
            if(sums[x]<sums[x+1]){
                int tmp=sums[x+1];
                sums[x]=sums[x+1];
                sums[x+1]=tmp;
                swap(x, x+1);
                sorted=false;
            }
        }

    }while(!sorted);
    
}
void swap(int x1, int x2){
    for(int y=0; y<r2; y++){
        int tmp=matrice2[y][x1];
        matrice2[y][x1]=matrice2[y][x2];
        matrice2[y][x2]=tmp;
    }
}
void printMatrix(){
    printf("\nMatrice 1:\n");
    for(int y=0; y<r1; y++){
        for(int x=0; x<c1; x++){
            printf("%d ", matrice1[y][x]);
        }
        printf("\n");
    }
    printf("\nMatrice 2:\n");
    for(int y=0; y<r2; y++){
        for(int x=0; x<c2; x++){
            printf("%d ", matrice2[y][x]);
        }
        printf("\n");
    }
}
void rigXcol(){
    int result[MAX][MAX];
   
   
    for(int y1=0; y1<r1; y1++){
       
        for(int x2=0; x2<c2; x2++){
            result[y1][x2]=0;
            for(int x1=0; x1<c1; x1++){
                result[y1][x2]+= matrice1[y1][x1]*matrice2[x1][x2];
            }
        }
    }
    printf("\nProdotto rigXcol\n");
    for(int y=0; y<r1; y++){
        for(int x=0; x<c2; x++){
            printf("%d ", result[y][x]);
        }
        printf("\n");
    }
}