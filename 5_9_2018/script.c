//FINISH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 100
#define N_COL 4

typedef struct{
    char string[MAX];
    int indx;
}MyStruct;

void scomposing(char* string){
    char buffer[MAX];
    int cont=0;
    int len=0;

    for(int i=0; i<strlen(string); i++){
        if(string[i]=='"'){cont++; i++;}
        if(cont==1){
            buffer[len]=string[i];
            len++;
        }
        else if(cont == 2){
            break;
        }
    }
    buffer[len]='\0';
    strcpy(string,buffer);
    printf("%s\n", string);
}

//buble sort
void sorting(MyStruct* result, int len){
    int cont;

    do{
        cont=0;

        for(int i=0; i<len-1; i++){
            if(strlen(result[i].string) < strlen(result[i+1].string) ){
                MyStruct tmp= result[i];
                result[i]=result[i+1];
                result[i+1]=tmp;
                cont++;
            }
        }
    }while(cont!=0);
}

//print in output.bin
void printing(MyStruct* result, int len, int matrice[][N_COL], int lenMatrice){
    FILE* output=fopen("output.bin", "wb");
    if(output==NULL){
        exit(0);
    }
    fprintf(output, "Matrice: \n");
    for(int i=0; i<lenMatrice; i++){
        for(int j=0; j<N_COL; j++){
            fprintf(output, "%d ", matrice[i][j]);
        }
        fprintf(output,"\n");
    }
    fprintf(output, "\nStruct: \n");
    for(int i=0; i<len; i++){
        fprintf(output, "%s, %d\n", result[i].string, result[i].indx);
    }
    fflush(output);
    fclose(output);
}

int main(void){
    char buffer[MAX];
    int matrice[MAX][N_COL];
    int len=0, max, n=0;

    MyStruct result[MAX];
    int lenResult=0;

    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(0);
    }

    while(fgets(buffer, sizeof(buffer), input)!=NULL){
        scomposing(buffer);
        max=0;
        n=0;
        for(int j=0; j<N_COL; j++){
            matrice[len][j]=0;
        }

        for(int i=0; i<strlen(buffer); i++){
            if(buffer[i]!=' '){
                if( ((int)buffer[i] - 32) >= 65 ){
                    //numero minuscole
                    matrice[len][N_COL-1]+=1;
                    printf("\nMin: %c, %d", buffer[i], (int)buffer[i]);
                }
                else{
                    matrice[len][N_COL-2]+=1;
                    printf("\nMax: %c, %d", buffer[i], (int)buffer[i]);
                }
                n++;
            }

            if(buffer[i]==' ' || i+1==strlen(buffer)){
                // numero parole
                matrice[len][0]+=1;
                if(n>max){
                    max=n;
                }
                matrice[len][1]=max;
                n=0;
            }
        }

        result[lenResult].indx=len;
        strcpy(result[lenResult].string,buffer);
        len++;
        lenResult++;
    }
    fflush(input);
    fclose(input);

    sorting(result, lenResult);

    printing(result, lenResult, matrice, len);  
}