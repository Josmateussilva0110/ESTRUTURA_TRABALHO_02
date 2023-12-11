#include <stdio.h>
#include <stdlib.h>
#include "funcoes.c"

int main()
{
    Arv_2_3 *arvore = NULL;
    int op;
    do
    {
        int sobe, valor, flag;
        printf("0- sair\n1- inserir\n2 - exibir\n>>> ");
        scanf("%d",&op);
        switch (op)
        {
            case 0:
                break;
            case 1:
                printf("valor: ");
                scanf("%d",&valor);
                inserir(&arvore, valor, NULL, &sobe, &flag);
                if(flag == 1)
                    printf("insercao completa.\n");
                else
                    printf("erro ao inserir\n");
                break;
            case 2:
                imprimir(arvore);
            default:
                break;
        }
    } while (op != 0);
}