#include <stdio.h>
#include <stdlib.h>
#include "import.h"

main(){
    char* string = malloc(sizeof(char));

    imprimir();

    printf("Seu nome: ");

    //scanf("%s", string);
    gets(string);

    printf("%s\n", string);
}
