//FINISH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50
#define N 20

//global variables
char filename_in[]="input.txt";
char filename_out[]="output.bin";
char stop[]="stop";

//functions
void init(int matrice[][MAX], int* R, int* C);
void printStdout(int matrice[][MAX], int R, int C);
void insertRig(int matrice[][MAX], int *R, int *C);
void sorting(int matrice[][MAX], int r, int c);
void swap(int matrice[][MAX], int pt_0, int pt_1, int r);

int main(void){
    
    int matrice[MAX][MAX];
    int R,C;

    init(matrice, &R, &C);
    printStdout(matrice, R, C);
    insertRig(matrice, &R, &C);
    printStdout(matrice, R, C);
    sorting(matrice, R,C);
    printStdout(matrice, R, C);
    return 0;

}
void init(int matrice[][MAX], int* R, int* C){
    FILE* input=fopen(filename_in, "r");
    if(input==NULL){
        perror("Errore in apertura file");
        exit(EXIT_FAILURE);
    }

    fscanf(input, "%d%*c%d\n", R,C);
    printf("R: %d, C: %d\n", *R, *C);
    for(int y=0; y< *R; y++){
        for(int x=0; x< *C; x++){
            matrice[y][x]=0;
        }
    }

    int i,j;
    char buffer[N];
    fgets(buffer, sizeof(buffer), input);

    while(strcmp(buffer, stop)){
        int val;
        sscanf(buffer, "%d%*c%d%*c%d", &i, &j, &val);
        matrice[i][j]=val;
        fgets(buffer, sizeof(buffer), input);
    }
    fclose(input);


}
void printStdout(int matrice[][MAX], int R, int C){
    FILE* output=fopen(filename_out, "wb");
    if(output==NULL){
        perror("Controlla regole di scrittura del file");
        exit(EXIT_FAILURE);
    }

    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            printf("%d ", matrice[y][x]);
            fprintf(output,"%d ", matrice[y][x]);
        }
        printf("\n");
        fprintf(output,"\n");
    }
    fflush(output);
    fclose(output);
    printf("\n\n");
}
void insertRig(int matrice[][MAX], int *R, int *C){
    int max;
    int j=0;

    printf("\n\n");
    for(int x=0; x< *C; x++){
        max=0;
        for(int y=0; y< *R; y++){
            if(max<matrice[y][x]){
                max=matrice[y][x];
            }
        }
        matrice[*R][j]=max;
        
        j++;
    }
    *R+=1;

}
void swap(int matrice[][MAX], int pt_0, int pt_1, int r){
    for(int y=0; y<r; y++){
        int tmp=matrice[y][pt_0];
        matrice[y][pt_0]=matrice[y][pt_1];
        matrice[y][pt_1]=tmp;
    }
}

//uso buble sort
void sorting(int matrice[][MAX], int r, int c){
    int cont;
    do{
        cont=0;

        for(int x=0; x<c-1; x++){
            if(matrice[r-1][x]>matrice[r-1][x+1]){
                swap(matrice, x, x+1, r);
                cont++;
            }
        }

    }while(cont!=0);
}
