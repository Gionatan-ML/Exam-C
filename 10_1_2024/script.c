
//FINISHED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_MAX 100
#define M_MAX 5
#define NUM_MAX 10

typedef struct{
    int indice;
    int n;
    int valori[N_MAX];
    float media;
}MyStruct;

typedef struct{
    int matrice[M_MAX][M_MAX];
    int cont;

}Pmatrice;

void space_struct(int lenght1, MyStruct*** str, int* _lenght){
    if(*_lenght<=lenght1){
        (*_lenght)++;
        *str=realloc(*str,sizeof(MyStruct*)*(*_lenght+1));
        if(*str==NULL){
            exit(0);
        }
        (*str)[lenght1]=malloc(sizeof(MyStruct));
        if((*str)[lenght1]==NULL){
            exit(0);
        }
    }
    (*str)[lenght1]->n=0;
}

int palindroma(int* array, int count) {
    int i = 0, j = count - 1;
    while (i < j) {
        if (array[i] != array[j]) {
            return 0;  // Not palindrome
        }
        i++;
        j--;
    }
    return 1;  // Is palindrome
}

void init(){
    printf("\n");
    int R, C;
    FILE* file=fopen("input.txt", "w");
    if(file==NULL){
        exit(0);
    }
    R=rand()%M_MAX+3;
    C=rand()%M_MAX+3;
    fprintf(file ,"%d %d\n\n", R,C);
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            int value=rand()%NUM_MAX;
            fprintf(file,"%d ",value);
        }
        fprintf(file,"\n");
    }
    fflush(file);
    fclose(file);


}

//bublesort
void bubblesort(MyStruct** str, int length) {
    int swapped;
    do {
        swapped = 0;
        for (int i = 0; i < length - 1; i++) { // confronta ogni coppia adiacente
            if (str[i]->media < str[i+1]->media) {
                // Scambia gli elementi
                MyStruct* tmp = str[i];
                str[i] = str[i+1];
                str[i+1] = tmp;
                swapped = 1; // indica che c'è stato uno scambio
            }
        }
    } while (swapped);
}

int main(void){
    srand(time(NULL));
    init();

    FILE* file=fopen("input.txt","r+");
    if(file==NULL){
        exit(0);
    }

    MyStruct**sorted=malloc(sizeof(MyStruct*));
    sorted[0]=malloc(sizeof(MyStruct));
    if(sorted[0]==NULL){
        exit(1);
    }
    sorted[0]->n=0;

    Pmatrice demo;
    demo.cont=0;

    int _lenght=1, C,R;
    int cont_struct=0;
    fscanf(file,"%d",&R);
    fscanf(file,"%d\n",&C);
    int array_C[C];

    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fscanf(file,"%d ",&array_C[x]);
        }
        if(palindroma(array_C,R)!=1){
            for(int j=0; j<R; j++){
                demo.matrice[demo.cont][j]=array_C[j];
            }
            if(C<M_MAX){
                for(int z=R; z<M_MAX; z++){
                    demo.matrice[demo.cont][z]=-1;
                }
            }
            demo.cont+=1;
        }
    }
    fflush(file);
    fclose(file);

    int sum=0;
    for(int y=0; y<demo.cont; y++){
        space_struct(y,&sorted,&_lenght);
        sorted[y]->indice=y;
        for(int x=0; x<C; x++){
            sorted[y]->valori[x]=demo.matrice[x][y]; // voglio salvare i valori delle colonne
            sorted[y]->n+=1;
            sum+=sorted[y]->valori[x];
        }
        sorted[y]->media=(float)sum/sorted[y]->n;
        sum=0;
    }
    //sort the struct with the bublesort
    bubblesort(sorted,_lenght);

    printf("\n\n");
    
    FILE* output=fopen("output.bin", "w");

    for(int y=0; y<_lenght; y++){
        if(sorted[y]->media>=0){
            printf("\n{ Array of the %d, with %f media: ", sorted[y]->indice, sorted[y]->media);
            fprintf(output,"\n{ Array of the %d, with %f media: ", sorted[y]->indice, sorted[y]->media);
            for(int x=0; x<sorted[y]->n; x++){
                printf("%d ", sorted[y]->valori[x]);
                fprintf(output,"%d ", sorted[y]->valori[x]);
            }
            printf(" }");
            fprintf(output," }");
        }
    }
    fflush(output);
    fclose(output);





    


}