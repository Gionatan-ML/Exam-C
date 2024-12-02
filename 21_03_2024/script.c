//FINISHED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N_MAX 100

char del[50];

typedef struct{
    int n;
    char line[N_MAX];
    int tokens[N_MAX][2];
    char dels[N_MAX];
    int cont_del;
}MyStruct;

void tokens(char* s){
    FILE* output=fopen("output.bin", "a");
    if(output==NULL){
        exit(0);
    }
    bool find=false;
    MyStruct token;
    memccpy(token.line, s, '\0', sizeof(token.line));
    token.n=0;
    token.cont_del=0;
    int start,end,cont=0;
    for(int i=0; i<strlen(s); i++){
        for(int j=0; j<strlen(del); j++){
            if(s[i]==del[j] && cont==0){
                token.tokens[token.n][0]=i;
                start=i;
                cont++;
                for(int z=0; z<token.cont_del; z++){
                    if(s[i]==token.dels[z]){
                        find=true;
                        break;
                    }
                }
                if(find==false){
                    token.dels[token.cont_del]=s[i];
                    token.cont_del+=1;
                }
                find=false;

                break;
            }
            else if(s[i]==del[j] && cont==1){
                end=i;
                token.tokens[token.n][1]=i;
                token.n+=1;

                for(int z=0; z<token.cont_del; z++){
                    if(s[i]==token.dels[z]){
                        find=true;
                        break;
                    }
                }
                if(find==false){
                    token.dels[token.cont_del]=s[i];
                    token.cont_del+=1;
                }
                find=false;

                cont=0;
                break;
            }
        }
    }
    token.dels[token.cont_del]='\0';
    if(token.n!=0){
        fprintf(output, "[%s, N_Token: %d, Dels: %s\n", token.line, token.n, token.dels);
        for(int i=0; i<token.n; i++){
            fprintf(output, "Start: %d, End: %d\n", token.tokens[i][0], token.tokens[i][1]);
        }
        fprintf(output, " ]\n\ns");
    }
    fclose(output);
    

}

int main(void){
    FILE* input=fopen("input.txt", "r");
    char c[100];
    int cont=0;
    if((fgets(c, sizeof(c), input))==NULL){
        exit(0);
    }
    memccpy(del,c,'\0',sizeof(del));
    memset(c,0,sizeof(c));
    if((fgets(c, sizeof(c), input))==NULL){
        exit(0);
    }
    tokens(c);

    while((fgets(c, sizeof(c), input))!=NULL){
        tokens(c);
        memset(c,0,sizeof(c));
    }

    
    fflush(input);
    fclose(input);


}