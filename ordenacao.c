#include <stdio.h>
#include <time.h>

#define ARQUIVO "listaOdenada.txt"
#define MAX 10000000

int vetor[MAX];
int auxiliar[MAX];

void intercalar(int v[], int aux[], int inicio, int meio, int fim) {
    int i = inicio;
    int j = meio;
    int k = inicio;

    while (i < meio && j < fim) {
        if (v[i] <= v[j]) {
            aux[k] = v[i];
            i++;
        } else {
            aux[k] = v[j];
            j++;
        }
        k++;
    }
    while (i < meio) {
        aux[k] = v[i];
        i++;
        k++;
    }
    while (j < fim) {
        aux[k] = v[j];
        j++;
        k++;
    }

    for (i = inicio; i < fim; i++) {
        v[i] = aux[i];
    }
}

void merge_sort(int v[], int aux[], int inicio, int fim) {
    if (fim - inicio <= 1) {
        return;
    }
    int meio = (inicio + fim) / 2;
    merge_sort(v, aux, inicio, meio);
    merge_sort(v, aux, meio, fim);
    if (v[meio - 1] <= v[meio]) {
        return;
    }
    intercalar(v, aux, inicio, meio, fim);
}

int main() {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", ARQUIVO);
        return 1;
    }

    int total_elementos = 0;
    while (total_elementos < MAX && fscanf(arquivo, "%d", &vetor[total_elementos]) == 1) {
        total_elementos++;
    }
    fclose(arquivo);

    if (total_elementos == 0) {
        printf("Arquivo vazio.\n");
        return 1;
    }

    clock_t inicio = clock();
    merge_sort(vetor, auxiliar, 0, total_elementos);
    clock_t fim = clock();
    double tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Tempo de ordenação: %f segundos (%f ms)\n", tempo_gasto, tempo_gasto * 1000.0);

    return 0;
}