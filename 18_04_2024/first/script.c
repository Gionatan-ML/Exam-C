
// FINISHED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M_MAX 3
#define N_MAX 100
#define NUM_MAX 5
#define NAN -999

typedef struct Mystruct{ // array of struct for every colums modified
    int col; // numero colonna
    int n; // numero elementi modificati
    int righe[N_MAX];  // indice per gli elementi nulli della colonna
    int elementi[N_MAX]; // new values
}Mystruct;

// data segments with global variables
int R, C,p;

//bubleSort for elements
void sort(int** matrice, int indx){
    int switched;
    do{
        switched=0;
        for(int y=0; y<R-1; y++){
            if(matrice[y][indx]>matrice[y+1][indx]){
                int tmp=matrice[y][indx];
                matrice[y][indx]=matrice[y+1][indx];
                matrice[y+1][indx]=tmp;
                switched++;
            }
        }
    }while(switched!=0);
}

int succ_max(int **matrice, int indx){
    int max=0;
    for(int y=0; y<R; y++){
        if(matrice[y][indx]>max){
            max=matrice[y][indx];
        }
    }
    return max;
}

int succ_min(int **matrice, int indx){
    int min=9999;
    for(int y=0; y<R; y++){
        if(matrice[y][indx]<min){
            min=matrice[y][indx];
        }
    }
    return min;
}

int col_zero(int** matrice, int indx, int value){
    int sum=0;
    for(int y=0; y<R; y++){
        sum+=matrice[y][indx];
    }
    if(sum!=0){
        sum-=value;
        value=sum-sum-sum;
        return value;
    }else{
        return value;
    }

}


void controll(int **matrice, Mystruct** vect_cl){
    int cont=0;
    for(int y=0; y<C; y++){
        vect_cl[y]->col=y;
        for(int x=0; x<R; x++){
            if(matrice[x][y]==0 && cont==0 && (y+1)<C){
                matrice[x][y]=succ_min(matrice, (y+1));
                vect_cl[y]->righe[cont]=x;
                vect_cl[y]->n+=1;
                vect_cl[y]->elementi[cont]=matrice[x][y];
                cont++;
            }
            else if(matrice[x][y]==0 && cont==1 && (y+1)<C){
                matrice[x][y]=succ_max(matrice, (y+1));
                vect_cl[y]->righe[cont]=x;
                vect_cl[y]->n+=1;
                vect_cl[y]->elementi[cont]=matrice[x][y];
                cont++;
            }
            else if(matrice[x][y]==0 && cont==2 && (y+1)<C){
                matrice[x][y]=col_zero(matrice, y, matrice[x][y]);
                vect_cl[y]->righe[cont]=x;
                vect_cl[y]->n+=1;
                vect_cl[y]->elementi[cont]=matrice[x][y];
                cont++;
            }
        }
        if(y==C-1){
            sort(matrice, y);
        }
        cont=0;
    }

}

void creation_matrix(int** matrice){
    FILE* file=fopen("input.txt", "r");
    if(file==NULL){
        exit(0);
    }
    fseek(file,p,1);
    printf("\nFile: %d\n", ftell(file));
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fscanf(file, "%d ", &(matrice[y][x]));
            printf("%d ", matrice[y][x]);
        }
        printf("\n");
    }
    fflush(file);
    fclose(file);
}

void init(){
    printf("\n");
    FILE* file=fopen("input.txt", "w");
    if(file==NULL){
        exit(0);
    }
    R=rand()%M_MAX+3;
    C=rand()%M_MAX+3;
    fprintf(file ,"%d %d\n\n", R,C);
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            int value=rand()%NUM_MAX-3;
            fprintf(file,"%d ",value);
        }
        fprintf(file,"\n");
    }
    fflush(file);
    fclose(file);


}

int main(void){
    srand(time(NULL));
    printf("\n");
    Mystruct** vect_cl;
    
    FILE* file=fopen("input.txt", "r");
    fscanf(file,"%d ", &R);
    fscanf(file,"%d ", &C);
    printf("\n%d, %d\n",R,C);
    p=ftell(file);
    fflush(file);
    fclose(file);
    printf("\nFile: %d", p);

    vect_cl=malloc(sizeof(Mystruct*)*C);
    if(vect_cl==NULL){
        exit(0);
    }
    for(int i=0; i<C; i++){
        vect_cl[i]=malloc(sizeof(Mystruct));
        if(vect_cl==NULL){
            exit(0);
        }
        vect_cl[i]->n=0;
    }


    int **matrice=malloc(sizeof(int*)*R);
    if(matrice==NULL){
        exit(0);
    }
    for(int i=0; i<R; i++){
        matrice[i]=malloc(sizeof(int)*C);
        if(matrice[i]==NULL){
            exit(0);
        }

    }

    creation_matrix(matrice);
    controll(matrice,vect_cl);
    printf("\n\n");
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            printf("%d ", matrice[y][x]);
        }
        printf("\n");
    }

    FILE* output=fopen("output.bin", "w");
    // save in a binary file
    for(int i=0; i<C; i++){
        if(vect_cl[i]->n==0){
            continue;
        }
        fprintf(output,"{%d, %d, [",vect_cl[i]->col, vect_cl[i]->n);
        for(int j=0; j<vect_cl[i]->n; j++){
            fprintf(output,"%d ", vect_cl[i]->righe[j]);
        }
        fprintf(output," ], [ ");
        for(int z=0; z<vect_cl[i]->n; z++){
            fprintf(output,"%d ", vect_cl[i]->elementi[z]);
        }
        fprintf(output,"] }\n");
    }
    fflush(output);
    fclose(output);


}