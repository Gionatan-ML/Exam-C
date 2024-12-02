#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N_MAX 100

// scambia le righe di input.txt in modo che siano ordinate in maniera decrescente in funzione della loro somma 
// elimina righe con somma dispari che hanno anche indice dispari
// salvare tutto in un vett di struct

typedef struct{
    int rig; // indx colonna
    int c; // num el colonna
    int el[N_MAX]; // el colonna
}MyStruct;

// inizializzo variabili globali
int vettLen=1, R,C;

// inizializzo gli indici e la matrice
int** init(){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(0);
    }

    fscanf(input, "%d ", &R);
    fscanf(input, "%d ", &C);

    printf("Matrice iniziale: \n");
    int **matrice=malloc(sizeof(int*)*R);
    if(matrice==NULL){
        exit(1);
    }
    for(int i=0; i<R; i++){
        matrice[i]=malloc(sizeof(int)*C);
        if(matrice[i]==NULL){
            exit(0);
        }
        for(int j=0; j<C; j++){
            fscanf(input, "%d ", &matrice[i][j]);
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
    fflush(input);
    fclose(input);

    return matrice;

}

int main() {

    bool go;
    int **matrice, sums_r;
    matrice=init();
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(0);
    }

    int len_del=0;

    int* del=malloc(sizeof(int)*R);
    if(del==NULL){
        exit(0);
    }

    MyStruct** strCols;

    //sums of rig
    for(int y=0; y<R; y++){
        sums_r=0;
        for(int x=0; x<C; x++){
            sums_r+=matrice[y][x];
        }
        if(sums_r%2==1 && y%2==1){
            del[len_del]=y;
            len_del++;
        }
    }

    //save in struct;
    strCols=malloc(sizeof(MyStruct*)*(R-len_del));
    if(strCols==NULL){
        exit(0);
    }
    
    int cont=0;
    for(int i=0; i<(R-len_del); i++){
        strCols[i]=malloc(sizeof(MyStruct)*(C));
        if(strCols[i]==NULL){
            exit(0);
        }
        go=false;
        for(int j=0; j<len_del; j++){
            if(del[j]==cont){
                go=true;
                break;
            }
        }
        if(go==true){
            cont++;
            continue;
        }
        strCols[i]->rig=cont;
        strCols[i]->c=0;

        fprintf(output, "{ Indx: %d, Vals: ", strCols[i]->rig);
        for(int y=0; y<C; y++){  
            strCols[i]->el[strCols[i]->c]=matrice[cont][y];
            fprintf(output, "%d ", strCols[i]->el[strCols[i]->c]);
            strCols[i]->c+=1;
        }
        fprintf(output, "Num_El: %d }\n",strCols[i]->c);
        cont++;
    }


    
    

    return 0;
}