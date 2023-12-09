#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "album.c"

typedef struct Artista 
{
    char nome[50];
    char estilo_musical[50];
    int num_albuns;
    Album *albuns;  // árvore vermelha-preta de álbuns
    struct Artista *esq, *dir;  // Ponteiros para a árvore vermelha-preta
    int cor;  // 0 para preto, 1 para vermelho
} Artista;


int eh_nulo_raiz(Artista **raiz)
{
    return (*raiz == NULL);
}

int eh_nulo_dir(Artista **raiz)
{
    return ((*raiz)->dir == NULL);
}

int eh_nulo_esq(Artista **raiz)
{
    return ((*raiz)->esq == NULL);
}


void rotacao_esquerda(Artista **raiz) 
{
    Artista *aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = (*raiz);
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = 1;
    (*raiz) = aux;
}

void rotacao_direita(Artista **raiz) 
{
    Artista *aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = (*raiz);
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = 1;
    (*raiz) = aux;
}

void trocar_cor(Artista **raiz)
{
    (*raiz)->cor = 1;
    (*raiz)->esq->cor = 0;
    (*raiz)->dir->cor = 0;
}

void balancear(Artista **raiz)
{
    if(!eh_nulo_dir(raiz) && (*raiz)->dir->cor == 1)
        rotacao_esquerda(raiz);
    if(!eh_nulo_esq(raiz) && (*raiz)->esq->cor == 1 && (*raiz)->esq->esq != NULL && (*raiz)->esq->esq->cor == 1)
        rotacao_direita(raiz);
    if(!eh_nulo_esq(raiz) && (*raiz)->esq->cor == 1 && !eh_nulo_dir(raiz) && (*raiz)->dir->cor == 1)
        trocar_cor(raiz);
}

// Função para criar um novo nó de artista
Artista *criar_artista(Artista **raiz, char *nome_artista, char *estilo_musical, int numero_albuns, int *valid) 
{
    if(eh_nulo_raiz(raiz))
    {
        Artista *novo_artista = (Artista *)malloc(sizeof(Artista));
        if(novo_artista != NULL)
        {
            strcpy(novo_artista->nome, nome_artista);
            strcpy(novo_artista->estilo_musical, estilo_musical);
            novo_artista->num_albuns = numero_albuns;
            novo_artista->albuns = NULL;
            novo_artista->esq = NULL;
            novo_artista->dir = NULL;
            novo_artista->cor = 1;
            *valid = 1;
        }
        else
            *valid = 0;
        return novo_artista;
    } 
    int comparacao = strcmp(nome_artista, (*raiz)->nome);
    if(comparacao == 0)
        *valid = 0;
    else if(comparacao < 0)
        (*raiz)->esq = criar_artista(&(*raiz)->esq, nome_artista, estilo_musical, numero_albuns, valid);
    else
       (*raiz)->dir = criar_artista(&(*raiz)->dir, nome_artista, estilo_musical, numero_albuns, valid); 
    balancear(raiz);
    return *raiz;
}


Artista *inserir(Artista **raiz, char *nome_artista, char *estilo_musical, int numero_albuns)
{
    int valid = 0;
    *raiz = criar_artista(raiz, nome_artista, estilo_musical, numero_albuns, &valid);
    if(*raiz != NULL)
        (*raiz)->cor = 0;
    return *raiz;
}




void exibir_arvore(Artista **raiz)
{
    if (!eh_nulo_raiz(raiz))
    {
        exibir_arvore(&(*raiz)->esq);
        printf("nome: %s\n", (*raiz)->nome);
        printf("estilo: %s\n", (*raiz)->estilo_musical);
        printf("numero albuns: %d\n", (*raiz)->num_albuns);
        printf("cor: %d\n", (*raiz)->cor);
        exibir_arvore(&(*raiz)->dir);
    }
}