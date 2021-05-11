#include "funcionalidadesLinhas.h"

typedef struct CabecalhoLinha
{
    char status;
    long long int byteProxReg;
    int nroRegistros;
    int nroRegRemovidos;
    char descreveCodigo[15];
    char descreveCartao [13];
    char descreveNome[13];
    char descreveCor[24];
}CabecalhoLinha;

typedef struct RegistroLinha
{
    char removido;
    int tamanhoRegistro;
    int codLinha;
    char aceitaCartao; // S, N, F
    int tamanhoNome;
    char *nomeLinha;
    int tamanhoCor;
    char* corLinha;
}RegistroLinha;


void createTableLinhas(char *arquivoEntrada, char *arquivoSaida) {

}


void selectFromLinhas(char *arquivoEntrada, char *arquivoSaida) {

}


void selectWhereLinhas(char *arquivoEntrada, char *arquivoSaida) {

}


void insertIntoLinhas(char *arquivoEntrada, char *arquivoSaida) {

}
