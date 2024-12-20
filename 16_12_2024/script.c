//FINISHED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define N_MAX 100

int R,C;
int len_vett, lenStruct=0;
int cont=0;
int matrix[50][50];
int vett[10];

typedef struct{
    int occ;
    int riga;
    int col;
    int len;
    int *vettore;
}MyStruct;

void init(){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        perror("File not found");
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d %d", &R, &C);
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fscanf(input, "%d ", &matrix[y][x]);
            printf("%d ",matrix[y][x]);
        }
        printf("\n");
    }
    fscanf(input, "%d", &len_vett);
    len_vett+=1;
    printf("Len Vett: %d, Vett:\n", len_vett);
    for(int i=0; i<len_vett; i++){
        fscanf(input, "%d", &vett[i]);
        printf("%d ", vett[i]);
    }

}
bool verify(int* x_s, int* y_s) {
    int j = 0;
    for (int y = *y_s; y < R; y++) {
        for (int x = ((y > *y_s)?0:*x_s); x < C; x++) {
            if (j >= len_vett) {
                *y_s = y;
                *x_s = x;
                printf("\n\n\ntrue\n\n\n");
                return true;
            }
            if (vett[j] != matrix[y][x]) {
                return false;
            }
            j++;
        }
    }
    return false;
}

int main(void){
    init();
    bool find;
    MyStruct vettContainer[N_MAX];
    for(int i=0; i<N_MAX; i++){
        vettContainer[i].len=len_vett;
        vettContainer[i].vettore=vett;
    }
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            printf("\nBefore: %d, %d", x,y);
            find=verify(&x,&y);
            printf("\nAfter: %d, %d", x,y);

            if(find==true){
                printf("x");
                vettContainer[lenStruct].col=x;
                vettContainer[lenStruct].riga=y;
                lenStruct++;
            }
        }
    }
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<lenStruct; i++){
        for(int j=0; j<len_vett; j++){
            fprintf(output, "%d ", vett[j]);
        }
        fprintf(output, "{%d, %d, %d, %d}\n", vettContainer[i].col, vettContainer[i].riga, len_vett, i);
    }
    fclose(output);

    
}