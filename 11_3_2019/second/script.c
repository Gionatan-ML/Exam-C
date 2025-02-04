#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct{
    int n_occ;
    int y;
    int x;
    int eq_val;
    int array[MAX];
}MyStruct;

void init(int* v1, int m2[][MAX], int*r, int* c, int* lenV1){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    char chr;
    char num[2];
    printf("\nv1: ");
    while((chr=fgetc(input))!='\n'){
        if(chr==' ') continue;
        num[0]=chr;
        num[1]='\0';
        v1[*lenV1]=atoi(num);
        printf("%d ", v1[*lenV1]);
        *lenV1+=1;
    }
    fscanf(input, "%d %d\n", r, c);
    printf("\nMatrice:\n");
    for(int y=0; y< *r; y++){
        for(int x=0; x< *c; x++){
            fscanf(input, "%d ", &m2[y][x]);
            printf("%d ", m2[y][x]);
        }
        printf("\n");
    }
}

int controll(int m2[][MAX], int y_0, int x_0, int* v1, int lenV1, int r, int c){
    int cont=0;
    int z=0;
    for(int i=0; i<lenV1; i++){
        if(x_0+cont<c && m2[y_0][x_0+cont]==v1[i]){
            cont++;
        }
        else if(x_0+cont>=c && y_0+1<r){
            if(m2[y_0+1][z]==v1[i]){
                z++;
            }
        }
        else{
            break;
        }
    }
    return (cont+z);
}

int main(void){
    int v1[MAX];
    int lenV1=0;
    int m2[MAX][MAX];
    int r,c;

    init(v1,m2,&r,&c, &lenV1);
    MyStruct result[MAX];
    int lenStruct=0;

    for(int y=0; y<r; y++){
        for(int x=0; x<c; x++){
            if(m2[y][x]==v1[0]){
                result[lenStruct].eq_val=controll(m2, y,x, v1, lenV1, r,c);
                result[lenStruct].n_occ=lenStruct;
                result[lenStruct].y=y;
                result[lenStruct].x=x;
                printf(" %d ,[ %d, %d ], %d { ",result[lenStruct].n_occ, result[lenStruct].y, result[lenStruct].x, result[lenStruct].eq_val );
                for(int i=0; i<result[lenStruct].eq_val; i++){
                    result[lenStruct].array[i]=v1[i];
                    printf("%d ", result[lenStruct].array[i]);
                }
                printf("}\n");
                lenStruct++;

            }
        }
    }

    return 1;
}