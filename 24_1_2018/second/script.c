// FINISHED

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int matrice[MAX][MAX];
int R,C;

typedef struct{
    float media;
    char type;
    int value;
    int sum;
}MyStruct;

typedef struct{
    float *array;
    int length;
}ArrayLength;

void init(){
    

    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d %d\n", &R, &C);

    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fscanf(input, "%d ", &matrice[y][x]);
            printf("%d ", matrice[y][x]);
        }
        printf("\n");
    }
    fclose(input);

}

char findValue(int val, int y_0, int x_0){
    
    // find in the rig
    int sum=0;
    for(int x=0; x<C; x++){
        if(x==x_0) continue;
        sum+=matrice[y_0][x];
    }
    if(sum==val){
        return 'r';
    }

    // find in the col 
    sum=0;
    for(int y=0; y<R; y++){
        if(y==y_0) continue;
        sum+=matrice[y][x_0];
    }
    if(sum==val){
        return 'c';
    }
    else{
        return 'f';
    }
}

void calcMedia(ArrayLength* arrayRig, ArrayLength* arrayCol, int* sumCol, int* sumRig){
    
    // calc media righe
    printf("\nSums Rig: ");
    int media;
    int sum;
    for(int y=0; y<R; y++){
        sum=0;
        for(int x=0; x<C; x++){
            sum+=matrice[y][x];
        }
        // controlla qui
        arrayRig->array[arrayRig->length]=(float) sum/C;
        sumRig[y]=sum;
        arrayRig->length+=1;
        printf(" %d", sumRig[y]);
    }
    // calc media col
    printf("\nSums Col: ");
    for(int x=0; x<C; x++){
        sum=0;
        for(int y=0; y<R; y++){
            sum+=matrice[y][x];
        }
        sumCol[x]=sum;
        arrayCol->array[arrayCol->length]= (float) sum/R;
        arrayCol->length+=1;
        printf(" %d", sumCol[x]);
    }

}

void sorting(MyStruct* result, int len){
    int isChange;
    do{
        isChange=0;
        for(int i=0; i<len-1; i++){
            if(result[i].media<result[i+1].media){
                MyStruct tmp=result[i];
                result[i]=result[i+1];
                result[i+1]=tmp;
                isChange+=1;
            }
        }

    }while(isChange!=0);
}

int main(void){
    init();
    int cont_rig=0, cont_col=0;
    MyStruct result[MAX];
    int len=0;
    ArrayLength arrayRig, arrayCol;
    int sumCol[MAX], sumRig[MAX];

    arrayRig.array= malloc(sizeof(int)*MAX);
    arrayCol.array=malloc(sizeof(int)*MAX);

    if(arrayRig.array == NULL || arrayCol.array == NULL){
        exit(EXIT_FAILURE);
    }
    arrayCol.length=0;
    arrayRig.length=0;

    // calc media of rig and col
    calcMedia(&arrayRig, &arrayCol, sumCol, sumRig);

    char tmp;
    for(int y=0; y<R; y++){
        cont_rig=0;
        for(int x=0; x<C; x++){
            // find if is the sum of rig or col
            tmp=findValue(matrice[y][x], y,x);
            if(tmp!='f'){
                result[len].value= matrice[y][x];
                result[len].type=tmp;
                // assign media and sum in function of his type
                if(result[len].type=='r' && cont_rig==0){
                    result[len].sum= sumRig[y];
                    result[len].media=arrayRig.array[y];
                    cont_rig++;
                }
                else if(cont_col==0){
                    result[len].sum= sumCol[x];
                    result[len].media=arrayCol.array[x];
                    cont_col++;
                }
                len++;
            }

        }
        cont_col=0;
    }
    // using buble sort for sorting the array of struct
    sorting(result, len);

    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<len; i++){
        fprintf(output, "%.2f, %d, %c, %d\n", result[i].media, result[i].sum, result[i].type, result[i].value);
    }
    fclose(output);

}