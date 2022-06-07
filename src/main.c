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

typedef struct Letra
{
    char chave;
    int frequencia;
} Letra;

struct NoHeap;
struct NoHeap {
    Letra chave;
    struct NoHeap* dir, * esq;
};

struct Heap {
    int tam;
    struct NoHeap* vetor_chaves;
};


// salva os digitos do binario
struct CodigoBinario {
    int digitos [8]; // cada digito do binario
};


// ordena o vetor do maior para a menor baseado
// na frequencia
void ordena_vetor(Letra* vetor_chaves, int tam) {

}

// retorna um heap baseado na frequencia
struct Heap* montar_heap(Letra* vetor_chaves, int tam) {
    ordena_vetor(vetor_chaves, tam);
}



int compacta_arquivo(char *nome_arquivo)
{
    Letra frequencia[MAX_FREQ];
    FILE *file;
    file = fopen(nome_arquivo, "r"); // abre o arquivo para leitura

    // inicia o vetor
    for (int i = 0; i < 257; i++)
        frequencia[i].frequencia = 0;

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