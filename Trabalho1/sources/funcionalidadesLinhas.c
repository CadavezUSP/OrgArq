#include "funcionalidadesLinhas.h"

/*
    Cria um arquivo binário com dados contidos em um arquivo csv
    @param arquivoEntrada nome do arquivo csv de onde os dados serão estraídos
    @param arquivoSaida nome do arquivo binário no qual os dados serão escritos 
*/
void createTableLinhas(char *arquivoEntrada, char *arquivoSaida) {
    
    // Abrindo o arquivo CSV para leitura e o arquivo binário para escrita:
    FILE *arquivoCSV = fopen(arquivoEntrada, "r");
    FILE *arquivoBIN = fopen(arquivoSaida, "wb");

    // Abortando a funcionalidade se ocorrer algum erro com a abertura dos arquivos:
    if (arquivoCSV == NULL || arquivoBIN == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }

    // Obtendo os campos do cabeçalho do arquivo CSV e escrevendo-os no arquivo binário:
    CabecalhoLinha *cabecalho = carregaCabecalhoLinhaDoCSV(arquivoCSV);
    escreveCabecalhoLinhaNoBIN(cabecalho, arquivoBIN);

    // Obtendo os registros de dados do arquivo CSV e escrevendo-os no arquivo binário:
    while (!fimDoArquivoCSV(arquivoCSV)) {
        RegistroLinha *registroAtual = carregaRegistroLinhaDoCSV(arquivoCSV);
        if (registroAtual->removido == '0') // se o registro estiver removido
            cabecalho->nroRegRemovidos += 1;
        else
            cabecalho->nroRegistros += 1;
        escreveRegistroLinhaNoBIN(registroAtual, arquivoBIN);
        free(registroAtual);
    }

    // Atualizando o arquivo de cabeçalho:
    cabecalho->status = '1';
    cabecalho->byteProxReg = ftell(arquivoBIN);
    escreveCabecalhoLinhaNoBIN(cabecalho, arquivoBIN);

    // Fechando os arquivos
    fclose(arquivoCSV);
    fclose(arquivoBIN);

    // Imprimindo o resultado do binário na tela:
    binarioNaTela(arquivoSaida);

    // Liberando memória do cabeçalho:
    free(cabecalho);
}


void selectFromLinhas(char *arquivoEntrada) {// Cadavez

}


void selectWhereLinhas(char *arquivoEntrada, char *campo, char *valor) {// Cadavez

}


void insertIntoLinhas(char *arquivoEntrada, int numeroRegistros) {

}
