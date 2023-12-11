#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura de uma Música
typedef struct Musica {
    char titulo[50];
    int duracao_minutos;
    struct Musica *prox;
} Musica;

// Função para criar um novo nó de música
Musica *criarMusica(char *titulo, int duracao_minutos) {
    Musica *nova_musica = (Musica *)malloc(sizeof(Musica));
    if (nova_musica != NULL) {
        strcpy(nova_musica->titulo, titulo);
        nova_musica->duracao_minutos = duracao_minutos;
        nova_musica->prox = NULL;
    }
    return nova_musica;
}

Musica *inserirMusica(Musica *raiz, char *titulo, int duracao_minutos) 
{
    printf("Entrou aqui inserirMusica\n");
    // Criar uma nova música
    Musica *novaMusica = criarMusica(titulo, duracao_minutos);

    // Caso a lista esteja vazia ou a nova música deva ser inserida no início
    if (raiz == NULL || strcmp(novaMusica->titulo, raiz->titulo) < 0) {
        novaMusica->prox = raiz;
        return novaMusica;
    }

    // Procura a posição correta para inserir a música mantendo a lista ordenada
    Musica *atual = raiz;
    while (atual->prox != NULL && strcmp(novaMusica->titulo, atual->prox->titulo) > 0) {
        atual = atual->prox;
    }

    // Insere a nova música na posição correta
    novaMusica->prox = atual->prox;
    atual->prox = novaMusica;

    return raiz;
}


// Função para exibir todas as músicas de um álbum
void exibir_musicas(Musica *raiz) {
    printf("entrou aqui exibir_musicas\n");
    while (raiz != NULL) {
        // Exibir informações da música
        printf("\tMusica: %s\n", raiz->titulo);
        printf("\tDuracao (minutos): %d\n", raiz->duracao_minutos);

        // Avançar para a próxima música na lista
        raiz = raiz->prox;
    }
}

// Função para buscar uma música por título
Musica *achar_musica(Musica *raiz, const char *titulo) {
    while (raiz != NULL) {
        // Comparar o título da música atual com o título desejado
        if (strcmp(raiz->titulo, titulo) == 0) {
            // A música foi encontrada
            return raiz;
        }

        // Avançar para a próxima música na lista
        raiz = raiz->prox;
    }

    // A música não foi encontrada
    return NULL;
}