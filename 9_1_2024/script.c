#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

typedef struct{
    int key;
    int value;
}HashMap;

typedef struct LinkedList{

    char word[MAX/3];
    int n_occ;
    int len_indxOcc;
    HashMap indx_occ[MAX/10];
    struct LinkedList* next;
    struct LinkedList* previus;

}LinkedList;

void wordControll(LinkedList** head, char* word, int keyLine, int position){
    bool isNew=true;
    LinkedList* copy= *head;
    while(copy!=NULL){
        if(!strcmp(copy->word, word)){
            isNew=false;
            copy->n_occ+=1;
            copy->indx_occ[copy->len_indxOcc].key=keyLine;
            copy->indx_occ[copy->len_indxOcc].value=position+1;
            copy->len_indxOcc+=1;
            return;
        }
        copy=copy->next;
    }
    if(isNew==true && strlen(word)>1){
        LinkedList* tmp=malloc(sizeof(LinkedList));
        if(tmp==NULL){
            exit(0);
        }
        tmp->len_indxOcc=0;
        tmp->n_occ=0;
        strcpy(tmp->word, word);
        tmp->indx_occ[tmp->len_indxOcc].key=keyLine;
        tmp->indx_occ[tmp->len_indxOcc].value=position+1;
        tmp->len_indxOcc+=1;
        tmp->n_occ=1;
        tmp->next=NULL;
        
        if(*head==NULL){
            *head=tmp;
        }else{
            LinkedList* tail = *head;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = tmp;
            tmp->previus = tail;
        }
    }
}

void printing(LinkedList *result){
    while(result!=NULL){
        printf("{ %s,%d, [ ", result->word, result->n_occ);
        for(int i=0; i<result->len_indxOcc; i++){
            printf("Line: %d, Pos: %d || ", result->indx_occ[i].key, result->indx_occ[i].value);
        }
        printf("\n");
        LinkedList* tmp=result;
        result=result->next;
        free(tmp);
    }
}
void extPrinting(LinkedList* result){
    FILE* output=fopen("output.bin", "wb");
    if(output==NULL){
        exit(0);
    }
    while(result!=NULL){
        fprintf(output,"{ %s,%d, [ ", result->word, result->n_occ);
        for(int i=0; i<result->len_indxOcc; i++){
            fprintf(output,"Line: %d, Pos: %d || ", result->indx_occ[i].key, result->indx_occ[i].value);
        }
        fprintf(output," ] } \n");
        LinkedList* tmp=result;
        result=result->next;
        free(tmp);
    }
    fflush(output);
    fclose(output);
}

int main(void){
    int contLine=0;
    int lenWord=0;
    char stringBuffer[MAX];
    char word[MAX/3];

    LinkedList* result;

    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }

    while(fgets(stringBuffer, sizeof(stringBuffer), input)!=NULL){
        for(int i=0; i<strlen(stringBuffer); i++){

            if(stringBuffer[i]!='\n'){
                word[lenWord]=stringBuffer[i];
                lenWord++;
            }

            if(stringBuffer[i]==' ' || i+1==strlen(stringBuffer)){
                word[lenWord]='\0';
                wordControll(&result, word, contLine, (i-strlen(word)));
                lenWord=0;
                memset(word, 0, sizeof(word));
            }
        }
        contLine++;
    }

    
    extPrinting(result);

    fflush(input);
    fclose(input);

}
