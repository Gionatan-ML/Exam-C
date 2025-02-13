//FINISHED

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 50

typedef struct{
    int occ;
    float val;
    int indx[2];
}MyStruct;

float matrice[MAX][MAX];
int R,C;

void init();
int counting(float value);
void printing(MyStruct** result, int len);
void freeMem(MyStruct*** result, int len);


void adding(MyStruct*** result, int *len, float value, int y, int x){

    *result= realloc(*result, sizeof(MyStruct*)*(*len+1));
    if(*result==NULL){
        exit(0);
    }
    (*result)[*len]=malloc(sizeof(MyStruct));
    if((*result)[*len]==NULL){
        exit(0);
    }

    (*result)[*len]->indx[0]=x;
    (*result)[*len]->indx[1]=y;
    (*result)[*len]->val=value;

}


int main(void){
    init();

    MyStruct** result=malloc(sizeof(MyStruct*));

    if(result==NULL){
        perror("NOT ENOUGHT MEMORY");
        exit(EXIT_FAILURE);
    }
    int len=0;
    bool isPresent;

    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            isPresent=false;

            for(int i=0; i<len; i++){
                if(matrice[y][x]==result[i]->val){
                    isPresent=true;
                    break;
                }
            }

            if(!isPresent){
                adding(&result, &len, matrice[y][x], y, x);
                result[len]->occ=counting(matrice[y][x]);

                printf("Result %d: %.2f, %d, [ x: %d, y: %d]\n", len, result[len]->val, result[len]->occ, result[len]->indx[0], result[len]->indx[1] );

                len++;
              
            }
        }
    }

    printing(result, len);
    freeMem(&result, len);

    if(*result==NULL){
        printf("\nOperation Finished!\n");
    }

    return 1;   
}


void init(){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }

    fscanf(input, "%d %d", &R, &C);

    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fscanf(input, "%f", &matrice[y][x]);
            printf("%.1f ", matrice[y][x]);
        }
        printf("\n");
    }
    
    printf("\n");

    fclose(input);
    
}

int counting(float value){
    int cont=0;

    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            if(matrice[y][x]==value) cont++;
        }
    }

    return cont;
}

void printing(MyStruct** result, int len){
    FILE* output=fopen("output.bin", "wb");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<len; i++){
        fprintf(output, "{ %.1f, %d, [ %d , %d ]}\n", result[i]->val, result[i]->occ, result[i]->indx[1], result[i]->indx[0]);
    }
    fflush(output);
    fclose(output);
}

void freeMem(MyStruct*** result, int len){
    for(int i=0; i<len; i++){
        free( (*result)[i]);
    }
    free(*result);
}