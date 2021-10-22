#include "funcao.h"
#include "utils.h"
#include  <stdio.h>

// Calcula a qualidade de uma solução
// Recebe:  A solução, a, a matriz de adjacências, mat e m
// Devolve: O custo que o número de ligações que existem na solução
int calcula_fit(int a[], int *mat, int m, int g, int n) {
    int total = 0;
    int i, j, t,z ,aux;
    int cont;
    int arm[n];

    int linhas = 0;
    for (i = 1; i < m; i++)
        linhas += i;

    for (i = 0; i < g; i++) { 
        
        for (j = 0, cont = 0; j < n; j++) 
            arm[j] = -1;

        for (j = 0; j < m || cont != n; j++)
            if (a[j] == i){
                arm[cont++] = j;
            }
        
        for (j = 0; j < n - 1; j++) { 
            for (z = 1; (j + z) < n; z++) { 
                for (t = 0, aux = 1; t < linhas && aux == 1; t++) {
                    if (mat[t * 3 + 0] == arm[j] && mat[t * 3 + 1] == arm[j + z]) {
                        total += mat[t * 3 + 2];
                        aux = 0;
                    }
                }
            }
        }          
    }
    return total;
    
    
}

