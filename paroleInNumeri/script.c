#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

typedef struct{
    int num;
    int num_sum;
    int one_count;

}MyStruct;

typedef struct{
    int save_numer[MAX];
    int len;
}Number_Save;


// define global variables

char *cifre[] = {"zero", "uno", "due", "tre", "quattro", "cinque", "sei", "sette", "otto", "nove"};
int struct_len=0;

void controll_value(MyStruct** custom, Number_Save number_save){
    int find_len=number_save.len;
    for(int j=0; j<number_save.len; j++){
        int cont=0;
        while(cont<find_len-1){
            number_save.save_numer[j]*=10;
            cont++;
        }
        find_len--;
        custom[struct_len]->num+=number_save.save_numer[j];
    }
}

int main(void){
    char c;

    MyStruct **custom=malloc(sizeof(MyStruct*)*(MAX*2));

    Number_Save number_save;
    number_save.len=0;

    if(custom==NULL){
        exit(0);
    }
    for(int i=0; i<MAX*2; i++){
        custom[i]=malloc(sizeof(MyStruct));
        if(custom[i]==NULL){
            exit(0);
        }
        custom[i]->num_sum=0;
        custom[i]->one_count=0;
        custom[i]->num = 0;
    }


    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        exit(0);
    }
    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        exit(0);
    }

    char buffer[MAX];
    int length=0;

    while((c=fgetc(input))!=EOF){
        if(c==' '){
            buffer[length]='\0';
            printf("Buff:%s",buffer);
            length=0;
            for(int i=0; i<10; i++){
                if(strcmp(cifre[i],buffer)==0){
                    number_save.save_numer[number_save.len]=i;
                    custom[struct_len]->num_sum+=i;
                    if(i==1){
                        custom[struct_len]->one_count+=1;
                    }
                    printf("%d",number_save.save_numer[number_save.len]);
                    number_save.len+=1;
                }
            }
            memset(buffer,0,sizeof(buffer));
        }
        else if(c=='\n'){
            controll_value(custom,number_save);
            printf("\n");
            memset(buffer,0,sizeof(buffer));
            memset(number_save.save_numer,0,sizeof(number_save.save_numer));
            fprintf(output, "{ %d, %d, %d }\n", custom[struct_len]->num, custom[struct_len]->num_sum, custom[struct_len]->one_count);
            struct_len++;
            number_save.len=0;
            length=0;

        }
        else{
            buffer[length]=c;
            length++;
        }
    }
    controll_value(custom,number_save);
    fprintf(output, "{ %d, %d, %d }\n", custom[struct_len]->num, custom[struct_len]->num_sum, custom[struct_len]->one_count);
    fflush(input);
    fclose(input);

    fflush(output);
    fclose(output);

}
