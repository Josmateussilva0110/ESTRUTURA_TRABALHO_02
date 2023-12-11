#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "musica.c"

typedef struct Album {
    char titulo[100];
    int ano_lancamento;
    int num_musicas;
    Musica *musicas;
    struct Album *esq, *dir;  // Ponteiros para a árvore vermelha-preta
    int cor;
} Album;


int eh_nulo_raiz_album(Album **raiz)
{
    return (*raiz == NULL);
}

int eh_nulo_dir_album(Album **raiz)
{
    return ((*raiz)->dir == NULL);
}

int eh_nulo_esq_album(Album **raiz)
{
    return ((*raiz)->esq == NULL);
}


void rotacao_esquerda_album(Album **raiz) 
{
    Album *aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = (*raiz);
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = 1;
    (*raiz) = aux;
}

void rotacao_direita_album(Album **raiz) 
{
    Album *aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = (*raiz);
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = 1;
    (*raiz) = aux;
}

void trocar_cor_album(Album **raiz)
{
    (*raiz)->cor = 1;
    (*raiz)->esq->cor = 0;
    (*raiz)->dir->cor = 0;
}

void balancear_album(Album **raiz)
{
    if(!eh_nulo_dir_album(raiz) && (*raiz)->dir->cor == 1)
        rotacao_esquerda_album(raiz);
    if(!eh_nulo_esq_album(raiz) && (*raiz)->esq->cor == 1 && (*raiz)->esq->esq != NULL && (*raiz)->esq->esq->cor == 1)
        rotacao_direita_album(raiz);
    if(!eh_nulo_esq_album(raiz) && (*raiz)->esq->cor == 1 && !eh_nulo_dir_album(raiz) && (*raiz)->dir->cor == 1)
        trocar_cor_album(raiz);
}

// Função para criar um novo nó de álbum
Album *criar_album(char *titulo, int ano_lancamento, int num_musicas)
{
    Album *novo_album = (Album *)malloc(sizeof(Album));
    if (novo_album != NULL) {
        strcpy(novo_album->titulo, titulo);
        novo_album->ano_lancamento = ano_lancamento;
        novo_album->num_musicas = num_musicas;
        novo_album->esq = novo_album->dir = NULL;
        novo_album->musicas = NULL;
        novo_album->cor = 1;  // Supondo que 1 representa a cor vermelha na árvore
    }
    return novo_album;
}

// Função para inserir um álbum em uma árvore vermelha e preta
Album *inserir_album(Album **raiz, char *titulo, int ano_lancamento, int num_musicas) {
    Album *resultado = NULL;

    // Caso base: árvore vazia ou chegou a uma folha
    if (*raiz == NULL) {
        resultado = criar_album(titulo, ano_lancamento, num_musicas);
        *raiz = resultado;  // Atualiza a raiz com o novo nó criado
    } else {
        // Inserção recursiva
        if (strcmp(titulo, (*raiz)->titulo) < 0) {
            (*raiz)->esq = inserir_album(&((*raiz)->esq), titulo, ano_lancamento, num_musicas);
        } else if (strcmp(titulo, (*raiz)->titulo) > 0) {
            (*raiz)->dir = inserir_album(&((*raiz)->dir), titulo, ano_lancamento, num_musicas);
        }

        // Aplicar as regras da árvore vermelha e preta
        balancear_album(raiz);
        resultado = *raiz;  // Atualiza a variável resultado com a raiz atualizada
    }

    // Retornar a variável resultado no final
    return resultado;
}

Album *achar_album(Album *raiz, const char *nome_do_album) {
    printf("Entrou aqui achar_album\n");
    Album *encontrado;
    encontrado = NULL;

    if (raiz != NULL) {
        int comparacao = strcmp(nome_do_album, raiz->titulo);

        if (comparacao == 0) {
            encontrado = raiz;
        } else if (comparacao < 0) {
            encontrado = achar_album(raiz->esq, nome_do_album);
        } else {
            encontrado = achar_album(raiz->dir, nome_do_album);
        }
    }
    return encontrado;
}

// Função para cadastrar músicas em um álbum
void cadastrar_musicas(Album *raiz_albuns, char *nome_do_album, char *nome_musica, int duracao_minutos) {
    printf("Entrou aqui cadastrar_musicas\n");
    Album *album_encontrado = achar_album(raiz_albuns, nome_do_album);

    if (album_encontrado) {
        album_encontrado->musicas = inserirMusica(album_encontrado->musicas, nome_musica, duracao_minutos);
    } else {
        printf("Álbum %s não encontrado.\n", nome_do_album);
    }
}

// Função para exibir as informações de um álbum e suas músicas
void exibir_album_e_musicas(Album *raiz) {
    if (raiz != NULL) {
        // Exibir informações do álbum
        printf("Album: %s\n", raiz->titulo);
        printf("Ano de Lancamento: %d\n", raiz->ano_lancamento);
        printf("Numero de Musicas: %d\n", raiz->num_musicas);

        // Exibir músicas do álbum
        exibir_musicas(raiz->musicas);

        // Recursivamente exibir álbuns e músicas
        exibir_album_e_musicas(raiz->esq);
        exibir_album_e_musicas(raiz->dir);
    }
}

void liberar_albuns(Album *raiz) {
    if (raiz != NULL) {
        // Liberar músicas do álbum
        liberar_musicas(raiz->musicas);

        // Liberar álbuns da subárvore esquerda
        liberar_albuns(raiz->esq);

        // Liberar álbuns da subárvore direita
        liberar_albuns(raiz->dir);

        // Liberar o próprio álbum
        free(raiz);
    }
}
