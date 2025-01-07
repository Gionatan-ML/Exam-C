//FINISH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char key;
    int value;
} HashMap;

typedef struct LinkedList{

    HashMap map;
    struct LinkedList *next;
    struct LinkedList *previous;

}LinkedList;

void saveInLD(char c, int len, LinkedList** head){
    
    LinkedList *ptr=malloc(sizeof(LinkedList));
    if(ptr==NULL){
        exit(0);
    }
    ptr->map.key=c;
    ptr->map.value=len;
    
    if(*head==NULL){
        ptr->previous=NULL;
        ptr->next=NULL;
        *head=ptr;
        return;
    }

    // aggiungo alla fine
    LinkedList *tail= *head;

    while(tail->next!=NULL){
        tail=tail->next;
    }

    tail->next=ptr;
    ptr->previous=tail;


    

}

void scompose(char* string, LinkedList** head){
    FILE* output=fopen("output.bin", "ab");
    if(output==NULL){
        exit(0);
    }

    int cont=0;

    fprintf(output,"Line: %s\n", string);

    for(int i=0; i<strlen(string); i++){
        if(string[i]!=string[i-1] || i+1==strlen(string)){
            if(i==0){
                cont++;
                continue;
            }
            cont= (i+1==strlen(string)) ? (cont+1):(cont);
            saveInLD(string[i-1], cont, head);
            fprintf(output, " %d: %c |", cont, string[i-1]);

            cont=0;

        }
        cont++;

    }
    fprintf(output,"\n");
    fflush(output);
    fclose(output);
}

void freeMemory(LinkedList** head){
    while(*head!=NULL){
        LinkedList *tmp= *head;
        *head=(*head)->next;
        free(tmp);
    }
    *head = NULL;
}

void printing(LinkedList* head){
    FILE* output=fopen("output.bin", "ab");
    if(output==NULL){
        exit(0);
    }
    int cont=0;
    fprintf(output, "Vettore di struct: \n");
    while(head!=NULL){
        fprintf(output,"%c -> %d\n", head->map.key, head->map.value);
        head=head->next;
        cont++;
    }
    fprintf(output,"\nLen: %d\n\n", cont);
    fflush(output);
    fclose(output);
}

int main(void){

    // cleaning
    FILE* output=fopen("output.bin", "wb");
    if(output==NULL){
        exit(0);
    }
    fclose(output);

    char bufferS[MAX];
    LinkedList *head = NULL;

    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(0);
    }

    while(fgets(bufferS, sizeof(bufferS), input)!=NULL){
        if(bufferS[strlen(bufferS)-1]=='\n'){
            bufferS[strlen(bufferS)-1]='\0';
        }
        scompose(bufferS, &head);
        printing(head);
        freeMemory(&head);
    }
    fclose(input);

    return 1;
}