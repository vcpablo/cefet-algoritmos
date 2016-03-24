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
    int f;
    struct _vertive * antecessor;
    cor c;
};
typedef struct _vertice vertice;


struct _topological_item{
    struct _topological_item * anterior;
    vertice * item;
};
typedef struct _topological_item topological_item;

void enqueue(vertice * elemento);

void add_vertice(vertice** grafo, char elemento);

int add_adjacencia(vertice* grafo, char origem, char elemento);

vertice * get_vertice(vertice* grafo, char elemento);

void busca_em_profundidade(vertice *grafo);

void visit(vertice *grafo, vertice *u, int *time);

void print_topological_queue();

topological_item * queue = NULL;

int main(){

    vertice * grafo = NULL;

    add_vertice(&grafo, 'm');
    add_vertice(&grafo, 'n');
    add_vertice(&grafo, 'o');
    add_vertice(&grafo, 'p');
    add_vertice(&grafo, 'q');
    add_vertice(&grafo, 'r');
    add_vertice(&grafo, 's');
    add_vertice(&grafo, 't');
    add_vertice(&grafo, 'u');
    add_vertice(&grafo, 'v');
    add_vertice(&grafo, 'w');
    add_vertice(&grafo, 'x');
    add_vertice(&grafo, 'y');
    add_vertice(&grafo, 'z');

    add_adjacencia(grafo, 'm', 'q');
    add_adjacencia(grafo, 'm', 'r');
    add_adjacencia(grafo, 'm', 'x');

    add_adjacencia(grafo, 'n', 'o');
    add_adjacencia(grafo, 'n', 'q');
    add_adjacencia(grafo, 'n', 'u');

    add_adjacencia(grafo, 'o', 'r');
    add_adjacencia(grafo, 'o', 's');
    add_adjacencia(grafo, 'o', 'v');

    add_adjacencia(grafo, 'p', 'o');
    add_adjacencia(grafo, 'p', 's');
    add_adjacencia(grafo, 'p', 'z');

    add_adjacencia(grafo, 'q', 't');

    add_adjacencia(grafo, 'r', 'u');
    add_adjacencia(grafo, 'r', 'y');

    add_adjacencia(grafo, 's', 'r');

    add_adjacencia(grafo, 'u', 't');

    add_adjacencia(grafo, 'v', 'w');
    add_adjacencia(grafo, 'v', 'x');

    add_adjacencia(grafo, 'w', 'z');

    add_adjacencia(grafo, 'y', 'v');


    busca_em_profundidade(grafo);
    print_topological_queue();
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
    novo->f = -1;
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
void busca_em_profundidade(vertice *grafo){

    //inicia a variável time
    int time = 0;

    //pega o vértice que será a origem da busca
    vertice * s = grafo;

    printf("\n** iniciando busca a partir de %c **\n\n", s->nome);

    //enquanto o ponteiro "atual" apontar para algum vértice, ou seja, percorre todas as adjacências do vértice "s"
    while(s != NULL){

        //se a adjacência estiver sinalizada como "não descoberta"
        if(s->c == BRANCO){

            //executa a busca em profundidade
            visit(grafo, s, &time);
        }

        //pega o próximo vértice
        s = s->prox_vertice;
    }

}




void visit(vertice *grafo, vertice *u, int *time){

    //incrementa o time
    *time = *time + 1;

    //seta o time inicial do vértice
    u->d = *time;

    //sinaliza o vértice como "descoberto"
    u->c = CINZA;

    //cria um ponteiro para armazenar a adjacência anterior que será atribuída ao vértice analisado
    vertice * adj_anterior = u;

    //cria um ponteiro que percorrerá os vértices adjacentes a "u" e faz com que ele aponte para a primeira adjacência
    vertice * adj_atual = adj_anterior->prox_adj;

    //cria um ponteiro para armazenar o vértice que está sendo analisado
    vertice * v = NULL;

    //enquanto o ponteiro "adj_atual" apontar para alguma adjacência, ou seja, percorre todas as adjacências do vértice "u"
    while(adj_atual != NULL){

        //pega o vértice correspondente à adjecência
        v = get_vertice(grafo, adj_atual->nome);

        //se o vértice estiver sinalizado como "não descoberto"
        if(v->c == BRANCO){

            //diz quem é o vértice antecessor
            v->antecessor = get_vertice(grafo, adj_anterior->nome);

            //executa a busca em profundidade em "v"
            visit(grafo, v, time);
        }

        //a adjacência anterior passa a ser a que foi analisada
        adj_anterior = adj_atual;

        //a adjacência atual passa a ser a próxima que será analisada
        adj_atual = adj_atual->prox_adj;
    }

    //sinaliza o vértice como "finalizado"
    u->c = PRETO;

    enqueue(u);

    //incrementa o time
    *time = *time + 1;

    //atribui o time final do vértice
    u->f = *time;

    printf("vertice %c: (%d, %d)\n", u->nome, u->d, u->f);
}




/**
Adiciona um elemento na pilha topológica.
*/
void enqueue(vertice * elemento){

    //cria um novo elemento
    topological_item *novo = malloc(sizeof(topological_item));
    novo->item = elemento;
    novo->anterior = NULL;

    //se a pilha topológica estiver vazia
    if(queue == NULL){

        //adiciona o primeiro elemento da pilha
        queue = novo;
    }else{

        //diz que o elemento anterior ao novo elemento é a cabeça da pilha
        novo->anterior = queue;

        //a cabeça da pilha passa a ser o novo elemento
        queue = novo;
    }
}




/**
Imprime a pilha topológica.
*/
void print_topological_queue(){
    topological_item *atual = queue;

    printf("\nLista topologica:\n");

    while(atual->anterior != NULL)
    {
        printf("%c - ", atual->item->nome);
        atual = atual->anterior;
    }

    printf("%c", atual->item->nome);
}
