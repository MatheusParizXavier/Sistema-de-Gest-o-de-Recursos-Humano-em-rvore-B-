#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rh.h"    // Nossas structs do Passo 2
#include "Bplus.h" // A API da Árvore B+ Genérica

// Callback de Comparação para a Árvore B+
// Retorna: < 0 se a < b | 0 se a == b | > 0 se a > b
int compara_chave(const void *chaveA, const void *chaveB) {
    ChaveBusca *cA = (ChaveBusca *)chaveA;
    ChaveBusca *cB = (ChaveBusca *)chaveB;

    // 1º Critério: Nome (Ordem Alfabética)
    int cmpNome = strcmp(cA->nome, cB->nome); //A função strcmp() serve para comparar duas strings caractere por caractere
    if (cmpNome !=0) {
        return cmpNome;
    }

    // 2º Critério: Data de Nascimento
    // Compara Ano, depois Mês, depois Dia
    if (cA->dataNascimento.ano != cB->dataNascimento.ano)
        return cA->dataNascimento.ano - cB->dataNascimento.ano;
    
    if (cA->dataNascimento.mes != cB->dataNascimento.mes)
        return cA->dataNascimento.mes - cB->dataNascimento.mes;
    
    return cA->dataNascimento.dia - cB->dataNascimento.dia;
}

int main () {
    int opcao;

    // Inicializar a Árvore B+ em disco
    // 
}