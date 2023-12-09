#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "artista.c"

void menu()
{
    printf("\nDigite a opcao desejada:\n0 - Sair\n1 - Cadastrar Artista\n2 - Exibir Artista\n3 - Cadastrar Albuns\n>>> ");
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
    char nome[70], estilo[70], titulo[100];
    char nome_artista[70];  // Alterado para array de caracteres
    int ano_lancamento, num_musicas;

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
                printf("Nome do artista: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Estilo musical: ");
                fgets(estilo, sizeof(estilo), stdin);
                estilo[strcspn(estilo, "\n")] = '\0';
                printf("Numero de albuns: ");
                scanf("%d", &numero_album);
                limparBuffer();
                inserir_artista(&arvore, nome, estilo, numero_album);
                break;
            case 2:
                exibir_arvore(&arvore);
                break;
            case 3:
                printf("Nome do artista: ");
                fgets(nome_artista, sizeof(nome_artista), stdin);
                nome_artista[strcspn(nome_artista, "\n")] = '\0';
                printf("Titulo do album: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';
                printf("Ano de lancamento: ");
                scanf("%d", &ano_lancamento);
                printf("Numero de musicas: ");
                scanf("%d", &num_musicas);
                limparBuffer(); 
                cadastrar_albuns(arvore, nome_artista, titulo, ano_lancamento, num_musicas);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op != 0);
}
