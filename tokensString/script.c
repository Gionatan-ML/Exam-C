#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define N_MAX 100

typedef struct{
    char line[N_MAX];
    int n;
    char tokens[N_MAX][N_MAX];

}MyStruct;


void abc(char* string){
    bool sort=false;
    while(sort==false){
        sort=true;
        for(int i=0; i<strlen(string)-1; i++){
            if((int)toupper(string[i])>(int)toupper(string[i+1])){
                char tmp=string[i];
                string[i]=string[i+1];
                string[i+1]=tmp;
                sort=false;
            }
        }
    }
}

void getWords(char* buffer, MyStruct* inTokens, int *len){
    char bufferW[N_MAX];
    int len_buff=0;
    for(int i=0; i<strlen(buffer); i++){
        if(buffer[i]==' ' || (i+1)==strlen(buffer)){
            bufferW[len_buff]='\0';

            strcpy(inTokens[*len].tokens[inTokens[*len].n] , bufferW);
            abc(inTokens[*len].tokens[inTokens[*len].n]);
            

            inTokens[*len].n+=1;
            len_buff=0;
            memset(bufferW, 0, sizeof(bufferW));
            
        }
        else{
            bufferW[len_buff]=buffer[i];
            len_buff++;
        }

    }
}

int main(void){
    MyStruct inTokens[N_MAX];
    int len=0;
    for(int i=0; i<N_MAX; i++){
        inTokens[i].n=0;
    }

    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }

    while(fgets(inTokens[len].line, sizeof(inTokens[len].line), input)!=NULL){
        getWords(inTokens[len].line, inTokens, &len);
        for(int i=0; i<inTokens[len].n; i++){
            fprintf(output, "%s, ", inTokens[len].tokens[i]);
        }
        fprintf(output, "%s, %d", inTokens[len].line, inTokens[len].n);
        fprintf(output, " \n");
        len++;
    }
    fclose(input);
    fclose(output);
    return 1;
}