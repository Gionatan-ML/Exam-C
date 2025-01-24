#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define MAX_STRING 100

int length=0;

typedef struct{
    int len;
    char string[MAX];
    int indx;
}PalStruct;

void print_output(PalStruct* pal);
void init_pal(PalStruct* pal);
void palindroma(char *buffer_word, bool *isPal);

int main(void){
    PalStruct pal[MAX];
    long pt;
    char buffer[MAX_STRING];
    char buffer_word[MAX];
    int len_buffer=0;
    bool isPal;
    int R_indx=0;
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        perror("Error");
        exit(EXIT_FAILURE);
    }
    init_pal(pal);
    while(fgets(buffer, sizeof(buffer),input)!=NULL){

        for(int i=0; i<strlen(buffer); i++){
            if(buffer[i]==' ' || buffer[i]=='\n'){
                if(len_buffer>1){
                    buffer_word[len_buffer]='\0';

                    palindroma(buffer_word, &isPal);
                    
                    if(isPal==true){
                     
                        strcpy(pal[length].string,buffer_word);
                        pal[length].indx=R_indx;
                        pal[length].len=strlen(buffer_word);
                        length++;

                    }
                }

                len_buffer=0;
                memset(buffer_word, 0, sizeof(buffer_word));
            }
            else{
                
                buffer_word[len_buffer]=buffer[i];
                len_buffer++;
            }
        }
        memset(buffer,0,sizeof(buffer));
        memset(buffer_word, 0, sizeof(buffer_word));
        R_indx++;
    }
    fseek(input, -1, SEEK_CUR);
    while(ftell(input) > 0 && fgetc(input) != ' '){
        fseek(input, -2, SEEK_CUR);
    }
    fscanf(input, "%s", buffer_word);
    palindroma(buffer_word, &isPal);
    if(isPal==true){
        pal[length].indx=R_indx-1;
        strcpy(pal[length].string, buffer_word);
        pal[length].len=strlen(buffer_word);
        length++;
    }
    
    print_output(pal);



}

void init_pal(PalStruct* pal){
    for(int i=0; i<MAX; i++){
        pal[i].len=0;
    }
}
void print_output(PalStruct* pal){
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        perror("An error occurred in the file");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<length; i++){
        fprintf(output, "Indx: %d, Len: %d, Word: %s\n", pal[i].indx, pal[i].len, pal[i].string);
    }
}

void palindroma(char *buffer_word, bool *isPal){
    *isPal=true;
    int x=strlen(buffer_word)-1;
    int y=0;
    while(y<x){
        if(toupper(buffer_word[x])!=toupper(buffer_word[y])){
            *isPal=false;
            break;
        }
        x--;
        y++;
    }
}