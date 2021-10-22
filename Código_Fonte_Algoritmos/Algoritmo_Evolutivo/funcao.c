#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Calcula a qualidade de uma soluçao
// Parametros de entrada: soluçao (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Parametros de saida: qualidade da soluçao (se a capacidade for excedida devolve 0)

float eval_individual(int sol[], struct info d, int mat[][3], int *v) {

    int i, cont, j, t, z, ro;
    int arm[d.n];
    int total = 0, aux;

    for (i = 0; i < d.g; i++) {

        for (j = 0, cont = 0; j < d.n; j++)
            arm[j] = -1;

        for (j = 0; j < d.m && cont != d.n; j++)
            if (sol[j] == i)
                arm[cont++] = j;

        for (j = 0; j < d.n - 1; j++)
            for (z = 1; (j + z) < d.n; z++) 
                for (t = 0, aux = 1; t < d.linhas && aux == 1; t++) 
                    if (mat[t][0] == arm[j] && mat[t][1] == arm[j + z]) {
                        total += mat[t][2];
                        aux = 0;
                    }           
    }
    /*ALGORITMO BASE*/
    /*for (i = 0; i < d.g; i++) {
        for (j = 0, cont = 0; j < d.m; j++) {
            if (sol[j] == i) {
                cont++;
            }
        }
        if (cont != d.n) {
            *v = 0;
            return 0;
        }
    }

    *v = 1;
    return total;*/
    /* PENALIZAÇÃO LINEAR */
/*    for (i = 0; i < d.g; i++) {
        for (j = 0, cont = 0; j < d.m; j++) {
            if (sol[j] == i) {
                cont++;
            }
        }
        if (cont != d.n) {
            *v = 1;
            ro = ceil(d.n / d.g);
            return total - ro * (d.m);
        }
    }
*/
    *v = 1;
    return total;

}

// Avaliacao da populaçao
// Parametros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Parametros de saida: Preenche pop com os valores de fitness e de validade para cada solu��o

void evaluate(pchrom pop, struct info d, int mat[][3]) {
    int i;

    for (i = 0; i < d.popsize; i++)
        pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido);

}
