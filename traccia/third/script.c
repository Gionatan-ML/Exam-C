#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

typedef struct{
    char key;
    int occ;
    int value;
}HashMap;

char filename_in[]="input.txt";
char filename_out[]="output.bin";

void printing(HashMap* map, int len){
    FILE* output=fopen(filename_out, "wb");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<len; i++){
        fprintf(output, "Val: %c, Occ: %d, Somma: %d\n", map[i].key, map[i].occ, map[i].value);
    }
}

void sorting(HashMap* map, int len){
    bool sorted;
    do{
        sorted=true;
        for(int i=0; i<len-1; i++){
            if(map[i].value<map[i+1].value){
                HashMap tmp=map[i];
                map[i]=map[i+1];
                map[i+1]=tmp;
                sorted=false;
            }
        }

    }while(!sorted);
}

void findOcc(HashMap *map, char matrice[][MAX], int r, int c){
    for(int y=0; y<r; y++){
        for(int x=0; x<c; x++){
            if(matrice[y][x]== (*map).key){
                (*map).value+= y*x;
                (*map).occ+=1;
            }
        }
    }
}

void init(char matrice[][MAX], char* array, int* r, int* c, int* lenArray){
    FILE* input=fopen(filename_in, "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d %d\n", r,c);
    printf("Matrice:\n");
    for(int y=0; y< *r; y++){
        for(int x=0; x< *c; x++){
            fscanf(input, "%c ", &matrice[y][x]);
            printf("%c ", matrice[y][x]);
        }
        printf("\n");
    }
    printf("\nArray: ");
    char chr;
    while((chr=fgetc(input))!=EOF){
        if(chr==' ') continue;
        array[*lenArray]=chr;
        printf("%c ", array[*lenArray]);
        *lenArray+=1;
    }
}

int main(void){
    char matrice[MAX][MAX];
    char array[MAX];
    int r,c,lenArray=0;
    init(matrice, array, &r,&c, &lenArray);
    HashMap map[MAX];
    for(int i=0; i<lenArray; i++){
        map[i].key=array[i];
        map[i].value=0;
        map[i].occ=0;
        findOcc(&map[i], matrice, r,c);
    }
    sorting(map, lenArray);
    printing(map, lenArray);
}