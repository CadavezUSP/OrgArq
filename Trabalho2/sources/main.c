#include <stdio.h>

#include "funcionalidadesLinhas.h"
#include "funcionalidadesVeiculos.h"


int main(int argc, char *argv[]) {

    int funcionalidade = 0;
    scanf("%d", &funcionalidade);

    if (funcionalidade == CREATE_INDEX_VEICULOS) {
        char nomeArquivoDados[100];
        char nomeArquivoIndice[100];
        scanf("%s %s", nomeArquivoDados, nomeArquivoIndice);
        createIndexVeiculos(nomeArquivoDados, nomeArquivoIndice);
    }
    else if (funcionalidade == CREATE_INDEX_LINHAS) {
        char nomeArquivoDados[100];
        char nomeArquivoIndice[100];
        scanf("%s %s", nomeArquivoDados, nomeArquivoIndice);
        createIndexLinhas(nomeArquivoDados, nomeArquivoIndice);
    }
    
    return 0;
}