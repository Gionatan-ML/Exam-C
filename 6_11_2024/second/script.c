#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N_MAX 100

typedef struct
{
    int index;
    int n;
    float elms[N_MAX];
    float media;
}MyStruct;

int main(void){
    int R,C, length=0;
    float max=0.f, somma;
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        perror("an error occurred");
        exit(EXIT_FAILURE);
    }

    MyStruct matrix[N_MAX];
    for(int i=0; i<N_MAX; i++){
        matrix[i].n=0;
    }

    fscanf(input, "%d %d", &R, &C);

    for(int y=0; y<R; y++){
        somma=0.f;
        matrix[y].index=y;
        for(int x=0; x<C; x++){
            fscanf(input, "%f", &matrix[y].elms[x]);
            matrix[y].n+=1;
            if(y==0 && max<matrix[y].elms[x]){
                max=matrix[y].elms[x];
            }
            somma+=matrix[y].elms[x];
        }
        matrix[y].media= (float) somma/matrix[y].n;
        if(y!=R-1){
            for(int x=0; x<C; x++){
                matrix[y].elms[x]/=max;
            }
        }
    }
    for(int x=0; x<C; x++){
        float last_num= matrix[R-1].elms[x];
        somma=0.f;
        for(int y=0; y<R; y++){
            somma+=matrix[y].elms[x];
        }
        if((int)somma!=0){
            somma-=last_num;
            last_num= (-somma);
            matrix[R-1].elms[x]=last_num;
        }
    }
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }

    for(int y=0; y<R; y++){
        fprintf(output, " %d, %d, %.2f, El: \n", matrix[y].index, matrix[y].n, matrix[y].media);
        for(int x=0; x<C; x++){
            fprintf(output, "%.2f ", matrix[y].elms[x]);
        }
        fprintf(output, "\n----------------\n");
    }

}
