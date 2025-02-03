#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX 50

typedef struct{
    int rig[MAX];
    char key_c;
    int len;
}MyStruct;

void sorting(MyStruct* result, int* array, int len){
    bool isSorted;
    do{
        isSorted=true;
        for(int i=0; i<len-1; i++){
            if(result[i].len<result[i+1].len){
                MyStruct tmp=result[i];
                result[i]=result[i+1];
                result[i+1]=tmp;
                int ptr=array[i];
                array[i]=array[i+1];
                array[i+1]=ptr;
                isSorted=false;
            }
        }
    }while(!isSorted);
}

int main(void){
    srand(time(NULL));
    int array[MAX];
    MyStruct result[MAX];
    int lenStruct=0;
    for(int i=0; i<MAX; i++){
        result[i].len=0;
    }

    char sBuffer[MAX];
    FILE* input=fopen("input.txt", "r"),*output;
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    if(fgets(sBuffer, MAX, input)==NULL) exit(EXIT_FAILURE);
    fclose(input);

    for(int i=0; i<strlen(sBuffer); i++){
        bool find=false;
        for(int j=0; j<lenStruct; j++){
            if(sBuffer[i]==result[j].key_c){
                find=true;
                result[j].rig[1]+=1;
                result[j].rig[result[j].len+2]=i;
                result[j].len+=1;
            }
        }
        if(!find){
            array[lenStruct]=rand()%128;
            result[lenStruct].key_c=sBuffer[i];
            result[lenStruct].rig[2]=i;
            result[lenStruct].len+=1;
            result[lenStruct].rig[0]= (int) sBuffer[i]+array[lenStruct];
            result[lenStruct].rig[1]=1;
            lenStruct++;
        }
    }
    
    sorting(result,array,lenStruct);
    output=fopen("output.bin", "wb");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<lenStruct; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
    for(int y=0; y<lenStruct; y++){
        printf("%c ", result[y].key_c);
        fprintf(output,"'%c' ", result[y].key_c);
        for(int x=0; x<result[y].len+2; x++){
            printf("%d ", result[y].rig[x]);
            fprintf(output,"%d ", result[y].rig[x]);
        }
        printf("\n");
        fprintf(output,"\n");
    }
    fflush(output);
    fclose(output);

    return 1;
}