#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "artista.c"

// Função para realizar 30 inserções seguidas de uma busca
void experimento_insercao_e_busca(Artista **raiz, char *nomes_artistas[], int num_artistas) {
    clock_t inicio, fim;
    double tempo_total_busca = 0.0;

    // Inserções
    for (int i = 0; i < num_artistas; i++) {
        // Realiza a inserção
        insere_Artista(raiz, nomes_artistas[i], "Estilo Musical", i + 1);
    }

    // Buscas por todos os artistas inseridos
    for (int i = 0; i < num_artistas; i++) {
        inicio = clock();

        // Realiza a busca
        Artista *encontrado = achar_artista(*raiz, nomes_artistas[i]);

        fim = clock();
        double tempo_gasto_busca = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        tempo_total_busca += tempo_gasto_busca;

        printf("Busca - Artista: %s\n", nomes_artistas[i]);

        if (encontrado != NULL) {
            printf("  Artista encontrado. Tempo gasto: %.2f microssegundos\n", tempo_gasto_busca * 100000);
        } else {
            printf("  Artista nao encontrado. Tempo gasto: %.2f microssegundos\n", tempo_gasto_busca * 100000);
        }
    }

    printf("Tempo medio gasto para todas as buscas: %.2f microssegundos \n", (tempo_total_busca/30)*100000);
}

int main() {
    Artista *arvore = NULL;

    char *nomes_artistas[30];

    // Gerar nomes de artistas automaticamente
    for (int i = 0; i < 30; i++) {
        char nome_artista[20];
        sprintf(nome_artista, "Artista%d", i + 1);
        nomes_artistas[i] = strdup(nome_artista);
    }

    // Realiza o experimento de inserção e busca
    experimento_insercao_e_busca(&arvore, nomes_artistas, 30);

    // Liberar memória alocada para os nomes de artistas
    for (int i = 0; i < 30; i++) {
        free((void *)nomes_artistas[i]);
    }

    return 0;
}
