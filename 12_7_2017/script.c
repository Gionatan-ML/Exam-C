#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 300
#define L_M 10

typedef struct{
    char chr;
    int y;
    int x;
} MyStruct;

typedef struct LinkedList{
    MyStruct value;
    struct LinkedList* next;
}LinkedList;

//global variables
char buffer[MAX];

//function
void add_list(LinkedList** head, char y_c, char x_c, char c){
    LinkedList* tmp= malloc(sizeof(LinkedList));
    if(tmp==NULL){
        exit(EXIT_FAILURE);
    }
    char x[2], y[2];
    x[0]=x_c;
    x[1]='\0';
    y[0]=y_c;
    y[1]='\0';

    if(*head==NULL){
        (*head)=tmp;
        (*head)->value.chr=c;
        (*head)->value.x=atoi(x);
        (*head)->value.y=atoi(y);
        (*head)->next=NULL;
        return;
    }
    else{
        LinkedList* ptr= *head;
        while(ptr->next!=NULL){
            ptr=ptr->next;
        }
        tmp->value.chr=c;
        tmp->value.x=atoi(x);
        tmp->value.y=atoi(y);
        tmp->next=NULL;
        ptr->next=tmp;
        
    }
}

void print_List(LinkedList* head){
    while(head!=NULL){
        printf("%c, x: %d, y: %d\n", head->value.chr, head->value.x, head->value.y);
        head=head->next;
    }
}
void save_inMatrix(LinkedList* head, char matrice[][L_M]){
    for(int y=0; y<L_M; y++){
        for(int x=0; x<L_M; x++){
            matrice[y][x]='0';
        }
    }
    for(int y=0; y<L_M; y++){
        for(int x=0; x<L_M; x++){
            if(head!=NULL){
                if(head->value.y==y && head->value.x==x){
                    matrice[y][x]=head->value.chr;
                    head=head->next;
                }
            }
            printf("%c ", matrice[y][x]);
        }
        printf("\n");
    }

}

int main(void){
    
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }

    char matrice[L_M][L_M];
    LinkedList* head=NULL;
    int x,y;
    char c;
    char* error=fgets(buffer, MAX, input);;

    while(strcmp(buffer,"")>0 && error!=NULL){
        int i=0;
        while(i<strlen(buffer)){
            
            if((int)buffer[i]<48 || (int)buffer[i]>57){
                int cont=0;
                c=buffer[i];
           
                i+=1;
                while((int)buffer[i]>=48 && (int) buffer[i]<=57 && i<strlen(buffer)){
                    cont++;
                    
                    if(cont>2) break;
                    i+=1;
                }
                if(cont==2){
                    add_list(&head, buffer[i-2], buffer[i-1], c);
                }
        
            }
            else{
                i++;
            }
        }

        error=fgets(buffer, MAX, input);
    }
    save_inMatrix(head, matrice);
    print_List(head);
    
    return 1;
}