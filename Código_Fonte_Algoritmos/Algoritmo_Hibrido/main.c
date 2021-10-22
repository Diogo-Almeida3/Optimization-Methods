#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define DEFAULT_RUNS 5

int main(int argc, char *argv[]) {
    char nome_fich[100];
    struct info EA_param;
    pchrom pop = NULL, parents = NULL;
    chrom best_run, best_ever;
    int gen_actual, r, runs, mat[MAX_OBJ][3],custo = 0,*sol;
    float mbf = 0.0;
    int final = 0;
    // Le os argumentos de entrada
    if (argc == 3) {
        runs = atoi(argv[2]);
        strcpy(nome_fich, argv[1]);
    } else if (argc == 2) {
        runs = DEFAULT_RUNS;
        strcpy(nome_fich, argv[1]);
    } else {
        runs = DEFAULT_RUNS;
        printf("Nome do Ficheiro: ");
        gets(nome_fich);
    }
    
    if (runs <= 0)
        return 0;

    init_rand();
    
    
    EA_param = init_data(nome_fich, mat);

    sol = malloc(sizeof (int) * EA_param.m);
    for (r = 0; r < runs; r++) {
        printf("\nRepeticao %d\n", r + 1);
        
        pop = init_pop(EA_param);
        evaluate(pop, EA_param, mat);
        gen_actual = 1;

        best_run = pop[0];
        best_run = get_best(pop, EA_param, best_run);
        parents = malloc(sizeof (chrom) * EA_param.popsize);

        if (parents == NULL) {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }
        //Ciclo Pesquisa Local
        gera_sol_inicial(sol,EA_param,mat);
        //custo = trepa_colinas(sol, EA_param,mat);
        custo = recristalizacao(sol, EA_param,mat);
        
        //Ciclo evolutivo
        while (gen_actual <= EA_param.numGenerations) {
            tournament(pop, EA_param, parents);
            genetic_operators(parents, EA_param, pop);
            evaluate(pop, EA_param, mat);
            best_run = get_best(pop, EA_param, best_run);
            gen_actual++;
        }
        
        if (custo > best_run.fitness) {
            printf("Melhor: %d\n",custo);
            mbf += custo;
            if (r == 0 || custo > final)
                final = custo;
        } else {
            printf("Melhor: %d\n",best_run.fitness);
            mbf += best_run.fitness;
            if (r == 0 || best_run.fitness > final)
                final = best_run.fitness;
        }

        free(sol);
        free(parents);
        free(pop);
    }
    
    
    printf("\n\nMBF: %f\n", mbf / r);
    printf("\nMelhor solucao encontrada");
    write_best(final, EA_param);
    return 0;
}
