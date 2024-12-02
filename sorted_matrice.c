
// UNFINISHED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ROW 2
#define MAX_COLS 1
#define MAX 4
#define MAX_VALUES 20

int matrice[MAX][MAX];
int lenght=0;
 int cols_sum=0, rows_sum=0;

typedef struct MyStruct{
    int row;
    int cols[MAX_ROW];
    int sum[MAX_ROW];
    int values[MAX_ROW];
}MyStruct;


void creationStruct(MyStruct*** str, int lenght_find){
    if(lenght<lenght_find){
        lenght++;
        *str=realloc(*str,sizeof(MyStruct*)*lenght);
        if(*str==NULL){
            exit(0);
        }

    }
    (*str)[lenght_find-1]=malloc(sizeof(MyStruct));
    if((*str)[lenght_find-1]==NULL){
        exit(0);
    }

    
}

void init(MyStruct*** str){
    int cont=0, lenght_finded=0;
    printf("\nMatrice riempita casaulmente:\n");
    for(int y=0; y<MAX; y++){
        for(int x=0; x<MAX; x++){
            matrice[y][x]=rand()%MAX_VALUES-10;// nel caso tutti i valori siano 20, per fare in modo che la somma sia pari a 20 dobbiamo avere almeno un valore negativo (nel peggiore dei casi) che possa far avverare la condizione
            if(matrice[y][x]<0){
                cont++;
                if(cont>MAX_ROW){
                    while(matrice[y][x]<0){
                        matrice[y][x]=rand()%MAX_VALUES-2;
                    }
                    cont--;
                }
            }
            printf("%d ", matrice[y][x]);
        }
        printf("\n");
        cont=0;
    }
    cont=0;
    for(int y=0; y<MAX; y++){
        for(int x=0; x<MAX; x++){
            if(matrice[x][y]<0){
                cont++;
                if(cont>MAX_COLS){
                    while(matrice[x][y]<0){
                        matrice[x][y]=rand()%MAX_VALUES-2;
                    }
                    cont--;
                }
            }
        }
        cont=0;
    }
    cont=0;
    printf("\n\n\n");
    for(int y=0; y<MAX; y++){
        for(int x=0; x<MAX; x++){
            printf("%d ", matrice[y][x]);
            if(matrice[y][x]<0 && cont==0){
                lenght_finded++;
                creationStruct(str, lenght_finded);
                (*str)[lenght_finded-1]->row=y;
                (*str)[lenght_finded-1]->cols[0]=x;
                (*str)[lenght_finded-1]->values[0]=matrice[y][x];
                cols_sum+=matrice[y][x];
                cont++;
            }
            else if(matrice[y][x]<0 && cont==1){
                (*str)[lenght_finded-1]->cols[1]=x;
                (*str)[lenght_finded-1]->values[1]=matrice[y][x];
                cols_sum+=matrice[y][x];
                cont++;
            }
        }
        printf("\n");
        cont=0;
    }
    printf("\nInizio processo di sostituzione valori...");
    //_sleep(2000); // se consideriamo una matrice piccola il processo sarà molto rapido

}

int main(void){
    srand(time(NULL));
    bool go=false, first_time=false;
    MyStruct** str=malloc(sizeof(MyStruct*)*2);
    if(str==NULL){
        exit(0);
    }
    str[lenght]=NULL;
    init(&str);
    
    // 1. Condition, cols_sum>20
    while(cols_sum<20){
        cols_sum=0;
        for(int i=0; i<lenght; i++){
            for(int j=0; j<2; j++){
                if(str[i]->values[j]<-1000){
                    continue;
                }
                str[i]->values[j]=rand()%20;
                cols_sum+=str[i]->values[j];
            }
        }
    }
    // 2. Condition, rows_sum=20

    for(int y=0; y<MAX; y++){
        rows_sum=0;
        for(int j=0; j<lenght; j++){
            if(str[j]->row==y){
                for(int x=0; x<MAX; x++){
                    for(int z=0; z<2; z++){
                        if(x==str[j]->cols[z]){
                            rows_sum+=str[j]->values[z];
                            go=true;
                        }
                    }
                    if(go==true) continue;
                    rows_sum+=matrice[y][x];
                }
                while(rows_sum!=20 || cols_sum<20){
                    rows_sum=0;
                    for(int x=0; x<MAX; x++){
                        for(int z=0; z<2; z++){
                                if(x==str[j]->cols[z]){
                                    cols_sum+=(-str[j]->values[z]);
                                    str[j]->values[z]=rand()%15-15;
                                    rows_sum+=str[j]->values[z];
                                    cols_sum+=str[j]->values[z];
                                    go=true;
                                }
                            }
                            if(go==true) continue;
                            rows_sum+=matrice[y][x];
                    }   
                }
                printf("Cols: %d, Row: %d", cols_sum, rows_sum);
            }
        }
    }
    printf("Cols: %d, Row: %d", cols_sum, rows_sum);
}
