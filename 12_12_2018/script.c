//FINISH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 20

//global variables
char filename_in[]="input.txt";
char filename_out[]="output.bin";
int r1,c1, r2,c2;

//functions
void init(int matrice1[][MAX], int matrice2[][MAX]);
void sorting1(int matrice[][MAX]);
void sorting2(int matrice[][MAX]);
void print_matrice(int matrice[][MAX], int choose);
void swap(int matrice[][MAX], int x1, int x2);
void prdRigxCol(int matrice1[][MAX], int matrice2[][MAX]);
void printFile(int matrice[][MAX]);

int main(void){
    int matrice1[MAX][MAX], matrice2[MAX][MAX];

    init(matrice1, matrice2);
    sorting1(matrice1);
    print_matrice(matrice1, 0);
    sorting2(matrice2);
    print_matrice(matrice2, 1);
    prdRigxCol(matrice1, matrice2);
}


void init(int matrice1[][MAX], int matrice2[][MAX]){
    FILE* input=fopen(filename_in, "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    char buffer[MAX];
    fgets(buffer, MAX, input);

    sscanf(buffer, "%d%*c%d", &r1, &c1);
    printf("r1: %d, c1: %d\n", r1, c1);
    for(int y=0; y<r1; y++){
        for(int x=0; x<c1; x++){
            fscanf(input, "%d ", &matrice1[y][x]);
            printf("%d ", matrice1[y][x]);
        }
        printf("\n");
    }

    fgets(buffer, MAX, input);

    sscanf(buffer, "%d%*c%d", &r2, &c2);
    printf("r2: %d, c2: %d\n", r2, c2);
    for(int y=0; y<r2; y++){
        for(int x=0; x<c2; x++){
            fscanf(input, "%d ", &matrice2[y][x]);
            printf("%d ", matrice2[y][x]);
        }
        printf("\n");
    }
   
    
}

void swap( int matrice[][MAX] ,int x1, int x2){
    for(int y=0; y<r2; y++){
        int tmp=matrice[y][x1];
        matrice[y][x1]=matrice[y][x2];
        matrice[y][x2]=tmp;
    }
}

//buble sort
void sorting1(int matrice[][MAX]){
    int cont;

    for(int y=0; y<r1; y++){
        do{
            cont=0;
            for(int x=0; x<c1-1; x++){
                if(matrice[y][x]>matrice[y][x+1]){
                    int tmp=matrice[y][x];
                    matrice[y][x]=matrice[y][x+1];
                    matrice[y][x+1]=tmp;
                    cont++;
                }
            }

        }while(cont!=0);
    }
}
void sorting2(int matrice[][MAX]){
    int sums[MAX];
    int cont;

    for(int x=0; x<c2; x++){
        for(int y=0; y<r2; y++){
            sums[x]+=matrice[y][x];
        }
    }
    
    do{
        cont=0;
        for(int i=0; i<c2-1; i++){
            if(sums[i]<sums[i+1]){
                swap(matrice, i, i+1);
                int tmp=sums[i];
                sums[i]=sums[i+1];
                sums[i+1]=tmp;
                cont++;
            }
        }
        
    }while(cont!=0);
}

void print_matrice(int matrice[][MAX], int choose){
    if(choose==0){
        printf("Prima Matrice:\n");
        for(int y=0; y<r1; y++){
            for(int x=0; x<c1; x++){
                printf("%d ", matrice[y][x]);
            }
            printf("\n ");
        }
    }
    else if(choose==1){
        printf("Seconda Matrice:\n");
        for(int y=0; y<r2; y++){
            for(int x=0; x<c2; x++){
                printf("%d ", matrice[y][x]);
            }
            printf("\n ");
        }
    }
    else{
        printf("Error");
    }

}
void prdRigxCol(int matrice1[][MAX], int matrice2[][MAX]){
    printf("\nRxC: \n");

    int m_buffer[MAX][MAX];
    for(int x2=0; x2<c2; x2++){
        for(int y1=0; y1<r1; y1++){
            m_buffer[y1][x2]=0;
            for(int y2=0; y2<r2; y2++){
                m_buffer[y1][x2]+= matrice1[y1][y2]*matrice2[y2][x2];
            }
        }
    }
    for(int y=0; y<r1; y++){
        for(int x=0; x<c2; x++){
            printf("%d ", m_buffer[y][x]);
        }
        printf("\n");
    }
    printFile(m_buffer);
}
void printFile(int matrice[][MAX]){
    FILE* output=fopen(filename_out, "w");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }
    for(int y=0; y<r1; y++){
        for(int x=0; x<c2; x++){
            fprintf(output,"%d ", matrice[y][x]);
        }
        fprintf(output,"\n");
    }



}