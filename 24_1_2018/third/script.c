//FINISHED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NMAX 50

int matrice_0[NMAX][NMAX];
int matrice_1[3][NMAX*NMAX];
int C,R;

void init(){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(0);
    }
    fscanf(input, "%d %d\n", &R, &C);
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fscanf(input, "%d ", &matrice_0[y][x]);
            printf("%d ", matrice_0[y][x]);
        }
        printf("\n");
    }

    fflush(input);
    fclose(input);

}

void parsing(){
    //save in the first line the value of matrice_0
    int cont=0;
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            matrice_1[0][cont]=matrice_0[y][x];
            matrice_1[1][cont]=y;
            matrice_1[2][cont]=x;
            cont++;
        }
    }


}
void sorting(){
    int len=R*C;
    int isChange;
    int array[3];
    // sorting with the bubleSort
    do{
        isChange=0;

        for(int i=0; i<len; i++){
            if(matrice_1[0][i]<matrice_1[0][i+1]){
                array[0]=matrice_1[0][i];
                array[1]=matrice_1[1][i];
                array[2]=matrice_1[2][i];

                matrice_1[0][i]=matrice_1[0][i+1];
                matrice_1[1][i]=matrice_1[1][i+1];
                matrice_1[2][i]=matrice_1[2][i+1];

                matrice_1[0][i+1]=array[0];
                matrice_1[1][i+1]=array[1];
                matrice_1[2][i+1]=array[2];

                isChange++;
            }
        }


    }while(isChange!=0);
}

void printing(){
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }
    fprintf(output,"\n");
    int len=R*C;
    int noPrint[NMAX];
    int Alength=0;
    bool pass;

    for(int y=0; y<3; y++){
        for(int x=0; x<len; x++){
            if(y==0 && matrice_1[0][x]==0){
                noPrint[Alength]=x;
                Alength++;
                continue;
            }
            pass=true;
            if(y>0){
                for(int i=0; i<Alength; i++){
                    if(x==noPrint[i]){
                        pass=false;
                        break;
                    }
                }
            }
            if(pass==true){
                fprintf(output, "%d ", matrice_1[y][x]);
            }
        }
        fprintf(output,"\n");

    }
    fflush(output);
    fclose(output);
}

int main(void){
    init();
    parsing();
    sorting();
    printing();
    




    return 1;
}