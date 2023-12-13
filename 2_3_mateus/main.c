#include <stdio.h>
#include <stdlib.h>
#include "artista_2_3.c"


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
    //Info *achado_artista = NULL;
    Artista *achou = NULL;
    Artista *no = NULL;
    int op, numero_album;
    char nome[70], estilo[70], nome_procurar[70];
    char titulo[70], artista[70];
    int ano_lancamento, num_musicas;
    do
    {
        int flag, achado, achado_2;
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
            
            case 3:
                printf("nome do artista que deseja procurar: ");
                fgets(nome_procurar, sizeof(nome_procurar), stdin);
                nome_procurar[strcspn(nome_procurar, "\n")] = '\0';
                no = achar_artista(arvore, nome_procurar, &achado);
                if(no)
                {
                    printf("posicao: %d\n",achado);
                    printf("nome info 1: %s\n",no->info_1->nome);
                    printf("nome info 2: %s\n",no->info_2->nome);
                    printf("titulo: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = '\0';
                    printf("ano lancamento: ");
                    scanf("%d",&ano_lancamento);
                    printf("Numero de albuns: ");
                    scanf("%d", &num_musicas);
                    cadastrar_albuns(no, titulo, ano_lancamento, num_musicas, achado);
                    printf("insercao completa.\n");
                }
                else
                    printf("nao achei\n");
                break;
            
            case 4:
                printf("artista: ");
                scanf("%s", artista);
                achou = achar_artista(arvore, artista, &achado_2);
                if(achou)
                    mostrar_album(achou, achado_2);
                else
                    printf("artista nao encontrado\n");
                break;
            default:
                break;
        }
    } while (op != 0);
}