#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct{
    int val_x;
    int val_y;
}HashMap;

typedef struct{
    float val;
    int n_occ;
    HashMap map[MAX/2];
    
}MyStruct;

void verify(float val, MyStruct* result, int* lenStruct, float matrice[][MAX], int r,int c){
    result[*lenStruct].n_occ=0;
    result[*lenStruct].val=val;
    int cont=0;
    for(int y=0; y<r; y++){
        for(int x=0; x<c; x++){
            if(matrice[y][x]==val){
                result[*lenStruct].map[result[*lenStruct].n_occ].val_y=y;
                result[*lenStruct].map[result[*lenStruct].n_occ].val_x=x;
                result[*lenStruct].n_occ+=1;
            }
        }
    }
    *lenStruct+=1;
}

void init(float matrice[][MAX], int* r, int* c){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d %d\n", r,c);
    for(int y=0; y< *r; y++){
        for(int x=0; x< *c; x++){
            fscanf(input, "%f", &matrice[y][x]);
            printf("%.1f ",matrice[y][x]);
        }
        printf("\n");
    }
    fclose(input);
}

int main(void){
    float matrice[MAX][MAX];
    int r,c;
    init(matrice, &r,&c);
    MyStruct result[MAX];
    int lenStruct=0;
    float array[MAX];
    int lenArray=0;

    for(int y=0; y<r; y++){
        for(int x=0; x<c; x++){
            int isNew=1;
            for(int i=0; i<lenArray; i++){
                if(matrice[y][x]==array[i]){
                    
                    isNew=0;
                }
            }
            if(isNew){
                array[lenArray]=matrice[y][x];
               
                lenArray++;
            }
        }
    }
    printf("\nArray: ");
    for(int i=0; i<lenArray; i++){
        verify(array[i], result, &lenStruct, matrice, r,c);
        printf("%.1f ", array[i]);
    }
    printf("\nStruct:\n");
    for(int i=0; i<lenStruct; i++){
        printf("%.1f, %d, Pt:\n", result[i].val, result[i].n_occ);
        for(int j=0; j<result[i].n_occ; j++){
            printf("[ %d, %d ] ", result[i].map[j].val_y, result[i].map[j].val_x);
        }
        printf("\n\n");
    }

    return 1;
}