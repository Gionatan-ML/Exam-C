//Finish

#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void merge(int * array1, int* array2, int len1, int len2){
    int i=0, j=0, z=0;
    int array_f[MAX];
    do{
        if(i>=len1){
            printf("x");
            for(int x=j; x<len2; x++){
                array_f[z]=array2[x];
                z++;
            }
            break;

        }
        else if(j>len2){
            printf("y");
            for(int x=i; x<len1; x++){
                array_f[z]=array1[x];
                z++;
            }
            break;
        }
        if(array1[i]<array2[j]){
            array_f[z]=array1[i];
            z++;
            i++;
        }
        else{
            array_f[z]=array2[j];
            z++;
            j++;
        }

    }while(i<=len1 && j<=len2);
    printf("I&J: %d, %d\n",i,j);

    for(int i=0; i<len1+len2; i++){
        printf("%d ", array_f[i]);
    }
}
