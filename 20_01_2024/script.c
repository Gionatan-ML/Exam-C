#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NMAX 100

typedef struct{
    char data1[11]; // prima data
    char data2[11]; // seconda
    int giorni;
    float media[2];
}MyStruct;

void saveDate(char *string, int* mese, int* giorno, float *ora1, float *ora2, MyStruct* date, int val){
    int cont=0, i=0;
    char buffer[10];
    int length=0;

    // get mounth and day
    while(string[i]!=','){
        if(string[i]=='/'&& cont>0){
            for(int j=i; string[j]!='/'; j++){
                if(string[j]=='0' && length == 0){
                    continue;
                }
                buffer[length]=string[j];
                length++;
            }
            buffer[length]='\0';
            length=0;
            if(cont==1){
                *mese=atoi(buffer);
            }
            else{
                *giorno=atoi(buffer);
            }
        }
        if(string[i]=='/'){
            cont++;
        }
        if(val==0){
            date->data1[i]=string[i];
        }
        else{
            date->data2[i]=string[i];
        }
        i++;
    }
    if(val==0){
        date->data1[i]='\0';
    }
    else{
        date->data2[i]='\0';
    }
    cont=0;
    memset(buffer,0,sizeof(buffer));
    bool isFloat;
    // get 2 dates
    for(int j=i; j<strlen(string); j++){
        if(string[j]==',' && cont>0){
            isFloat=false;
            for(int z=j; string[z]!=','||z<strlen(string); z++){
                if(length==0 && string[z]=='0'){
                    continue;
                }
                buffer[length]=string[z];
                length++;
            }
            buffer[length]='\0';
            if(cont==1){
                *ora1=atof(buffer);
            }
            else{
                *ora2=atof(buffer);
            }
        }
        if(string[j]==','){
            cont++;
        }
    }
    
}

int main(void){
    int mese, giorno,mese_prev, giorno_prev, cont=0, length=0;
    float ora1, ora2, ora1_prev, ora2_prev;
    char anno[]="2020";
    char string[NMAX];

    MyStruct** dates=malloc(sizeof(MyStruct*)*NMAX);
    if(dates==NULL){
        printf("just buy more ram bro...");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<NMAX; i++){
        dates[i]=malloc(sizeof(MyStruct));
        if(dates[i]==NULL){
            printf("bruh");
            exit(EXIT_FAILURE);
        }
    }

    FILE *input=fopen("input.txt", "r");
    if(input==NULL){
        exit(0);
    }
    FILE *output=fopen("output.bin", "w");
    if(output==NULL){
        exit(0);
    }

    while(fgets(string, sizeof(string), input) != NULL){
        if(cont==0){
            saveDate(string, &mese_prev, &giorno_prev, &ora1, &ora2, dates[length], cont);
            cont++;
        }
        else if(cont==1){
            saveDate(string, &mese, &giorno,&ora1_prev, &ora2_prev, dates[length], cont );
            cont++;
        }
        else if(cont==2){
            if(mese==mese_prev){
                dates[length]->giorni= giorno-giorno_prev;
            }
            else if(mese>mese_prev){
                dates[length]->giorni=30-mese_prev+mese;
            }
            dates[length]->media[0]=(float) (ora1-ora1_prev) / dates[length]->giorni;
            dates[length]->media[1]=(float) (ora2-ora2_prev) / dates[length]->giorni;
            fprintf(output, "%s, %s, %d, %f, %f", dates[length]->data1,  dates[length]->data2, dates[length]->giorni, dates[length]->media[0],  dates[length]->media[1]);
            length++;
            cont=0;
        }
        
        memset(string, 0, sizeof(string));
    }
    fclose(input);
    fclose(output);

}