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
    ArvoreBPlus *arvore = criar_arvore("rh_dados.bin", sizeof(ChaveBusca), sizeof(Funcionario), compara_chave, imprime_chave);

    if (arvore == NULL) {
        printf("Erro ao iniciar o arquivo da Árvore B+ em disco.\n");
        return 1;
    }

    do {
        printf("\n================ SISTEMA DE GESTAO DE RH ================\n");
        printf("1. Inserir Funcionario\n");
        printf("2. Buscar Funcionario\n");
        printf("3. Excluir Funcionario\n");
        printf("4. Listagem por Intervalo (Nome A ate Nome B)\n");
        printf("5. Exibir Estrutura do Indice (Arvore B+)\n");
        printf("6. Sair\n");
        printf("=========================================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        while(getchar() != '\n'); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                printf("\n--- Inserir Funcionario ---\n");
                // TODO: Solicitar Nome e Data. 
                // Verificar se existe. Se sim -> Update. Se não -> Pedir resto e Inserir.
                break;
            
            case 2:
                printf("\n--- Buscar Funcionario ---\n");
                // TODO: Solicitar Nome. Lidar com homônimos listando datas. Exibir ficha.
                break;
            
            case 3:
                printf("\n--- Excluir Funcionario ---\n");
                // TODO: Solicitar Nome. Desempatar. Pedir confirmacao e Remover.
                break;
            
            case 4:
                printf("\n--- Listagem por Intervalo ---\n");
                // TODO: Solicitar Nome A e Nome B. Chamar busca por intervalo na arvore.
                break;
            
            case 5:
                printf("\n--- Estrutura da Arvore B+ ---\n");
                // TODO: Imprimir a árvore hierarquicamente lendo do disco.
                break;
            
            case 6:
                printf("\nEncerrando o sistema e salvando arquivos...\n");
                // TODO: Fechar os ponteiros FILE de forma segura.
                break;
            
            default:
                printf("\nOpcao Invalida! Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}