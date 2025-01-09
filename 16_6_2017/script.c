//FINISHED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

void init(char matrice[][MAX], int* R, int* C);
int search_V(char matrice[][MAX], int pt_O, int pt_V, char *string, int R, int C);
int search_O(char matrice[][MAX], int pt_O, int pt_V, char *string, int R, int C);
int search_D(char matrice[][MAX], int pt_O, int pt_V, char *string, int R, int C);




typedef enum {
    VERTICAL = 'V',
    ORIZZONTALE = 'O',
    DIAGONALE = 'D'
} Direction;

typedef struct{
    int pt_O;
    int pt_V;
    Direction direction;
}MyStruct;


void printing(MyStruct result, char* string){
    FILE* output=fopen("output.bin", "ab");
    if(output==NULL){
        perror("File not found");
        exit(0);
    }
    fprintf(output ,"%s -> ( %d, %d, '%c' )\n", string, result.pt_O, result.pt_V, result.direction);

    fflush(output);
    fclose(output);

}


int main(void){

    FILE* output=fopen("output.bin", "wb");
    if(output==NULL){
        perror("File not found");
        exit(0);
    }
    fclose(output);

    char pass;
    bool find;
    char string[MAX];
    char matrice[MAX][MAX];
    MyStruct result;
    int R,C;
    init(matrice, &R, &C);
    do{
        find=false;
        printf("\nInserisci la parola da cercare: ");
        scanf(" %s", string);
        for(int y=0; y<R; y++){
            for(int x=0; x<C; x++){
                if(matrice[y][x]==string[0]){
                    if(search_D(matrice, x, y, string, R, C)){
                        result.direction=DIAGONALE;
                        result.pt_O=x;
                        result.pt_V=y;
                        find=true;
                        printing(result, string);
                        break;
                    }
                    if(search_O(matrice, x, y, string, R, C)){
                        result.direction=ORIZZONTALE;
                        result.pt_O=x;
                        result.pt_V=y;
                        find=true;
                        printing(result, string);
                        break;   
                    }
                    if(search_V(matrice, x, y, string, R, C)){
                        result.direction=VERTICAL;
                        result.pt_O=x;
                        result.pt_V=y;
                        find=true;
                        printing(result, string);
                        break;
                    }
                }
            }
        }
        if(!find){
            printf("\nParola non trovata");
        }
        printf("\nVuoi continuare? [y/n]: ");
        scanf(" %c", &pass);
        memset(string, 0, sizeof(string));
    }while(pass!='n');

}

void init(char matrice[][MAX],int* R, int* C){
    char buffer[MAX];
    int cont_C=0, cont_R=0;
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }

    while(fgets(buffer, sizeof(buffer), input)!=NULL){
        cont_C=0;
        for(int i=0; i<strlen(buffer); i++){
            if(buffer[i]!= ' ' && buffer[i]!= '\n'){
                matrice[cont_R][cont_C]=buffer[i];
                printf("%c ", matrice[cont_R][cont_C]);
                cont_C++;
            }
        }
        *C=cont_C;
        cont_R++;
        printf("\n");
    }
    *R=cont_R;

    fflush(input);
    fclose(input);
}

int search_V(char matrice[][MAX], int pt_O, int pt_V, char* string, int R, int C){
    int cont=0;
    for(int y=pt_V; y<R; y++){
        if(cont==strlen(string)) break;
        
        if(matrice[y][pt_O]!=string[cont]){
            return 0;
        }
        cont++;
    }
    if(cont==strlen(string)) return 1;
    else return 0;
}
int search_D(char matrice[][MAX], int pt_O, int pt_V, char* string, int R, int C){
    int cont=0;
    int y=pt_V;
    int x=pt_O;
    while(y<R && x<R && cont<strlen(string)){
        if(string[cont]!=matrice[y][x]){
            return 0;
        }

        y++;
        x++;
        cont++;
    }
    if(y<=R && x<=R && cont==strlen(string)){
        return 1;
    }
    else{
        return 0;
    }
}
int search_O(char matrice[][MAX], int pt_O, int pt_V, char* string, int R, int C){
    int cont=0;
    for(int x=pt_O; x<C; x++){
        if(string[cont]!=matrice[pt_V][x]){
            return 0;
        }
        cont++;
    }
    if(cont==strlen(string)){
    
        return 1;
    }
    else{
        return 0;
    }
}
