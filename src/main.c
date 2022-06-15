/**************************************************
 *
 * Alunos: Rafael Eitaró Oshiro e Luis Fernando Leite França
 * Trabalho 2
 * Professor(a): Nome do(a) professor(a)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>

#define COMPACTA "c"
#define DESCOMPACTA "d"
#define MAX_FREQ 257
#define MAX_TAM_NOME 201
#define MAX_TAM_HEAP 256
#define FOLHA 1
#define NAO_FOLHA 0

typedef struct Letra
{
    char chave;
    int frequencia;
} Letra;

struct Heap
{
    int tam;
    Letra *vetor_chaves;
};

// salva os digitos do binario
struct CodigoBinario
{
    int codigo_bin;
    int tamanho;
    char caractere;
};

struct NoArvHuff {
    struct NoArvHuff* dir, * esq;
    union {
        struct Letra letra;
        int soma_frequencia;
    } info;
    char tipo;
};

struct ArvHuff {
    struct NoArvHuff* raiz;
    int tam;
};

struct ArvHuff gerar_arv_huff (struct Heap heap) {
    struct ArvHuff arv_huff;
    arv_huff.raiz = NULL;
    arv_huff.raiz = 0;
    int i = 0;

    while(i < heap.tam) {
        struct NoArvHuff* nova_folha = (struct NoArvHuff*)(malloc(sizeof(struct NoArvHuff)));

        nova_folha->tipo = FOLHA;
        nova_folha->info.letra = heap.vetor_chaves[i];
        nova_folha->esq = nova_folha->dir = NULL;

        struct NoArvHuff* novo = (struct NoArvHuff*)(malloc(sizeof(struct NoArvHuff)));

        //  no primeiro elemento, a raiz nao esta alocada, na linha 74 vai acessar memoria nao alocada
        // , gerando assim um segmentation fault
        novo->tipo = NAO_FOLHA;
        novo->info.soma_frequencia = arv_huff.raiz->info.soma_frequencia + nova_folha->info.letra.frequencia; // erro de segmentation
        novo->dir = nova_folha;
        novo->esq = arv_huff.raiz;

        arv_huff.raiz = novo;

        i++;
    }
    return arv_huff;
}

int pai(int i)
{
    if (i == 0)
        return 0;
    else
        return (i - 1) / 2;
}

int esquerdo(int i)
{
    return (2 * i) + 1;
}

int direito(int i)
{
    return (2 * i) + 2;
}

void troca(Letra *letra1, Letra *letra2)
{
    Letra aux = *letra1;
    *letra1= *letra2;
    *letra2 = aux;
}

void desce(struct Heap heap, int i)
{
    int esq, dir, maior;

    esq = esquerdo(i);
    dir = direito(i);

    if (esq < heap.tam && heap.vetor_chaves[esq].frequencia > heap.vetor_chaves[i].frequencia)
        maior = esq;
    else
        maior = i;

    if (dir < heap.tam && heap.vetor_chaves[dir].frequencia > heap.vetor_chaves[maior].frequencia)
        maior = dir;

    if(maior != i) {
        troca(heap.vetor_chaves + i, heap.vetor_chaves + maior);
        desce(heap, maior);
    }
}

void imprime_heap(struct Heap heap)
{
    printf("\nHeap:\n");
    for (int i = 0; i < heap.tam; i++)
    {
        printf("Chave: %c Frequencia: %d\n", heap.vetor_chaves[i].chave, heap.vetor_chaves[i].frequencia);
    }
}

void heapsort (struct Heap heap)
{
    for (int i = heap.tam- 1; i >= 0; i--) {
        troca(heap.vetor_chaves, heap.vetor_chaves + i);
        heap.tam--;
        desce(heap, 0);
    }
}

struct Heap inicia_heap ()
{
    struct Heap hp;
    hp.vetor_chaves = (struct Letra*)(malloc(MAX_TAM_HEAP * sizeof(struct Letra)));
    hp.tam = 0;
    return hp;
}

void libera_heap(struct Heap heap)
{
    free(heap.vetor_chaves);
}

Letra inicia_letra (char c) {
    struct Letra l;
    l.chave = c;
    l.frequencia = 0;
    return l;
}

int compacta_arquivo(char *nome_arquivo)
{
    Letra frequencia[MAX_FREQ];
    FILE *file;
    file = fopen(nome_arquivo, "r"); // abre o arquivo para leitura

    // inicia o vetor
    for (int i = 0; i < 257; i++)
        frequencia[i] = inicia_letra(i);


    char c;

    while ((c = fgetc(file)) != EOF)
        frequencia[c].frequencia++; // calcula as frequencias


    // imprime as informacoes lidas
    for (int i = 0; i < 257; i++)
    {
        if (frequencia[i].frequencia != 0)
        {
            printf("Chave: %c Frequencia: %d\n", (char)i, frequencia[i].frequencia);
        }
    }
    printf("===============================");


    struct Heap heap = inicia_heap();

    // percoree o vetor com as chaves e as adiciona
    // no heap
    for (int i = 0; i < MAX_TAM_HEAP; i++)
    {
        // se a letra foi lida alguma vez
        if (frequencia[i].frequencia != 0)
        {
            heap.vetor_chaves[heap.tam] = frequencia[i];
            heap.tam++;
        }
    }

    heapsort(heap);

    struct ArvHuff arv_huff = gerar_arv_huff(heap);


    libera_heap(heap);
    return 0;
}

int main(int argc, char **argv)
{

    if (!strcmp(argv[1], COMPACTA))
    {
        compacta_arquivo(argv[2]);
    }
    else
        printf("Descompacta\n");
    return 0;
}
