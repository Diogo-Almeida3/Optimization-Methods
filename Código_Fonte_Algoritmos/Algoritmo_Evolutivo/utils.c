#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"

// Inicializaçao do gerador de numeros aleatorios

void init_rand() {
    srand((unsigned) time(NULL));
}

// Leitura dos parametros e dos dados do problema
// Parametros de entrada: Nome do ficheiro e matriz a preencher com os dados dos objectos (peso e valor)
// Parametros de saida: Devolve a estrutura com os parametros

struct info init_data(char *filename, int mat[MAX_OBJ][3]) {
    struct info x;
    FILE *f;
    char c;
    int i; 
    
    f = fopen(filename, "rt");
    if (!f) {
        printf("File not found\n");
        exit(1);
    }
    // Leitura dos parametros do problema
    fscanf(f,"%d %d",&x.m,&x.g);
    while((c = getc(f) != '\n'));
    
    x.linhas = 0;
    for( i = 0; i < x.m; i++)
        x.linhas += i;
    
    x.numGenerations = 1250;
    x.popsize = 50;
    x.pm = 0.01;
    
    x.pr = 0.7;
    x.tsize = 2;
    x.n = x.m / x.g;
    
    
    x.ro = 0.0;
    // Leitura dos dados da matriz
    for (i = 0; i < x.linhas; i++)
        fscanf(f, "%d %d %d", &mat[i][0], &mat[i][1],&mat[i][2]);
    fclose(f);
    
    // Devolve a estrutura com os parametros
    return x;
}

// Simula o lançamento de uma moeda, retornando o valor 0 ou 1
int flip() {
    if ((((float) rand()) / RAND_MAX) < 0.5)
        return 0;
    else
        return 1;
}

// Criacao da populacao inicial. O vector e alocado dinamicamente
// Parametro de entrada: Estrutura com parametros do problema
// Parametro de saida: Preenche da estrutura da populaçao apenas o vector binario com os elementos

pchrom init_pop(struct info d) {
    int i, j,z,x;
    pchrom indiv; 

    indiv = malloc(sizeof (chrom) * d.popsize);
    if (indiv == NULL) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
    for (i = 0; i < d.popsize; i++) { 
        
        for (j = 0; j < d.m; j++)
            indiv[i].p[j] = -1;
        
        for (j = 0; j < d.g; j++){
            for(z = 0; z < d.n; z++){
                do{
                    x = random_l_h(0, d.m - 1);
                } while(indiv[i].p[x] != -1);
                indiv[i].p[x] = j;
            }
        }   
    }
    return indiv;
}

// Actualiza a melhor soluçao encontrada
// Parametro de entrada: populacao actual (pop), estrutura com parametros (d) e a melhor solucao encontrada ate a geracao imediatamente anterior (best)
// Parametro de saida: a melhor solucao encontrada ate a geraçao actual
//FITNESS QUALIDADE
chrom get_best(pchrom pop, struct info d, chrom best) {
    int i;

    for (i = 0; i < d.popsize; i++) {
        if (best.fitness < pop[i].fitness)
            best = pop[i];
    }
    return best;
}

// Devolve um valor inteiro distribuido uniformemente entre min e max

int random_l_h(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Devolve um valor real distribuido uniformemente entre 0 e 1

float rand_01() {
    return ((float) rand()) / RAND_MAX;
}

// Escreve uma solucao na consola
// Parametro de entrada: populacao actual (pop) e estrutura com parametros (d)

void write_best(chrom x, struct info d) {
    int i;

    printf("\nBest individual: %d\n", x.fitness);
    for (i = 0; i < d.m; i++)
        printf("%d ", x.p[i]);
    putchar('\n');
}
