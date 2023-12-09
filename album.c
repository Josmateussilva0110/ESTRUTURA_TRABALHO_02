#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "musica.c"

typedef struct Album {
    char titulo[50];
    int ano_lancamento;
    int num_musicas;
    Musica *musicas;  // Lista de músicas
    struct Album *esq, *dir;  // Ponteiros para a árvore vermelha-preta
    int cor;  // 0 para preto, 1 para vermelho
} Album;


// Função para criar um novo nó de álbum
Album *criarAlbum(char titulo[], int ano_lancamento, int num_musicas) {
    Album *novo_album = (Album *)malloc(sizeof(Album));
    strcpy(novo_album->titulo, titulo);
    novo_album->ano_lancamento = ano_lancamento;
    novo_album->num_musicas = num_musicas;
    novo_album->musicas = NULL;
    novo_album->esq = novo_album->dir = NULL;
    novo_album->cor = 1;  // Novo nó é vermelho por padrão
    return novo_album;
}


// Função para inserir um nó na árvore vermelha-preta
Album *inserirAlbum(Album *raiz, Album *novo_album) 
{
    // Implementação da inserção em árvore vermelha-preta
    // ...

    // Retornar a nova raiz após a inserção
    return raiz;
}