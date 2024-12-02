//FINISHED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N_MAX 100

typedef struct{
    int indx;
    int n;
    int valori[N_MAX];
    float nmass;
}MyStruct;

typedef struct controll
{
    int no_indx[20];
    int lenght;
}controll;

int R,C, n_buffer=0,max=0;



void palindrome(int **matrice, MyStruct** buffer){
    bool pal;
    int max_r=0;
    controll controll;
    controll.lenght=0;

    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(1);
    }

    fscanf(input, "%d ", &R);
    fscanf(input, "%d", &C);

    for(int x=0; x<C; x++){
        pal=true;
        int j=R-1;
        for(int y=0; y<R; y++){
            if(matrice[y][x]!=matrice[j][x]){
                pal=false;
                break;
            }
            j--;
        }
        if(pal==true){
            controll.no_indx[controll.lenght]=x;
            controll.lenght+=1;
        }
    }
    bool go=false;
    for(int y=0; y<R; y++){
        buffer[n_buffer]->indx=y;
        for(int x=0; x<C; x++){
            go=false;
            for(int j=0; j<controll.lenght; j++){
                if(x==controll.no_indx[j]){
                    go=true;
                    break;
                }
            }
     
            if(go==true){ continue;}
          
            buffer[n_buffer]->valori[buffer[n_buffer]->n]=matrice[y][x];
            if(max_r<buffer[n_buffer]->valori[buffer[n_buffer]->n]){
                max_r=buffer[n_buffer]->valori[buffer[n_buffer]->n];
            }
            buffer[n_buffer]->n+=1;
  
        }
        buffer[n_buffer]->nmass=(float)max_r/max;
        n_buffer+=1;
    }

    // bubble sort
    bool sort=false;
    while(1){
        sort=true;
        for(int i=0; i<n_buffer-1; i++){
            if(buffer[i]->nmass>buffer[i+1]->nmass){
                MyStruct* tmp=buffer[i];
                buffer[i]=buffer[i+1];
                buffer[i+1]=tmp;
                sort=false;
            }
        }
        if(sort==true){
            break;
        }
    }
    fflush(input);
    fclose(input);

    FILE* output=fopen("output.bin", "w");
    for(int i=0; i<n_buffer; i++){
      
        if(buffer[i]->n>0){
           
            fprintf(output, "\nIndice: %d, N_El riga: %d, Rapporto: %f, Valori: ", buffer[i]->indx, buffer[i]->n, buffer[i]->nmass);
            for(int j=0; j<buffer[i]->n; j++){
                fprintf(output, "%d ", buffer[i]->valori[j]);
            }
        }
    }
    fflush(output);
    fclose(output);
}

void init(int*** matrice){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(1);
    }
    fscanf(input, "%d ", &R);
    fscanf(input, "%d", &C);
    *matrice=malloc(sizeof(int*)*R);
    if(*matrice==NULL){
        exit(1);
    }
    for(int i=0; i<R; i++){
        (*matrice)[i]=malloc(sizeof(int)*C);
        if((*matrice)[i]==NULL){
            exit(1);
        }
    }
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fscanf(input, "%d",&(*matrice)[y][x]);
            if(max<(*matrice)[y][x]){
                max=(*matrice)[y][x];
            }
        }
    }
    fflush(input);
    fclose(input);

}

int main(void){
    MyStruct** buffer;
    int **matrice;
    init(&matrice);
  

    buffer=malloc(sizeof(MyStruct*)*R);
    if(buffer==NULL){
        exit(1);
    }

    for(int i=0; i<R; i++){
        buffer[i]=malloc(sizeof(MyStruct));
        if(buffer[i]==NULL){
            exit(1);
        }
        buffer[i]->n=0;
    }

    palindrome(matrice, buffer);
}