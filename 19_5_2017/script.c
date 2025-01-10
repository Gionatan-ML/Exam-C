#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

void init(char matrice[][MAX], char *vett,int *R, int *C);
int findChr(char c, char* array, int* cont);
void sorting(int* array, int len);
void printing(int* array, int len);


int main(void){
    int R,C;
    char vett[MAX], matrice[MAX][MAX]; 
    int contVal=0;
    int newVett[MAX];

    init(matrice, vett, &R, &C);

    for(int i=0; i<strlen(vett); i++){
        contVal=0;
        newVett[i]=0;
        printf("\n %c:  ", vett[i]);
        for(int y=0; y<R; y++){
            newVett[i]+=findChr(vett[i], matrice[y], &contVal);
        }
    }
    printf("\nVett:");
    for(int i=0; i<strlen(vett); i++){
        printf("%d ", newVett[i]);
    }

    sorting(newVett, strlen(vett));
    printing(newVett, strlen(vett));

}
void init(char matrice[][MAX], char *vett,int *R, int *C){
    int x=0,y=0;
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(0);
    }

    int cont=0;
    char c;
    char pv_C;
    while((c=fgetc(input))!=EOF){
        if(c=='\n' && pv_C=='\n'){
            break;
        }
        pv_C=c;

        if(c==' '){
            continue;
        }
        else if(c=='\n'){
            y++;
            *C=x;
            x=0;
            printf("\n");
            continue;
        }
        matrice[y][x]=c;
        printf("%c ", matrice[y][x]);
        x++;
    }
    *R=y;
    printf("\nDimensioni Matrice: %d, %d", *R, *C);

    while(( c=fgetc(input) ) != EOF){
        if(c==' ' || c=='\n') continue;
        vett[cont]=c;
        cont++;
    }
    vett[cont]='\0';
    printf("\nVettore: %s", vett);

    fclose(input);
}


int findChr(char c, char* array, int* cont){
    int val=0;
    for(int i=0; i<strlen(array); i++){
        if(c==array[i]){
            val+= *cont * i;
            printf("%d * %d | ", i, *cont);
            *cont+=1;
        }
    }
    return val;
}


void sorting(int* array, int len){

    // buble_sort O(n)= n^2, best case: n

    int cont;
    do{
        cont=0;
        for(int i=0; i<len-1; i++){
            if(array[i]<array[i+1]){
                int tmp=array[i];
                array[i]=array[i+1];
                array[i+1]=tmp;
                cont++;
            }
        }

    }while(cont!=0);
}
void printing(int* array, int len){
    FILE* output=fopen("output.bin", "wb");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }

    fprintf(output ,"Vettore Ordinato -> ");
    for(int i=0; i<len; i++){
        fprintf(output, "%d ", array[i]);
    }

    fflush(output);
    fclose(output);
}