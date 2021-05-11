//! Todos os char * podem ser alocados estaticamente como um char de 100 byes!!!!!!!
// o ideal eh ler e armazenar linha por linha!!
typedef struct CabecalhoVeiculo //cabecalho soh na hr de abrir e fechar 
{
    char status;
    long long int byteProxReg; //ftell
    int nroRegistros; // complementar de Removidos
    int nroRegRemovidos;// complementar de registros
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
    char prefixo[5];// nao pode assumir valor nulo e nem se repetir
    char data[10];// AAAA - MM - DD
    int quantidadeLugares;
    int codLinha;
    int tamanhoModelo;
    char* modelo;
    int tamanhoCategoria;
    char* categoria;
}RegistroVeiculo;

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

//teste de final do arquivo com fseek -1