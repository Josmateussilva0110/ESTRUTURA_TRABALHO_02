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


// =================================
// ROTAÇÃO
// =================================
Album* rotacao_esquerda_album(Album* A)
{
    Album* B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = 1;
    return B;
}

Album* rotacao_direita_album(Album* A)
{
    Album* B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = 1;
    return B;
}


int cor(Album* H)
{
    int cor_resultado = 0;  // Variável local para armazenar o resultado

    if (H == NULL)
        cor_resultado = 0;
    else
        cor_resultado = H->cor;

    return cor_resultado;
}

void trocar_cor_album(struct Album* H){
    H->cor = !H->cor;
    if(H->esq != NULL)
        H->esq->cor = !H->esq->cor;
    if(H->dir != NULL)
        H->dir->cor = !H->dir->cor;
}

Album* move2EsqRED(Album* H){
    trocar_cor_album(H);
    if(cor(H->dir->esq) == 1){
        H->dir = rotacao_direita_album(H->dir);
        H = rotacao_esquerda_album(H);
        trocar_cor_album(H);
    }
    return H;
}

Album* move2DirRED(Album* H){
    trocar_cor_album(H);
    if(cor(H->esq->esq) == 1){
        H = rotacao_direita_album(H);
        trocar_cor_album(H);
    }
    return H;
}

Album* balancear_album(Album* H){
    //nó Vermelho é sempre filho à esquerda
    if(cor(H->dir) == 1)
        H = rotacao_esquerda_album(H);

    //Filho da esquerda e neto da esquerda são vermelhos
    if(H->esq != NULL && cor(H->esq) == 1 && cor(H->esq->esq) == 1)
        H = rotacao_direita_album(H);

    //2 filhos Vermelhos: troca cor!
    if(cor(H->esq) == 1 && cor(H->dir) == 1)
        trocar_cor_album(H);

    return H;
}


// Função para criar um Albumvo nó de álbum
Album *criar_album(char *titulo, int ano_lancamento, int num_musicas)
{
    Album *novo_album = (Album *)malloc(sizeof(Album));
    strcpy(novo_album->titulo, titulo);
    novo_album->ano_lancamento = ano_lancamento;
    novo_album->num_musicas = num_musicas;
    novo_album->esq = NULL;
    novo_album->dir = NULL;
    novo_album->musicas = NULL;
    novo_album->cor = 1;
    return novo_album;
}
Album* insereNo_Album(Album* H, char *titulo, int ano_lancamento, int num_musicas, int *resp) {
    Album *resultado;
    resultado = H;  // Variável local para armazenar o resultado

    if (H == NULL) {
        // Cria um novo nó de álbum usando a função criar_album
        Album *novo = criar_album(titulo, ano_lancamento, num_musicas);

        if (novo == NULL) {
            *resp = 0;
            resultado = NULL;
        } else {
            *resp = 1;
            resultado = novo;
        }
    } else {
        int comparacao = strcmp(titulo, H->titulo);

        if (comparacao == 0)
            *resp = 0; // Valor duplicado
        else {
            if (comparacao < 0)
                H->esq = insereNo_Album(H->esq, titulo, ano_lancamento, num_musicas, resp);
            else
                H->dir = insereNo_Album(H->dir, titulo, ano_lancamento, num_musicas, resp);
        }

        // Ajustes para manter a propriedade da árvore vermelha-preta
        // Aqui é o balanceamento
        if (cor(H->dir) == 1 && cor(H->esq) == 0)
            H = rotacao_esquerda_album(H);

        if (cor(H->esq) == 1 && cor(H->esq->esq) == 1)
            H = rotacao_direita_album(H);

        if (cor(H->esq) == 1 && cor(H->dir) == 1)
            trocar_cor_album(H);
    }

    return resultado;
}


int insere_Album(Album **raiz, char *titulo, int ano_lancamento, int num_musicas) {
    int resp;

    *raiz = insereNo_Album(*raiz, titulo, ano_lancamento, num_musicas, &resp);

    if (*raiz != NULL)
        (*raiz)->cor = 0;

    return resp;
}


Album *achar_album(Album *raiz, const char *nome_do_album) {
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
        printf("Cor: %d\n",raiz->cor);

        // Exibir músicas do álbum
        exibir_musicas(raiz->musicas);

        // Recursivamente exibir álbuns e músicas
        exibir_album_e_musicas(raiz->esq);
        exibir_album_e_musicas(raiz->dir);
    }
}

    Album *remover_musica_do_album(Album *raiz, const char *nome_musica) {
    Album *resultado = raiz;  // Variável local para armazenar o resultado

    if (raiz == NULL) {
        // printf("Álbum não encontrado.\n");
        resultado = NULL;
    } else {
        // Remover a música do álbum
        raiz->musicas = remover_musica(raiz->musicas, nome_musica);
        // printf("Música removida do álbum '%s'.\n", raiz->titulo);
    }

    return resultado;
}



////////////////REMOVER//////////////////////

int consulta_ArvLLRB_album(Album *raiz, const char *nome) {
    int encontrado = 0;  // Variável local para armazenar o resultado

    if (raiz != NULL) {
        int comparacao = strcmp(nome, raiz->titulo);

        if (comparacao == 0) {
            encontrado = 1; // Álbum encontrado
        } else if (comparacao < 0) {
            encontrado = consulta_ArvLLRB_album(raiz->esq, nome);
        } else {
            encontrado = consulta_ArvLLRB_album(raiz->dir, nome);
        }
    }

    return encontrado;
}



// tirei a recursão, assim fica igual a usada na AVL
Album* procuraMenorAlbum(Album* atual){
    Album *no1 = atual;
    Album *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

Album* removerMenorAlbum(Album* H) {
    Album* resultado;
    resultado = H;  // Variável local para armazenar o resultado

    if (H->esq == NULL) {
        free(H);
        resultado = NULL;
    } else {
        if (cor(H->esq) == 0 && cor(H->esq->esq) == 0)
            H = move2EsqRED(H);

        H->esq = removerMenorAlbum(H->esq);
        resultado = balancear_album(H);
    }

    return resultado;
}


Album* removeAlbum(Album** raiz, const char* nome) {
    Album* H = *raiz;

    if (H == NULL) {
        // Árvore vazia ou artista não encontrado
        return NULL;
    }

    if (strcmp(nome, H->titulo) < 0) {
        if (H->esq != NULL && cor(H->esq) == 0 && H->esq->esq != NULL && cor(H->esq->esq) == 0) {
            H = move2EsqRED(H);
        }

        H->esq = removeAlbum(&(H->esq), nome);
    } else if (strcmp(nome, H->titulo) > 0) {
        if (H->dir != NULL && cor(H->dir) == 0 && H->dir->esq != NULL && cor(H->dir->esq) == 0) {
            H = move2DirRED(H);
        }

        H->dir = removeAlbum(&(H->dir), nome);
    } else {
        // Nó encontrado para remoção
        if (H->dir == NULL) {
            // Se não houver filho à direita, armazene a referência à raiz para liberar a memória e retorne NULL
            Album* temp = H;
            H = NULL;
            free(temp);
        } else {
            // Substitui o nó com o menor valor à direita e remove esse nó menor
            Album* x = procuraMenorAlbum(H->dir);
            strcpy(H->titulo, x->titulo);
            H->dir = removerMenorAlbum(H->dir);
        }
    }

    // Após a remoção, é necessário reequilibrar e ajustar os ponteiros
    if (H != NULL) {
        if (cor(H->esq) == 1 && cor(H->dir) == 1) {
            trocar_cor_album(H);
        }

        if (cor(H->dir) == 1) {
            H = rotacao_esquerda_album(H);
        }

        if (cor(H->esq) == 1 && cor(H->esq->esq) == 1) {
            H = rotacao_direita_album(H);
        }
    }

    *raiz = H;
    return H;
}

int remove_ArvLLRB_album(Album** raiz, const char* nome) {
    int removido = 0;  // Variável local para armazenar o resultado

    if (consulta_ArvLLRB_album(*raiz, nome)) {
        removeAlbum(raiz, nome);

        if (*raiz != NULL) {
            (*raiz)->cor = 0; // Define a cor da raiz como preta após a remoção
        }

        removido = 1; // Artista removido com sucesso
    } else {
        removido = 0; // Artista não encontrado na árvore
    }

    return removido;
}
