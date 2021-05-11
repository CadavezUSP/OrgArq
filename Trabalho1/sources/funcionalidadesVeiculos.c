#include "funcionalidadesVeiculos.h"

typedef struct CabecalhoVeiculo //cabecalho soh na hr de abrir e fechar 
{
    char status;
    long long int byteProxReg; //ftell
    int nroRegistros; // complementar de Removidos
    int nroRegRemovidos; // complementar de registros
    char descrevePrefixo[18];
    char descreveData [35];
    char descreveLugares[42];
    char descreveLinha[26];
    char descreveModelo[17];
    char descreveCategoria[20];
}CabecalhoVeiculo;

typedef struct RegistroVeiculo
{
    char removido; // eh um char!! '0' ou '1'
    int tamanhoRegistro;
    char prefixo[5]; // nao pode assumir valor nulo e nem se repetir
    char data[10]; // AAAA - MM - DD
    int quantidadeLugares;
    int codLinha;
    int tamanhoModelo;
    char* modelo;
    int tamanhoCategoria;
    char* categoria;
}RegistroVeiculo;


void createTableVeiculos(char *arquivoEntrada, char *arquivoSaida) {

}


void selectFromVeiculos(char *arquivoEntrada, char *arquivoSaida) {

}


void selectWhereVeiculos(char *arquivoEntrada, char *arquivoSaida) {

}


void insertIntoVeiculos(char *arquivoEntrada, char *arquivoSaida) {

}
