#include "Bplus.h"
#include <stdbool.h>


// Escreve um novo no em uma posição especifica do disco.
void escreve_no(FILE *arq, long endereço, NoBPlus *no){
    if(endereço == -1) return;
    fseek(arq, endereço, SEEK_SET);
    fwrite(no, sizeof(NoBPlus), 1, arq);
}

// tem a tarefa de ler um no de uma posicao especifica do disco para a memoria RAM.
void ler_no(FILE *arq, long endereço, NoBPlus *no){
    if(endereço == -1) return;
    fseek(arq, endereço, SEEK_SET);
    fread(no, sizeof(NoBPlus), 1, arq);
}

// Aloca um nova pagina no fim do arquivo para armazenar um novo nó.
long aloca_novaPagina(FILE *arq){
    fseek(arq, 0, SEEK_END);
    long pagina = ftell(arq);


    // Inicializa uma nova pagina no disco e zera seus espaços.
    NoBPlus novaPagina;
    novaPagina.folha = 1;
    novaPagina.qtdChave = 0;
    novaPagina.proxFolha = -1;
    for(int i = 0; i < ORDEM; i++){
        novaPagina.filhos[i] = -1;
        if( i < ORDEM -1) novaPagina.registro[i] = -1;
    }

    escreve_no(arq, pagina, &novaPagina);
    return pagina;
}

ArvoreBPlus *criar_arvore(const char *caminho_arquivo, size_t tamanho_chave, size_t tamanho_registro, FuncaoCompara comp, FuncaoImpressao impr){
    ArvoreBPlus *arvore = (ArvoreBPlus *)malloc(sizeof(ArvoreBPlus));
    if(arvore == NULL) return NULL;

    arvore->tamanho_chave = tamanho_chave;
    arvore->tamanho_registro = tamanho_registro;
    arvore->comparar = comp;
    arvore->imprime = impr;

    // Tenta abrir par aleitura e escrita se falhar tentamos com "wb+"
    arvore->arquivo_indice = fopen(caminho_arquivo, "rb+");
    if(arvore->arquivo_indice == NULL){
        arvore->arquivo_indice = fopen(caminho_arquivo, "wb+");
        arvore->raiz = -1; // aqui a arvore começa vazia.

        fwrite(&arvore->raiz, sizeof(long), 1, arvore->arquivo_indice);
    }else{/*Se o arquivo exista, a raiz vai estar no inicio*/
        // ATENÇÃO TALVEZ TEREMOS QUE VOLTAR AQUI.
        fseek(arvore->arquivo_indice, 0, SEEK_SET);
        if(fread(&arvore->raiz, sizeof(long), 1, arvore->arquivo_indice) != 1){
            arvore->raiz = -1;
        }
    }

    return arvore;
}

void fechaArvore(ArvoreBPlus *arvore){
    if(arvore){
        if(arvore->arquivo_indice){
            //Salva o endereço atual da raiz no inicio e depois fecha o arquivo.
            fseek(arvore->arquivo_indice, 0, SEEK_SET);
            fwrite(&arvore->raiz, sizeof(long), 1, arvore->arquivo_indice);
            fclose(arvore->arquivo_indice);
        }
        free(arvore);
    }
}

long buscar(ArvoreBPlus *arvore, const void *chave){
    int i;
    
    if(arvore->raiz == -1){
        return -1; // arvore está vazia
    }

    long atual = arvore->raiz;
    NoBPlus pagina_atual;

    // Navefa da raiz até a folha adequada

    while(true){
        //carrega a pagina atual do disco para a memoria ram
        ler_no(arvore->arquivo_indice, atual, &pagina_atual);
        i = 0;

        // Passamos o ponteiro dos bytes genericos para nossa função callback
        while(i < pagina_atual.qtdChave && arvore->comparar(chave, pagina_atual.chaves[i]) > 0){
            i++;
        }

        if(pagina_atual.folha){
            // se for uma folha, verficamos se a chave exite.
            if(i < pagina_atual.qtdChave && arvore->comparar(chave, pagina_atual.chaves[i]) == 0){
                return pagina_atual.registro[i];
            }
            else{
                return -1; // chave nao existe
            }
        }else{
            /*Se for uma pagina descemos para sua pagina filha
              O indice aponta para o filho, caso a busca der menor ele ira para esquerda
              , caso contrario vai para direita*/
            
            //Caso haja impate, ele vai para direita.
            if( i < pagina_atual.qtdChave && arvore->comparar(chave, pagina_atual.chaves[i]) == 0){
                i++;
            }
            atual = pagina_atual.filhos[i];
        }
    }
}

void inserir(ArvoreBPlus *arvore, const void *chave, long registro){
    // CASO 1: Arvore vazia

    if(arvore->raiz == -1){
        long novo = aloca_novaPagina(arvore->arquivo_indice);
        NoBPlus novaRaiz;
        ler_no(arvore->arquivo_indice, novo, &novaRaiz);

        novaRaiz.folha = 1; // A primeira raiz tambem é uma folha.
        novaRaiz.qtdChave = 1;
        memcpy(novaRaiz.chaves[0], chave, arvore->tamanho_chave); // copia os bytes genéricos
        novaRaiz.registro[0] = registro;

        escreve_no(arvore->arquivo_indice, novo, &novaRaiz);
        arvore->raiz = novo;
        return;
    }

    // // Variaveis para garantir que nao percamos a chave e o ponteiro caso seja necessario fazer cisao na raiz
    // unsigned char chave_raiz[TAM_MAXCHAVE];
    // long filhoDir = -1;

    // int splitRaiz //= // função split aqui

    // //if(splitRaiz){
    // //    long
    // //}

}