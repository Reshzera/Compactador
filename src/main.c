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

int main(int argc, char **argv)
{

    if (!strcmp(argv[0], COMPACTA))
    {
        printf("Compacta\n");
    }
    else
        printf("Descompacta\n");
    return 0;
}