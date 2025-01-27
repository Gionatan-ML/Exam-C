#include <stdio.h>
#include <stdlib.h>

#define MAX 20

void init(int* R, int* C, int matrice[][MAX], int* array){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d %d\n", R, C);
    for(int y=0; y< *R; y++){
        for(int x=0; x< *C; x++){
            fscanf(input, "%d", &matrice[y][x]);
            printf("%d ", matrice[y][x]);
        }
        printf("\n");
    }
    printf("Array: \n");
    for(int i=0; i< *R; i++){
        fscanf(input, "%d", &array[i]);
        printf("%d ", array[i]);
    }
    fclose(input);
}

int main(void){
    int matrice[MAX][MAX];
    int array[MAX];
    int R,C,prdScalare=0, cont=0;
    int max=0, min=10000, somma=0;
    float media;

    init(&R, &C, matrice, array);

    printf("\nPrdScalare: ");
    for(int x=0; x<C; x++){
        prdScalare=0;
        for(int y=0; y<R; y++){
            prdScalare+= matrice[y][x]*array[y];
        }
        printf("%d ", prdScalare);
        max= (max<prdScalare) ? prdScalare : max;
        min= (min>prdScalare) ? prdScalare: min;
        somma+=prdScalare;
        cont++;   
    }
    media= (float) somma/cont;
    printf("\nMax: %d, Min: %d, Media: %.1f", max, min, media);


    return 0;
}