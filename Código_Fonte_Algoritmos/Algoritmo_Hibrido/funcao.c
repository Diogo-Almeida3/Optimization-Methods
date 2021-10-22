#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float eval_individual(int sol[], struct info d, int mat[][3]) {

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


    return total;

}

void evaluate(pchrom pop, struct info d, int mat[][3]) {
    int i;

    for (i = 0; i < d.popsize; i++)
        pop[i].fitness = eval_individual(pop[i].p, d, mat);

}


void gera_vizinho(int a[], int b[], struct info d) {
    int i, x, j;

    for (i = 0; i < d.m; i++)
        b[i] = a[i];
    j = random_l_h(0, d.g - 1);
    
    do {
        x = random_l_h(0, d.m - 1);
    } while (b[x] != j); 
    
    do{
        i = random_l_h(0, d.g - 1);
    } while(i == j);
    b[x] = i;
    
    do {
        x = random_l_h(0, d.m - 1);
    } while(b[x] != i);
    b[x] = j;
     
}
/*
int trepa_colinas(int sol[], struct info d,int mat[][3]) {
    int *nova_sol, custo, custo_viz, i;
    int iteracoes = 5000;
    nova_sol = malloc(sizeof (int) * d.m);

    if (nova_sol == NULL ) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    
    // Avalia solucao inicial
    custo = eval_individual(sol ,d, mat );
    
    for (i = 0; i < iteracoes; i++) {
        // Gera vizinho
        gera_vizinho(sol, nova_sol, d);
        // Avalia vizinho
        custo_viz = eval_individual(nova_sol,d, mat);

        if (custo_viz >= custo) {
            substitui(sol, nova_sol, d.m);
            custo = custo_viz;
        }
     
    }   
    free(nova_sol);
    return custo;
}*/

int recristalizacao(int sol[], struct info d,int mat[][3]) {
    int *nova_sol, custo, custo_viz;
    float temp, erro, prob_aceitar;
    
    float max = 10, min = 0.5; //Temperaturas
    float iteracoes = 5000;

    nova_sol = malloc(sizeof (int) * d.m);

    if (nova_sol == NULL) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Avalia solucao inicial
    custo = eval_individual(sol ,d, mat );
    temp = max;
    while (temp > min) {
        temp -= (max - min) / iteracoes; //Faz com que a temperatura desca

        gera_vizinho(sol, nova_sol, d);

        custo_viz = eval_individual(nova_sol,d, mat);

        
        if (custo_viz >= custo ) {
            substitui(sol, nova_sol, d.m);
            custo = custo_viz;
        }  else {
            erro = custo - custo_viz;
            prob_aceitar = exp(erro / temp);
            if (prob_aceitar > rand_01()) {
                substitui(sol, nova_sol, d.m);
                custo = custo_viz;
            }
        }
    }

    free(nova_sol);
    return custo;
}