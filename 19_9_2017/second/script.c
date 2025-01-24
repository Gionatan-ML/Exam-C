//FINISH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 40

//global variables 
char filename_in[]="input.txt";
char filename_out[]="output.bin";
int R;

void init(char strings[][MAX], int matrice[][MAX], int* lenString){
    char buffer[MAX];
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d", &R);
    for(int y=0; y<R; y++){
        for(int x=0; x<R; x++){
            fscanf(input, "%d", &matrice[y][x]);
            printf("%d ", matrice[y][x]);
        }
        printf("\n");
    }
    while (fgets(buffer, MAX, input)!=NULL){
        if(!strcmp(buffer, "\n")) continue;
        // eliminazione da buffer delle virgoles
        char len=0;
        for(int i=0; i<strlen(buffer); i++){
            if(buffer[i]!=',' && buffer[i]!='\n'){
                strings[*lenString][len]=buffer[i];
                len++;
            }
        }
        strings[*lenString][len]='\0';
        *lenString+=1;
    }
    
    fclose(input);
}

int calculate(char* string, int matrice[][MAX]){
    int somma=0;
    char bufferWord[2];
    int y, x;
    for(int i=0; i<strlen(string)-1; i++){
        bufferWord[0]=string[i];
        bufferWord[1]='\0';
        y=atoi(bufferWord);
        bufferWord[0]=string[i+1];
        bufferWord[1]='\0';
        x=atoi(bufferWord);
        printf("YX: %d %d\n", y, x);
        somma+=matrice[y][x];
        if(matrice[y][x]<0){
            somma=-1;
            break;
        }
    }
    return somma;
}

int main(void){
    char strings[MAX][MAX];
    int lenString=0;
    int matrice[MAX][MAX];
    init(strings, matrice, &lenString);

    for(int i=0; i<lenString; i++){
        int result=calculate(strings[i], matrice);
        printf("Somma: %d\n", result);
    }
}
