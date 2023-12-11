#include <stdio.h>
#include <stdlib.h>


typedef struct Arv_2_3
{
    int info1, info2;
    int numInfo;
    struct Arv_2_3 *esq, *centro, *dir;
}Arv_2_3;


Arv_2_3 *criaNo(int valor, Arv_2_3 *noEsq, Arv_2_3 *noCentro) 
{
    Arv_2_3 *no = (Arv_2_3*) malloc(sizeof(Arv_2_3)); 

    no->info1 = valor; 
    no->numInfo = 1;
    no->esq = noEsq;
    no->centro = noCentro;
    no->dir = NULL;
    return no;
}

void adicionaNo(Arv_2_3 **raiz, int valor, Arv_2_3 *filho) 
{

    if(valor > (*raiz)->info1)
    {
        (*raiz)->info2 = valor;
        (*raiz)->dir = filho;
    }
    else
    {
        (*raiz)->info2 = (*raiz)->info1;
        (*raiz)->info1 = valor; 

        (*raiz)->dir = (*raiz)->centro;
        (*raiz)->centro = filho;
    }
    (*raiz)->numInfo = 2;
}

Arv_2_3 *quebraNo(Arv_2_3 **raiz, Arv_2_3 *filho, int valor, int *sobe) 
{
    Arv_2_3 *maiorNo;
    maiorNo = NULL;

    if (valor > (*raiz)->info2) 
    {
        *sobe = (*raiz)->info2;
        maiorNo = criaNo(valor, (*raiz)->dir, filho);
    } 
    
    else if (valor < (*raiz)->info1) 
    {
        *sobe = (*raiz)->info1;
        maiorNo = criaNo((*raiz)->info2, (*raiz)->centro, (*raiz)->dir);
        
        (*raiz)->info1 = valor;
        (*raiz)->centro = filho;
    }

    else 
    {
        *sobe = valor;
        maiorNo = criaNo((*raiz)->info2, filho, (*raiz)->dir);  
    }

    (*raiz)->numInfo = 1;
    (*raiz)->info2 = 0;
    (*raiz)->dir = NULL; 

    return maiorNo;
}

int folha(Arv_2_3 *raiz)
{
    int valid = 0;
    if(raiz->esq == NULL)
        valid = 1;
    return valid;
}

Arv_2_3 *inserir(Arv_2_3 **raiz, int valor, Arv_2_3 *pai, int *infoSobe, int *flag)
{
    Arv_2_3 *maiorNo;
    if (*raiz == NULL)
    {
        *raiz = criaNo(valor, NULL, NULL);
        *flag = 1;
    }
    else
    {
        if (folha(*raiz))
        {
            if ((*raiz)->numInfo == 1)
            {
                adicionaNo(raiz, valor, NULL);
                maiorNo = NULL;
                *flag = 1;
            }
            else
            {
                maiorNo = quebraNo(raiz, NULL, valor, infoSobe);

                if (pai == NULL)
                {
                    *raiz = criaNo(*infoSobe, *raiz, maiorNo);
                    maiorNo = NULL;
                }
                *flag = 1;
            }
        }
        else
        {
            if (valor < (*raiz)->info1)   
                maiorNo = inserir(&((*raiz)->esq), valor, *raiz, infoSobe, flag);
            else if (((*raiz)->numInfo == 1) || (((*raiz)->numInfo == 2) && valor < (*raiz)->info2))
                maiorNo = inserir(&((*raiz)->centro), valor, *raiz, infoSobe, flag);
            else
                maiorNo = inserir(&((*raiz)->dir), valor, *raiz, infoSobe, flag);   

            if (maiorNo != NULL)
            {
                if ((*raiz)->numInfo == 1)
                {
                    adicionaNo(raiz, *infoSobe, maiorNo);
                    maiorNo = NULL;
                }
                else
                {
                    maiorNo = quebraNo(raiz, maiorNo, *infoSobe, infoSobe);
                    if (pai == NULL)
                    {
                        *raiz = criaNo(*infoSobe, *raiz, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }
    return maiorNo;
}


void imprimir(Arv_2_3 *raiz)
{
    if(raiz != NULL)
    {
        imprimir(raiz->esq);
        printf("Info 1: %d\n", raiz->info1);
        
        imprimir(raiz->centro);
        if(raiz->numInfo == 2)
        {
            printf("Info 2: %d\n", raiz->info2);
        }
        imprimir(raiz->dir);
    }
}