
// FINISHED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define NWORD 20

int matrice[50][50];
char string[50];
int R,C;

typedef struct{
    char word[20];
    int indx;
    int lenW;
}MyStruct;

void init(){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d %d\n", &R, &C);

    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fscanf(input, "%d ", &matrice[y][x]);
            printf("%d ", matrice[y][x]);
        }
        printf("\n");
    }
    fclose(input);

}
void parsingS(){
    int len=0;
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            if(matrice[y][x]>=0 && x>0){
                string[matrice[y][x]]= (char)matrice[y][0];
                printf("\n%d, %c", matrice[y][0],(char)matrice[y][0]);
                if(matrice[y][x]>len){
                    len=matrice[y][x];
                }
            }
        }
    }
    string[len+1]='\0';
    len++;
    printf("\nString: '%s'", string);

}

int main(void){
    init();

    MyStruct result[MAX];
    int length=0;

    for(int i=0; i<MAX; i++){
        result[i].lenW=0;
    }
    
    parsingS();

    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(0);
    }
    printf("\nLen: %ld", strlen(string));
    for(int i=0; i<=strlen(string); i++){
        if(string[i]!=' ' && string[i]!='\0'){
            result[length].word[result[length].lenW]=string[i];
            result[length].lenW+=1;
        }
        else{
            result[length].word[result[length].lenW]='\0';
            result[length].indx=i-result[length].lenW;
            fprintf(output, "{ %s, %d }\n", result[length].word, result[length].indx);
            length++;
        }
    }


}