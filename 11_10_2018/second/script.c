#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX 50

typedef struct{
    int values[MAX];
    int key;
}HashMap;

int matrice[MAX][MAX];
int r,c;

void init(int* delVal, int* lenDel){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d %d\n", &r, &c);
    for(int y=0; y<r; y++){
        for(int x=0; x<c; x++){
            fscanf(input, "%d", &matrice[y][x]);
            printf("%d ", matrice[y][x] );
            if(matrice[y][x]==0){
                delVal[*lenDel]=x;
                printf("\nx: %d\n", x);
                *lenDel+=1;
            }
        }
        printf("\n");
    }
}
int parseValue(HashMap* map, int lenMap, int new_matrice[][MAX]){
    bool find;
    int x_new=0;
    for(int x=0; x<c; x++){
        find=false;
        for(int i=0; i<lenMap; i++){
            if(x==map[i].key){
                find=true;
                break;
            }
        }
        if(find) continue;
        for(int y=0; y<r; y++){
            new_matrice[y][x_new]=matrice[y][x];
        }
        x_new++;
    }
    printf("New Matrice:\n");
    for(int y=0; y<r; y++){
        for(int x=0; x<x_new; x++){
            printf("%d ", new_matrice[y][x]);
        }
        printf("\n");
    }
    return x_new;
}

int main() {

    HashMap* map = malloc(sizeof(HashMap) * MAX);
    int lenMap=0;
    if(map==NULL){
        exit(EXIT_FAILURE);
    }
    int delVal[MAX];
    int lenDel=0;
    int c_new;
    int new_matrice[MAX][MAX];
    init(delVal, &lenDel);
    bool find;

    printf("Struct:\n");
    for(int i=0; i<lenDel; i++){
        find=false;
        for(int j=0; j<lenDel; j++){
            if(i==j) continue;
            if(delVal[i]==delVal[j]){
                find=true;
                break;
            }
        }
        if(!find){
            map[lenMap].key=delVal[i];
            for(int y=0; y<r; y++){
                map[lenMap].values[y]=matrice[y][delVal[i]];
                printf("%d ",map[lenMap].values[y] );
            }
            lenMap+=1;
            printf("\n");
        }
    }
    c_new=parseValue(map, lenMap, new_matrice);
    for(int x=0; x<lenMap; x++){
        
    }


    
    free(map);

    return 0;
}