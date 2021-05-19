#ifndef __REGISTROS_VEICULOS_H__
    #define __REGISTROS_VEICULOS_H__

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "leitorCSV.h"
    #include "util.h"

    typedef struct CabecalhoVeiculo
    {
        char status;
        long long byteProxReg;
        int nroRegistros; // complementar de removidos
        int nroRegRemovidos; // complementar de registros
        char descrevePrefixo[19];
        char descreveData[36];
        char descreveLugares[43];
        char descreveLinha[27];
        char descreveModelo[18];
        char descreveCategoria[21];
    }CabecalhoVeiculo;

    typedef struct RegistroVeiculo
    {
        char removido; // '0' ou '1'
        int tamanhoRegistro;
        char prefixo[6];
        char data[11]; // AAAA - MM - DD
        int quantidadeLugares;
        int codLinha;
        int tamanhoModelo;
        char modelo[100];
        int tamanhoCategoria;
        char categoria[100];
    }RegistroVeiculo;

    CabecalhoVeiculo *carregaCabecalhoVeiculoDoCSV(FILE *arquivoCSV);
    RegistroVeiculo *carregaRegistroVeiculoDoCSV(FILE *arquivoCSV);
    CabecalhoVeiculo *carregaCabecalhoVeiculoDoBIN(FILE *arquivoBIN); 
    RegistroVeiculo *carregaRegistroVeiculoDoBIN(FILE *arquivoBIN); 
    RegistroVeiculo *carregaRegistroVeiculoDaStdin(void);
    void escreveCabecalhoVeiculoNoBIN(CabecalhoVeiculo *cabecalho, FILE *arquivoBIN);
    void escreveRegistroVeiculoNoBIN(RegistroVeiculo *registroVeiculo, FILE *arquivoBIN); 
    void veiculoNaTela (RegistroVeiculo *Reg, CabecalhoVeiculo *cabecalho);
    RegistroVeiculo *localizarVeiculo(FILE *arquivoBIN, char* valor, char *campo);

#endif