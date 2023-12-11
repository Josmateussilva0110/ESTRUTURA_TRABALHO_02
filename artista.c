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
    Album *albuns;
    struct Artista *esq, *dir;  // Ponteiros para a árvore vermelha-preta
    int cor;  // 0 para preto, 1 para vermelho
    struct Artista *pai;
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
    printf("Rotacao Esquerda: %s\n", (*raiz)->nome);
    Artista *aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = (*raiz);
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = 1;
    (*raiz) = aux;
    printf("Nova cor de %s: %s\n", (*raiz)->nome, (*raiz)->cor == 0 ? "preta" : "vermelha");
}

void rotacao_direita(Artista **raiz) 
{
    printf("Rotacao Direita: %s\n", (*raiz)->nome);
    Artista *aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = (*raiz);
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = 1;
    (*raiz) = aux;
}

void trocar_cor(Artista **raiz)
{
    printf("Trocar Cor: %s\n", (*raiz)->nome);
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
Artista *criar_artista(char *nome_artista, char *estilo_musical, int numero_albuns) 
{
    Artista *novo_artista;
    novo_artista = (Artista *)malloc(sizeof(Artista));
    strcpy(novo_artista->nome, nome_artista);
    strcpy(novo_artista->estilo_musical, estilo_musical);
    novo_artista->num_albuns = numero_albuns;
    novo_artista->albuns = NULL;
    novo_artista->esq = NULL;
    novo_artista->dir = NULL;
    novo_artista->pai = NULL;
    novo_artista->cor = 1;
    return novo_artista;
}


Artista *inserir_artista(Artista **raiz, Artista *pai, char *nome, char *estilo, int num_albuns) 
{
    Artista *artista_inserido = NULL;

    if (*raiz == NULL) 
    {
        artista_inserido = criar_artista(nome, estilo, num_albuns);
        *raiz = artista_inserido;
        
        if (pai == NULL)
            (*raiz)->cor = 0;
    }  
    else 
    {
        if (strcmp(nome, (*raiz)->nome) < 0)
            artista_inserido = inserir_artista(&((*raiz)->esq), *raiz, nome, estilo, num_albuns);
        else if (strcmp(nome, (*raiz)->nome) > 0)
            artista_inserido = inserir_artista(&((*raiz)->dir), *raiz, nome, estilo, num_albuns);
    }

    balancear(raiz);
    return artista_inserido;
}



// exibe em ordem 
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


// Função para encontrar um artista na árvore com base no nome
Artista *achar_artista(Artista *raiz, const char *nome_artista) {
    printf("entrou aqui achar_artista\n");
    Artista *encontrado;
    encontrado = NULL;

    if (raiz != NULL) {
        int comparacao = strcmp(nome_artista, raiz->nome);

        if (comparacao == 0) {
            encontrado = raiz;
        } else if (comparacao < 0) {
            encontrado = achar_artista(raiz->esq, nome_artista);
        } else {
            encontrado = achar_artista(raiz->dir, nome_artista);
        }
    }
    return encontrado;
}

// Cadastra um álbum na árvore de álbuns do artista
void cadastrar_albuns(Artista *albuns, const char *nome_artista, char *titulo, int ano_lancamento, int num_musicas) {
    Artista *aux = achar_artista(albuns, nome_artista);

    if (aux) {
        aux->albuns = inserir_album(&(aux->albuns), titulo, ano_lancamento, num_musicas);
        printf("Artista %s encontrado.\n", nome_artista);
    } else {
        printf("Artista %s não encontrado.\n", nome_artista);
    }
}

// Função para buscar um artista na árvore com base no nome e exibir suas informações
void buscar_artista_e_exibir(Artista *raiz, const char *nome_artista) {
    printf("Buscando artista...\n");
    Artista *encontrado = achar_artista(raiz, nome_artista);

    if (encontrado != NULL) {
        // Exibir informações do artista
        printf("Artista Encontrado:\n");
        printf("Nome: %s\n", encontrado->nome);
        printf("Estilo Musical: %s\n", encontrado->estilo_musical);
        printf("Numero de Albuns: %d\n", encontrado->num_albuns);
        printf("Cor: %d\n", encontrado->cor);

        // Exibir álbuns e músicas
        printf("\nalbuns e Musicas:\n");
        exibir_album_e_musicas(encontrado->albuns);
    } else {
        printf("Artista nao encontrado.\n");
    }
}


void buscar_artista_pelo_album_recursivo(Artista *raiz_artistas, const char *nome_album, Artista **encontrado) {
    if (raiz_artistas != NULL) {
        // Verificar se o álbum está na lista de álbuns do artista atual
        Album *album_atual = achar_album(raiz_artistas->albuns, nome_album);
        if (album_atual != NULL) {
            *encontrado = raiz_artistas;

            // Exibir informações do artista
            // printf("Artista Encontrado:\n");
            printf("Nome: %s\n", (*encontrado)->nome);
            printf("Estilo Musical: %s\n", (*encontrado)->estilo_musical);
            printf("Numero de Albuns: %d\n", (*encontrado)->num_albuns);
            printf("Cor: %d\n", (*encontrado)->cor);

            // Exibir informações do álbum
            printf("\nAlbum Encontrado aqui em:\n");
            printf("Nome do Album: %s\n", nome_album);
            printf("Ano de Lancamento: %d\n", album_atual->ano_lancamento);
            printf("Numero de Musicas: %d\n", album_atual->num_musicas);

            // Exibir músicas do álbum
            printf("\nMusicas do Album '%s':\n", nome_album);
            exibir_musicas(album_atual->musicas);
        }

        // Buscar na subárvore esquerda
        buscar_artista_pelo_album_recursivo(raiz_artistas->esq, nome_album, encontrado);

        // Buscar na subárvore direita
        buscar_artista_pelo_album_recursivo(raiz_artistas->dir, nome_album, encontrado);
    }
}

Artista *achar_artista_pelo_album(Artista *raiz_artistas, const char *nome_album) {
    Artista *artista_encontrado = NULL;  // Inicializa como NULL para indicar que não encontrou nenhum artista

    if (raiz_artistas != NULL) {
        // Buscar o álbum em cada artista da árvore
        buscar_artista_pelo_album_recursivo(raiz_artistas, nome_album, &artista_encontrado);
    }

    return artista_encontrado;
}

// Busca um álbum dado o nome de uma música
Album *achar_album_pela_musica_recursivo(Album *raiz_albuns, const char *nome_musica) {
    Album *album_encontrado = NULL;

    if (raiz_albuns != NULL) {
        // Procurar na lista de músicas do álbum atual
        Musica *musica_atual = achar_musica(raiz_albuns->musicas, nome_musica);
        if (musica_atual != NULL) {
            album_encontrado = raiz_albuns;
        } else {
            // Buscar na subárvore esquerda
            album_encontrado = achar_album_pela_musica_recursivo(raiz_albuns->esq, nome_musica);

            // Se não encontrado na subárvore esquerda, buscar na subárvore direita
            if (album_encontrado == NULL) {
                album_encontrado = achar_album_pela_musica_recursivo(raiz_albuns->dir, nome_musica);
            }
        }
    }

    return album_encontrado;
}


// Busca um artista dado o nome de uma música
Artista *achar_artista_pela_musica_recursivo(Artista *raiz_artistas, const char *nome_musica) {
    printf("entrou aqui achar_artista_pela_musica_recursivo\n");
    Artista *artista_encontrado = NULL;

    if (raiz_artistas != NULL) {
        Album *album_encontrado = achar_album_pela_musica_recursivo(raiz_artistas->albuns, nome_musica);

        if (album_encontrado != NULL) {
            artista_encontrado = raiz_artistas;
        } else {
            // Buscar na subárvore esquerda apenas se ainda não foi encontrado
            if (artista_encontrado == NULL) {
                artista_encontrado = achar_artista_pela_musica_recursivo(raiz_artistas->esq, nome_musica);
            }
            // Buscar na subárvore direita apenas se ainda não foi encontrado
            if (artista_encontrado == NULL) {
                artista_encontrado = achar_artista_pela_musica_recursivo(raiz_artistas->dir, nome_musica);
            }
        }
    }

    return artista_encontrado;
}

// Função para buscar e exibir informações de álbuns e artistas com base no nome de uma música
void buscar_albums_e_artistas_pela_musica(Artista *raiz_artistas, const char *nome_musica) {
    printf("Buscando album...\n");
    Album *album_encontrado = NULL;

    // Buscar um álbum dado o nome da música
    album_encontrado = achar_album_pela_musica_recursivo(raiz_artistas->albuns, nome_musica);

    if (album_encontrado != NULL) {
        // Buscar o artista associado ao álbum
        Artista *artista_encontrado = achar_artista_pela_musica_recursivo(raiz_artistas, nome_musica);

        if (artista_encontrado != NULL) {
            // Exibir informações do artista
            printf("Artista Encontrado:\n");
            printf("Nome: %s\n", artista_encontrado->nome);
            printf("Estilo Musical: %s\n", artista_encontrado->estilo_musical);
            printf("Numero de Albuns: %d\n", artista_encontrado->num_albuns);
            printf("Cor: %d\n", artista_encontrado->cor);

            // Exibir informações do álbum
            printf("\nAlbum Encontrado:\n");
            printf("Nome do Album: %s\n", album_encontrado->titulo);
            printf("Ano de Lancamento: %d\n", album_encontrado->ano_lancamento);
            printf("Numero de Musicas: %d\n", album_encontrado->num_musicas);

            // Exibir músicas do álbum
            printf("\nMusicas do Album '%s':\n", album_encontrado->titulo);
            exibir_musicas(album_encontrado->musicas);
        } else {
            printf("Artista nao encontrado para o album %s.\n", album_encontrado->titulo);
        }
    } else {
        printf("Album nao encontrado para a musica %s ou musica nao existente.\n", nome_musica);
    }
}

