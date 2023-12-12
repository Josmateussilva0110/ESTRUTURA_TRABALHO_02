#include <stdio.h>
#include <stdlib.h>
#include "artista.c"


void menu()
{
    printf("\nDigite a opcao desejada:\n0 - Sair\n1 - Cadastrar Artista\n2 - Exibir Artista\n3 - Cadastrar Albuns\n4 - Cadastrar Musicas\n5 - Buscas\n6 - Excluir\n>>> ");
}

void limparBuffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    Artista *arvore = NULL;
    int op, numero_album;
    char nome[70], estilo[70];
    do
    {
        int flag;
        Info sobe;
        menu();
        scanf("%d",&op);
        limparBuffer(); 
        switch (op)
        {
            case 0:
                break;
            case 1:
                printf("Nome do artista: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Estilo musical: ");
                fgets(estilo, sizeof(estilo), stdin);
                estilo[strcspn(estilo, "\n")] = '\0';
                printf("Numero de albuns: ");
                scanf("%d", &numero_album);
                limparBuffer();
                inserir(&arvore, nome, estilo, numero_album, NULL, &sobe, &flag);
                if(flag == 1)
                    printf("insercao completa.\n");
                else
                    printf("erro ao inserir\n");
                break;
            case 2:
                imprimir(arvore);
                break;
            default:
                break;
        }
    } while (op != 0);
}