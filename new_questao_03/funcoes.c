#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>
#include<time.h>


typedef struct Bloco 
{
	int I_bloco,F_bloco; 
	char estado;         
}Bloco;


typedef struct Memoria
{
	Bloco info_1, info_2, info_3, info_4;
	struct Memoria *esq, *centro_esq, *centro, *centro_dir, *dir;
	int n_info;

}Memoria;



int folha(Memoria *no)
{ 
	int flag = 0;
	if (no != NULL)
    {
		if (no->esq == NULL && no->centro_esq == NULL && no->centro == NULL && no->centro_dir == NULL && no->dir == NULL)
			flag = 1;
	}
	return flag;
}

void criaNo(Memoria **no, Bloco info, Memoria *esq, Memoria *centro_esq, Memoria *centro, Memoria *centro_dir, Memoria *dir)
{
	*no = (Memoria *)malloc(sizeof(Memoria));

	(*no)->info_1 = info;
	(*no)->n_info = 1;
	(*no)->esq = esq;
	(*no)->centro_esq = centro_esq;
	(*no)->centro = centro;
	(*no)->centro_dir = centro_dir;
	(*no)->dir = dir;
}

void adicionaNo(Memoria **no, Bloco info, Memoria *filho)
{
    if((*no)->n_info == 1)
    {
        if (info.I_bloco > (*no)->info_1.F_bloco)
        { 
            (*no)->info_2 = info;
            (*no)->centro = filho;
        }
        else
        {
            (*no)->info_2 = (*no)->info_1;
            (*no)->info_1 = info;
            
            (*no)->centro = (*no)->centro_esq;
            (*no)->centro_esq = filho;
        }
        (*no)->n_info = 2;
    }
    else if((*no)->n_info == 2)
    {
        if(info.I_bloco > (*no)->info_2.F_bloco)
        {
            (*no)->info_3 = info;
            (*no)->centro_dir = filho;
        }
        else if(info.I_bloco > (*no)->info_1.F_bloco && info.F_bloco < (*no)->info_2.I_bloco)
        {
            (*no)->info_3 = (*no)->info_2; 
            (*no)->info_2 = info;
			
            (*no)->centro_dir = (*no)->centro;
            (*no)->centro = filho;
        } else{
			(*no)->info_3 = (*no)->info_2;
			(*no)->info_2 = (*no)->info_1;
			(*no)->info_1 = info;

			(*no)->centro_dir = (*no)->centro;
			(*no)->centro = (*no)->centro_esq;
			(*no)->centro_esq = filho;
		}
        (*no)->n_info = 3;
    }
    else 
    {
        if(info.I_bloco > (*no)->info_3.F_bloco)
        {
            (*no)->info_4 = info;
            (*no)->dir = filho;
        }
        else if(info.I_bloco > (*no)->info_2.F_bloco && info.F_bloco < (*no)->info_3.I_bloco)
        {
            (*no)->info_4 = (*no)->info_3; 
            (*no)->info_3 = info;

            (*no)->dir = (*no)->centro_dir;
            (*no)->centro_dir = filho;
        } else if(info.I_bloco > (*no)->info_1.F_bloco && info.F_bloco < (*no)->info_2.I_bloco){
			(*no)->info_4 = (*no)->info_3;
			(*no)->info_3 = (*no)->info_2;
			(*no)->info_1 = info;

			(*no)->dir = (*no)->centro_dir;
			(*no)->centro_dir = (*no)->centro;
			(*no)->centro = filho;
		} else{
			(*no)->info_4 = (*no)->info_3;
			(*no)->info_3 = (*no)->info_2;
			(*no)->info_2 = (*no)->info_1;
			(*no)->info_1 = info;

			(*no)->dir = (*no)->centro_dir;
			(*no)->centro_dir = (*no)->centro;
			(*no)->centro = (*no)->centro_esq;
			(*no)->centro_esq = filho;
		}
        (*no)->n_info = 4;
    }
}


void limpa_buffer(){ 
	int ch;
	while((ch = fgetc(stdin)) != EOF && ch != '\n' ){}

}

void quebraNo(Memoria **No, Bloco info, Bloco *sobe, Memoria **No_maior, Memoria *filho)
{
	printf("\t\tentrou no quebra\n");
    if (info.I_bloco < (*No)->info_1.I_bloco)
    {
		printf("\t\t\tif  quebra\n");
        *sobe = (*No)->info_1;
        criaNo(No_maior, (*No)->info_2, (*No)->centro_esq, (*No)->centro, (*No)->centro_dir, NULL, NULL);
        (*No)->info_1 = info;
        (*No)->centro = filho;
    }
    else if (info.I_bloco < (*No)->info_2.I_bloco)
    {
		printf("\t\t\telse if 1  quebra\n");
        *sobe = info;
        criaNo(No_maior, (*No)->info_2, filho, (*No)->centro_dir, NULL, NULL, NULL);
    }
    else if (info.I_bloco < (*No)->info_3.I_bloco)
    {
		printf("\t\t\telse if 2  quebra\n");
        *sobe = (*No)->info_2;
        criaNo(No_maior, info, filho, (*No)->centro_dir, NULL, NULL, NULL);
    }
    else
    {
		printf("\t\t\telse  quebra\n");
        *sobe = (*No)->info_3;
        criaNo(No_maior, (*No)->info_4, filho, NULL, NULL, NULL, NULL);
    }
	(*No)->esq = NULL;
	(*No)->centro_esq = NULL;
	(*No)->centro = NULL;
    (*No)->centro_dir = NULL;
	(*No)->dir = NULL;
    (*No)->n_info = 1;
}




Memoria *insere(Memoria **Pai,Memoria **Raiz ,Bloco info, Bloco *sobe)
{ 

	Memoria *No_maior;
	No_maior = NULL;

	if (*Raiz == NULL){
		criaNo(Raiz,info,NULL,NULL, NULL, NULL, NULL);

	}else{

		if (folha(*Raiz) == 1){
			
			if ((*Raiz)->n_info == 1){
				adicionaNo(Raiz,info,NULL);
			
			}else{

				quebraNo(Raiz,info,sobe,&No_maior,NULL);

				if (*Pai == NULL){
					Memoria *aux;
					criaNo(&aux,*sobe,*Raiz,No_maior, NULL, NULL, NULL);

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
			    No_maior= insere(Raiz,&(*Raiz)->centro,info,sobe);
		    }

			if (No_maior != NULL){

				if ((*Raiz)->n_info == 1){
					adicionaNo(Raiz,*sobe,No_maior);			
					No_maior = NULL;
					
				}else{

					Bloco sobe2;
					Memoria *No_maior2;

					quebraNo(Raiz,*sobe,&sobe2,&No_maior2,No_maior);

					if (*Pai == NULL){
						Memoria *aux;

						criaNo(&aux,sobe2,*Raiz,No_maior2, NULL, NULL, NULL);
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

void imprime_bloco_info(Bloco b)
{
	printf("Bloco: %d , %d - %c\n",b.I_bloco,b.F_bloco,b.estado);
}

void imprimir(Memoria *Raiz)
{
	if(Raiz != NULL)
    {
		imprimir(Raiz->esq);
		imprime_bloco_info(Raiz->info_1);
		imprimir(Raiz->centro_esq);
		imprimir(Raiz->centro);
		if(Raiz->n_info == 2)
			imprime_bloco_info(Raiz->info_2);
        if(Raiz->n_info == 3)
            imprime_bloco_info(Raiz->info_3);
        if(Raiz->n_info == 4)
            imprime_bloco_info(Raiz->info_4);
		imprimir(Raiz->centro_dir);
		imprimir(Raiz->dir);
	}
}




void insere_bloco_NaMemoria(Memoria **Raiz, int quant_blocos)
{

	Bloco info,sobe;
	Memoria *Pai;

	info.I_bloco = info.F_bloco = 0;

	limpa_buffer();
	printf("digite o estado do primeiro Bloco da memoria(l = livre ||  o = ocupado): ");
	scanf("%c",&info.estado);
	limpa_buffer();

	info.estado = tolower(info.estado);

	while(info.estado != 'o' && info.estado != 'l' ){
		printf("\ndigite um estado valido || (l = livre ||  o = ocupado)!!\n");
		printf("digite o estado do primeiro Bloco da memoria(l = livre ||  o = ocupado): ");
		scanf("%c",&info.estado);
		info.estado = tolower(info.estado);
		limpa_buffer();

	}

	while(info.F_bloco < quant_blocos-1){

		Pai = NULL;
		printf("Espaco disponivel : %d Mb",quant_blocos -info.I_bloco);
		printf("\ninicio do Bloco: %d\n",info.I_bloco);
		printf("digite o fim do Bloco: ");
		scanf("%d",&info.F_bloco);
		printf("\n");

		while(info.F_bloco >= quant_blocos || info.F_bloco < info.I_bloco )
        {
			
			printf("\nValor invalido\n");
			printf("digite um valor valido para o fim do Bloco(Espaco disponivel: %d Mb): ",quant_blocos -info.I_bloco);
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

