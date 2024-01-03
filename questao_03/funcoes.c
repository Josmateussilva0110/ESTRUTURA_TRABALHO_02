#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>
#include<time.h>


typedef struct Bloco 
{
    int I_bloco,F_bloco; 
    char estado;         
}bloco;


typedef struct Memoria
{
    bloco info_1, info_2, info_3, info_4;
    struct Memoria *esq, *cen_esq, *centro, *cen_dir, *dir;
    int n_info;

}Memoria;

// função que cria um novo nó
Memoria *criaNo(bloco info, Memoria *esq, Memoria *cen_esq)
{
    Memoria *no;
    no = (Memoria *)malloc(sizeof(Memoria));
    no->info_1 = info;
    no->n_info = 1;
    no->esq = esq;
    no->cen_esq = cen_esq;
    no->centro = NULL;
    no->cen_dir = NULL;
    no->dir = NULL;
    return no;
}

// verifica se um nó é folha
int folha(Memoria *no)
{
    int flag = 0;
    if(no->esq == NULL && no->cen_esq == NULL && no->centro == NULL && no->cen_dir == NULL && no->dir == NULL)
        flag = 1;
    return flag;
}

// exibe informações de determinado nó
void imprime_bloco_info(bloco b)
{
	printf("bloco: %d , %d - %c\n",b.I_bloco,b.F_bloco,b.estado);
}

// função que adiciona a info em info1, info2, info3, info4
void adicionaNo(Memoria **No, bloco info, Memoria *filho)
{

    if((*No)->n_info == 1)
    {
        printf("\t\tadicionou na info 1\n");
        if(info.I_bloco > (*No)->info_1.I_bloco)
        {
            (*No)->info_2 = info;
            (*No)->centro = filho;

        }
        else
        {
            (*No)->info_2 = (*No)->info_1;
            (*No)->info_1 = info;

            (*No)->centro = (*No)->cen_esq;
            (*No)->cen_esq = filho;

        }
        (*No)->n_info = 2;

    }
    else if((*No)->n_info == 2)
    {
        if(info.I_bloco > (*No)->info_2.I_bloco)
        {
            (*No)->info_3 = info;
            (*No)->cen_dir = filho;

        }else if(info.I_bloco > (*No)->info_1.I_bloco && info.I_bloco < (*No)->info_2.I_bloco)
        {
            (*No)->info_3 = (*No)->info_2;
            (*No)->info_2 = info;

            (*No)->cen_dir = (*No)->centro;
            (*No)->centro = filho;

        }
        else
        {
            (*No)->info_3 = (*No)->info_2;
            (*No)->info_2 = (*No)->info_1;
            (*No)->info_1 = info;

            (*No)->cen_dir = (*No)->centro;
            (*No)->centro = (*No)->cen_esq;
            (*No)->cen_esq = filho;

        }
        (*No)->n_info = 3;

    }
    else
    {
        if(info.I_bloco > (*No)->info_3.I_bloco)
        {
            (*No)->info_4 = info;
            (*No)->dir = filho;

        }
        else if(info.I_bloco > (*No)->info_2.I_bloco && info.I_bloco < (*No)->info_3.I_bloco)
        {
            (*No)->info_4 = (*No)->info_3;
            (*No)->info_3 = info;

            (*No)->dir = (*No)->cen_dir;
            (*No)->cen_dir = filho;

        }
        else if (info.I_bloco > (*No)->info_1.I_bloco && info.I_bloco < (*No)->info_2.I_bloco)
        {
            (*No)->info_4 = (*No)->info_3;
            (*No)->info_3 = (*No)->info_2;
            (*No)->info_2 = info;

            (*No)->dir = (*No)->cen_dir;
            (*No)->cen_dir = (*No)->centro;
            (*No)->centro = filho;

        }
        else
        {
            (*No)->info_4 = (*No)->info_3;
            (*No)->info_3 = (*No)->info_2;
            (*No)->info_2 = (*No)->info_1;
            (*No)->info_1 = info;

            (*No)->dir = (*No)->cen_dir;
            (*No)->cen_dir = (*No)->centro;
            (*No)->centro = (*No)->cen_esq;
            (*No)->cen_esq = filho;
        }
        (*No)->n_info = 4;
        
    }
}


void limpa_buffer(){ 
    int ch;
    while((ch = fgetc(stdin)) != EOF && ch != '\n' ){}

}

// função destinada para quebrar o nó quando a arvore chega a 4 info
Memoria *quebraNo(Memoria **raiz, bloco info, bloco **sobe, Memoria *filho) 
{
    Memoria *maiorNo;

    if (info.I_bloco > (*raiz)->info_4.I_bloco) 
    {
        *sobe = &((*raiz)->info_3);

        maiorNo = criaNo((*raiz)->info_4, (*raiz)->cen_dir, (*raiz)->dir);
        
        maiorNo->info_2 = info;

        maiorNo->centro = filho;

        maiorNo->n_info = 2;
    } 
    else if (info.I_bloco > (*raiz)->info_3.I_bloco) 
    {
        *sobe = &((*raiz)->info_3);

        maiorNo = criaNo(info, (*raiz)->cen_dir, filho);
        
        maiorNo->info_2 = (*raiz)->info_4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->n_info = 2;
    } 
    else if (info.I_bloco > (*raiz)->info_2.I_bloco) 
    {
        *sobe = &((*raiz)->info_3);

        maiorNo = criaNo((*raiz)->info_4, (*raiz)->cen_dir, (*raiz)->dir);
        
        maiorNo->info_2 = info;

        maiorNo->centro = filho;

        maiorNo->n_info = 2;

        (*raiz)->info_3 = (*raiz)->info_2;
        (*raiz)->info_2 = info;

        (*raiz)->cen_dir = (*raiz)->centro;
        (*raiz)->centro = filho;
    } 
    else if (info.I_bloco > (*raiz)->info_1.I_bloco) 
    {
        *sobe = &((*raiz)->info_2);

        maiorNo = criaNo((*raiz)->info_3, (*raiz)->centro, (*raiz)->cen_dir);
        
        maiorNo->info_2 = (*raiz)->info_4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->n_info = 2;

        (*raiz)->info_2 = info;
        (*raiz)->centro = filho;
    } 
    else 
    {
        *sobe = &((*raiz)->info_2);

        maiorNo = criaNo((*raiz)->info_3, (*raiz)->centro, (*raiz)->cen_dir);
        
        maiorNo->info_2 = (*raiz)->info_4;

        maiorNo->centro = (*raiz)->dir;

        maiorNo->n_info = 2;

        (*raiz)->info_2 = (*raiz)->info_1;
        (*raiz)->centro = (*raiz)->cen_esq;
        
        (*raiz)->info_1 = info;
        (*raiz)->cen_esq = filho;
    }

    (*raiz)->n_info = 2;
    (*raiz)->cen_dir = NULL;
    (*raiz)->dir = NULL;

    return maiorNo;
}



// função que serve para fazer a inserção na arvore 
Memoria *inserir(Memoria **raiz, Memoria *pai, bloco **sobe, bloco info)
{
    Memoria *maiorNO;
    maiorNO = NULL;

    if(*raiz == NULL){
        *raiz = criaNo(info, NULL, NULL);
    }else{
        if(folha(*raiz)){
            if((*raiz)->n_info < 4){
                adicionaNo(raiz, info, NULL);
                maiorNO = NULL;
            }else{
                maiorNO = quebraNo(raiz, info, sobe, NULL);

                if(pai == NULL){
                    *raiz = criaNo(**sobe, *raiz, maiorNO);
                    maiorNO = NULL;
                }
            }
        }else{
            if(info.I_bloco < (*raiz)->info_1.I_bloco)
                maiorNO = inserir(&((*raiz)->esq), *raiz, sobe, info);

            else if((*raiz)->n_info == 1 || ((*raiz)->n_info <= 4 && info.I_bloco < (*raiz)->info_2.I_bloco))
                maiorNO = inserir(&((*raiz)->cen_esq), *raiz, sobe, info);

            else if(((*raiz)->n_info == 2)  || ((*raiz)->n_info <= 4 && info.I_bloco < (*raiz)->info_3.I_bloco))
                maiorNO = inserir(&((*raiz)->centro), *raiz,  sobe, info);

            else if(((*raiz)->n_info == 3) || ((*raiz)->n_info == 4 && info.I_bloco < (*raiz)->info_4.I_bloco))
                maiorNO = inserir(&((*raiz)->cen_dir), *raiz, sobe, info);

            else 
                maiorNO = inserir(&((*raiz)->dir), *raiz, sobe, info);

            if(maiorNO){
                if((*raiz)->n_info < 4){
                    adicionaNo(raiz, **sobe, maiorNO);
                    maiorNO = NULL;
                }else{
                    maiorNO = quebraNo(raiz, **sobe, sobe, maiorNO);

                    if(pai == NULL){
                        *raiz = criaNo(**sobe, *raiz, maiorNO);
                        maiorNO = NULL;
                    }
                }
            }
        }
    }
    return maiorNO;
}


// exibe as infos da arvore 
void imprimir(Memoria *Raiz)
{
    if (Raiz != NULL)
    {
        imprimir(Raiz->esq);

        if (Raiz->n_info >= 1)
            imprime_bloco_info(Raiz->info_1);

        imprimir(Raiz->cen_esq);

        if (Raiz->n_info >= 2)
            imprime_bloco_info(Raiz->info_2);

        imprimir(Raiz->centro);

        if (Raiz->n_info >= 3)
            imprime_bloco_info(Raiz->info_3);

        if (Raiz->n_info == 4)
            imprime_bloco_info(Raiz->info_4);

        imprimir(Raiz->cen_dir);
        imprimir(Raiz->dir);
    }
}



// função destinada a inserir os blocos na arvore
void insere_bloco(Memoria **Raiz, int quant_blocos)
{
    bloco info, *sobe;
    Memoria *Pai;

    info.I_bloco = info.F_bloco = 0;

    limpa_buffer();
    printf("estado do primeiro bloco da memoria\n(l = livre ||  o = ocupado): ");
    scanf("%c", &info.estado);
    limpa_buffer();

    info.estado = tolower(info.estado);

    while (info.F_bloco < quant_blocos-1) 
    {

        Pai = NULL;
        printf("Espaco disponivel : %d Mb", quant_blocos - info.I_bloco);
        printf("\ninicio do bloco: %d\n", info.I_bloco);
        printf("digite o fim do bloco: ");
        scanf("%d", &info.F_bloco);
        printf("\n");

        while (info.F_bloco >= quant_blocos || info.F_bloco < info.I_bloco) {
            printf("\nValor invalido\n");
            printf("digite um valor valido para o fim do bloco(Espaco disponivel: %d Mb): ", quant_blocos - info.I_bloco);
            scanf("%d", &info.F_bloco);
        }

        inserir(Raiz, Pai, &sobe, info);

        info.I_bloco = info.F_bloco+1;

        if (info.estado == 'l') {
            info.estado = 'o';
        } else {
            info.estado = 'l';
        }
    }
}


// busca espaço livre na arvore 
bloco *buscar_espaco_livre(Memoria *raiz, int tam) 
{
    bloco *aux = NULL;

    if (raiz != NULL) 
    {
        aux = buscar_espaco_livre(raiz->esq, tam);

        if (raiz->n_info >= 1 && raiz->info_1.estado == 'l' &&
        (raiz->info_1.F_bloco - raiz->info_1.I_bloco + 1) >= tam) 
            aux = &(raiz->info_1);

        if (aux == NULL) 
        {
            aux = buscar_espaco_livre(raiz->cen_esq, tam);
            if (raiz->info_2.estado == 'l' &&
            (raiz->info_2.F_bloco - raiz->info_2.I_bloco + 1) >= tam) {
                aux = &(raiz->info_2);
            }
        }

        if (aux == NULL) 
        {
            aux = buscar_espaco_livre(raiz->centro, tam);
            if (raiz->info_3.estado == 'l' &&
            (raiz->info_3.F_bloco - raiz->info_3.I_bloco + 1) >= tam) 
                aux = &(raiz->info_3);
        }

        if (aux == NULL && raiz->n_info == 4) 
        {
            aux = buscar_espaco_livre(raiz->cen_dir, tam);
            if (raiz->info_4.estado == 'l' &&
            (raiz->info_4.F_bloco - raiz->info_4.I_bloco + 1) >= tam)
                aux = &(raiz->info_4);
        }

        if (aux == NULL)
            aux = buscar_espaco_livre(raiz->dir, tam);
    }

    return aux;
}
