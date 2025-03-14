#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
// #include <string.h>

typedef struct{
    char objeto;
    int power;
}tElemento;

int main () {
    char ch;
    char matrix[10][10];

    FILE* teste = fopen("lab1.txt", "r");
    //fputc leitura de caracter
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            fscanf(teste, " %c", &matrix[i][j]);
        }
    }
    fclose(teste);   
    
    printf("\n");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }    

    printf("\n");
    return 0;
}
