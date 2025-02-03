#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define STRUCT 40
#define MAX 300

typedef struct{
    char word[MAX-100];
    int len;
    char last;
    char key;
}Mystruct;

void parseStruct(Mystruct* result, int* lenStruct, char token, char* string, int len, int previus){
    result[*lenStruct].len=0;
    int tmp= (previus==0) ? previus:previus+1;
    for(int i=tmp; i<=len; i++){
        result[*lenStruct].word[result[*lenStruct].len]=string[i];
        result[*lenStruct].len+=1;
    }
    result[*lenStruct].word[result[*lenStruct].len]='\0';
    result[*lenStruct].last= (previus==0) ? '0': string[previus] ;
    result[*lenStruct].key= token;
    printf("\n%s ->%c,", result[*lenStruct].word,result[*lenStruct].key);
    if( result[*lenStruct].last=='0'){
        printf("\\0");
    }
    else{
        printf(" '%c' ",  result[*lenStruct].last);
    }

    *lenStruct+=1;
}

int main(void){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    Mystruct result[STRUCT];
    int lenResult=0;
    int previus=0;

    char newString[MAX];
    int lenString=0;
    char c1,c2='0';
    while((c1=fgetc(input)) != EOF){
        if(lenString==0){
            newString[lenString]=c1;
            lenString++;
        }
        else{
            if(toupper(c1)==toupper(c2)){
                newString[lenString]='-';
                lenString++;
                newString[lenString]=c1;
                lenString++;
            }
            else{
                newString[lenString]=c1;
                lenString++;
            }
        }
        c2=c1;
    }
    newString[lenString]='\0';
    printf("%s", newString);

    for(int i=0; i<lenString; i++){
        if(newString[i]=='-'){
            printf("\n%d, %d\n", i, previus);
            parseStruct(result, &lenResult, '-', newString, i, previus);
            previus=i;

        }
        else if(newString[i]=='.'){
            printf("\n%d, %d\n", i, previus);
            parseStruct(result, &lenResult, '-', newString, i, previus);
            previus=i;
        }
        else if(newString[i]==' ' &&  (i-previus)>=19){
            printf("\n%d, %d\n", i, previus);
            parseStruct(result, &lenResult, '-', newString, i, previus);
            previus=i;
        }
    }


}