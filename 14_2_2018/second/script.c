#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 20

typedef struct{
    float rig[MAX];
    int delete;
    int indx;
}Mystruct;


void saveInResult(Mystruct* result, int indx , float* buffer, int C){
    for(int x=0; x<C; x++){
        result[indx].rig[x]=buffer[x];
    }
}

void printMatrice(float matrice[][MAX], int R, int C){
    printf("\nMatrice:\n");
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            printf("%.1f ", matrice[y][x]);
        }
        printf("\n");
    }
}

void bubleSortPari(float matrice[][MAX], int y, int C){
    bool stop;
    do{
        stop=true;
        for(int x=0; x<C-1; x++){
            if(matrice[y][x]>matrice[y][x+1]){
                float tmp=matrice[y][x];
                matrice[y][x]=matrice[y][x+1];
                matrice[y][x+1]=tmp;
                stop=false;
            }
        }

    }while(stop!=true);
}
void bubleSortDispari(float matrice[][MAX], int y, int C){
    bool stop;
    do{
        stop=true;
        for(int x=0; x<C-1; x++){
            if(matrice[y][x]<matrice[y][x+1]){
                float tmp=matrice[y][x];
                matrice[y][x]=matrice[y][x+1];
                matrice[y][x+1]=tmp;
                stop=false;
            }
        }

    }while(stop!=true);
}

void sorting(float matrice[][MAX], int R, int C){
    bool isPari;
    for(int y=0; y<R; y++){
        isPari= ((y+1)%2==0) ? true:false;
        if(isPari){
            bubleSortPari(matrice, y, C);
        }
        else{
            bubleSortDispari(matrice, y, C);
        }
    }
    printMatrice(matrice, R,C);
}


void findCopy(float matrice[][MAX],int startPoint, int R, int C, int *indxDelete,int *lenIndx, Mystruct* result, int *lenResult ){
    saveInResult(result, *lenResult, matrice[startPoint], C);
    result[*lenResult].indx=startPoint;
    for(int y=startPoint+1; y<R; y++){
        int cont=0;
        for(int x=0; x<C; x++){
            if(matrice[y][x]==matrice[startPoint][x]) cont++;
        }
        if(cont==C){
            indxDelete[ *lenIndx]=y;
            *lenIndx+=1;
            result[*lenResult].delete+=1;
        }
    }
    *lenResult+=1; 
    
}
void printInFile(Mystruct* result, int len, int C){
    FILE* output=fopen("output.bin", "wb");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<len; i++){
        fprintf(output, "%d, %d Rig: \n", result[i].delete, result[i].indx);
        for(int x=0; x<C; x++){
            fprintf(output, "%.1f ",result[i].rig[x]);
        }
        fprintf(output, "\n");
    }
    fflush(output);
    fclose(output);
}
int main(void){
    int indxDelete[MAX];
    bool pass;
    int lenIndx=0;
    float matrice[MAX][MAX];
    Mystruct result[MAX];
    int lenResult=0;
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }

    int R,C;

    fscanf(input, "%d %d\n", &R, &C);
    printf("Matrice Iniziale:\n");
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fscanf(input, "%f ", &matrice[y][x]);
            printf("%.1f ", matrice[y][x]);
        }
        printf("\n");
    }
    fclose(input);
    
    sorting(matrice, R,C);

    for(int y=0; y<R; y++){
        pass=true;
        for(int i=0; i<lenIndx; i++){
            if(y==indxDelete[i]){
                pass=false;
                break;
            }
        }
        if(pass){
            findCopy(matrice, y, R,C, indxDelete, &lenIndx, result, &lenResult);
        }
    }
    printf("\nRes:\n");
    for(int y=0; y<lenResult; y++){
        for(int x=0; x<C; x++){
            printf("%.1f ", result[y].rig[x]);
        }
        printf("\n");
    }
    printInFile(result, lenResult, C);
}