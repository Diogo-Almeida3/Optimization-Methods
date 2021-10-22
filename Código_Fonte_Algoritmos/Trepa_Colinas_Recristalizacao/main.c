#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 10

int main(int argc, char *argv[]) {
    char nome_fich[100];
    int m, g, k, n, runs, custo, best_custo;
    int *sol, *best, *grafo;
    float mbf = 0.0;

    if (argc == 3) {
        runs = atoi(argv[2]);
        strcpy(nome_fich, argv[1]);
    } else
        if (argc == 2) {
        runs = DEFAULT_RUNS;
        strcpy(nome_fich, argv[1]);
    } else {
        runs = DEFAULT_RUNS;
        printf("Nome do Ficheiro: ");
        gets(nome_fich);
    }
    if (runs <= 0)
        return 0;
    //Inicia o random
    init_rand();
    
    // Preenche matriz de adjacencias vert -> m / num_iter = G
    grafo = init_dados(nome_fich, &m, &g);
    
    //Quantidade de elementos por diversidade
    n = m / g;
    
    //Aloca espaço para a solução
    sol = malloc(sizeof (int) * m);
    
    //Aloca espaço para a melhor solução
    best = malloc(sizeof (int) * m);
    
    if (sol == NULL || best == NULL) {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    
    for (k = 0; k < runs; k++) {
        // Gerar solucao inicial
        gera_sol_inicial(sol, m,g,n);       
        //escreve_sol(sol, m);
        // Trepa colinas sol -> soluçao
        //custo = trepa_colinas(sol, grafo, m, g, n);
        custo = recristalizacao(sol, grafo, m, g, n);
        // Escreve resultados da repeticao k
        printf("\nRepeticao %d:", k + 1);
        //escreve_sol(sol, m);
        printf("Custo final: %2d\n", custo);
        mbf += custo;
        if (k == 0 || best_custo < custo) {
            best_custo = custo;
            substitui(best, sol, m);
        }
    }
    // Escreve eresultados globais
    printf("\n\nMBF: %f\n", mbf / k);
    printf("\nMelhor solucao encontrada");
    escreve_sol(best, m);
    printf("Custo final: %2d\n", best_custo);
    
    free(grafo);
    free(sol);
    free(best);
    return 0;
}
