#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>
#include<time.h>
#include "funcoes.c"


int main()
{
    Memoria *Raiz = NULL;
	
	//int op,n,flag,quant_blocos;
    int quant_blocos;
	//double tempo_busca_total, tempo_insere_total;

	printf("\ntamanho total da memoria em Mb: ");
	scanf("%d",&quant_blocos);

	while(quant_blocos <= 0)
    {
		printf("\nNao existe memoria com tamanho igual ou menor que 0!!\n");
		printf("\ndigite o tamanho total da memoria em Mb acima de 0: ");
		scanf("%d",&quant_blocos);
	}
	insere_bloco_NaMemoria(&Raiz,quant_blocos);
    imprimir(Raiz);
}