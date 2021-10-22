#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#include <math.h>
#define PROB 0.01
// Gera um vizinho
// Parametros: solucao actual, vizinho, quantidade elementos, subconjuntos
//swap two vertices

void gera_vizinho(int a[], int b[], int m,int g) {
    int i, x, j;
    //Transfere o vetor para o vizinho
    for (i = 0; i < m; i++)
        b[i] = a[i];
    //Escolhe um bit j random
    j = random_l_h(0, g - 1);
    
    //Escolhe uma posição random com o bit j
    do {
        x = random_l_h(0, m - 1);
    } while (b[x] != j); 
    
    do{
        i = random_l_h(0, g - 1);
    } while(i == j);
    b[x] = i;
    
    //Procura uma posição com o bit i
    do {
        x = random_l_h(0, m - 1);
    } while(b[x] != i);
    b[x] = j;
     
}

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de m elementos e numero de subcconjuntos
// Devolve o custo da melhor solucao encontrada

/*
int trepa_colinas(int sol[], int *mat, int m, int g,int n) {
    int *nova_sol,*nova_sol2, custo, custo_viz,custo_viz2, i;
    int iteracoes = 5000;
    nova_sol = malloc(sizeof (int) * m);
    nova_sol2 = malloc(sizeof (int) * m);
    if (nova_sol == NULL ) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    
    // Avalia solucao inicial
    custo = calcula_fit(sol , mat , m ,g , n);
    
    for (i = 0; i < iteracoes; i++) {
        // Gera vizinho
        gera_vizinho(sol, nova_sol, m,g);
        gera_vizinho(sol, nova_sol2, m,g);
        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, mat,m,g,n);
        custo_viz2 = calcula_fit(nova_sol2, mat,m,g,n);
        // Aceita vizinho se o custo aumentar (problema de maximizaçao) 
        if (custo_viz >= custo) {
            substitui(sol, nova_sol, m);
            custo = custo_viz;
        } else {
            if (rand_01() <  PROB) {
                substitui(sol, nova_sol, m);
                custo = custo_viz;
            }
        }
        if (custo_viz >= custo && custo_viz >= custo_viz2) {
            substitui(sol, nova_sol, m);
            custo = custo_viz;
        } else if (custo_viz2 >= custo && custo_viz2 >= custo_viz) {
            substitui(sol, nova_sol2, m);
            custo = custo_viz;
        }
    }   
    free(nova_sol);
    free(nova_sol2);
    return custo;
}*/


int recristalizacao(int sol[], int *mat, int m, int g, int n) {
    int *nova_sol, *nova_sol2, custo, custo_viz,custo_viz2;
    float temp, erro, prob_aceitar;
    
    float max = 10, min = 0.5; //Temperaturas
    float iteracoes = 1000;

    nova_sol = malloc(sizeof (int) * m);
    nova_sol2 = malloc(sizeof (int) * m);
    if (nova_sol == NULL) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, m, g, n);
    temp = max;
    while (temp > min) {
        temp -= (max - min) / iteracoes; //Faz com que a temperatura desca

        gera_vizinho(sol, nova_sol, m, g);
        gera_vizinho(sol, nova_sol2, m, g);
        custo_viz = calcula_fit(nova_sol, mat, m, g, n);
        custo_viz2 = calcula_fit(nova_sol2, mat, m, g, n);
        
        if (custo_viz >= custo && custo_viz >= custo_viz2) {
            substitui(sol, nova_sol, m);
            custo = custo_viz;
        } else if (custo_viz2 >= custo && custo_viz2 >= custo_viz) {
            substitui(sol, nova_sol2, m);
            custo = custo_viz2;
        } else {
            erro = custo - custo_viz;
            prob_aceitar = exp(erro / temp);
            
            if (prob_aceitar > rand_01()) {
                substitui(sol, nova_sol, m);
                custo = custo_viz;
            }
        }
    }

    free(nova_sol);
    free(nova_sol2);
    return custo;
}