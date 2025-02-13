#include <stdio.h>
#include <stdlib.h>

#define NMAX 20

typedef struct{
    int array[NMAX];
    int pt;
    int nval_np;
    int nval;
}Mystruct;

typedef struct LinkedList{

    int val;
    struct LinkedList* next;
    struct LinkedList* previous;

}LinkedList;

void fillLD(LinkedList** head, int* array) {
    for (int i = 0; i < array[0]; i++) {
        LinkedList* tmp = malloc(sizeof(LinkedList));
        if (tmp == NULL) {
            perror("Error allocating memory");
            exit(EXIT_FAILURE);
        }
        tmp->val = array[i + 1];
        tmp->next = *head;
        tmp->previous = NULL;
        if (*head != NULL) {
            (*head)->previous = tmp;
        }
        *head = tmp;
    }
}

void findOcc(LinkedList** head, int* array) {
    LinkedList* tmp = *head;
    for (int i = 0; i < array[0]; i++) {
        while (tmp != NULL) {
            if (array[i + 1] == tmp->val) {
                LinkedList* toDelete = tmp;
                if (tmp->previous != NULL) {                    
                    tmp->previous->next = tmp->next;
                } else {
                    *head = tmp->next;
                }
                if (tmp->next != NULL) {
                    tmp->next->previous = tmp->previous;
                }
                tmp = tmp->next;
                free(toDelete);
            } else {
                tmp = tmp->next;
            }
        }
        tmp = *head;
    }
}

void freeMem(LinkedList** head){
    LinkedList* ptr;
    while(*head!=NULL){
        ptr= *head;
        *head =(*head)->next;
        free(ptr);
    }
}

void init(int matrice[][NMAX], int* r){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    int c;
    do{
        
        if(fscanf(input, "%d", &c)==EOF) break;
        matrice[*r][0]=c;
        printf("%d ", matrice[*r][0]);
        for(int i=0; i<c; i++){
            fscanf(input, "%d", &matrice[*r][i+1]);
            printf("%d ", matrice[*r][i+1]);
        }
        *r+=1;
        printf("\n");

    }while(1);
}

void fillResult(LinkedList* head, Mystruct* result){
    int i=0;
    while(head!=NULL){
        (*result).array[i]=head->val;
        i++;
        head=head->next;
    }
    (*result).nval_np=i;
}

int main(void){
    int matrice[NMAX][NMAX];
    int r=0;
    init(matrice, &r);
    Mystruct result[NMAX];
    int lenStruct=0;
    for(int i=0; i<r; i++){
        LinkedList* head=NULL;
        result[i].nval=matrice[i][0];
        result[i].nval_np=0;
        result[i].pt=i;
        fillLD(&head, matrice[i]);
        for(int j=0; j<r; j++){
            if(j==i) continue;
            findOcc(&head, matrice[j]);
        }
        fillResult(head, &result[i]);
        freeMem(&head);
    }
    printf("\nResult:\n");
    for(int i=0; i<r; i++){
        printf("%d, %d, %d,[ ", result[i].pt, result[i].nval, result[i].nval_np);
        for(int j=0; j<result[i].nval_np; j++){
            printf("%d ", result[i].array[j]);
        }
        printf("]\n");
    }
    return 1;
}