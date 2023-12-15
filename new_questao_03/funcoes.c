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
	struct Memoria *esq,*cen,*dir;
	int n_info;

}Memoria;



int folha(Memoria *no)
{ 
	int flag = 0;
	if (no != NULL)
    {
		if (no->esq == NULL && no->cen == NULL && no->dir == NULL)
			flag = 1;
	}
	return flag;
}

void criaNo(Memoria **no, bloco info, Memoria *esq, Memoria *cen, Memoria *dir)
{

	*no = (Memoria *)malloc(sizeof(Memoria));

	(*no)->info_1 = info;
	(*no)->n_info = 1;
	(*no)->esq = esq;
	(*no)->cen = cen;
	(*no)->dir = dir;
}

void adicionaNo(Memoria **no, bloco info, Memoria *filho)
{
    if((*no)->n_info == 1)
    {
        if (info.I_bloco > (*no)->info_1.I_bloco )
        { 
            (*no)->info_2 = info;
            (*no)->dir = filho;
        }
        else
        {

            (*no)->info_2 = (*no)->info_1;
            (*no)->info_1 = info;
            (*no)->dir = (*no)->cen;
            (*no)->cen = filho;
        }

        (*no)->n_info = 2;
    }
    else if((*no)->n_info == 2)
    {
        if(info.I_bloco > (*no)->info_2.I_bloco)
        {
            (*no)->info_3 = info;
            (*no)->dir = filho;
        }
        else
        {
            (*no)->info_3 = (*no)->info_2; 
            (*no)->info_2 = info;
            (*no)->dir = (*no)->cen;
            (*no)->cen = filho;
        }
        (*no)->n_info = 3;
    }
    else if((*no)->n_info == 3)
    {
        if(info.I_bloco > (*no)->info_3.I_bloco)
        {
            (*no)->info_4 = info;
            (*no)->dir = filho;
        }
        else
        {
            (*no)->info_4 = (*no)->info_3; 
            (*no)->info_3 = info;
            (*no)->dir = (*no)->cen;
            (*no)->cen = filho;
        }
        (*no)->n_info = 4;
    }
}

void limpa_buffer(){ 
	int ch;
	while((ch = fgetc(stdin)) != EOF && ch != '\n' ){}

}

void quebraNo(Memoria **No, bloco info, bloco *sobe, Memoria **No_maior,  Memoria *filho)
{
    if (info.I_bloco < (*No)->info_1.I_bloco )
    { 
        *sobe = (*No)->info_1;
        criaNo(No_maior, (*No)->info_2, (*No)->cen, (*No)->dir, NULL);
        (*No)->info_1 = info;
        (*No)->cen = filho;
    }
    else if (info.I_bloco < (*No)->info_2.I_bloco )
    { 
        *sobe = info;
        criaNo(No_maior, (*No)->info_2, filho, (*No)->dir, NULL);
    }
    else if (info.I_bloco < (*No)->info_3.I_bloco )
    { 
        *sobe = (*No)->info_2;
        criaNo(No_maior, info, filho, (*No)->dir, NULL);
    }
    else
    {
        *sobe = (*No)->info_3;
        criaNo(No_maior, (*No)->info_4, filho, NULL, NULL);
    }

    (*No)->dir = NULL;
    (*No)->n_info = 1;
}

Memoria *insere(Memoria **Pai,Memoria **Raiz ,bloco info, bloco *sobe)
{ 

	Memoria *No_maior;
	No_maior = NULL;

	if (*Raiz == NULL){
		criaNo(Raiz,info,NULL,NULL, NULL);

	}else{

		if (folha(*Raiz) == 1){
			
			if ((*Raiz)->n_info == 1){
				adicionaNo(Raiz,info,NULL);
			
			}else{

				quebraNo(Raiz,info,sobe,&No_maior,NULL);

				if (*Pai == NULL){
					Memoria *aux;
					criaNo(&aux,*sobe,*Raiz,No_maior, NULL);

					*Raiz = aux;

					No_maior = NULL;
				}
			}
		
		}else {

			if (info.I_bloco < (*Raiz)->info_1.I_bloco ){
			    No_maior= insere(Raiz,&(*Raiz)->esq,info,sobe);
			
		    }else if ((*Raiz)->n_info == 2 && info.I_bloco > (*Raiz)->info_2.I_bloco){
			    No_maior= insere(Raiz,&(*Raiz)->dir,info,sobe);
		   	
		   	}else{
			    No_maior= insere(Raiz,&(*Raiz)->cen,info,sobe);
		    }

			if (No_maior != NULL){

				if ((*Raiz)->n_info == 1){
					adicionaNo(Raiz,*sobe,No_maior);			
					No_maior = NULL;
					
				}else{

					bloco sobe2;
					Memoria *No_maior2;

					quebraNo(Raiz,*sobe,&sobe2,&No_maior2,No_maior);

					if (*Pai == NULL){
						Memoria *aux;

						criaNo(&aux,sobe2,*Raiz,No_maior2, NULL);
						*Raiz = aux;
						No_maior = NULL;
					
					}else{
						*sobe = sobe2;
						No_maior= No_maior2;
					}
				}
			}
		}
	}

	return No_maior;
}

void imprime_bloco_info(bloco b)
{
	printf("bloco: %d , %d - %c\n",b.I_bloco,b.F_bloco,b.estado);
}

void imprimir(Memoria *Raiz)
{
	if(Raiz != NULL)
    {
		imprimir(Raiz->esq);
		imprime_bloco_info(Raiz->info_1);
		imprimir(Raiz->cen);
        
		if(Raiz->n_info == 2)
			imprime_bloco_info(Raiz->info_2);
        if(Raiz->n_info == 3)
            imprime_bloco_info(Raiz->info_3);
        if(Raiz->n_info == 4)
            imprime_bloco_info(Raiz->info_4);
		imprimir(Raiz->dir);
	}
}

void insere_bloco_NaMemoria(Memoria **Raiz, int quant_blocos)
{

	bloco info,sobe;
	Memoria *Pai;

	info.I_bloco = info.F_bloco = 0;

	limpa_buffer();
	printf("digite o estado do primeiro bloco da memoria(l = livre ||  o = ocupado): ");
	scanf("%c",&info.estado);
	limpa_buffer();

	info.estado = tolower(info.estado);

	while(info.estado != 'o' && info.estado != 'l' ){
		printf("\ndigite um estado valido || (l = livre ||  o = ocupado)!!\n");
		printf("digite o estado do primeiro bloco da memoria(l = livre ||  o = ocupado): ");
		scanf("%c",&info.estado);
		info.estado = tolower(info.estado);
		limpa_buffer();

	}

	while(info.F_bloco < quant_blocos-1){

		Pai = NULL;
		printf("Espaco disponivel : %d Mb",quant_blocos -info.I_bloco);
		printf("\ninicio do bloco: %d\n",info.I_bloco);
		printf("digite o fim do bloco: ");
		scanf("%d",&info.F_bloco);
		printf("\n");

		while(info.F_bloco >= quant_blocos || info.F_bloco < info.I_bloco )
        {
			
			printf("\nValor invalido\n");
			printf("digite um valor valido para o fim do bloco(Espaco disponivel: %d Mb): ",quant_blocos -info.I_bloco);
			scanf("%d",&info.F_bloco);
		}

		insere(&Pai,Raiz,info,&sobe);

		info.I_bloco = info.F_bloco +1;

		if (info.estado == 'l')
			info.estado = 'o';
		else 
			info.estado = 'l';

	}
}