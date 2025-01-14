//Finish

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_S 30

typedef struct{
    int indx;
    char word[MAX_S];
    int len;
}MyStruct;


//global variables
const char filename_in[]="input.txt";
const char filename_out[]="output.bin";

//functions
void handleWord(MyStruct* result, int* length, int lenRig);
void printing(MyStruct* result, int length);
void printing_stdout(MyStruct* result, int length);
void sorting(MyStruct* result, int length);

int main(void){
    FILE *input=fopen(filename_in, "r");
    if(input==NULL){
        perror("Can not open the file");
        exit(EXIT_FAILURE);
    }

    int length=0, lenRig;
    char c;

    MyStruct result[MAX_S];
    result[length].len=0;

    while((c=fgetc(input))!=EOF){
        switch(c){
            case ' ':
                result[length].word[ result[length].len ]='\0';
                handleWord(result, &length, lenRig); // usato per length l'operatore unario di referenzazione
                result[length].len=0;
                break;
            case '\n':
                break;
            case '.': lenRig++; break;
            case '!': lenRig++; break;
            case '?': lenRig++; break;

            default:
                result[length].word[ result[length].len ]=c;
                result[length].len+=1;
                break;
        }
    }
    sorting(result, length);
    printing(result, length);
    printing_stdout(result, length);

    return 0;
}
void handleWord(MyStruct* result, int* length, int lenRig){
    if((int)result[*length].word[0]>=65 && (int)result[*length].word[0]<97){ // usato per length l'operatore unario di dereferenzazione
        result[*length].indx=lenRig;
        *length+=1;
    }
}
void printing(MyStruct* result, int length){
    FILE *output=fopen(filename_out, "wb");
    
    if(output==NULL){
        perror("Errore nella scrittura del file, Controlla se il file e' in modalita' di sola lettura! ");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<length; i++){
        fprintf(output, "Word: %s, Rig: %d, Len: %d\n", result[i].word, result[i].indx, result[i].len);
    }

}
void printing_stdout(MyStruct* result, int length){
    for(int i=0; i<length; i++){
        printf( "Word: %s, Rig: %d, Len: %d\n", result[i].word, result[i].indx, result[i].len);
    }
}

// sorting with bubleSort, best case O(n), worst case O(n^2)
void sorting(MyStruct* result, int length){
    int cont;

    do{
        cont=0;

        for(int i=0; i<length-1; i++){
            if(result[i].len<result[i+1].len){
                MyStruct tmp=result[i];
                result[i]=result[i+1];
                result[i+1]=tmp;
                cont++;
            }
        }

    }while(cont!=0);
}