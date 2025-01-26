//FINISHED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct
{
   int indxC;
   int len;
   float el[MAX];
   int n_zero;

}MyStruct;


float matrice[MAX][MAX];
int R,C;
int R_f=0, C_f=0;

void init(){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d %d\n", &R, &C);

    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fscanf(input, "%f ", &matrice[y][x]);
            printf("%.1f ", matrice[y][x]);
        }
        printf("\n");
    }
    fclose(input);

}
void changeRig(int i_0, int i_1){
    float tmp[C];
    for(int x=0; x<C; x++){
        tmp[x]=matrice[i_0][x];
        matrice[i_0][x]=matrice[i_1][x];
        matrice[i_1][x]=tmp[x];
    }

}
void sorting(){
    int cont;
    do{
        cont=0;
        for(int i=0; i<R-1; i++){
            if(matrice[i][0]>matrice[i+1][0]){
                changeRig(i,i+1);
                cont++;
            }
        }

    }while(cont!=0);
}

void printing_stdout(){
    printf("\n");
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            printf("%.1f ", matrice[y][x]);
        }
        printf("\n");
    }
}

void copying(int indx, MyStruct *result){

    printf("\nstruct: \n");
    for(int y=0; y<R; y++){
        if(matrice[y][indx]==0){
            result->n_zero+=1;
        }
        result->el[y]=matrice[y][indx];
        printf(" %f", result->el[y]);
        result->len+=1;
    }
    result->indxC=indx;


}

int main(void){
    init();
    bool blocked;
    MyStruct result[MAX];
    int length=0;
    for(int i=0; i<MAX; i++){
        result[i].len=0;
        result[i].n_zero=0;
    }

    sorting();
    printing_stdout();
    float matrice_f[MAX][MAX];

    for(int x=0; x<C; x++){
        R_f=0;
        blocked=false;
        for(int y=0; y<R; y++){
            if(matrice[y][x]==0){
                copying( x, &result[length]);
                length++;
                blocked=true;
                break;
            }
            matrice_f[R_f][C_f]=matrice[y][x];
            R_f+=1;
        }
        if(blocked==false) C_f+=1;
    }
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }
    fprintf(output, "Matrice Finale:\n");
    for(int y=0; y<R; y++){
        for(int x=0; x<C_f; x++){
            fprintf(output, "%.1f ", matrice_f[y][x]);
        }
        fprintf(output,"\n");
    }
    fprintf(output, "\nStruct: \n");
    for(int i=0; i<length; i++){
        fprintf(output, "{ %d, %d, [ ", result[i].indxC,result[i].len);
        for(int j=0; j<result[i].len; j++){
            fprintf(output, "%.1f ", result[i].el[j]);
        }
        fprintf(output, " ], %d }\n", result[i].n_zero);
    }
    fflush(output);
    fclose(output);

}