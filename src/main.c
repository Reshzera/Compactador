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
    int digitos[8]; // cada digito do binario
};

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
    Letra *aux = letra1;
    letra1 = letra2;
    letra2 = aux;
}

void desce(struct Heap *heap, int i)
{
    int no_esquerdo_pos, no_direito_pos, maior;

    no_esquerdo_pos = esquerdo(i);
    no_direito_pos = direito(i);

    if (no_esquerdo_pos < heap->tam && heap->vetor_chaves[no_direito_pos].frequencia > heap->vetor_chaves[i].frequencia)
        maior = no_esquerdo_pos;
    else
        maior = i;

    if (no_direito_pos < heap->tam && heap->vetor_chaves[no_direito_pos].frequencia > heap->vetor_chaves[maior].frequencia)
        maior = no_direito_pos;

    if (maior != i)
    {
        troca((heap->vetor_chaves + maior), (heap->vetor_chaves + maior));
        desce(heap, maior);
    }
}

void imprime_heap(struct Heap heap)
{
    printf("\nHeap:\n");
    for (int i = 0; i <= heap.tam; i++)
    {
        printf("Chave: %c Frequencia: %d\n", heap.vetor_chaves[i].chave, heap.vetor_chaves[i].frequencia);
    }
}

int compacta_arquivo(char *nome_arquivo)
{
    Letra frequencia[MAX_FREQ];
    FILE *file;
    file = fopen(nome_arquivo, "r"); // abre o arquivo para leitura

    struct Heap heap;
    // inicia o heap
    heap.tam = -1;
    // dar free
    heap.vetor_chaves = malloc(MAX_TAM_HEAP * sizeof(Letra));

    // inicia o vetor
    for (int i = 0; i < 257; i++)
    {
        frequencia[i].frequencia = 0;
        frequencia[i].chave = i;
    }

    // leitura do arquivo
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

    // percoree o vetor com as chaves e as adiciona
    // no heap
    for (int i = 0; i < 256; i++)
    {
        // se a letra foi lida alguma vez
        if (frequencia[i].frequencia != 0)
        {
            heap.tam++;
            *(heap.vetor_chaves + heap.tam) = frequencia[i];
        }
    }
    desce(&heap, i);

    imprime_heap(heap);

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