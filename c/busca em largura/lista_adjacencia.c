#include <stdio.h>
#include <stdlib.h>

/**
Cores que representam o estado do vértice: desconhecido, descoberto, finalizado.
*/
enum _cor {BRANCO, CINZA, PRETO};
typedef enum _cor cor;


/**
Estrutura do vértice.
*/
struct _vertice{
    char nome;
    struct _vertice * prox_adj;
    struct _vertice * prox_vertice;
    int d;
    struct _vertive * antecessor;
    cor c;
};
typedef struct _vertice vertice;


/**
Item que da fila de vértices descobertos.
*/
struct _queue_item {
    struct _queue_item * prox;
    vertice * item;
};
typedef struct _queue_item queue_item;

void add_vertice(vertice** grafo, char elemento);

int add_adjacencia(vertice* grafo, char origem, char elemento);

void enqueue(queue_item ** queue, vertice * elemento);

vertice * dequeue(queue_item ** queue);

vertice * get_vertice(vertice* grafo, char elemento);

void busca_em_largura(vertice *grafo, char origem);

void print_path(vertice *grafo, char s, char v);

void _print_path(vertice * s, vertice * v);

void imprimir_vertices_descobertos(queue_item* queue);

int main(){

    vertice * grafo = NULL;

    add_vertice(&grafo, 'r');
    add_vertice(&grafo, 's');
    add_vertice(&grafo, 't');
    add_vertice(&grafo, 'u');
    add_vertice(&grafo, 'v');
    add_vertice(&grafo, 'w');
    add_vertice(&grafo, 'x');
    add_vertice(&grafo, 'y');

    add_adjacencia(grafo, 's', 'r');
    add_adjacencia(grafo, 's', 'w');

    add_adjacencia(grafo, 'r', 's');
    add_adjacencia(grafo, 'r', 'v');

    add_adjacencia(grafo, 't', 'w');
    add_adjacencia(grafo, 't', 'x');
    add_adjacencia(grafo, 't', 'u');

    add_adjacencia(grafo, 'u', 't');
    add_adjacencia(grafo, 'u', 'x');
    add_adjacencia(grafo, 'u', 'y');

    add_adjacencia(grafo, 'v', 'r');

    add_adjacencia(grafo, 'w', 's');
    add_adjacencia(grafo, 'w', 't');
    add_adjacencia(grafo, 'w', 'x');

    add_adjacencia(grafo, 'x', 'w');
    add_adjacencia(grafo, 'x', 't');
    add_adjacencia(grafo, 'x', 'u');
    add_adjacencia(grafo, 'x', 'y');

    add_adjacencia(grafo, 'y', 'x');
    add_adjacencia(grafo, 'y', 'u');


    busca_em_largura(grafo, 'v');
    print_path(grafo,'v','y');
    return 0;
}



/**
Adiciona um vértice no grafo.
*/
void add_vertice(vertice** grafo, char elemento){

    /*
        "grafo" recebe o endereço de um ponteiro quando esta
        função é chamada. Ou seja, recebe o endereço de um
        espaço de memória que armazena o endereço de um vértice.

        Portanto, "grafo" não é a mesma variável passada por parâmetro.
        "grafo" é uma variável desta função.

        Ele é um espaço de memória que armazena o endereço
        de um outro espaço de memória que armazena o
        endereço de um vértice.
        Ou seja, "grafo" é um ponteiro que aponta para um
        ponteiro que aponta para um vértice.
    */

    vertice *novo, *atual;
    novo = malloc(sizeof(vertice));
    novo->nome = elemento;
    novo->prox_adj = NULL;
    novo->prox_vertice = NULL;
    novo->c = BRANCO;
    novo->d = -1;
    novo->antecessor = NULL;

    if(*grafo == NULL){

        /*
            se "*grafo" for NULL, significa que ainda não há
            nenhum "vértice origem" sendo apontado por "*grafo",
            ou seja, o grafo está vazio.
        */

        //se o grafo estiver vazio, passa a apontar para o novo vértice
        *grafo = novo;
    }
    else{

        //pega o endereço do vértice que está sendo apontado por *grafo
        atual = *grafo;

        //pega o último vértice do grafo
        while(atual->prox_vertice != NULL)
            atual = atual->prox_vertice;

        //adiciona o novo vértice
        atual->prox_vertice = novo;
    }

    printf("criou vertice %c\n", elemento);
}



/**
Retorna positivo caso encontre a origem no vetor de vértices.
Caso contrário retorna negativo.
*/
int add_adjacencia(vertice* grafo, char origem, char elemento){

    /*
        "grafo" é o endereço do vértice inicial.
        Ou seja, é um ponteiro que aponta para o
        vértice inicial do grafo.
    */

    int i, encontrou = 0;
    vertice * atual, * temp;

    //atual recebe o vértice inicial
    atual = grafo;

    //se ainda não houver um vértice inicial, retorna negativo
    if(atual == NULL)
        return 0;

    while(atual != NULL){

        //se o vértice inicial for o vértice procurado
        if (atual->nome == origem){

            //encontrou o vértice no qual será dicionada a adjacência
            encontrou = 1;

            //percorre a lista de adjacência do vértice e pega a última adjacência da lista
            while(atual->prox_adj != NULL)
                atual = atual->prox_adj;

            //cria uma nova adjacência
            temp = malloc(sizeof(vertice));
            temp->nome = elemento;
            temp->prox_adj = NULL;
            temp->prox_vertice = NULL;

            //anexa na lista de adjacencia do vértice "origem"
            atual->prox_adj = temp;

            printf("criou adjacencia %c %c\n", origem, elemento);

            break;
        }else{

            //se o vértice não for o "origem", passa para o próximo
            atual = atual->prox_vertice;
        }
    }

    return encontrou;
}



/**
Adiciona um elemento que contém um ponteiro para um vértice na fila.
*/
void enqueue(queue_item ** queue, vertice * elemento){

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
        queue_item * atual = *queue;

        //percorre a fila até chegar ao último item
        while(atual->prox != NULL)
            atual = atual->prox;

        //adiciona o novo item na lista
        atual->prox = item;
    }

    printf("vertice %c encontrado\n", elemento->nome);

    imprimir_vertices_descobertos(*queue);
}



/**
Imprime a lista de vértices descobertos.
*/
void imprimir_vertices_descobertos(queue_item* queue){
    printf("lista de vertices descobertos: (");

    while(queue != NULL){
        printf("%c", queue->item->nome);
        queue = queue->prox;

        if(queue != NULL) printf(", ");
    }

    printf(")\n");
}



/**
Remove o primeiro elemento da fila de vértices descobertos.
*/
vertice * dequeue(queue_item ** queue){

    //se a "queue" ainda não aponta para nenhum item
    if(*queue == NULL){
        return NULL;
    }else{

        //pega o vértice do primeiro item da fila
        vertice * atual = (*queue)->item;

        //pega o primeiro item da fila
        queue_item * atual_q = *queue;

        //a cabeça da fila passa a ser o segundo item
        *queue = (*queue)->prox;

        printf("removeu %c da fila\n", atual_q->item->nome);

        //elimina o primeiro item da fila
        free(atual_q);

        //retorna o vértice do item eliminado
        return atual;
    }
}



/**
Pega um vértice pelo nome.
*/
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



/**
Executa a busca em largura a partir de um vértice origem.
*/
void busca_em_largura(vertice *grafo, char origem){

    //pega o vértice que será a origem da busca
    vertice * s = get_vertice(grafo, origem);

    printf("\n** iniciando busca a partir de %c **\n\n", s->nome);

    //se o vértice não for encontrado, retorna NULL
    if (s == NULL)
        return;

    //sinaliza o vértice como "descoberto"
    s->c = CINZA;

    //atribui distância 0 ao vértice
    s->d = 0;

    //Cria a fila de vértices "descobertos"
    queue_item * q = NULL;

    //coloca o vértice origem na fila
    enqueue(&q, s);

    //enquanto houver elementos na fila de vértices "descobertos"...
    while(q != NULL){

        //pega o primeiro vértice da fila = "u"
        vertice * u = dequeue(&q);

        printf("analisando vertices de %c...\n", u->nome);

        //cria um ponteiro que percorrerá os vértices adjacentes a "u" e faz com que ele aponte para a primeira adjacência
        vertice * atual = u->prox_adj;

        //enquanto o ponteiro "atual" apontar para algum vértice, ou seja, percorre todas as adjacências do vértice "u"
        while(atual != NULL){

            //pega o vértice adjacente
            vertice * v = get_vertice(grafo, atual->nome);

            //se o vértice estiver sinalizado como "não descoberto"
            if(v->c == BRANCO){

                //sinaliza o vértice como "descoberto"
                v->c = CINZA;

                //calcula a distância em relação à origem baseado na distância do vértice "u"
                v->d = u->d + 1;

                //diz quem é o vértice antecessor
                v->antecessor = u;

                //adiciona o vértice na fila de "descobertos"
                enqueue(&q, v);

                printf("distancia de %c ate %c = %d\n", origem, v->nome, v->d);
            }

            //se o vértice estiver sinalizado como "descoberto" ou "finalizado", passa para a próxima adjacência
            atual = atual->prox_adj;
        }

        //sinaliza o vértice como "finalizado"
        u->c = PRETO;

        printf("%c concluido\n\n", u->nome);
    }

}



/**
Imprime o melhor caminho de um vértice origem a um vértice destino.
*/
void print_path(vertice *grafo, char origem, char destino){

    //pega o vértice origem
    vertice * s_vertice = get_vertice(grafo, origem);

    //pega o vértice destino
    vertice * v_vertice = get_vertice(grafo, destino);

    //imprime o melhor caminho
    _print_path(s_vertice, v_vertice);
}




void _print_path(vertice * origem, vertice * destino){

    //se o vértice origem for o mesmo que o destino
    if (origem == destino){

        //imprime o nome do vértice origem
        printf("%c - ", origem->nome);

    //se o vértice destino não tiver antecessores
    }else if (destino->antecessor == NULL){

        //diz que não há caminho entre o vértice origem e o destino
        printf("Nao ha caminho entre %c %c\n", origem->nome, destino->nome);

    }else{

        //imprime o melhor caminho entre o vértice origem e o vértice antecessor ao vértice destino
        _print_path(origem, destino->antecessor);

        printf("%c - ", destino->nome);
    }
}
