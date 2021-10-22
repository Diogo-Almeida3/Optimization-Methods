//#define MAX_OBJ 28680  // Numero maximo de objectos -> 240
//#define MAX_OBJ 7140  // Numero maximo de objectos -> 120
#define MAX_OBJ 1770  // Numero maximo de objectos -> 60
//#define MAX_OBJ 465  // Numero maximo de objectos -> 30
//#define MAX_OBJ 66 // Numero maximo de objectos -> 12
//#define MAX_OBJ 45 // Numero maximo de objectos -> 10
// EStrutura para armazenar parametros

struct info {
    int popsize;
    // Tamanho da população
    int m;
    //Quantidade de subconjuntos
    int g;
    //Quantidade de elementos por subconjunto
    int n;
    //Numero de linhas
    int linhas;
    // Probabilidade de mutaçao
    float pm;
    // Probabilidade de recombinaçao
    float pr;
    // Tamanho do torneio para seleçao do pai da praxima geraçao
    int tsize;
    // Constante para avaliaçao com penalizaçao
    float ro;
    // Numero de geraçaes
    int numGenerations;
};

// Individuo (soluçao)
typedef struct individual chrom, *pchrom;

struct individual {
    // Solucao (objetos que estao dentro da mochila)
    int p[MAX_OBJ];
    // Valor da qualidade da soluçao
    int fitness;
    // 1 se for uma soluçao valida e 0 se nao for
    int valido;
};

void tournament(pchrom pop, struct info d, pchrom parents);

void genetic_operators(pchrom parents, struct info d, pchrom offspring);

void crossover(pchrom parents, struct info d, pchrom offspring);

void mutation(pchrom offspring, struct info d);
