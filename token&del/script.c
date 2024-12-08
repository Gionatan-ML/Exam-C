//FINISHED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define N_MAX 100
#define DELS 20

typedef struct{
    char line[N_MAX];
    int n;
    char tokens[N_MAX][2];
    int nTokens;
    char dels[N_MAX];
}MyStruct;

int len=0;

void findDel(MyStruct* string, char* dels){
    bool isStart=false;
    bool find=false;
    bool contS=false;
    for(int i=0; i<strlen(string->line); i++){
        for(int j=0; j<strlen(dels); j++){
            if(string->line[i]==dels[j]){
                isStart= !isStart;
                if(isStart==true && i<strlen(string->line)+1){
                    string->tokens[string->nTokens][0]=string->line[i+1];
                    printf("\nTs: %c", string->tokens[string->nTokens][0]);
                    contS=true;
                    
                }
                else if(isStart==false && contS==true){
                    string->tokens[string->nTokens][1]=string->line[i-1];
                    printf("\nTf: %c", string->tokens[string->nTokens][1]);
                    contS=false;
                    string->nTokens+=1;
                }
                
                string->n++;
                find=false;
                for(int z=0; z<strlen(string->dels); z++){
                    if(string->dels[z]==string->line[i]){
                        find=true;
                        break;
                    }
                }
                if(find==false){
                    size_t stringLen= strlen(string->dels);
                    string->dels[stringLen]=string->line[i];
                    string->dels[stringLen+1]='\0';
                }
            }
        }
    }
}


int main(void){
    MyStruct strings[N_MAX];
    for(int i=0; i<N_MAX; i++){
        strings[len].n=0;
        strings[len].nTokens=0;
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
        findDel(&strings[len], dels);
        
        len++;
        memset(strings[len].line, 0, sizeof(strings[len].line));
    }
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<len; i++){
        fprintf(output, "String: %s, Dels: %s, N:%d,", strings[i].line, strings[i].dels, strings[i].n);
        for(int j=0; j<strings[i].nTokens; j++){
            fprintf(output, "\nSt: %c , Stop: %c ", strings[i].tokens[j][0], strings[i].tokens[j][1]);
        }
        fprintf(output, "\n\n");
    }
}