//FINISHED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define LIMIT 100

char stop[]="exit";

typedef struct
{
    int indx;
    int result;
    int pt;

}MyStruct;


int main(void){
    int contLine=0;
    char buffer[MAX];
    char word[MAX];
    int contStr=0;
    int find=0;

    MyStruct result[LIMIT];
    int lenR=0;

    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }

    fgets(word, sizeof(word), input);
    int lenString=strlen(word)-1;

    while(contLine<LIMIT && fgets(buffer, sizeof(buffer), input)!=NULL){
        if(buffer[strlen(buffer)-1]=='\n') { buffer[strlen(buffer)-1]='\0'; }
        if(!strcmp(buffer, stop)){
            printf("find, %d", contLine);
            break;
        } 

        contStr=0;
        find=0;
        
        for(int i=0; i<strlen(buffer); i++){
            if(buffer[i]==word[contStr]){
                contStr++;
            }
            else{
                contStr=0;
            }

            if(contStr==lenString){
                result[lenR].pt= i-lenString;
                result[lenR].indx=contLine;
                result[lenR].result=1;
                lenR++;
                find++;
                contStr=0;
            }
        }

        if(find==0){
            result[lenR].pt= -1;
            result[lenR].indx= contLine;
            result[lenR].result= -1;
            lenR++;
        }
        contLine++;
    }
    fclose(input);

    FILE* output=fopen("output.bin", "wb");
    if(output==NULL){
        exit(0);
    }

    for(int i=0; i<lenR; i++){
        if(result[i].result==-1) continue;
        fprintf(output, "%d -> %d -> %d\n", result[i].indx, result[i].pt, result[i].result);
    }

    fflush(output);
    fclose(output);
}

