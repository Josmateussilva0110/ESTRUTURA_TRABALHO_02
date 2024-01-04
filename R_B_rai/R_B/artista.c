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
} Artista;


Artista* rotacao_esquerda(Artista* A)
{
    Artista* B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = 1;
    return B;
}

Artista* rotacao_direita(Artista* A){
    Artista* B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = 1;
    return B;
}
// =================================
// PROPRIEDADES
// =================================

void trocar_cor(Artista* H){
    H->cor = !H->cor;
    if(H->esq != NULL)
        H->esq->cor = !H->esq->cor;
    if(H->dir != NULL)
        H->dir->cor = !H->dir->cor;
}


int cor_artista(Artista* H) {
    int cor_resultado = 0;  // Variável local para armazenar o resultado

    if (H == NULL)
        cor_resultado = 0;
    else
        cor_resultado = H->cor;

    return cor_resultado;  
}

Artista* move2EsqRED_artista(Artista* H){
    trocar_cor(H);
    if(cor_artista(H->dir->esq) == 1){
        H->dir = rotacao_direita(H->dir);
        H = rotacao_esquerda(H);
        trocar_cor(H);
    }
    return H;
}
Artista* move2DirRED_artista(Artista* H){
    trocar_cor(H);
    if(cor_artista(H->esq->esq) == 1){
        H = rotacao_direita(H);
        trocar_cor(H);
    }
    return H;
}

Artista* balancear(Artista* H){
    //nó Vermelho é sempre filho à esquerda
    if(cor_artista(H->dir) == 1)
        H = rotacao_esquerda(H);

    //Filho da esquerda e neto da esquerda são vermelhos
    if(H->esq != NULL && cor_artista(H->esq) == 1 && cor_artista(H->esq->esq) == 1)
        H = rotacao_esquerda(H);

    //2 filhos Vermelhos: troca cor_artista!
    if(cor_artista(H->esq) == 1 && cor_artista(H->dir) == 1)
        trocar_cor(H);

    return H;
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
    novo_artista->cor = 1;
    return novo_artista;
}

Artista* insereNO(Artista* H, char *nome_artista, char *estilo_musical, int numero_albuns, int *resp) {
    Artista *resultado = H;  // Variável local para armazenar o resultado

    if (H == NULL) {
        // Cria um novo nó de artista usando a função criar_artista
        Artista *novo = criar_artista(nome_artista, estilo_musical, numero_albuns);
        
        if (novo == NULL) {
            *resp = 0;
            resultado = NULL;
        } else {
            *resp = 1;
            resultado = novo;
        }
    } else {
        int comparacao = strcmp(nome_artista, H->nome);

        if (comparacao == 0)
            *resp = 0; // Valor duplicado
        else {
            if (comparacao < 0)
                H->esq = insereNO(H->esq, nome_artista, estilo_musical, numero_albuns, resp);
            else
                H->dir = insereNO(H->dir, nome_artista, estilo_musical, numero_albuns, resp);
        }

        // Ajustes para manter a propriedade da árvore vermelha-preta
        // Aqui é o balanceamento
        if (cor_artista(H->dir) == 1 && cor_artista(H->esq) == 0)
            H = rotacao_esquerda(H);

        if (cor_artista(H->esq) == 1 && cor_artista(H->esq->esq) == 1)
            H = rotacao_direita(H);

        if (cor_artista(H->esq) == 1 && cor_artista(H->dir) == 1)
            trocar_cor(H);
    }

    return resultado;
}


int insere_Artista(Artista **raiz, char *nome_artista, char *estilo_musical, int numero_albuns) {
    int resp;

    *raiz = insereNO(*raiz, nome_artista, estilo_musical, numero_albuns, &resp);

    if (*raiz != NULL)
        (*raiz)->cor = 0;

    return resp;
}



// exibe em ordem 
void exibir_arvore(Artista *raiz) {
    if (raiz != NULL) {
        exibir_arvore(raiz->esq);
        printf("Nome: %s\n", raiz->nome);
        printf("Estilo: %s\n", raiz->estilo_musical);
        printf("Numero de Albuns: %d\n", raiz->num_albuns);
        printf("Cor: %d\n", raiz->cor);
        printf("\n");
        exibir_arvore(raiz->dir);
    }
}



// Função para encontrar um artista na árvore com base no nome
Artista *achar_artista(Artista *raiz, const char *nome_artista) {
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
void cadastrar_albuns(Artista *raiz_artistas, const char *nome_artista, char *titulo, int ano_lancamento, int num_musicas) {
    Artista *artista = achar_artista(raiz_artistas, nome_artista);

    if (artista != NULL) {
        // Inserir álbum na árvore de álbuns do artista
        insere_Album(&(artista->albuns), titulo, ano_lancamento, num_musicas);
    } else {
        printf("Artista '%s' nao encontrado.\n", nome_artista);
    }
}



// Função para buscar um artista na árvore com base no nome e exibir suas informações
void buscar_artista_e_exibir(Artista *raiz, const char *nome_artista) {
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
            printf("Cor: %d\n",album_atual->cor);

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

Album *achar_album_pela_musica(Album *raiz, const char *nome_musica) {
    Album *album_encontrado;
    album_encontrado = NULL;

    if (raiz != NULL) {
        Musica *musica_atual = raiz->musicas;

        while (musica_atual != NULL) {
            if (strcmp(musica_atual->titulo, nome_musica) == 0) {
                // A música foi encontrada neste álbum
                album_encontrado = raiz;
                break;
            }

            musica_atual = musica_atual->prox;
        }

        // Buscar na subárvore esquerda
        if (album_encontrado == NULL) {
            Album *album_na_esquerda;
            album_na_esquerda = achar_album_pela_musica(raiz->esq, nome_musica);
            if (album_na_esquerda != NULL) {
                album_encontrado = album_na_esquerda;
            }
        }

        // Buscar na subárvore direita
        if (album_encontrado == NULL) {
            Album *album_na_direita;
            album_na_direita = achar_album_pela_musica(raiz->dir, nome_musica);
            if (album_na_direita != NULL) {
                album_encontrado = album_na_direita;
            }
        }
    }

    return album_encontrado;
}


// Função para exibir informações sobre um álbum contendo uma música específica
void exibir_album_com_musica_recursivo(Album *raiz, const char *nome_musica) {
    if (raiz != NULL) {
        // Verificar se a música está na lista de álbuns do artista atual
        Musica *musica_atual = achar_musica(raiz->musicas, nome_musica);
        if (musica_atual != NULL) {
            // Exibir informações do álbum e da música
            printf("Álbum: %s\n", raiz->titulo);
            printf("Musica: %s\n", musica_atual->titulo);
            // printf("Duracao (minutos): %d\n", musica_atual->duracao_minutos);
        }

        // Buscar na subárvore esquerda
        exibir_album_com_musica_recursivo(raiz->esq, nome_musica);

        // Buscar na subárvore direita
        exibir_album_com_musica_recursivo(raiz->dir, nome_musica);
    }
}

// Função para encontrar artistas e álbuns que contenham uma música específica
void encontrar_artistas_e_albuns_pela_musica_recursivo(Artista **raiz_artistas, const char *nome_musica) {
    if (*raiz_artistas != NULL) {
        // Verificar se a música está na lista de álbuns do artista atual
        Album *album_atual = achar_album_pela_musica((*raiz_artistas)->albuns, nome_musica);
        if (album_atual != NULL) {
            // Exibir informações do artista e álbum
            printf("\nArtista: %s\n", (*raiz_artistas)->nome);
            // Exibir músicas do álbum
            exibir_album_com_musica_recursivo(album_atual, nome_musica);
        }

        // Buscar na subárvore esquerda
        encontrar_artistas_e_albuns_pela_musica_recursivo(&((*raiz_artistas)->esq), nome_musica);

        // Buscar na subárvore direita
        encontrar_artistas_e_albuns_pela_musica_recursivo(&((*raiz_artistas)->dir), nome_musica);
    }
}

// Função principal para encontrar artistas e álbuns que contenham uma música específica
void encontrar_artistas_e_albuns_pela_musica(Artista *raiz_artistas, const char *nome_musica) {
    if (raiz_artistas == NULL) {
        printf("Nenhum artista na árvore.\n");
    }

    // Percorrer a árvore de artistas para encontrar os artistas e álbuns
    encontrar_artistas_e_albuns_pela_musica_recursivo(&raiz_artistas, nome_musica);
}


void remover_musica_do_album_artista(Artista *raiz_artistas, const char *nome_artista, const char *nome_album, const char *nome_musica) {
    Artista *artista = achar_artista(raiz_artistas, nome_artista);

    if (artista != NULL) {
        Album *album = achar_album(artista->albuns, nome_album);

        if (album != NULL) {
            // Remover a música do álbum do artista
            album = remover_musica_do_album(album, nome_musica);
        } else {
            printf("Album '%s' nao encontrado para o artista '%s'.\n", nome_album, nome_artista);
        }
    } else {
        printf("Artista '%s' nao encontrado.\n", nome_artista);
    }
}

///////////////////////////////////REMOVER ALBUM//////////////////////////////////////////////////

// Função para remover um álbum pelo nome do artista e título do álbum
Artista *remover_album_por_nome_artista_titulo(Artista *raiz_artistas, const char *nome_artista, const char *titulo_album) {
    Artista *artista = achar_artista(raiz_artistas, nome_artista);

    if (artista != NULL) {
        // Buscar o álbum pelo título
        Album *album = achar_album(artista->albuns, titulo_album);

        if (album != NULL) {
            // Remover o álbum da árvore de álbuns do artista
            remove_ArvLLRB_album(&(artista->albuns), titulo_album);
            printf("Album '%s' removido do artista '%s'.\n", titulo_album, nome_artista);

        } else {
            printf("Album '%s' nao encontrado para o artista '%s'.\n", titulo_album, nome_artista);
        }
    } else {
        printf("Artista '%s' nao encontrado.\n", nome_artista);
    }

    return raiz_artistas;
}

//////////////////////////////Remover Artista///////////////////////////

int consulta_ArvLLRB(Artista *raiz, const char *nome) {
    int encontrado = 0; // Variável local para armazenar o resultado

    if (raiz != NULL) {
        int comparacao = strcmp(nome, raiz->nome);

        if (comparacao == 0) {
            encontrado = 1; // Artista encontrado
        } else if (comparacao < 0) {
            encontrado = consulta_ArvLLRB(raiz->esq, nome);
        } else {
            encontrado = consulta_ArvLLRB(raiz->dir, nome);
        }
    }

    return encontrado;
}



Artista* procuraMenorArtista(Artista* atual)
{
    Artista* no1 = atual;
    Artista* no2 = atual->esq;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

Artista* removerMenorArtista(Artista* H)
{
    Artista* resultado;
    resultado = H;  // Cria uma variável local para armazenar o resultado

    if (H != NULL) {
        if (H->esq == NULL) {
            // Se não houver filho à esquerda, libere a memória e atualize a variável local
            free(H);
            resultado = NULL;
        } else {
            // Se o filho à esquerda e o neto à esquerda são pretos, faz a rotação à esquerda
            if (cor_artista(H->esq) == 0 && H->esq->esq != NULL && cor_artista(H->esq->esq) == 0) {
                H = move2DirRED_artista(H);
            }

            H->esq = removerMenorArtista(H->esq);
            resultado = balancear(H);  // Atualiza a variável com o resultado final
        }
    }

    return resultado;
}

Artista* removeArtista(Artista** raiz, const char* nome)
{
    Artista* H = *raiz;

    if (H == NULL) {
        // Árvore vazia ou artista não encontrado
        return NULL;
    }

    if (strcmp(nome, H->nome) < 0) {
        if (H->esq != NULL && cor_artista(H->esq) == 0 && H->esq->esq != NULL && cor_artista(H->esq->esq) == 0) {
            H = move2EsqRED_artista(H);
        }

        H->esq = removeArtista(&(H->esq), nome);
    } else if (strcmp(nome, H->nome) > 0) {
        if (H->dir != NULL && cor_artista(H->dir) == 0 && H->dir->esq != NULL && cor_artista(H->dir->esq) == 0) {
            H = move2DirRED_artista(H);
        }

        H->dir = removeArtista(&(H->dir), nome);
    } else {
        // Nó encontrado para remoção
        if (H->dir == NULL) {
            // Se não houver filho à direita, armazene a referência à raiz para liberar a memória e retorne NULL
            Artista* temp = H;
            H = NULL;
            free(temp);
        } else {
            // Substitui o nó com o menor valor à direita e remove esse nó menor
            Artista* x = procuraMenorArtista(H->dir);
            strcpy(H->nome, x->nome);
            H->dir = removerMenorArtista(H->dir);
        }
    }

    // Após a remoção, é necessário reequilibrar e ajustar os ponteiros
    if (H != NULL) {
        if (cor_artista(H->esq) == 1 && cor_artista(H->dir) == 1) {
            trocar_cor(H);
        }

        if (cor_artista(H->dir) == 1) {
            H = rotacao_esquerda(H);
        }

        if (cor_artista(H->esq) == 1 && cor_artista(H->esq->esq) == 1) {
            H = rotacao_direita(H);
        }
    }

    *raiz = H;
    return H;
}

int remove_ArvLLRB(Artista** raiz, const char* nome)
{
    int remove = 0;
    if (consulta_ArvLLRB(*raiz, nome)) {
        removeArtista(raiz, nome);

        if (*raiz != NULL) {
            (*raiz)->cor = 0; // Define a cor da raiz como preta após a remoção
        }

        remove = 1; // Artista removido com sucesso
    } else {
        remove = 0; // Artista não encontrado na árvore
    }
    return remove;
}

