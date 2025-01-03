//FINISHED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 7
#define MAX 50

typedef struct{
    char *day;
    int val;
}Day;

typedef struct{
    Day weekday;
    int hours;
    float overlap;
    float average;
    int cont;
}MyStruct;

int main() {
    
    MyStruct calendar[SIZE];
    char *days[]={"LUN","MAR","MER","GIO","VEN","SAB","DOM"};
    char day_name[3];
    int num, num_hour, mounth[31]={0}, index;
    char buffer[MAX], hour_start[10];

    for(int i=0; i<SIZE; i++){
        calendar[i].weekday.day=days[i];
        calendar[i].weekday.val=i;
        calendar[i].hours=0;
        calendar[i].average=0.f;
        calendar[i].overlap=0.f;
        calendar[i].cont=0;
    }
    FILE* dates=fopen("input.txt", "r");
    if(dates==NULL){
        perror("bruh");
        exit(EXIT_FAILURE);
    }

    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        perror("bruh");
        exit(EXIT_FAILURE);
    }

    while(fgets(buffer,sizeof(buffer),dates)!=NULL){
        sscanf(buffer, "%s %d %s %d", day_name, &num, hour_start, &num_hour);
        for(int i=0; i<SIZE; i++){
            if(strcmp(days[i],day_name)==0){
                index=i;
                break;
            }
        }
        
        mounth[num]+=1;
        if(mounth[num]>1){
            calendar[index].overlap=(float)mounth[num];
        }
        calendar[index].hours+=num_hour;
        calendar[index].cont+=1;
        memset(buffer,0,sizeof(buffer));
    }
    for(int i=0; i<SIZE; i++){
        if(calendar[i].cont>0){
            calendar[i].average=(float) calendar[i].hours/calendar[i].cont;
            if(strcmp(calendar[i].weekday.day, "VEN")==0){
                printf("%d, %d", calendar[i].cont, calendar[i].hours);
            }
        }
        fprintf(output, "%s, %d, %f, %f\n", calendar[i].weekday.day, calendar[i].hours, calendar[i].overlap, calendar[i].average);

    }
    fclose(dates);
    fclose(output);





    return 0;
}