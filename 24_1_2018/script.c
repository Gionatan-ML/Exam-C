#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define S_MAX 100


typedef struct{
    int cont;
    float frz;
}Map;

typedef struct{
    char val;
    Map frz;
    int *posit;
}MyStruct;


//global value
int struct_len=0;


void getNC(char *string, char* buffer){
    bool find;
    int length=0;
    for(int i=0; i<strlen(string); i++){
        printf("%c\n", string[i]);
        find=false;
        for(int j=0; j<length; j++){
            if(string[i]==buffer[j]){
                find=true;
                break;
            }

        }
        if(find==false){
            buffer[length]=string[i];
            length++;
        }
    }
    buffer[length]='\0';
}
Map getFrz(char c, char* string){
    Map frz;
    frz.cont=0;
    for(int i=0; i<strlen(string); i++){
        if(string[i]==c){
            frz.cont+=1;

        }
    }
    frz.frz=(float)frz.cont/strlen(string);
    return frz;
}
int* getPosition(char c, char* string){
    int* buffer= malloc(MAX);
    if(buffer==NULL){
        exit(EXIT_FAILURE);
    }
    int cont=0;
    for(int i=0; i<strlen(string); i++){
        if(string[i]==c){
            buffer[cont]=i;
            cont++;
        }
    }
    buffer[cont]=-1;
    return buffer;
}


int main(void){
    int cont=0;
    MyStruct dict[MAX];
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        perror("Pirito");
        exit(EXIT_FAILURE);
    }
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        perror("scurreggia");
        exit(EXIT_FAILURE);
    }
    char buffer[MAX];
    char string[S_MAX];
    fgets(string, sizeof(string), input);
    getNC(string,buffer);
    for(int i=0; i<strlen(buffer); i++){
        dict[struct_len].val=buffer[i];
        dict[struct_len].frz=getFrz(buffer[i], string);
        dict[struct_len].posit=getPosition(buffer[i], string);
        fprintf(output, "%c, %d, %.2f, [ ", dict[struct_len].val, dict[struct_len].frz.cont, dict[struct_len].frz.frz);
        for(int j=0; dict[struct_len].posit[j]!=-1; j++){
            fprintf(output, "%d, ", dict[struct_len].posit[j]);
        }
        fprintf(output, " ]\n");
        struct_len++;
    }
    fclose(input);
    fclose(output);



}