

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ull;

/* ---------- Funcoes de calculo ---------- */

/* Fatorial (cabe em ull ate n = 20) */
ull fatorial(int n) {
    ull r = 1;
    for (int i = 2; i <= n; i++)
        r *= i;
    return r;
}

/* Arranjo: A(n,p) = n * (n-1) * ... * (n-p+1)  (evita estourar com fatoriais grandes) */
ull arranjo(int n, int p) {
    if (p < 0 || p > n) return 0;
    ull r = 1;
    for (int i = 0; i < p; i++)
        r *= (ull)(n - i);
    return r;
}

/* Permutacao simples: P(n) = n! */
ull permutacao(int n) {
    return fatorial(n);
}

/* Combinacao: C(n,p) calculada de forma incremental (divisao sempre exata) */
ull combinacao(int n, int p) {
    if (p < 0 || p > n) return 0;
    if (p > n - p) p = n - p;           /* C(n,p) = C(n,n-p) */
    ull r = 1;
    for (int i = 1; i <= p; i++) {
        r = r * (ull)(n - p + i) / i;
    }
    return r;
}

/* ---------- Triangulo de Pascal ---------- */

void trianguloPascal(int linhas) {
    /* Aloca a matriz triangular */
    ull **t = malloc(linhas * sizeof(ull *));
    if (!t) { printf("Erro de memoria.\n"); return; }

    for (int i = 0; i < linhas; i++) {
        t[i] = malloc((i + 1) * sizeof(ull));
        t[i][0] = t[i][i] = 1;
        for (int j = 1; j < i; j++)
            t[i][j] = t[i - 1][j - 1] + t[i - 1][j];
    }

    /* Largura de cada celula, baseada no maior numero da ultima linha */
    int larg = 1;
    ull maior = 0;
    for (int j = 0; j < linhas; j++)
        if (t[linhas - 1][j] > maior) maior = t[linhas - 1][j];
    for (ull m = maior; m >= 10; m /= 10) larg++;
    larg++;                              /* espaco entre os numeros */

    printf("\nTriangulo de Pascal (%d linhas):\n\n", linhas);
    for (int i = 0; i < linhas; i++) {
        /* recuo para centralizar */
        for (int s = 0; s < (linhas - 1 - i) * larg / 2; s++) putchar(' ');
        for (int j = 0; j <= i; j++)
            printf("%*llu", larg, t[i][j]);
        putchar('\n');
        free(t[i]);
    }
    free(t);
}



static void troca(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static void gerarPermutacoes(int *v, int ini, int n, ull *cont) {
    if (ini == n) {
        (*cont)++;
        printf("%4llu: ", *cont);
        for (int i = 0; i < n; i++) printf("%d ", v[i]);
        putchar('\n');
        return;
    }
    for (int i = ini; i < n; i++) {
        troca(&v[ini], &v[i]);
        gerarPermutacoes(v, ini + 1, n, cont);
        troca(&v[ini], &v[i]);
    }
}

/* ---------- Entrada de dados ---------- */

int lerInt(const char *msg, int min, int max) {
    int x;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &x) != 1) {
            while (getchar() != '\n');   /* limpa entrada invalida */
            printf("Entrada invalida.\n");
            continue;
        }
        if (x < min || x > max) {
            printf("Digite um valor entre %d e %d.\n", min, max);
            continue;
        }
        return x;
    }
}

/* ---------- Programa principal ---------- */

int main(void) {
    int op;

    do {
        printf("\n===== ANALISE COMBINATORIA =====\n");
        printf("1 - Triangulo de Pascal\n");
        printf("2 - Arranjo A(n,p)\n");
        printf("3 - Permutacao Simples P(n)\n");
        printf("4 - Combinacao C(n,p)\n");
        printf("0 - Sair\n");
        op = lerInt("Opcao: ", 0, 4);

        switch (op) {
        case 1: {
            int linhas = lerInt("Numero de linhas (1 a 20): ", 1, 20);
            trianguloPascal(linhas);
            break;
        }
        case 2: {
            int n = lerInt("n (0 a 20): ", 0, 20);
            int p = lerInt("p (0 a n): ", 0, n);
            printf("\nA(%d,%d) = %d!/(%d-%d)! = %llu\n", n, p, n, n, p, arranjo(n, p));
            break;
        }
        case 3: {
            int n = lerInt("n (0 a 20): ", 0, 20);
            printf("\nP(%d) = %d! = %llu\n", n, n, permutacao(n));
            if (n >= 1 && n <= 5) {
                char r;
                printf("Listar todas as permutacoes? (s/n): ");
                scanf(" %c", &r);
                if (r == 's' || r == 'S') {
                    int v[5];
                    ull cont = 0;
                    for (int i = 0; i < n; i++) v[i] = i + 1;
                    printf("\n");
                    gerarPermutacoes(v, 0, n, &cont);
                }
            }
            break;
        }
        case 4: {
            int n = lerInt("n (0 a 60): ", 0, 60);
            int p = lerInt("p (0 a n): ", 0, n);
            printf("\nC(%d,%d) = %d!/(%d! * %d!) = %llu\n", n, p, n, p, n - p, combinacao(n, p));
            break;
        }
        case 0:
            printf("Encerrando...\n");
            break;
        }
    } while (op != 0);

    return 0;
}