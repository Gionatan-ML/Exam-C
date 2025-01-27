#include <stdio.h>
#include <stdlib.h>

#define MAX 2

void fill_matrice(int matrice[][MAX]){
    
    int halfSize=MAX/2;
    for(int y=0; y<MAX; y++){
        int num1=0;
        if(y<halfSize){
            for(int x=0; x<MAX; x++){
                printf("\n Inserisci un numero pari e maggiore di 0: ");
                do{
                    scanf("%d", &num1);
                    if(num1%2!=0 || num1==0) printf("\n Try again:");    
                }while(num1%2!=0 || num1==0);
                matrice[y][x]=num1;
            }
        }
        if(y>=halfSize){
            for(int x=0; x<MAX; x++){
                printf("\n Inserisci un numero dispari e maggiore di 0: ");
                do{
                    scanf("%d", &num1);
                    if(num1%2==0 || num1==0) printf("\n Try again:");    
                }while(num1%2==0 || num1==0);
                matrice[y][x]=num1;
            }
        }
            
    }
    printf("matrice: \n");
    for(int y=0; y<MAX; y++){
        for(int x=0; x<MAX; x++){
            printf("%d ", matrice[y][x]);
        }
        printf("\n ");
    }
}

int main(void){
    int matrice[MAX][MAX];
    fill_matrice(matrice);
}