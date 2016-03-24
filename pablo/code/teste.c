#include <stdio.h>
#include <stdlib.h>
#include "import.h"

main(){
    char* string = malloc(sizeof(char));
    int* ints = (int*)malloc(sizeof(int)*2);

    imprimir();

    //string
    /*printf("Seu nome: ");

    gets(string);

    printf("%s\n", string);*/
    //string


    //int
    int i = 1;
    enqueue(&ints, &i);
    printf("%d\n", *ints);

    /*ints[0] = 1;
    printf("%d\n", *ints);

    ints[1] = 2;
    printf("%d\n", ints[1]);*/
    //int
}

void enqueue(int ** queue, int* elemento){

    if(*queue == NULL)
        printf("NULL\n");
    else
        printf("%d\n", *queue);
    *queue = elemento;

    printf("inseriu %d na fila\n", *elemento);
}
