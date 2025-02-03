#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 50

char matrice[MAX][MAX];
int r,c;

typedef struct{
    int init[2];
    int final[2];
    int pt;
}MyStruct;

void printAll(MyStruct* result, int len, char matrice[][MAX]){
    for(int y=0; y<r; y++){
        for(int x=0; x<c; x++){
            printf("%c ", matrice[y][x]);
        }
        printf("\n");  
    }
    FILE* output=fopen("output.bin", "wb");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<len; i++){
        fprintf(output, "{ [%d, %d], [%d, %d], %d }\n", result[i].init[0], result[i].init[1], result[i].final[0], result[i].final[1], result[i].pt);
    }
    fclose(output);
}

int main(void){
    srand(time(NULL));

    MyStruct result[100];
    int lenStruct=0;

    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    char chr;
    fscanf(input,"%d %d", &r, &c);
    for(int y=0; y<r; y++){
        for(int x=0; x<c; x++){
            chr=fgetc(input);
            if(chr=='\n' || chr==EOF){
                x--;
                continue;
            }
            
            matrice[y][x]=chr;
            printf("%c", matrice[y][x]);

        }
        printf("\n");
    }
    fclose(input);
    for(int y=0; y<r; y++){
        for(int x=0; x<c; x++){
            if(matrice[y][x]=='0'){
              
                int maxLaunch=rand()%101+10;
                int cont=0;
                int x_init=x;
                int y_init=y;
                while(cont<maxLaunch){
                    int x_rand=rand()%c;
                    int y_rand=rand()%r;
                    chr=matrice[y_rand][x_rand];
                    matrice[y_rand][x_rand]='0';
                    matrice[y_init][x_init]=chr;
                    
                    result[lenStruct].init[0]=y_init;
                    result[lenStruct].init[1]=x_init;
                    result[lenStruct].final[0]=y_rand;
                    result[lenStruct].final[1]=x_rand;
                    result[lenStruct].pt=cont;
                    x_init=x_rand;
                    y_init=y_rand;
                    cont++;
                    lenStruct++;
                }
            }
        }
    }
   
    printAll(result, lenStruct, matrice);
}