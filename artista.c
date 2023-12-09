#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "album.c"

typedef struct Artista {
    char nome[50];
    char estilo_musical[50];
    int num_albuns;
    Album *albuns;  // Raiz da árvore vermelha-preta de álbuns
    struct Album *esq_art, *dir_art;  // Ponteiros para a árvore vermelha-preta
    int cor_art;  // 0 para preto, 1 para vermelho
} Artista;


// Função para criar um novo nó de artista
Artista *criarArtista(char nome[], char estilo_musical[]) 
{
    Artista *novo_artista = (Artista *)malloc(sizeof(Artista));
    strcpy(novo_artista->nome, nome);
    strcpy(novo_artista->estilo_musical, estilo_musical);
    novo_artista->num_albuns = 0;
    novo_artista->albuns = NULL;
    novo_artista->esq_art = novo_artista->dir_art = NULL;
    novo_artista->cor_art = 1;  // Novo nó é vermelho por padrão
    return novo_artista;
}


// Função para inserir um álbum para um artista
void inserirAlbumParaArtista(Artista *artista, char titulo[], int ano_lancamento, int num_musicas) 
{
    Album *novo_album = criarAlbum(titulo, ano_lancamento, num_musicas);
    artista->albuns = inserirAlbum(artista->albuns, novo_album);
    artista->num_albuns++;
}


// Função para inserir um nó na árvore vermelha-preta de artistas
Artista *inserirArtista(Artista *raiz, Artista *novo_artista) 
{
    // Implementação da inserção em árvore vermelha-preta
    // ...

    // Retornar a nova raiz após a inserção
    return raiz;
}
