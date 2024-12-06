#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

typedef struct
{
    float media;
    float* rig;
    float total;
}MyStruct;

int len=0;
int R,C;
float matrix[MAX][MAX];

void calc(MyStruct* buffer){
    for(int y=0; y<R; y++){
        buffer[len].total=0.0f;
        for(int x=0; x<C; x++){
            buffer[len].total+=(float)matrix[y][x];
        }
        buffer[len].media=(float) buffer[len].total / C;
        buffer[len].rig=matrix[y];
        printf("C: ");
        for(int i=0; i<C; i++){
            printf("%f ", buffer[len].rig[i]);
        }
        len++;
    }

}
void sorting2(MyStruct* buffer){
    int last_el=C-1;
    bool isChange;
    do{
        isChange=false;
        for(int i=0; i<len-1; i++){
            if(buffer[i].rig[last_el]>buffer[i+1].rig[last_el]){
                MyStruct tmp=buffer[i];
                buffer[i]=buffer[i+1];
                buffer[i+1]=tmp;
                isChange=true;
            }
        }
        printf("x");

    }while(isChange==true);
}
void sorting(MyStruct buffer) {
    bool isChange;
    int cont = 0;
    do {
        isChange = false;
        for (int i = 0; i < C - 1; i++) {
            if (buffer.rig[i] > buffer.rig[i + 1]) {
                float tmp = buffer.rig[i];
                buffer.rig[i] = buffer.rig[i + 1];
                buffer.rig[i + 1] = tmp;
                isChange = true;
            }
        }
        cont++;
    } while (isChange == true);
}

void init(){
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    fscanf(input, "%d %d\n", &R, &C);
    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            fscanf(input, "%f ", &matrix[y][x]);
            printf("%.2f ", matrix[y][x]);
        }
        printf("\n");
    }
    fflush(input);
    fclose(input);
    
}

int main(void){
    MyStruct buffer[MAX];
    init();
    calc(buffer);
    printf("\nFine");
    for(int i=0; i<R; i++){
        sorting(buffer[i]);
    }
    sorting2(buffer);
    FILE* output=fopen("output.bin", "w");
    for(int i=0; i<len; i++){
        for(int x=0; x<C; x++){
            fprintf(output, "%.2f ", buffer[i].rig[x]);
        }
        fprintf(output, " Media: %.2f\n", buffer[i].media);
    }
}
