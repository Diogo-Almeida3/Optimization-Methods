#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias

int* init_dados(char *nome, int *m, int *g) {
    FILE *f;
    int *p, *q;
    int i,j,pos;
    char c;
    
    //Abrir ficheiro para leitura
    f = fopen(nome, "r");
    if (!f) {
        printf("Erro no acesso ao ficheiro dos dados\n");
        exit(1);
    }
    
    // Numero de m elementos e g subjconjuntos
    fscanf(f, "%d %d", m, g);
    while ((c = getc(f)) != '\n');

    
    //Quantidade de linhas
    int linhas = 0;
    for (i = 1; i < *m; i++)
        linhas += i;
    
    // Alocacao dinamica da matriz numero de linhas x 3 colunas
    p = (int *)malloc(sizeof (int)* linhas * 3);
    if (!p) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
    
    
    // Preenchimento da matriz 
    for (i = 0; i < linhas; i++){
        for(j = 0; j < 3 ; j++){
            pos = i * 3 +j;
            fscanf(f, "%d ", &p[pos]);
        }
    }

    
    //Fechar ficheiro
    fclose(f);
    return p;
}



// Gera a solucao inicial
// Parametros: solucao, preenche com 0 e 1 o vetor

void gera_sol_inicial(int *sol, int m,int g, int n) {
    int i, x, j;
    for (i = 0; i < m; i++)
        sol[i] = -1;

    for (i = 0; i < g; i++){
        for (j = 0; j < n; j++) {
            do {
                x = random_l_h(0, m - 1);
            } while (sol[x] != -1 );
            sol[x] = i;
        }
    }
    
    
}

// Escreve solucao
// Parametros: solucao e numero de vertices

void escreve_sol(int *sol, int m) {
    int i;
    printf("\nSolucao: \n");
    for (i = 0; i < m; i++)
        printf("%d ", sol[i]);
    printf("\n");
}

// copia vector b para a (tamanho n)

void substitui(int a[], int b[], int m) {
    int i;
    for (i = 0; i < m; i++)
        a[i] = b[i];
}

// Inicializa o gerador de numeros aleatorios

void init_rand() {
    srand((unsigned) time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max

int random_l_h(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]

float rand_01() {
    return ((float) rand()) / RAND_MAX;
}
