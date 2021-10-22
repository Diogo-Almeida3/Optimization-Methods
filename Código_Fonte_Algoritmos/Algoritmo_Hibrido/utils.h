struct info init_data(char *s, int mat[][3]);

pchrom init_pop(struct info d);

void print_pop(pchrom pop, struct info d);

chrom get_best(pchrom pop, struct info d, chrom best);

void write_best(int x, struct info d);

void init_rand();

int random_l_h(int min, int max);

float rand_01();

int flip();

void substitui(int a[], int b[], int n);

void gera_sol_inicial(int sol[], struct info d,int mat[][3]);