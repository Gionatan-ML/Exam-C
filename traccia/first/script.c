#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 150

typedef struct{

    int key_line;
    int val_cont;
    int val_max;

}HashMap;

void print_out(int matrice[][2], int len){
    FILE* output=fopen("output.bin", "wb");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<len; i++){
        fprintf(output, "%d  %d\n", matrice[i][0], matrice[i][1]);
    }
    fflush(output);
    fclose(output);


}
void sorting(int matrice[][2], int len){
    int cont=0;
    do{
        cont=0;

        for(int i=0; i<len-1; i++){
            if(matrice[i][0]>matrice[i+1][0]){
                int tmp= matrice[i][0];
                matrice[i][0]=matrice[i+1][0];
                matrice[i+1][0]=tmp;
                cont++;
            }
        }

    }while(cont!=0 && cont < 1000000000);
}

int main(void){

    FILE* input=fopen("input.txt", "r"), *output;
    if(input==NULL){
        exit(EXIT_FAILURE);
    }

    HashMap map[MAX/10];
    int lenHash=0;

    char buffer[MAX];
    int matrice[MAX/10][2];
    int contLine=0;
    int maxWord=0;
    int cont;
    int contSpace=0;

    while(fgets(buffer, MAX, input)!=NULL){
        maxWord=0;
        map[lenHash].key_line=contLine;
        map[lenHash].val_cont=0;
        if(!strcmp(buffer, "")) break;
        for(int i=0; i<strlen(buffer); i++){
            if(buffer[i-1]==' ' && buffer[i]==' ') continue;
            if(buffer[i]==' ' || i+1==strlen(buffer)){
                maxWord= (maxWord<cont) ? cont:maxWord;
                map[lenHash].val_cont+=1;
                cont=0;
                
                continue;
            }
            cont++;

        }
        map[lenHash].val_max=maxWord;
        matrice[contLine][0]=map[lenHash].val_cont;
        matrice[contLine][1]=map[lenHash].val_max;
        printf("%d  %d\n",  matrice[contLine][0],  matrice[contLine][1]);
        lenHash++;
        contLine++;
    }

    sorting(matrice, lenHash);
    print_out(matrice, lenHash);
    return 1;
}