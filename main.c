#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "artista.c"

void menu()
{
    printf("\nDigite a opcao desejada:\n0 - Sair\n1 - Cadastrar_artista\n2 - exibir_artista\n>>> ");
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
        menu();
        scanf("%d", &op);
        limparBuffer(); 
        switch (op)
        {
            case 0:
                break;
            case 1:
                printf("nome do artista: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("estilo musical: ");
                fgets(estilo, sizeof(estilo), stdin);
                estilo[strcspn(estilo, "\n")] = '\0';
                printf("numero de albuns: ");
                scanf("%d", &numero_album);
                inserir(&(arvore), nome, estilo, numero_album);
                break;
            
            case 2:
                exibir_arvore(&arvore);
                break;
        }
    } while (op != 0);
}
