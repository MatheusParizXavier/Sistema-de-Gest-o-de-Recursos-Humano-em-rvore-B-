#ifndef BPLUS_H
#define BPLUS_H

//Biblioteca

//Apagar depois
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ORDEM 4 // ordem maxima das paginas.
#define TAM_MAXCHAVE 256 // tamanho maximo da chave(nome e data).

//Função resposanvel por comparar um byte generico, ou seja, responsavel por comparar duas chaves
// Return 1 se a > b, -1 se a < b e 0 se a == b; 
typedef int (*FuncaoCompara)(const void *chaveA, const void *chaveB);

//Função responsavel por dar imprimir o dado generico na tela, usando callback
typedef void (*FuncaoImpressao)(const void *chave);

typedef struct NoBPlus{


    // Usado por todos os Nos.

    int folha; // Responsavel por garantir se o no que estamos analisando é no interno ou folha(0 folha e 1 interno).
    int qtdChave; // Informa a quantidade de cadastros que possuem o No.
    // long pai; // Informa o endereço do arquivo onde esta o pai desse No.

    // Usado Apenas pelo no Interno;

    unsigned char chaves[ORDEM-1][TAM_MAXCHAVE]; // responsavel por armazenar todos os funcionarios que possuem na pagina analisada.
    
    long filhos[ORDEM]; // Guarda o endereço dos nos filhos de seu respectivo no interno.

    // Usado Apenas pelo no Folha;w

    long registro[ORDEM - 1]; // Guarda o endereço da informação de funcionario.

    long proxFolha; // Guarda o endereço do proxima "pagina" folha.

}NoBPlus;

typedef struct ArvoreBPlus{

    FILE *arquivo_indice; // Ponteiro do arquivo binario da arvore no disco.
    long raiz; // Guarda a posição onde esta a raiz da arvore no disco.
    size_t tamanho_chave; // Guarda o tamanho em bytes do tipo de dado usado como a chave;
    size_t tamanho_registro;
    // Ponteiros para as funções que mexem com os dados genericos.
    FuncaoCompara comparar;
    FuncaoImpressao imprime;
}ArvoreBPlus;

//Inicializa a árvore, abre o arquivo em disco e configura as funções genéricas.
ArvoreBPlus *criar_arvore(const char *caminho_arquivo, size_t tamanho_chave, FuncaoCompara comp, FuncaoImpressao impr);

// Insere uma chave e o registra o ponteiro do mesmo na arvore em disco.
void inserir(ArvoreBPlus *arvore, const void *chave, long registro);

// Busca o registro que desejamos e retorna o endereço do registro na árvore em disco.
long buscar(ArvoreBPlus *arvore, const void *chave);

// Imprime a estrutura no terminal, usando callback de impressao.
void imprimirEstrutura(ArvoreBPlus *arvore);

// fechar a arvore de forma correta.
void fechaArvore(ArvoreBPlus *arvore);

#endif
