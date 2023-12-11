#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "artista.c"

void menu()
{
    printf("\nDigite a opcao desejada:\n0 - Sair\n1 - Cadastrar Artista\n2 - Exibir Artista\n3 - Cadastrar Albuns\n4 - Cadastrar Musicas\n5 - Buscas\n>>> ");
}

void menu_busca()
{
    printf("\nEscolha o tipo de busca:\n1 - Buscar Artista\n2 - Buscar Album\n3 - Buscar Musica\n0 - Voltar\n>>> ");
}

void limparBuffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    Artista *arvore = NULL;
    Artista *aux;
    Album *encontrada = NULL;
    int op, numero_album;
    char nome[70], estilo[70], titulo[100];
    char nome_artista[70], nome_musica[50], nome_artista1[70], nome_album[70], nome_musica1[50];
;  // Alterado para array de caracteres
    int ano_lancamento, num_musicas, duracao_minutos;

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
                inserir_artista(&arvore, NULL, nome, estilo, numero_album);
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
            case 4:
                printf("Nome do artista para buscar: ");
                fgets(nome_artista, sizeof(nome_artista), stdin);
                nome_artista[strcspn(nome_artista, "\n")] = '\0';
                aux = achar_artista(arvore,nome_artista);
                if (aux) 
                {
                    printf("Titulo do album: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = '\0';
                    encontrada = achar_album(aux->albuns, titulo);
                    if (encontrada) 
                    {
                        printf("Nome da musica: ");
                        fgets(nome_musica, sizeof(nome_musica), stdin);
                        nome_musica[strcspn(nome_musica, "\n")] = '\0';

                        printf("Duracao da musica: ");
                        scanf("%d", &duracao_minutos);
                        limparBuffer();

                        cadastrar_musicas(encontrada, titulo, nome_musica, duracao_minutos);
                        printf("Musica cadastrada com sucesso.\n");
                    }

                }
                
                break;
            case 5:
                    menu_busca();
                    int op_busca;
                    scanf("%d", &op_busca);
                    limparBuffer();

                    switch (op_busca)
                    {
                        case 1:
                            printf("Nome do artista para buscar: ");
                            fgets(nome_artista1, sizeof(nome_artista1), stdin);
                            nome_artista1[strcspn(nome_artista1, "\n")] = '\0';
                            buscar_artista_e_exibir(arvore, nome_artista1);
                            break;
                        case 2:
                            printf("Nome do album para buscar o artista: ");
                            fgets(nome_album, sizeof(nome_album), stdin);
                            nome_album[strcspn(nome_album, "\n")] = '\0';

                            achar_artista_pelo_album(arvore, nome_album);

                            break;
                        case 3:
                            printf("Nome da musica para buscar: ");
                            fgets(nome_musica1, sizeof(nome_musica1), stdin);
                            nome_musica1[strcspn(nome_musica1, "\n")] = '\0';
                            buscar_albums_e_artistas_pela_musica(arvore, nome_musica1);

                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                    }
                    break;
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op != 0);
}
