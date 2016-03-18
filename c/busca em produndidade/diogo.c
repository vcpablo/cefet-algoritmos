#include <stdio.h>
#include <stdlib.h>

enum _cor {BRANCO, CINZA, PRETO};
typedef enum _cor cor;

struct _vertice{
    char nome;
    struct _vertice * prox_adj;
    struct _vertice * prox_vertice;
    int d;
    int f;
    struct _vertice * antecessor;
    cor c;
};

typedef struct _vertice vertice;

void add_vertice(vertice** grafo, char elemento);

int add_adjacencia(vertice* grafo, char origem, char elemento);

vertice * get_vertice(vertice* grafo, char elemento);

void busca_em_profundidade(vertice * grafo);

void busca_em_profundidade_visit(vertice * grafo, vertice * u, int * time);


int main(){
    vertice * grafo = NULL;

    add_vertice(&grafo, 'u');
    add_vertice(&grafo, 'v');
    add_vertice(&grafo, 'x');
    add_vertice(&grafo, 'y');
    add_vertice(&grafo, 'w');
    add_vertice(&grafo, 'z');

    add_adjacencia(grafo, 'u', 'v');
    add_adjacencia(grafo, 'v', 'y');
    add_adjacencia(grafo, 'y', 'x');
    add_adjacencia(grafo, 'x', 'v');
    add_adjacencia(grafo, 'u', 'x');
    add_adjacencia(grafo, 'w', 'y');
    add_adjacencia(grafo, 'w', 'z');
    add_adjacencia(grafo, 'z', 'z');

    busca_em_profundidade(grafo);

    return 0;
}
/**
*/
void add_vertice(vertice** grafo, char elemento){
    vertice *novo, *atual;
    novo = malloc(sizeof(vertice));
    novo->nome = elemento;
    novo->prox_adj = NULL;
    novo->prox_vertice = NULL;
    novo->c = BRANCO;
    novo->d = -1;
    novo->f = -1;
    novo->antecessor = NULL;

    if(*grafo == NULL){
        //vazio
        *grafo = novo;
        printf("criou vertice %c\n", elemento);
        return;
    }
    atual = *grafo;
    while(atual->prox_vertice != NULL)
        atual = atual->prox_vertice;
    atual->prox_vertice = novo;
    printf("criou vertice %c\n", elemento);
    return;
}

/**
Retorna positivo caso encontre a oritem no vetor de v�rtices
caso contr�rio retorna negativo.
*/
int add_adjacencia(vertice* grafo, char origem, char elemento){
    int i, encontrou = 0;
    vertice * atual, * temp;
    atual = grafo;
    if(atual == NULL)
        return 0;

    while(atual != NULL){
        if (atual->nome == origem){
            encontrou = 1;
            //percorre a lista de adjac�ncia do v�rtice
            while(atual->prox_adj != NULL)
                atual = atual->prox_adj;
            //criar a adjac�ncia
            temp = malloc(sizeof(vertice));
            temp->nome = elemento;
            temp->prox_adj = NULL;
            temp->prox_vertice = NULL;
            //anexa na lista de adjac�ncia
            atual->prox_adj = temp;
            printf("criou adjacencia %c %c\n", origem, elemento);
            break;
        }else{
            atual = atual->prox_vertice;
        }
    }

    return encontrou;
}


vertice * get_vertice(vertice* grafo, char elemento){
    vertice * atual = grafo;
    while(atual != NULL){
        if(atual->nome == elemento)
            return atual;
        else
            atual = atual->prox_vertice;
    }
    return NULL;
}

void busca_em_profundidade(vertice * grafo){
    int time = 0;
    vertice * atual = grafo;
    while(atual != NULL){
        if(atual->c == BRANCO){
            busca_em_profundidade_visit(grafo, atual, &time);
        }
        atual = atual->prox_vertice;
    }
}

void busca_em_profundidade_visit(vertice * grafo, vertice * u, int * time){
    *time = *time + 1;
    u->d = *time;
    printf("vertice %c d = %d\n", u->nome, *time);
    u->c = CINZA;

    vertice * anterior_adj = u;
    vertice * atual_adj = anterior_adj->prox_adj;
    vertice * atual_vert = NULL;
    //printf("atual = %c\n", atual->nome);
    while(atual_adj != NULL){
        atual_vert = get_vertice(grafo, atual_adj->nome);
        if (atual_vert->c == BRANCO){
            atual_vert->antecessor = get_vertice(grafo, anterior_adj->nome);
            busca_em_profundidade_visit(grafo, atual_vert, time);
        }
        anterior_adj = atual_adj;
        atual_adj = atual_adj->prox_adj;
    }
    u->c = PRETO;
    *time = *time + 1;
    u->f = *time;
    printf("vertice %c f = %d\n", u->nome, *time);
}


