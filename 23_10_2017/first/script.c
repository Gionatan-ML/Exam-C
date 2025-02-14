#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_S 200

typedef struct{
    char* indx_container;
    char* indx_content;
    int occ;
    int pt;
}MyStruct;

//global variables
char filename_in[]="input.txt";
char filename_out[]="output.bin";

char container[MAX_S], content[MAX_S/10];

void init();

int main(void){
    init();

    MyStruct result[MAX_S/10];
    int lenStruct=0;
    int cont=0, occ=0;
    bool find=false;

    long len_word= strlen(content);

    for(int i=0; i<strlen(container); i++){
       if(cont==3){
            occ++;
            result[lenStruct].indx_container=container;
            result[lenStruct].indx_content=content;
            result[lenStruct].occ=occ;
            result[lenStruct].pt= i-len_word;
            lenStruct++;
       }

       if(container[i]==content[cont] && cont<len_word){
            cont++;
       }
       else{
            cont=0;
       }
    }

    for(int i=0; i<lenStruct; i++){

        int j=result[i].pt;
        char buffer[MAX_S/10];
        int lenBuffer=0;

        while(container[j]!=' ' && j!=0){
            j--;
        }
        j= container[j]==' ' ? j+1:j; 
        while(container[j]!=' ' && j<strlen(container) && container[j]!='\n'){
            buffer[lenBuffer]=container[j];
            lenBuffer++;
            j++;
        }
        buffer[lenBuffer]='\0';


        printf("%s ,%d, %d\n", buffer, result[i].occ, result[i].pt);
        memset(buffer, 0, sizeof(buffer));
    }

    return 1;
}

void init(){
    FILE* input=fopen(filename_in, "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }

    fgets(container, sizeof(container), input);
    fgets(content, sizeof(content), input);

    fclose(input);
}