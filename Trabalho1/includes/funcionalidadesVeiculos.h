#ifndef __FUNCIONALIDADES_VEICULOS_H__
    #define __FUNCIONALIDADES_VEICULOS_H__

    #include <stdio.h>

    #define CREATE_TABLE_VEICULOS 1
    #define SELECT_FROM_VEICULOS 3
    #define SELECT_WHERE_VEICULOS 5
    #define INSERT_INTO_VEICULOS 7

    void createTableVeiculos(char *arquivoEntrada, char *arquivoSaida);
    void selectFromVeiculos(char *arquivoEntrada, char *arquivoSaida);
    void selectWhereVeiculos(char *arquivoEntrada, char *arquivoSaida);
    void insertIntoVeiculos(char *arquivoEntrada, char *arquivoSaida);

#endif