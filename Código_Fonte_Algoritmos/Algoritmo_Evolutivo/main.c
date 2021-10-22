#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define DEFAULT_RUNS 15

int main(int argc, char *argv[]) {
    char nome_fich[100];
    struct info EA_param;
    pchrom pop = NULL, parents = NULL;
    chrom best_run, best_ever;
    int gen_actual, r, runs, i, inv, mat[MAX_OBJ][3];
    float mbf = 0.0;

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
    //Inicializa o gerador de números aleatórios
    init_rand();
    
    // Preenche a matriz 
    EA_param = init_data(nome_fich, mat);
    // Faz um ciclo com o numero de execuçoes definidas
    for (r = 0; r < runs; r++) {
        printf("Repeticao %d\n", r + 1);
        
        // Geraçao da populaçao inicial
        pop = init_pop(EA_param);

        // Avalia a populaçao inicial
        evaluate(pop, EA_param, mat);

        gen_actual = 1;
        // Como ainda nao existe, escolhe-se como melhor solucao a primeira da populaçao (poderia ser outra qualquer)
        best_run = pop[0];
        // Encontra-se a melhor solucao dentro de toda a populacao
        best_run = get_best(pop, EA_param, best_run);
        // Reserva espaco para os pais da popula��o seguinte
        parents = malloc(sizeof (chrom) * EA_param.popsize);
        // Caso nao consiga fazer a alocacao, envia aviso e termina o programa
        if (parents == NULL) {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }
        
        // Ciclo de optimizacao
        while (gen_actual <= EA_param.numGenerations) {
            
            // Torneio binario para encontrar os progenitores (ficam armazenados no vector parents)
            tournament(pop, EA_param, parents);
            
            // Aplica os operadores geneticos aos pais (os descendentes ficam armazenados na estrutura pop)
            genetic_operators(parents, EA_param, pop);

            // Avalia a nova populacao (a dos filhos)
            evaluate(pop, EA_param, mat);

            // Actualiza a melhor solucao encontrada
            best_run = get_best(pop, EA_param, best_run);
            gen_actual++;
        }
        
        // Contagem das solucoes invalidas
        for (inv = 0, i = 0; i < EA_param.popsize; i++)
            if (pop[i].valido == 0)
                inv++;
        
        // Escreve resultados da repeticao que terminou
        write_best(best_run, EA_param);
        
        printf("\nPercentagem Invalidos: %.2f\n", 100 * (float) inv / EA_param.popsize);
        mbf += best_run.fitness;
        
        if (r == 0 || best_run.fitness > best_ever.fitness)
            best_ever = best_run;
        //Liberta a memoria usada
        free(parents);
        free(pop);
    }
    
    
    
    // Escreve resultados globais
    printf("\n\nMBF: %f\n", mbf / r);
    printf("\nMelhor solucao encontrada");
    write_best(best_ever, EA_param);
    return 0;
}
