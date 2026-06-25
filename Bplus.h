#ifndef BPLUS_H
#define BPLUS_H

//Biblioteca

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ORDEM 4 // ordem maxima das paginas.
#define TAM_MAXCHAVE 100 // tamanho maximo da chave(nome e data).

typedef struct NoBplus{


    // Usado por todos os Nos.

    int folha; // Responsavel por garantir se o no que estamos analisando é no interno ou folha(0 folha e 1 interno).
    int qtdChave; // Informa a quantidade de cadastros que possuem o No.
    // long pai; // Informa o endereço do arquivo onde esta o pai desse No.

    // Usado Apenas pelo no Interno;

    char chave[ORDEM-1][TAM_MAXCHAVE]; // responsavel por armazenar todos os funcionarios que possuem na pagina analisada.
    
    long filhos[ORDEM]; // Guarda o endereço dos nos filhos de seu respectivo no interno.

    // Usado Apenas pelo no Folha;w

    long registro[ORDEM - 1]; // Guarda o endereço da informação de funcionario.

    long proxFolha; // Guarda o endereço do proxima "pagina" folha.

}NoBplus;

#endif
