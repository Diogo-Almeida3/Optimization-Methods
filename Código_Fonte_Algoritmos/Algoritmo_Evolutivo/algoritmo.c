#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

// Preenche uma estrutura com os progenitores da proxima geraçao, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Parametros de entrada: populaçao actual (pop), estrutura com parametros (d) e populaçao de pais a encher

void tournament(pchrom pop, struct info d, pchrom parents) {
    int i, x1, x2;

    // Realiza popsize torneios
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

// Operadores geneticos a usar na geraçao dos filhos
// Parametros de entrada: estrutura com os pais (parents), estrutura com parametros (d), estrutura que guardar os descendentes (offspring)

void genetic_operators(pchrom parents, struct info d, pchrom offspring) {
    // Recombinaçao com um ponto de corte
    crossover(parents, d, offspring);
    // Mutaçao binaria
    mutation(offspring, d);
}

// Preenche o vector descendentes com o resultado das operaçoes de recombinaçao
// Parametros de entrada: estrutura com os pais (parents), estrutura com par�metros (d), estrutura que guardar os descendentes (offspring)
/*
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
}*/

//Recombinacao com 2 pontos de corte
/*
void crossover(pchrom parents, struct info d, pchrom offspring) {
    int i, j, point,point2;

    for (i = 0; i < d.popsize; i += 2) {       
        if (rand_01() < d.pr) {
            point = random_l_h(0, d.m - 2);
            point2 = random_l_h(point, d.m - 1);
            for (j = 0; j < point; j++) {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i + 1].p[j];
            }
            for(;j < point2;j++){
                offspring[i].p[j] = parents[i + 1].p[j];
                offspring[i + 1].p[j] = parents[i].p[j];
            }
            for (j = point; j < d.m; j++) {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i+1].p[j];
            }
        } else {
            offspring[i] = parents[i];
            offspring[i + 1] = parents[i + 1];
        }
    }
}*/

//Recombinaçao uniforme

void crossover(pchrom parents, struct info d, pchrom offspring) {
    int i, j;

    for (i = 0; i < d.popsize; i += 2) {   
        if (rand_01() < d.pr) {
            for(j = 0; j < d.m; j++){
                if(rand_01() < 0.5) {
                    offspring[i].p[j] = parents[i].p[j];
                    offspring[i + 1].p[j] = parents[i + 1].p[j];
                } else{
                    offspring[i + 1].p[j] = parents[i].p[j];
                    offspring[i].p[j] = parents[i + 1].p[j];
                }
            }
        } else {
            offspring[i] = parents[i];
            offspring[i + 1] = parents[i + 1];
        }
    }
}

// Mutaçao binaria com varios pontos de mutaçao
// Parametros de entrada: estrutura com os descendentes (offspring) e estrutura com par�metros (d)

void mutation(pchrom offspring, struct info d) {
    int i, j;

    for (i = 0; i < d.popsize; i++)
        for (j = 0; j < d.m; j++)
            if (rand_01() < d.pm)
                offspring[i].p[j] = !(offspring[i].p[j]);
}

//Mutaçao por troca
/*
void mutation(pchrom offspring, struct info d) {
    int i, j,t,x;

    for (i = 0; i < d.popsize; i++){

        if (rand_01() < d.pm) {
            x = random_l_h(0, d.m - 1); //Escolhe um número de subconjunto
            do {
                j = random_l_h(0, d.m - 1); //Escolhe uma posição da solução diferente de x
            } while (offspring[i].p[j] == offspring[i].p[x]);
            
            t = offspring[i].p[x];
            offspring[i].p[x] = offspring[i].p[j];
            offspring[i].p[j] = t;
            
            
        }
    }
}*/