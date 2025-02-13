#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

typedef struct{
    char line[MAX];
    int n_words;
    int lenWords[MAX/2];
}MyStruct;

static char token[]=".!?";



void endWord(MyStruct* result, int lenStruct, int* lenWord){
    result[lenStruct].lenWords[result[lenStruct].n_words]= *lenWord;
    result[lenStruct].n_words+=1;
 
    *lenWord=0;
}

void print_out(MyStruct* result, int lenStruct){
    for(int i=0; i<lenStruct; i++){
        printf("%s, %d, [ ", result[i].line, result[i].n_words);
        for(int j=0; j<result[i].n_words; j++){
            printf("%d ", result[i].lenWords[j]);
        }
        printf("]\n");
    }
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }
    fwrite(result, sizeof(MyStruct), lenStruct, output);
    fflush(output);
    fclose(output);
}

int main(void){
    MyStruct result[MAX];
    for(int i=0; i<MAX; i++){
        result[i].n_words=0;
    }
    bool find=false;
    int lenStruct=0;
    char c;
    char buffer[MAX];
    int lenBuffer=0;
    int cont_space=0;
    int cont_word=0;
    FILE *input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    

    while(( c=fgetc(input)) != EOF){
        if(c=='\n') continue;
        for(int i=0; i<strlen(token); i++){
            if(c==token[i]){
                endWord(result, lenStruct, &cont_word);
                buffer[lenBuffer]='\0';
                strcpy(result[lenStruct].line, buffer);
                lenStruct++;
                memset(buffer, 0, sizeof(buffer));
                lenBuffer=0;
                find=true;
               
                break;
            }
        }
        if(find==true){
            find=false;
            continue;
        }
        if(c==' ' && buffer[lenBuffer-1]!=' '){ 
            endWord(result, lenStruct, &cont_word);
           
        }
        buffer[lenBuffer]=c;
        lenBuffer++;
        cont_word++;
    }
    fclose(input);
    print_out(result, lenStruct);

    return 1;
}