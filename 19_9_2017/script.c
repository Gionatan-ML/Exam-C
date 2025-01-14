//FINISH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N_MAX 100
#define MAX_S 200

typedef struct{
    char c_key;
    int n_value;
}HashMap;

typedef struct{
    char orgString[MAX_S];
    char nwString[MAX_S];
    HashMap isFind[MAX_S/10];
    int lenHash;
    int lenString;
    float media;
}MyStruct;

// Poteri utilizzare toupper() della libreria ctype, ma la creo direttamente io
char myToupper(char c);
void findChar(MyStruct* result, int len, char c, char orgC, int pt);

int main(void){

    FILE* input=fopen("input.txt", "r"), *output=fopen("output.bin", "wb");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    if(output==NULL){
        exit(0);
    }
    fclose(output);


    MyStruct result[N_MAX];
    int length=0;

    while(fgets(result[length].orgString, sizeof(result[length].orgString), input) != NULL && length<N_MAX){
        result[length].lenHash=0;
        result[length].lenString=0;

        

        for(int i=0; i<strlen(result[length].orgString); i++){
            char c=myToupper(result[length].orgString[i]);
            findChar(result, length, c,result[length].orgString[i], i);
        }
        result[length].nwString[ result[length].lenString ]='\0';

        int sum=0, cont=0;
        for(int i=0; i<result[length].lenHash; i++){
            sum+=result[length].isFind[i].n_value;
            cont++;
        }

        result[length].media= (float) sum/cont;

        output=fopen("output.bin", "ab");
        if(output==NULL){
            exit(EXIT_FAILURE);
        }
        fprintf(output," -> %.2f\n", result[length].media);
        fflush(output);
        fclose(output);
        length++;
    }
    fclose(input);


    return 1;
}

char myToupper(char c){
    if((int)c <=122 && (int)c>=97){
        char newC= (char) (c - 32);
      
        return newC;
    }
    else{
        return c;
    }
}

void findChar(MyStruct* result, int len, char c, char orgC, int pt){
    FILE* output=fopen("output.bin", "ab");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }

    int cont=0;
    bool find=false;

    if(c=='\n'){
        fflush(output);
        fclose(output);
        return;
    }

    for(int i=0; i< MAX_S/10; i++){
        if(result[len].isFind[i].c_key==c){
            find=true;
            break;
        }
    }
    if(find==true) return;
    for(int i=pt; i<strlen(result[len].orgString); i++){
        if(myToupper(result[len].orgString[i])==c){
            cont++;
        }
    }
    result[len].isFind[ result[len].lenHash ].c_key=c;
    result[len].isFind[ result[len].lenHash ].n_value=cont;
    result[len].lenHash+=1;

    result[len].nwString[ result[len].lenString ]=orgC;
    result[len].nwString[ result[len].lenString +1 ]=(char)cont;

    fprintf(output,"%c%d", result[len].nwString[ result[len].lenString ], result[len].nwString[ result[len].lenString + 1]);
    result[len].lenString+=2;

    fflush(output);
    fclose(output);
}