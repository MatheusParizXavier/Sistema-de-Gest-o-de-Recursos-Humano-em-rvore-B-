#include "Bplus.h"


// Escreve um novo no em uma posição especifica do disco.
void escreve_no(FILE *arq, long endereço, NoBplus *no){
    if(endereço == -1) return;
    fseek(arq, endereço, SEEK_SET);
    fwrite(no, sizeof(NoBplus), 1, arq);
}

// tem a tarefa de ler um no de uma posicao especifica do disco para a memoria RAM.
void ler_no(FILE *arq, long endereço, NoBplus *no){
    if(endereço == -1) return;
    fseek(arq, endereço, SEEK_SET);
    fread(no, sizeof(NoBplus), 1, arq);
}

long aloca_novoNo(FILE *arq){
    fseek(arq, 0, SEEK_END);
    long novo = ftell(arq);

    NoBplus novoNo;
    novoNo.folha = 1;
    novoNo.qtdChave = 0;
    novoNo.proxFolha = -1;
    for(int i = 0; i < ORDEM; i++){
        novoNo.filhos[i] = -1;
        if( i < ORDEM -1) novoNo.registro[i] = -1;
    }

    escreve_no(arq, novo, &novoNo);
    return novo;
}