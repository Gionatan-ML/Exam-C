#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 10
#define MAX 20
int r=0;

void printASCII(int *array, int len){
    for(int i=0; i<len; i++){
        printf("%c", (char)array[i]);
    }
}
void saveInMatrix(char *buffer, int matrix[][MAX]){
    int cont=0;
    int i=0;
    do{
        matrix[r][cont+1]=buffer[i];
        cont++;
        i++;
    }while(cont<=N_MAX && i<strlen(buffer));
    matrix[r][0]=cont;
    r++;
}
int main(void){
    int isFinish=0;
    int matrice[MAX][MAX];
    char buffer[MAX];

    do{
        isFinish=0;
        printf("\nInserisci una frase: ");
        scanf(" %s", buffer);
        saveInMatrix(buffer, matrice);
        printf("\nVuoi continuare:[0,1]: ");
        scanf("%d", &isFinish);
    }while(!isFinish); 
    for(int i=0; i<r; i++){
        for(int j=0; j<matrice[i][0]; j++){
            printf("%d ", matrice[i][j]);
        }
        printf(" -> ");
        printASCII(matrice[i], matrice[i][0]);
        printf("\n");
    }
    return 1;
}