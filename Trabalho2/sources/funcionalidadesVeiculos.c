#include "funcionalidadesVeiculos.h"

/*
Descrição: Lê vários registros de um arquivo binário e cria um arquivo de índice árvore B
@param nomeArquivoDados nome do arquivo bin de onde os registros serão lidos
@param nomeArquivoIndice nome do arquivo de índice que será gerado
*/
void createIndexVeiculos(char *nomeArquivoDados, char *nomeArquivoIndice) {

    // Abrindo o arquivo de dados para leitura e o de índice para escrita:
    FILE *arquivoDados = fopen(nomeArquivoDados, "rb");
    FILE *arquivoIndice = fopen(nomeArquivoIndice, "w+b");
    
    // Abortando a funcionalidade se ocorrer algum erro com a abertura dos arquivos:
    if (arquivoDados == NULL || arquivoIndice == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }

    CabecalhoVeiculo *cabecalhoVeiculos = carregaCabecalhoVeiculoDoBIN(arquivoDados);
    NoCabecalhoAB *cabecalhoAB = carregaNoCabecalhoDaAB(arquivoIndice);


    while (!fimDoArquivoBIN(arquivoDados)) {
        long long byteOffsetAtual = ftell(arquivoDados);
        RegistroVeiculo *registroAtual = carregaRegistroVeiculoDoBIN(arquivoDados);
        if (registroAtual->removido == '1') {
            int prefixoInteiro = convertePrefixo(registroAtual->prefixo);
            insereRegistroDadosNaAB(arquivoIndice, cabecalhoAB, prefixoInteiro, byteOffsetAtual);
        }
        free(registroAtual);
    }

    cabecalhoAB->status = '1';
    escreveNoCabecalhoNaAB(arquivoIndice, cabecalhoAB);

    imprimeArvore(arquivoIndice);

    free(cabecalhoAB);
    free(cabecalhoVeiculos);
    
    fclose(arquivoDados);
    fclose(arquivoIndice);

    binarioNaTela(nomeArquivoIndice);
}

void selectWhereVeiculos(char *nomeArquivoDados, char *nomeArquivoIndice, char *campo, char *valor) {

}

void insertIntoVeiculos(char *nomeArquivoDados, char *nomeArquivoIndice, int numeroRegistros) {

}
