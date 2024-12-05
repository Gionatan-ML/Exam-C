//UNFINISHED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define N_MAX 100
#define DELS 20

typedef struct{
    char line[N_MAX];
    int n;
    int tokens[N_MAX][2];
    char dels[N_MAX];
}MyStruct;

int len=0;

void findDel(MyStruct string, char* dels){
    bool isStart=false;
    bool find=false;
    int cont=0;
    for(int i=0; i<strlen(string.line); i++){
        for(int j=0; j<strlen(dels); j++){
            if(string.line[i]==dels[j]){
                isStart= isStart ? false:true;
                if(isStart==true){
                    string.tokens[cont][1]=string.line[i-1];
                    
                }
                else if(isStart==false && i>1){
                    string.tokens[cont][0]=string.line[i+1];
                }
                cont++;
                string.n++;
                find=false;
                for(int z=0; z<strlen(string.dels); z++){
                    if(string.dels[z]==string.line[i]){
                        find=true;
                        break;
                    }
                }
                if(find==false){
                    string.dels[strlen(string.dels)]=string.line[i];
                    string.dels[strlen(string.dels)+1]='\0';
                }
            }
        }
    }
}


int main(void){
    MyStruct strings[N_MAX];
    for(int i=0; i<N_MAX; i++){
        strings[len].n=0;
    }
    char dels[DELS];
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    fgets(dels, sizeof(dels), input);

    while(fgets(strings[len].line, sizeof(strings[len].line), input)!=NULL){
        if(strlen(strings[len].line)<=1){
            memset(strings[len].line, 0, sizeof(strings[len].line));
            continue;
        }
        findDel(strings[len], dels);
        
        len++;
        memset(strings[len].line, 0, sizeof(strings[len].line));
    }
}