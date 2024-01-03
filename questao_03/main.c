#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>
#include<time.h>
#include "funcoes.c"


void menu()
{
	printf("0 - sair\n1- inserir bloco\n2- mostrar\n3- alocar espaco\n>>> ");
}

int main()
{
    Memoria *arvore = NULL;
	
    int quant_blocos, tam_espaco, op;
	do
	{
		menu();
		scanf("%d",&op);
		switch (op)
		{
			case 0:
				break;
			
			case 1:
				printf("\ntamanho total da memoria em Mb: ");
				scanf("%d",&quant_blocos);

				while(quant_blocos <= 0)
				{
					printf("\nNao existe memoria com tamanho igual ou menor que 0!!\n");
					printf("\ndigite o tamanho total da memoria em Mb acima de 0: ");
					scanf("%d",&quant_blocos);
				}
				insere_bloco(&arvore,quant_blocos);
				break;
			
			case 2:
				imprimir(arvore);
				break;
			
			case 3:
				printf("digite o tamanho do espaco que deseja alocar: ");
				scanf("%d",&tam_espaco);
				bloco *alocado = buscar_espaco_livre(arvore, tam_espaco);
				if(alocado)
				{
					printf("bloco achado:\n");
					imprime_bloco_info((*alocado));
				}
				else
					printf("nenhum espaco encontrado\n");
				break;
			default:
				break;
		}
		
	} while (op != 0);
	
}
