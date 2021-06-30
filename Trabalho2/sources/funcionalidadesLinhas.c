// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#include "funcionalidadesLinhas.h"

/*
Descrição: Lê vários registros de um arquivo binário e cria um arquivo de índice árvore B
@param nomeArquivoDados nome do arquivo binário de onde os registros serão lidos
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

    // Carregando os cabeçalhos dos arquivos de dados e de índice para a memória:
    CabecalhoLinha *cabecalhoLinha = carregaCabecalhoLinhaDoBIN(arquivoDados);
    NoCabecalhoAB *cabecalhoAB = carregaNoCabecalhoDaAB(arquivoIndice);

    // Abortando a funcionalidade se o status do arquivo de dados for inconsistente:
    if (cabecalhoLinha->status == '0') {
        imprimeMensagemErro(stdout);
        return;
    }

    // Obtendo os registros do arquivo de dados e inserindo suas chaves/byteoffsets no arquivo de índice:
    while (!fimDoArquivoBIN(arquivoDados)) {
        long long byteOffsetAtual = ftell(arquivoDados);
        RegistroLinha *registroAtual = carregaRegistroLinhaDoBIN(arquivoDados);
        if (registroAtual->removido == '1')
            insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, registroAtual->codLinha, byteOffsetAtual);
        free(registroAtual);
    }

    // Atualizando o registro de cabeçalho do arquivo de índice para consistente:
    cabecalhoAB->status = '1';
    escreveNoCabecalhoNaAB(arquivoIndice, cabecalhoAB);

    // Fechando os arquivos:
    fclose(arquivoDados);
    fclose(arquivoIndice);

    // Liberando memória alocada:
    free(cabecalhoAB);
    free(cabecalhoLinha);
    
    // Imprimindo o resultado do arquivo de índice com binário na tela:
    binarioNaTela(nomeArquivoIndice);
}

void selectWhereLinhas(char *nomeArquivoDados, char *nomeArquivoIndice, char *campo, int valor) {
    // campo sempre vai ser "codLinha" e valor sempre inteiro
}

/*
Descrição: Insere um conjunto de registros em um arquivo binário com dados lidos da entrada padrão, 
atualizando também o arquivo de índice 
@param nomeArquivoDados nome do arquivo de dados em que os registros serão inseridos 
@param nomeArquivoIndice nome do arquivo de índice referente ao arquivo de dados
@param numeroRegistros número de registros que serão inseridos
*/
void insertIntoLinhas(char *nomeArquivoDados, char *nomeArquivoIndice, int numeroRegistros) {

    // Abrindo os arquivos de dado e índice para leitura e escrita:
    FILE *arquivoDados = fopen(nomeArquivoDados, "r+b");
    FILE *arquivoIndice = fopen(nomeArquivoIndice, "r+b");

    // Abortando a funcionalidade se algum dos arquivos não existir:
    if (arquivoDados == NULL || arquivoIndice == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }

    // Carregando os cabeçalhos dos arquivos de dados e de índice para a memória:
    CabecalhoLinha *cabecalhoLinha = carregaCabecalhoLinhaDoBIN(arquivoDados);
    NoCabecalhoAB *cabecalhoAB = carregaNoCabecalhoDaAB(arquivoIndice);

    // Abortando a funcionalidade se algum arquivo estiver inconsistente:
    if (cabecalhoLinha->status == '0' || cabecalhoAB->status == '0') {
        imprimeMensagemErro(stdout);
        return;
    }

    // Atualizando os registros de cabeçalho para inconsistentes:
    cabecalhoLinha->status = '0';
    cabecalhoAB->status = '0';
    fseek(arquivoDados, 0, SEEK_SET);
    fseek(arquivoIndice, 0, SEEK_SET);
    fwrite(&cabecalhoLinha->status, 1, 1, arquivoDados);
    fwrite(&cabecalhoAB->status, 1, 1, arquivoIndice);

    // Inserindo os registros lidos da entrada padrão:
    fseek(arquivoDados, 0, SEEK_END);
    for (int i = 0; i < numeroRegistros; i++) {
        long long byteOffsetAtual = ftell(arquivoDados);
        RegistroLinha *registroAtual = carregaRegistroLinhaDaStdin();
        escreveRegistroLinhaNoBIN(registroAtual, arquivoDados);
        cabecalhoLinha->nroRegistros += 1;
        insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, registroAtual->codLinha, byteOffsetAtual);
        free(registroAtual);
    }
    
    // Atualizando o cabeçalho do arquivo de dados:
    cabecalhoLinha->status = '1';
    cabecalhoLinha->byteProxReg = ftell(arquivoDados);
    escreveCabecalhoLinhaNoBIN(cabecalhoLinha, arquivoDados);

    // Atualizando o cabeçalho do arquivo de índice:
    cabecalhoAB->status = '1';
    escreveNoCabecalhoNaAB(arquivoIndice, cabecalhoAB);

    // Fechando os arquivos:
    fclose(arquivoDados);
    fclose(arquivoIndice);

    // Liberando memória alocada:
    free(cabecalhoLinha);
    free(cabecalhoAB);

    // Imprimindo o resultado do arquivo de índice na tela:
    binarioNaTela(nomeArquivoIndice);
}