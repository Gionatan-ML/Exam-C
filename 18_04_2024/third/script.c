#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define S_MAX 100
#define C_MAX 15
// Scartare la riga se il 3 valore è 0 o la differenza di secondi rispetto al precedente è < di 5 minuti

int Vm = 60 * 5, len = 0;
long long ptr = 0;

typedef struct {
    long long time;
    float frz;
    float sleep;
    int agit;
} MyStruct;

void _controll(MyStruct*** status) {
    len += 1;
    MyStruct** temp = realloc(*status, sizeof(MyStruct*) * len);
    if (temp == NULL) {
        exit(1);
    }
    *status = temp;
    (*status)[len - 1] = malloc(sizeof(MyStruct));
    if ((*status)[len - 1] == NULL) {
        exit(1);
    }
}

bool firstCond(char* s){
    char buffer[C_MAX];
    int cont=0;
    long long tmp;
    while(s[cont]!=','){
        buffer[cont]=s[cont];
        cont++;
    }
    buffer[cont]='\0';
    tmp=atoll(buffer);
    if((tmp-ptr)>=Vm){
        ptr=tmp;
        return true;
    }
    else{
        ptr=tmp;
        return false;
    }
}
bool secondCond(char* s){
    int cont=0,i=0;
    while(s[i]!='\0'){
        if(s[i]==','){
            cont++;
        }
        if(cont==2){
            cont=i-1;
            break;
        }
    }
    char ffr[1];
    ffr[0]=s[cont];
    ffr[1]='\0';
    int tmp=atoi(ffr);
    if(tmp==1){
        return true;
    }
    else{
        return false;
    }
}

int main() {
    bool cont=0;
    int t_cont=0;
    MyStruct** condition;
    char s[S_MAX],buffer[C_MAX];
    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(0);
    }
    while(fgets(s,sizeof(s),input)!=EOF){
        if(firstCond(s)==true && secondCond(s)==true){
            _controll(&condition);
            fscanf(input, "%lld", &condition[len-1]->time);
            fseek(input,1,SEEK_CUR);
            fscanf(input, "%f", &condition[len-1]->frz);
            fseek(input,1,SEEK_CUR);
            fscanf(input, "%d", &condition[len-1]->sleep);
            fseek(input,1,SEEK_CUR);
            fscanf(input, "%d", &condition[len-1]->agit);    
            printf("Time: %lld, Frz: %.2f, Sleep: %d, Agit: %d\n", condition[len-1]->time, condition[len-1]->frz, condition[len-1]->sleep, condition[len-1]->agit);
        }

        memset(s,0,sizeof(s));
    }


    return 0;
}