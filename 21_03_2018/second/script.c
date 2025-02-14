#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

typedef struct{
    char word[MAX/2];
    int pt_0;
    int len;
}MyStruct;

char string[MAX];

void init(){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    fgets(string, MAX, input);
    fclose(input);

}

int findFirstOcc(int i){
    while(string[i]==' ' && i<strlen(string)) i++;
    return i;
}
void sorting(MyStruct* result, int lenStruct){
    int find;
    do{
        find=false;
        for(int i=0; i<lenStruct-1; i++){
            if(result[i].len>result[i+1].len){
                MyStruct tmp= result[i];
                result[i]=result[i+1];
                result[i+1]=tmp;
                find=true;
            }
        }

    }while(find);
}

int main(void){
    init();
    MyStruct result[MAX/2];
    result[0].len=0;
    result[0].pt_0=findFirstOcc(0);
    int lenStruct=0;
    

    for(int i=result[0].pt_0; i<strlen(string); i++){
        if(string[i]==' ' || i+1==strlen(string)){

            result[lenStruct].word[ result[lenStruct].len ]='\0';
           
            lenStruct++;

            if(i+1==strlen(string)){
                result[lenStruct-1].word[ result[lenStruct-1].len ]=string[i];
                result[lenStruct-1].len+=1;
                result[lenStruct-1].word[ result[lenStruct-1].len ]='\0';
            }
            else{
                result[lenStruct].pt_0=findFirstOcc(i);
                i=result[lenStruct].pt_0;
                result[lenStruct].len=0;
            }

        
        }
        result[lenStruct].word[ result[lenStruct].len ]=string[i];
        result[lenStruct].len+=1;   
    }
    sorting(result, lenStruct);
    for(int i=0; i<lenStruct; i++){
        printf("%s, %d, %d\n", result[i].word, result[i].pt_0, result[i].len);
    }

    int cont=0;
    printf("New String: \n");
    for(int i=0; i<lenStruct; i++){
        for(int j=0; j<result[i].len; j++){
            string[cont]=result[i].word[j];
            printf("%c",string[cont]);
            cont++;
        }
        if(i+1!=lenStruct){
            string[cont]=' ';
            printf("%c",string[cont]);
            cont++;
        }
    }


    return 1;
}