#ifndef RH_H
#define RH_H

#include <stdbool.h>

//Tipo de estrutura para Datas
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

// Chave Composta: Critério principal (Nome) e desempate (Data de Nascimento)
typedef struct {
    char nome[50];
    Data dataNascimento;
} ChaveBusca;

// Estrutura auxiliares do funcionário
typedef struct {
    char nomeMae[50];
    char nomePai[50];
} Filiacao;

typedef struct {
    char endereco[100];
    char telefone[50];
} Contato;

typedef struct {
    Data dataContratacao;
    bool atividade; // true = Ativo, false = Inativo
    Data dataDesligamento;
} DadosContratuais;

typedef struct {
    float valor;
    int mes;
    int ano;
} Pagamento;

// Registro completo do funcionario
typedef struct {
    ChaveBusca chave;
    Filiacao filiacao;
    Contato contato;
    DadosContratuais contrato;
    Pagamento historicoPagamento[12]; // Vetor estatico de 12 meses
} Funcionario;


#endif