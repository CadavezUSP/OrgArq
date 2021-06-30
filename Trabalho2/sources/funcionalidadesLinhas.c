#include "funcionalidadesLinhas.h"

/*
Descrição: Lê vários registros de um arquivo binário e cria um arquivo de índice árvore B
@param nomeArquivoDados nome do arquivo bin de onde os registros serão lidos
@param nomeArquivoIndice nome do arquivo de índice que será gerado
*/
void createIndexLinhas(char *nomeArquivoDados, char *nomeArquivoIndice) {

    // Abrindo o arquivo de dados para leitura e o de índice para escrita:
    FILE *arquivoDados = fopen(nomeArquivoDados, "rb");
    FILE *arquivoIndice = fopen(nomeArquivoIndice, "w+b");
    
    // Abortando a funcionalidade se ocorrer algum erro com a abertura dos arquivos:
    if (arquivoDados == NULL || arquivoIndice == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }

    CabecalhoLinha *cabecalhoLinha = carregaCabecalhoLinhaDoBIN(arquivoDados);
    NoCabecalhoAB *cabecalhoAB = carregaNoCabecalhoDaAB(arquivoIndice);

    while (!fimDoArquivoBIN(arquivoDados)) {
        long long byteOffsetAtual = ftell(arquivoDados);
        RegistroLinha *registroAtual = carregaRegistroLinhaDoBIN(arquivoDados);
        if (registroAtual->removido == '1') {
            insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, registroAtual->codLinha, byteOffsetAtual);
        }
        free(registroAtual);
    }

/*
    printf("-> Insercao do 10\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 10, 0);

    printf("-> Insercao do 30\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 30, 0);

    printf("-> Insercao do 20\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 20, 0);

    printf("-> Insercao do 5\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 5, 0);

    printf("-> Insercao do 60\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 60, 0);

    printf("-> Insercao do 11\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 11, 0);

    printf("-> Insercao do 12\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 12, 0);

    printf("-> Insercao do 61\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 61, 0);

    printf("-> Insercao do 62\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 62, 0);
*/
/*
    printf("-> Insercao do 3\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 3, 0);
*/
/*
    printf("-> Insercao do 63\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 63, 0);
*/
/*
    printf("-> Insercao do 1\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 1, 0);

    printf("-> Insercao do 2\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 2, 0);

    printf("-> Insercao do 3\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 3, 0);

    printf("-> Insercao do 4\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 4, 0);

    printf("-> Insercao do 0\n");
    insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, 0, 0);
*/

    cabecalhoAB->status = '1';
    escreveNoCabecalhoNaAB(arquivoIndice, cabecalhoAB);

/*
    FILE *certo = fopen("indicePrefixo4.bin", "rb");
    imprimeArvore(certo);
    fclose(certo);
*/

    imprimeArvore(arquivoIndice);

    free(cabecalhoAB);
    free(cabecalhoLinha);
    
    fclose(arquivoDados);
    fclose(arquivoIndice);

    binarioNaTela(nomeArquivoIndice);
}

void selectWhereLinhas(char *nomeArquivoDados, char *nomeArquivoIndice, char *campo, char *valor) {

}

void insertIntoLinhas(char *nomeArquivoDados, char *nomeArquivoIndice, int numeroRegistros) {

}