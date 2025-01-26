#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 150
#define MAX_S 10

typedef struct{
    int line;
    char word[MAX_S];
    int rep;
}MyStruct;



int main(void){
    
    MyStruct result[MAX_S];
    int lenStruct=0;

    FILE* input=fopen("input.txt", "r"), *output;
    if(input==NULL){
        perror("Can not open the file");
        exit(EXIT_FAILURE);
    }
    char s_buffer[MAX];
    char word[MAX_S];
    int lenWord=0;
    int contLine=0;

    while(fgets(s_buffer, MAX, input)!=NULL){
        for(int i=0; i<strlen(s_buffer); i++){
            if(s_buffer[i]>=65 && s_buffer[i]<97){
                lenWord=0;
                while(i<strlen(s_buffer) && s_buffer[i]!=' '){
                    word[lenWord]=s_buffer[i];
                    lenWord++;
                    i+=1;
                }
                if(word[lenWord-1]=='\n') lenWord--;
                word[lenWord]='\0';
                result[lenStruct].line=contLine;
                strcpy(result[lenStruct].word, word);
                int cont=0;
                for(int j=0; j<lenStruct; j++){
                    if(strcmp(result[j].word, result[lenStruct].word)==0){
                        cont++;
                    }
                    
                }
                result[lenStruct].rep=cont+1;
                printf("%s, %d, %d\n", result[lenStruct].word, result[lenStruct].line, result[lenStruct].rep);
                lenStruct++;
            }
        }
        contLine++;
    }
    fclose(input);

    output=fopen("output.bin", "wb");
    for(int i=0; i<lenStruct; i++){
        fprintf(output,"{ %s, %d, %d }\n", result[i].word, result[i].line, result[i].rep);
    }
    fflush(output);
    fclose(output);

    return 1;
}