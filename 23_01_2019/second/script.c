#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 20


typedef struct{
    int key;
    long value;

}HashMap;

typedef struct{
    HashMap map[MAX];
    int len;
}SP;

typedef struct{
    int* indirizzo1;
    int* indirizzo2;
    int occ[2];
    int pt[2];
}Mystruct;

//global variables
static int rangeSearch= (int)'a'-(int)'A';
SP vett1, vett2;


int main(void){

    vett1.len=0;
    vett2.len=0;
    bool start=false;
    Mystruct result[MAX];
    int lenStruct=0;
    char c;

    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(0);
    }

    int num;
    int contToken=0;

    while((c=fgetc(input))!=EOF){
        if(c==':') {start=true; contToken++;}
        if((int)c >= 48 && (int)c<=57 && start){
            fseek(input, -1, SEEK_CUR);
            fscanf(input, "%d", &num);
            printf("N: %d\n", num);

            if(contToken==1){
                vett1.map[vett1.len].key=num;
                vett1.map[vett1.len].value= ftell(input);
                
                vett1.len+=1;
            }
            else{
                vett2.map[vett2.len].key=num;
                vett2.map[vett2.len].value= ftell(input);
                
                vett2.len+=1;
            }
        }
        else if(c=='\n') start=false;

    }

    if(vett1.len<vett2.len){
        while(vett1.len<vett2.len){
            vett1.map[vett1.len].key=-1;
            vett1.map[vett1.len].value=-1;
            vett1.len+=1;
        }
    }
    else if(vett2.len<vett1.len){
        while(vett1.len<vett2.len){
            vett2.map[vett2.len].key=1;
            vett2.map[vett2.len].value= -1;
            vett2.len+=1;
        }
    }

    int prdSc=0;
    for(int i=0; i<vett1.len; i++){
        printf("F: %d, %ld\n", vett1.map[i].key, vett1.map[i].value);
        printf("S: %d, %ld\n\n", vett2.map[i].key, vett2.map[i].value);
        prdSc+= vett1.map[i].key*vett2.map[i].key;

        result[lenStruct].indirizzo1= &vett1.map[i].key;
        result[lenStruct].indirizzo2= &vett2.map[i].key;
        result[lenStruct].pt[0]=vett1.map[i].value;
        result[lenStruct].pt[1]=vett2.map[i].value;

        result[lenStruct].occ[0]=0;
        result[lenStruct].occ[1]=0;
        for(int j=0; j<vett1.len; j++){
            if(vett1.map[j].key==vett1.map[i].key) result[lenStruct].occ[0]+=1;
            if(vett2.map[j].key==vett1.map[i].key) result[lenStruct].occ[0]+=1;
            if(vett1.map[j].key==vett2.map[i].key) result[lenStruct].occ[1]+=1;
            if(vett2.map[j].key==vett2.map[i].key) result[lenStruct].occ[1]+=1;
        }
        lenStruct++;
    }
    printf("Prodotto scalare: %d\n", prdSc);

    fclose(input);
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<lenStruct; i++){
        fprintf(output, "%p, %p, Occ1: %d, Occ2: %d, Pt1: %d, Pt2: %d, Val1: %d, Val2: %d\n", result[i].indirizzo1, result[i].indirizzo2, result[i].occ[0],result[i].occ[1], result[i].pt[0], result[i].pt[1], vett1.map[i].key, vett2.map[i].key);
    }
    fprintf(output, "\nProdotto scalare: %d", prdSc);
    fflush(output);
    fclose(output);



    
    return 1;
}