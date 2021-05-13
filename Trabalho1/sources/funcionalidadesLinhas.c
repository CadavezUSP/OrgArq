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
    char nomeLinha[100];
    int tamanhoCor;
    char corLinha[100];
}RegistroLinha;


void createTableLinhas(char *arquivoEntrada, char *arquivoSaida) {

}


void selectFromLinhas(char *arquivoEntrada, char *arquivoSaida) {// Cadavez

}


void selectWhereLinhas(char *arquivoEntrada, char *arquivoSaida) {// Cadavez

}


void insertIntoLinhas(char *arquivoEntrada, char *arquivoSaida) {

}
