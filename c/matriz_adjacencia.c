#include <stdio.h>
#include <stdlib.h>

/**
Dimensão da matriz.
*/
const MAX = 8;


/**
Cores que representam o estado do vértice: desconhecido, descoberto, finalizado.
*/
enum _cor {BRANCO, CINZA, PRETO};
typedef enum _cor cor;


/**
Item que da fila de vértices descobertos.
*/
struct _queue_item {
    struct _queue_item * prox;
    int item;
};
typedef struct _queue_item queue_item;

void enqueue(queue_item ** queue, int elemento);

int dequeue(queue_item ** queue);

void busca_em_largura(int matriz[MAX][MAX], int origem);

void imprimirMatriz(int matriz[MAX][MAX]);

char toChar(int numero);

/*void print_path(vertice *grafo, char s, char v);

void _print_path(vertice * s, vertice * v);*/

void imprimir_vertices_descobertos(queue_item* queue);

int main(){


    int matriz[MAX][MAX];
    int i, j;

    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            matriz[i][j] = 0;
        }
    }

    matriz[0][1] = 1;
    matriz[0][4] = 1;

    matriz[1][0] = 1;
    matriz[1][5] = 1;

    matriz[2][5] = 1;
    matriz[2][3] = 1;
    matriz[2][6] = 1;

    matriz[3][2] = 1;
    matriz[3][6] = 1;
    matriz[3][7] = 1;

    matriz[4][0] = 1;

    matriz[5][1] = 1;
    matriz[5][2] = 1;
    matriz[5][6] = 1;

    matriz[6][5] = 1;
    matriz[6][2] = 1;
    matriz[6][3] = 1;
    matriz[6][7] = 1;

    matriz[7][6] = 1;
    matriz[7][3] = 1;

    imprimirMatriz(matriz);

    busca_em_largura(matriz, 4);
    //print_path(grafo,'v','y');
    return 0;
}



/**
Adiciona um elemento que contém um inteiro na fila.
*/
void enqueue(queue_item ** queue, int elemento){

    //cria o elemento da fila
    queue_item * item = malloc(sizeof(queue_item));
    item->item = elemento;
    item->prox = NULL;

    //se a "queue" ainda não aponta para nenhum item
    if(*queue == NULL){

        //"queue" passa a apontar para o novo item
        *queue = item;
    }else{

        //pega o primeiro item da fila
        queue_item * verificador = *queue;

        //verifica se já existe o valor "elemento" na fila
        while(verificador != NULL)
        {
            //se existir, não adiciona nada na fila
            if(verificador->item == elemento) return;
            verificador = verificador->prox;
        }

        //pega o primeiro item da fila
        queue_item * atual = *queue;

        //percorre a fila até chegar ao último item
        while(atual->prox != NULL)
            atual = atual->prox;

        //adiciona o novo item na lista
        atual->prox = item;
    }

    printf("\n\ninseriu %c na fila\n", toChar(elemento));

    imprimir_vertices_descobertos(*queue);
}



/**
Imprime a lista de vértices descobertos.
*/
void imprimir_vertices_descobertos(queue_item* queue){
    printf("lista de vertices descobertos: (");

    while(queue != NULL){
        printf("%c", toChar(queue->item));
        queue = queue->prox;

        if(queue != NULL) printf(", ");
    }

    printf(")\n");
}



/**
Remove o primeiro elemento da fila de vértices descobertos.
*/
int dequeue(queue_item ** queue){

    //se a "queue" ainda nao aponta para nenhum item
    if(*queue == NULL){
        return NULL;
    }else{

        //pega õ int do primeiro item da fila
        int atual = (*queue)->item;

        //pega o primeiro item da fila
        queue_item * atual_q = *queue;

        //a cabeça da fila passa a ser o segundo item
        *queue = (*queue)->prox;

        printf("removeu %c da fila\n", toChar(atual_q->item));

        //elimina o primeiro item da fila
        free(atual_q);

        //retorna o int do item eliminado
        return atual;
    }
}



/**
Executa a busca em largura a partir de um valor origem.
*/
void busca_em_largura(int matriz[MAX][MAX], int s){

    printf("iniciando busca a partir de %c\n", toChar(s));

    //cria listas de MAX elementos para armazenar valores sobre os nós
    //ex: cor[3] armazena a cor do vértice com valor = 3
    int* cor = (int*)malloc(sizeof(int)*MAX);
    int* d = (int*)malloc(sizeof(int)*MAX);
    int* pi = (int*)malloc(sizeof(int)*MAX);
    int* aux = (int*)malloc(sizeof(int)*MAX);

    //cria variáveis para iteração
    int i, j;

    //atribui valores default para cada vértice
    for(i=0; i<MAX; i++){
        cor[i] = BRANCO;
        d[i] = 0;
        pi[i] = -1;
    }

    //atribui os valores do vértice de origem
    cor[s] = CINZA;
    d[s] = 0;
    pi[s] = -1;

    //Cria a fila de vértices "descobertos"
    queue_item * q = NULL;

    //coloca o vértice origem na fila
    enqueue(&q, s);

    //enquanto houver elementos na fila de vértices "descobertos"...
    while(q != NULL){

        //pega o primeiro vértice da fila = "u"
        int u = dequeue(&q);

        for(i=0; i<MAX; i++){

            //pega o valor na matriz de adjacência
            int v = matriz[u][i];

            //se o valor for 1, significa que o vértice "i" é adjacente de "u"
            if(v){

                //se o vértice "i" ainda não foi descoberto
                if(cor[i] == BRANCO){

                    //diz que o vértice "i" foi descoberto
                    cor[i] == CINZA;

                    //calcula a distância de "i" em relação a origem
                    d[i] = d[u] + 1;

                    //diz quem é o antecessor de "i"
                    pi[i] = u;

                    //coloca o vértice "i" na fila de vértices descobertos
                    enqueue(&q, i);

                    printf("distancia de %c ate %c = %d\n", toChar(s), toChar(i), d[i]);
                }
            }
        }

        //diz que o vértice "u" foi finalizado
        cor[u] = PRETO;
    }
}



/**
Imprime a matriz.
*/
void imprimirMatriz(int matriz[MAX][MAX]){

    int i,j;

    for(i=0; i<MAX; i++)
    {
        for(j=0; j<MAX; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}



/**
Converte um valor inteiro do vértice em seu valor correspondente utilizado na
implementação do BFS com lista de adjacências em "lista_adjacencia.c".
*/
char toChar(int numero){

    switch(numero){
        case 0: return 'r';
        case 1: return 's';
        case 2: return 't';
        case 3: return 'u';
        case 4: return 'v';
        case 5: return 'w';
        case 6: return 'x';
        case 7: return 'y';
    }
}
/**
Imprime o melhor caminho de um v�rtice origem a um v�rtice destino.
*/
/*void print_path(vertice *grafo, char origem, char destino){

    //pega o v�rtice origem
    vertice * s_vertice = get_vertice(grafo, origem);

    //pega o v�rtice destino
    vertice * v_vertice = get_vertice(grafo, destino);

    //imprime o melhor caminho
    _print_path(s_vertice, v_vertice);
}

void _print_path(vertice * origem, vertice * destino){

    //se o v�rtice origem for o mesmo que o destino
    if (origem == destino){

        //imprime o nome do v�rtice origem
        printf("%c - ", origem->nome);

    //se o v�rtice destino n�o tiver antecessores
    }else if (destino->antecessor == NULL){

        //diz que n�o h� caminho entre o v�rtice origem e o destino
        printf("Nao ha caminho entre %c %c\n", origem->nome, destino->nome);

    }else{

        //imprime o melhor caminho entre o v�rtice origem e o v�rtice antecessor ao v�rtice destino
        _print_path(origem, destino->antecessor);

        printf("%c - ", destino->nome);
    }
}*/
