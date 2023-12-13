#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "musicas_2_3.c"

typedef struct Info_album
{
    char titulo[50];
    int ano_lancamento;
    int num_musicas;
}Info_album;

typedef struct Album {
    Info_album *info_1, *info_2;
    //Musica *musicas;
    struct Album *esq, *dir, *centro;
    int num_info;
} Album;


Album *criaNo_album(char *titulo, int ano_lancamento, int num_musicas, Album *noEsq, Album *noCentro) 
{
    Album *no = (Album*)malloc(sizeof(Album)); 
    no->info_1 = (Info_album*)malloc(sizeof(Info_album));
    strcpy(no->info_1->titulo, titulo);
    no->info_1->ano_lancamento = ano_lancamento;
    no->info_1->num_musicas = num_musicas;
    no->num_info = 1;
    no->esq = noEsq;
    no->centro = noCentro;
    no->dir = NULL;
    //no->musicas = NULL;
    return no;
}


void adicionaNo_album(Album **raiz, char *titulo, int ano_lancamento, int num_musicas, Album *filho) 
{
    (*raiz)->info_2 = (Info_album*)malloc(sizeof(Info_album));
    if(strcmp(titulo, (*raiz)->info_1->titulo) > 0)
    {
        strcpy((*raiz)->info_2->titulo, titulo);
        (*raiz)->info_2->ano_lancamento = ano_lancamento;
        (*raiz)->info_2->num_musicas = num_musicas;
        (*raiz)->dir = filho;
    }
    else
    {
        strcpy((*raiz)->info_2->titulo, (*raiz)->info_1->titulo);
        (*raiz)->info_2->ano_lancamento = (*raiz)->info_1->ano_lancamento;
        (*raiz)->info_2->num_musicas = (*raiz)->info_1->num_musicas;

        strcpy((*raiz)->info_1->titulo, titulo);
        (*raiz)->info_1->ano_lancamento = ano_lancamento;
        (*raiz)->info_1->num_musicas = num_musicas;

        (*raiz)->dir = (*raiz)->centro;
        (*raiz)->centro = filho;
    }
    (*raiz)->num_info = 2;
}


Album *quebraNo_album(Album **raiz, Album *filho, char *titulo, int ano_lancamento, int num_musicas, Info_album *sobe) 
{
    Album *maiorNo;
    maiorNo = NULL;

    if (strcmp(titulo, (*raiz)->info_2->titulo) > 0) 
    {
        strcpy(sobe->titulo, (*raiz)->info_2->titulo);
        sobe->ano_lancamento = (*raiz)->info_2->ano_lancamento;
        sobe->num_musicas = (*raiz)->info_2->num_musicas;

        maiorNo = criaNo_album(titulo, ano_lancamento, num_musicas, (*raiz)->dir, filho);
    } 
    
    else if (strcmp(titulo, (*raiz)->info_1->titulo) < 0) 
    {
        strcpy(sobe->titulo, (*raiz)->info_1->titulo);
        sobe->ano_lancamento = (*raiz)->info_1->ano_lancamento;
        sobe->num_musicas = (*raiz)->info_1->num_musicas;

        maiorNo = criaNo_album((*raiz)->info_2->titulo, (*raiz)->info_2->ano_lancamento, (*raiz)->info_2->num_musicas, (*raiz)->centro, (*raiz)->dir);
        
        strcpy((*raiz)->info_1->titulo, titulo);
        (*raiz)->info_1->ano_lancamento = ano_lancamento;
        (*raiz)->info_1->num_musicas = num_musicas;
        (*raiz)->centro = filho;
    }

    else 
    {
        strcpy(sobe->titulo, titulo);
        sobe->ano_lancamento = ano_lancamento;
        sobe->num_musicas = num_musicas;
        maiorNo = criaNo_album((*raiz)->info_2->titulo,(*raiz)->info_2->ano_lancamento, (*raiz)->info_2->num_musicas, filho, (*raiz)->dir);  
    }

    (*raiz)->num_info = 1;
    (*raiz)->info_2 = NULL;
    (*raiz)->dir = NULL; 
    return maiorNo;
}

int folha_album(Album *raiz)
{
    int valid = 0;
    if(raiz->esq == NULL)
        valid = 1;
    return valid;
}

Album *inserir_album(Album **raiz, char *titulo, int ano_lancamento, int num_musicas, Album *pai, Info_album *infoSobe)
{
    printf("entrou em inserir album\n");
    Album *maiorNo;
    if (*raiz == NULL)
        *raiz = criaNo_album(titulo, ano_lancamento, num_musicas, NULL, NULL);
    else
    {
        if (folha_album(*raiz))
        {
            if ((*raiz)->num_info == 1)
            {
                adicionaNo_album(raiz, titulo, ano_lancamento, num_musicas, NULL);
                maiorNo = NULL;
            }
            else
            {
                maiorNo = quebraNo_album(raiz, NULL, titulo, ano_lancamento, num_musicas, infoSobe);

                if (pai == NULL)
                {
                    *raiz = criaNo_album(infoSobe->titulo, infoSobe->ano_lancamento, infoSobe->num_musicas, *raiz, maiorNo);
                    maiorNo = NULL;
                }
            }
        }
        else
        {
            if (strcmp(titulo, (*raiz)->info_1->titulo) < 0)   
                maiorNo = inserir_album(&((*raiz)->esq), titulo, ano_lancamento, num_musicas, *raiz, infoSobe);
            else if (((*raiz)->num_info == 1) || (((*raiz)->num_info == 2) && strcmp(titulo, (*raiz)->info_2->titulo) < 0))
                maiorNo = inserir_album(&((*raiz)->centro), titulo, ano_lancamento, num_musicas, *raiz, infoSobe);
            else
                maiorNo = inserir_album(&((*raiz)->dir), titulo, ano_lancamento, num_musicas, *raiz, infoSobe);   

            if (maiorNo != NULL)
            {
                if ((*raiz)->num_info == 1)
                {
                    adicionaNo_album(raiz, infoSobe->titulo, infoSobe->ano_lancamento, infoSobe->num_musicas, maiorNo);
                    maiorNo = NULL;
                }
                else
                {
                    maiorNo = quebraNo_album(raiz, maiorNo, infoSobe->titulo, infoSobe->ano_lancamento, infoSobe->num_musicas, infoSobe);
                    if (pai == NULL)
                    {
                        *raiz = criaNo_album(infoSobe->titulo, infoSobe->ano_lancamento, infoSobe->num_musicas, *raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }
    return maiorNo;
}

void imprimir_album(Album *raiz)
{
    if(raiz != NULL)
    {
        imprimir_album(raiz->esq);
        printf("Info 1 titulo: %s\n", raiz->info_1->titulo);
        printf("Info 1 ano lancamento: %d\n", raiz->info_1->ano_lancamento);
        printf("Info 1 numero musicas: %d\n", raiz->info_1->num_musicas);
        printf("\n");
        imprimir_album(raiz->centro);
        if(raiz->num_info == 2)
        {
            printf("Info 2 titulo: %s\n", raiz->info_2->titulo);
            printf("Info 2 ano lancamento: %d\n", raiz->info_2->ano_lancamento);
            printf("Info 2 numero musicas: %d\n", raiz->info_2->num_musicas);
        }
        imprimir_album(raiz->dir);
    }
}

Album *achar_album(Album *raiz, const char *palavra)
{
    Album *encontrada = NULL;

    if(raiz != NULL)
    {
        if(strcmp(palavra, raiz->info_1->titulo) == 0)
            encontrada = raiz;

        if(raiz->num_info == 2 && strcmp(palavra, raiz->info_2->titulo) == 0)
            encontrada = raiz;

        if(encontrada == NULL)
        {
            if(strcmp(palavra, raiz->info_1->titulo) < 0)
                encontrada = achar_album(raiz->esq, palavra);
            else if((raiz->num_info == 1 || (raiz->num_info == 2 && strcmp(palavra, raiz->info_2->titulo) < 0)))
                encontrada = achar_album(raiz->centro, palavra);
            else
                encontrada = achar_album(raiz->dir, palavra);
        }
    }
    return encontrada;
}