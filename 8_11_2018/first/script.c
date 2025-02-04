//FINISH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 200
#define STR 30

typedef struct{
    int pt;
    char word[STR];
    int len;

}MyStruct;

void sorting(MyStruct* result, int length);
void printing(MyStruct* result, int length);

int main(void){
    
    FILE* input=fopen("input.txt", "r"), output;
    if(input==NULL){
        perror("File not found");
        exit(EXIT_FAILURE);
    }

    MyStruct result[STR];
    int length=0;

    char c;
    result[length].len=0;

    while((c=fgetc(input))!=EOF){
        if(c==' '){
            result[length].word[ result[length].len ]='\0';
            result[length].pt=(int)ftell(input) - result[length].len - 1;
            printf("String: %s, Len: %d, Pt: %d\n", result[length].word, result[length].len, result[length].pt);
            length++;
            result[length].len=0;
            continue;
        }
        result[length].word[ result[length].len ]=c;
        result[length].len+=1;
    }
    result[length].word[ result[length].len ]='\0';
    result[length].pt=(int)ftell(input) - result[length].len - 1;
    printf("String: %s, Len: %d, Pt: %d\n", result[length].word, result[length].len, result[length].pt);
    length++;

    fclose(input);

    sorting(result, length);
    printing(result, length);



}

//Buble sort
void sorting(MyStruct* result, int length){
    int cont;
    int strcont=0;

    do{
        cont=0;

        for(int i=0; i<length-1; i++){
            if((int) toupper(result[i].word[strcont])> (int) toupper(result[i+1].word[strcont])){
                MyStruct tmp= result[i];
                result[i]=result[i+1];
                result[i+1]=tmp;
                cont++;
                strcont=0;
            }
            else if((int) toupper(result[i].word[strcont]) == (int) toupper(result[i+1].word[strcont]) && strcont < strlen(result[i].word)){
                strcont++;
                i--;
            }
            else{
                strcont=0;
            }
        }

    }while(cont!=0);
}

void printing(MyStruct* result, int length){
    
    FILE* output=fopen("output.bin", "wb");
    if(output==NULL){
        exit(0);
    }

    for(int i=0; i<length; i++){
        fprintf(output,"String: %s, Len: %d, Pt: %d\n", result[i].word, result[i].len, result[i].pt);
    }
    fflush(output);
    fclose(output);
}