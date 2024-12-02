#include <stdio.h>
#include <stdlib.h>

int main() {
    long long tmp;
    int c;
    FILE* input = fopen("input.txt", "r");
    if (input == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fscanf(input, "%lld", &tmp);
    fseek(input,2,SEEK_CUR);
    fscanf(input, "%d", &c);
    printf("Long long value: %lld\n", tmp);
    printf("Int value: %d\n", c);
    fclose(input);

    return 0;
}