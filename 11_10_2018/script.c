//FINISHED

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100
#define N_STR 50

typedef struct{

    int len;
    char string[MAX];
    int n;
    int n_words;


}MyStruct;

void scompose(char* string){
    int cont=0;
    char buffer[MAX];

    for(int i=0; i<strlen(string); i++){
        if(string[i]=='"' && i+1<strlen(string)){
            i++;
            buffer[cont]=string[i];
            cont++;
        }
        else if(cont>0){
            buffer[cont]=string[i];
            cont++;
        }
    }
    cont-=1;
    buffer[cont]='\0';
    strcpy(string, buffer);
    printf("%s\n", string);
}

void sorting(MyStruct* result, int len){
    int cont;
    do{
        cont=0;
        for(int i=0; i<len; i++){
            if(result[i].len<result[i+1].len){
                MyStruct tmp= result[i];
                result[i]=result[i+1];
                result[i+1]=tmp;
                cont++;
            }
        }
    }while(cont!=0);
}

int main(void){
    char buffer[MAX];
    
    MyStruct result[N_STR];
    int length=0;

    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }

    while(fgets(buffer, sizeof(buffer), input)!=NULL){
        scompose(buffer);
        strcpy(result[length].string, buffer);
        result[length].len=strlen(buffer);
        result[length].n=length;
        
        for(int i=0; i<strlen(buffer); i++){
            if(buffer[i]==' '){
                result[length].n_words+=1;
            }
        }
        result[length].n_words+=1;
        length++;
        memset(buffer, 0, sizeof(buffer));
    }
    sorting(result, length);

    for(int i=0; i<length; i++){
        printf("\nLen: %d, N: %d, String: %s , N_Words: %d", result[i].len, result[i].n, result[i].string, result[i].n_words);
    }
}