#include <stdio.h>
#include <stdlib.h>
#define MAX 4

// ordinamento interi quickSort

int changePosition(int l, int h, int* array){
    int pivot=array[l];
    int i=l, j=h;
    while(i<j){
        do{
            i++;
        }while(array[i]<=pivot && i<h);

        do{
            j--;
        }while(array[j]>pivot && j>l);
        if(i<j){
            int tmp=array[i];
            array[i]=array[j];
            array[j]=tmp;
        }
    }
    int tmp=array[l];
    array[l]=array[j];
    array[j]=tmp;
    return j;

    
}



void sort(int l, int h, int* array){
    if(l<h){
        int j=changePosition(l,h, array);
        sort(l,j, array);
        sort(j+1, h, array);
    }else{
        return;
    }
}


/*void quickSort(int *array, int max_lenght){
    sort(0,max_lenght, array);
}
/*int main(void){
    srand(time(NULL));
    int array[MAX];
    printf("\n");
    for(int i=0; i<MAX; i++){
        array[i]=(int)rand()%10000+1;
        printf(" %d", array[i]);
    }
    quickSort(array,MAX);
    printf("\n");
    for(int i=0; i<MAX; i++){
        printf(" %d", array[i]);
    }
}
*/