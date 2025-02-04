#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct{
    char c;
    int pt[2];
    int len;

}MyStruct;

void init(char matrice[][MAX], int *r, int *c){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d %d\n", r,c);
    for(int y=0; y< *r; y++){
        for(int x=0; x< *c; x++){
            fscanf(input, "%c ", &matrice[y][x]);
            printf("%c ", matrice[y][x]);
        }
        printf("\n");
    }
    fclose(input);
}
void printStruct(MyStruct* result, int len){
    FILE* output=fopen("output.bin", "wb");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<len; i++){
        printf("%c, [ %d, %d ], %d\n", result[i].c, result[i].pt[0], result[i].pt[1], result[i].len);
        fprintf(output,"%c, [ %d, %d ], %d\n", result[i].c, result[i].pt[0], result[i].pt[1], result[i].len);
    }

    fflush(output);
    fclose(output);
}

int main(void){

    char matrice[MAX][MAX];
    int new_matrice[MAX][MAX];
    int r,c;

    init(matrice, &r,&c);

    MyStruct result[MAX];
    int lenStruct=0;

    for(int y=0; y<r; y++){
        for(int x=0; x<c; x++){
            result[lenStruct].len=0;
            result[lenStruct].c=matrice[y][x];
            result[lenStruct].pt[0]=y;
            result[lenStruct].pt[1]=x;
            if(x>0 && matrice[y][x-1]=='*'){
                result[lenStruct].len+=1;
            }
            else if(x==0 && y>0 && matrice[y-1][c-1]=='*'){
                result[lenStruct].len+=1;
            }
            if(x<c && matrice[y][x+1]=='*'){
                result[lenStruct].len+=1;
            }
            else if(x+1==c && y+1<r && matrice[y+1][0]=='*'){
                result[lenStruct].len+=1;
            }
            lenStruct++;
        }
    }
    printStruct(result, lenStruct);
    int cont=0;
    printf("\nNew Matrice:\n");
    for(int y=0; y<r; y++){
        for(int x=0; x<c; x++){
            if(matrice[y][x]=='*'){
                new_matrice[y][x]=-1;
            }
            else if(matrice[y][x]=='-'){
                new_matrice[y][x]=result[cont].len;
            }
            printf("%d ", new_matrice[y][x]);
            cont++;
        }
        printf("\n");
    }

    return 1;
}