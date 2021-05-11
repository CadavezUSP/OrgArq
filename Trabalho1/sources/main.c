#include <stdio.h>

#include "funcionalidadesLinhas.h"
#include "funcionalidadesVeiculos.h"


int main(int argc, char *argv[]) {

    int funcionalidade = 0;
    char arquivoEntrada[12];
    char arquivoSaida[12];

    scanf("%d %s %s", &funcionalidade, arquivoEntrada, arquivoSaida);
    
    switch (funcionalidade) {
        case CREATE_TABLE_VEICULOS:
            createTableVeiculos(arquivoEntrada, arquivoSaida);
            break;
        case CREATE_TABLE_LINHAS:
            createTableLinhas(arquivoEntrada, arquivoSaida);
            break;
        case SELECT_FROM_VEICULOS:
            selectFromVeiculos(arquivoEntrada, arquivoSaida);
            break;
        case SELECT_FROM_LINHAS:
            selectFromLinhas(arquivoEntrada, arquivoSaida);
            break;
        case SELECT_WHERE_VEICULOS:
            selectWhereVeiculos(arquivoEntrada, arquivoSaida);
            break;
        case SELECT_WHERE_LINHAS:
            selectWhereLinhas(arquivoEntrada, arquivoSaida);
            break;
        case INSERT_INTO_VEICULOS:
            insertIntoVeiculos(arquivoEntrada, arquivoSaida);
            break;
        case INSERT_INTO_LINHAS:
            insertIntoLinhas(arquivoEntrada, arquivoSaida);
            break;
        default:
            fprintf(stderr, "Funcionalidade desconhecida!\n");
    }

    return 0;
}
