// FINISH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

int R,C; 
float matrice[MAX][MAX];

void init();
void calcMediana(float* array, int indx, float *repo);
void swap(int i, int j);
void sorting(float *repo);
void printing(float* repo);

int main(void){
    init();

    float arrayMed[MAX];

    for(int y=0; y<R; y++){
        calcMediana(matrice[y], y, arrayMed);
    }

    sorting(arrayMed);

    printing(arrayMed);

    return 1;
}

void init(){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        perror("File not found");
        exit(EXIT_FAILURE);
    }

    fscanf(input, "%d %d", &R, &C);

    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fscanf(input, "%f ", &matrice[y][x]);
        }
    }
    fclose(input);

}

void calcMediana(float* array, int indx, float *repo){
    float med;
    int half= (C%2==0) ? (C/2 + 1) : ( (C-1) / 2 + 1);
    int cont;

    for(int x=0; x<C; x++){
        med=array[x];
        cont=0;

        for(int z=0; z<C; z++){
            if(array[z]>=med) cont++;
        }
        if(cont==half){
            repo[indx]=med;
            return;
        }
    }
}

void swap(int i, int j){

    for(int x=0; x<C; x++){
        float tmp=matrice[i][x];
        matrice[i][x]=matrice[j][x];
        matrice[j][x]=tmp;
    }
}

void sorting(float* repo){
    //BubleSort

    int cont;

    do{
        cont=0;

        for(int i=0; i<R-1; i++){
            if(repo[i]<repo[i+1]){

                float tmp=repo[i];
                repo[i]=repo[i+1];
                repo[i+1]=tmp;

                swap(i, i+1);
                cont++;
                
            }
        }

    }while(cont!=0);

}

void printing(float* repo){
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(0);
    }

    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fprintf(output, "%.1f ", matrice[y][x]);
        }
        fprintf(output, "  -> Mediana: %.1f", repo[y]);
        fprintf(output, "\n");
    }
    fflush(output);
    fclose(output);
}