#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

void tournament(pchrom pop, struct info d, pchrom parents) {
    int i, x1, x2;

    for (i = 0; i < d.popsize; i++) {
        x1 = random_l_h(0, d.popsize - 1);
        do {
            x2 = random_l_h(0, d.popsize - 1);
        } while (x1 == x2);
        if (pop[x1].fitness > pop[x2].fitness) // Problema de maximizacao
            parents[i] = pop[x1];
        else
            parents[i] = pop[x2];
    }
}

void genetic_operators(pchrom parents, struct info d, pchrom offspring) {
    crossover(parents, d, offspring);
    mutation(offspring, d);
}


void crossover(pchrom parents, struct info d, pchrom offspring) {
    int i, j, point;

    for (i = 0; i < d.popsize; i += 2) {
        
        if (rand_01() < d.pr) {
            point = random_l_h(0, d.m - 1);
            for (j = 0; j < point; j++) {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i + 1].p[j];
            }
            for (j = point; j < d.m; j++) {
                offspring[i].p[j] = parents[i + 1].p[j];
                offspring[i + 1].p[j] = parents[i].p[j];
            }
        } else {
            offspring[i] = parents[i];
            offspring[i + 1] = parents[i + 1];
        }
    }
}

void mutation(pchrom offspring, struct info d) {
    int i, j;

    for (i = 0; i < d.popsize; i++)
        for (j = 0; j < d.m; j++)
            if (rand_01() < d.pm)
                offspring[i].p[j] = !(offspring[i].p[j]);
}

