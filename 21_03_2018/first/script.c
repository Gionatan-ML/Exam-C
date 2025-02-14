#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define N_W 10

typedef struct{
    int position;
    char type;
    int lenght;
}StructWords;


int getP( char* word, long pt){
    int position= (int) pt - strlen(word);
    printf(", %d,size: %d\n", position, (int)strlen(word));
    return position;
}
char getType(char* word){
    bool type[]={false, false};
    for(int i=0; i<strlen(word); i++){
        if(isnumber(word[i])){     printf("n:%c\n",word[i]); type[0]=true;}
        else if(isalpha(word[i])){ printf("w:%c\n",word[i]); type[1]=true;}
    }
    if(type[0]==true && type[1]==true){
        return 'c';
    }
    else if(type[0]==true){
        return 'b';
    }
    else if (type[1]==true){
        return 'a';
    }
    else{
        printf("??: %s", word);
        return 'z';
    }
}

int main(void){
    int len=0;
    char wordBuffer[N_W];
    char stringBuffer[MAX];

    StructWords words[MAX];
    for(int i=0; i<MAX; i++){
        words[i].lenght=0;
    }
    

    FILE* input=fopen("input.txt", "r");
    if(input==NULL){
        perror("ciuppa");
        exit(EXIT_FAILURE);
    }

    fgets(stringBuffer, sizeof(stringBuffer), input);
    fseek(input, 0, SEEK_SET);

    FILE* output=fopen("output.bin", "w");
    if(output==NULL){
        perror("ciuppa");
        exit(EXIT_FAILURE);
    }

    while(fscanf(input, "%s ", wordBuffer) != EOF){
        printf("%s,%ld", wordBuffer, ftell(input)-1);
        words[len].position=getP( wordBuffer, ftell(input)-1);
        words[len].lenght= (int)strlen(wordBuffer);
        words[len].type=getType(wordBuffer);
        fprintf(output, "%d, %c, %d\n", words[len].lenght, words[len].type, words[len].lenght);
        memset(wordBuffer, 0, sizeof(wordBuffer));
        len++;
    }
    fclose(input);
    fclose(output);
}