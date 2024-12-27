//FINISHED

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define S_MAX 100
#define C_MAX 15
// Scartare la riga se il 3 valore è 0 o la differenza di secondi rispetto al precedente è < di 5 minuti

int fiveMinutes= 60*5;

typedef struct {
    int time;
    float frz;
    float sleep;
    int agit;
} MyStruct;

typedef struct{
    int time;
    int presence;
    int mov;
    int frz;
}Condition;

int main(void){
    int agitation=0;
    int sum_time=0, sum_prz=0;
    int length_struct=0;
    MyStruct result[S_MAX];
    FILE* input=fopen("input.txt", "r");
    FILE* output;
    Condition prev_cond, cond;
    if(input==NULL){
        exit(EXIT_FAILURE);
    }
    char line[S_MAX];
    int cont=0;

    while(fgets(line, sizeof(line), input)!=NULL){
        if(cont>0){
            prev_cond=cond;
        }
        sscanf(line, "%d, %d, %d, %d", &cond.time, &cond.frz, &cond.presence, &cond.mov);
        if(cond.mov==1) agitation++;
        sum_prz+=cond.presence;
        if(cont>0){
            int sum_tmp=cond.time-sum_time;
            if(cond.time-prev_cond.time>fiveMinutes){
                if(cond.mov==1 && prev_cond.mov==0){
                    result[length_struct].frz=(float)cond.frz;
                }
                else{
                    result[length_struct].frz=-1.f;
                }
                result[length_struct].sleep=(float) sum_prz/sum_tmp;
                result[length_struct].agit=agitation;
                result[length_struct].time=cond.time;
                length_struct+=1;
            }
        }
        else{
            sum_time=cond.time;
        }
        cont++;
    }
    output=fopen("output.bin", "w");
    if(output==NULL){
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<length_struct; i++){
        fprintf(output, "{ %d, %f, %f, %d }\n", result[i].time, result[i].frz,result[i].sleep,result[i].agit);
    }
    fclose(output);
    fclose(input);

}