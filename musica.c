#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura de uma Música
typedef struct {
    char titulo[50];
    int duracao_minutos;
} Musica;


// Função para criar um novo nó de música
Musica *criarMusica(char titulo[], int duracao_minutos) 
{
    Musica *nova_musica = (Musica *)malloc(sizeof(Musica));
    strcpy(nova_musica->titulo, titulo);
    nova_musica->duracao_minutos = duracao_minutos;
    return nova_musica;
}

