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
Musica *criarMusica(char titulo[], int duracao_minutos) 
{
    Musica *nova_musica = (Musica *)malloc(sizeof(Musica));
    strcpy(nova_musica->titulo, titulo);
    nova_musica->duracao_minutos = duracao_minutos;
    nova_musica->prox = NULL;
    return nova_musica;
}

Musica *inserirMusica(Musica *cabeca, Musica *novaMusica) 
{
    // Caso a lista esteja vazia ou a nova música deva ser inserida no início
    if (cabeca == NULL || strcmp(novaMusica->titulo, cabeca->titulo) < 0) {
        novaMusica->prox = cabeca;
        return novaMusica;
    }

    // Procura a posição correta para inserir a música mantendo a lista ordenada
    Musica *atual = cabeca;
    while (atual->prox != NULL && strcmp(novaMusica->titulo, atual->prox->titulo) > 0) {
        atual = atual->prox;
    }

    // Insere a nova música na posição correta
    novaMusica->prox = atual->prox;
    atual->prox = novaMusica;

    return cabeca;
}

// Função para exibir a lista de músicas
void exibirListaDeMusicas(Musica *cabeca) 
{
    Musica *atual = cabeca;
    while (atual != NULL) {
        printf("Título: %s, Duração: %d minutos\n", atual->titulo, atual->duracao_minutos);
        atual = atual->prox;
    }
}

// Função para liberar a memória alocada para a lista de músicas
void liberarListaDeMusicas(Musica *cabeca) 
{
    while (cabeca != NULL) {
        Musica *temp = cabeca;
        cabeca = cabeca->prox;
        free(temp);
    }
}