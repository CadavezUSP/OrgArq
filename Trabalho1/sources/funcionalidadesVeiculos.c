#include "funcionalidadesVeiculos.h"
#include <string.h>



/*
    Cria um arquivo binário com dados contidos em um arquivo csv
    @param arquivoEntrada nome do arquivo csv de onde os dados serão estraídos
    @param arquivoSaida nome do arquivo binário no qual os dados serão escritos 
*/
void createTableVeiculos(char *arquivoEntrada, char *arquivoSaida) {
    
    // Abrindo o arquivo CSV para leitura e o arquivo binário para escrita:
    FILE *arquivoCSV = fopen(arquivoEntrada, "r");
    FILE *arquivoBIN = fopen(arquivoSaida, "wb");

    // Abortando a funcionalidade se ocorrer algum erro com a abertura dos arquivos:
    if (arquivoCSV == NULL || arquivoBIN == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }

    // Obtendo os campos do cabeçalho do arquivo CSV e escrevendo-os no arquivo binário:
    CabecalhoVeiculo *cabecalho = carregaCabecalhoVeiculoDoCSV(arquivoCSV);
    escreveCabecalhoVeiculoNoBIN(cabecalho, arquivoBIN);

    // Obtendo os registros de dados do arquivo CSV e escrevendo-os no arquivo binário:
    while (!fimDoArquivoCSV(arquivoCSV)) {
        RegistroVeiculo *registroAtual = carregaRegistroVeiculoDoCSV(arquivoCSV);
        if (registroAtual->removido == '0') // se o registro estiver removido
            cabecalho->nroRegRemovidos += 1;
        else
            cabecalho->nroRegistros += 1;
        escreveRegistroVeiculoNoBIN(registroAtual, arquivoBIN);
        free(registroAtual);
    }

    // Atualizando o arquivo de cabeçalho:
    cabecalho->status = '1';
    cabecalho->byteProxReg = ftell(arquivoBIN);
    escreveCabecalhoVeiculoNoBIN(cabecalho, arquivoBIN);

    // Fechando os arquivos
    fclose(arquivoCSV);
    fclose(arquivoBIN);

    // Liberando memória do cabeçalho:
    free(cabecalho);

    // Imprimindo o resultado do binário na tela:
    binarioNaTela(arquivoSaida);
}

/*
Descricao: Le os veiculos do arquivo binario e printa na tela os registros
@param arquivoEntrada  nome do arquivo de entrada
*/
void selectFromVeiculos(char *arquivoEntrada) { 
    FILE* arquivoBin = fopen(arquivoEntrada, "rb"); // arquivo binario
    CabecalhoVeiculo *Cabecalho = carregaCabecalhoVeiculoDoBIN(arquivoBin); // cabecalho
    int printouRegistro = 0;
    while (!fimDoArquivoBIN(arquivoBin))
    {
        RegistroVeiculo *Reg = carregaRegistroVeiculoDoBIN(arquivoBin);
        if (Reg->removido == '1') veiculoNaTela(Reg, Cabecalho);
        printouRegistro =1;
        free(Reg);
    }
    if (printouRegistro == 0){
        printf("Registro inexistente.\n");
    }
    fclose(arquivoBin);
    free(Cabecalho);
}
/*
Descricao: faz uma busca sequencial no binario dos veiculos e retorna em todos os arquivos que satisfazem a condicao da busca
@param arquivoEntrada nome do arquivo binario
@param campo nome do campo buscado
@param valor valor do campo buscado
*/
void selectWhereVeiculos(char *arquivoEntrada, char *campo, char *valor) {//Cadavez
    FILE *arquivoBIN = fopen(arquivoEntrada, "rb");
    CabecalhoVeiculo *cabecalho = carregaCabecalhoVeiculoDoBIN(arquivoBIN);
    RegistroVeiculo *reg;
    int printouRegistro = 0;
    do {
        reg = localizarVeiculo(arquivoBIN, valor, campo);
        if (reg == NULL) break;
        printouRegistro =1;
        veiculoNaTela(reg, cabecalho);
        free(reg);
    } while (!fimDoArquivoBIN(arquivoBIN));
    if (printouRegistro == 0){
        printf("Registro inexistente.\n");
    }
    fclose(arquivoBIN);
    free (cabecalho);
}

/*
    Insere um conjunto de registros em um arquivo binário com dados lidos da entrada padrão 
    @param arquivoEntrada nome do arquivo binário em que os registros serão inseridos 
    @param numeroRegistros numero de registros que serão inseridos
*/
void insertIntoVeiculos(char *arquivoEntrada, int numeroRegistros) {

    // Abrindo o arquivo binário para leitura e escrita:
    FILE *arquivoBIN = fopen(arquivoEntrada, "r+b");

    // Abortando a funcionalidade se o arquivo de entrada não existir:
    if (arquivoBIN == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }

    // Carregando o registro de cabeçalho do arquivo binário para a memória:
    CabecalhoVeiculo *cabecalho = carregaCabecalhoVeiculoDoBIN(arquivoBIN);

    // Abortando a funcionalidade se o arquivo de entrada estiver inconsistente:
    if (cabecalho->status == '0') {
        imprimeMensagemErro(stdout);
        fclose(arquivoBIN);
        free(cabecalho);
        return;
    }

    // Atualizando o registro de cabeçalho no arquivo binário:
    cabecalho->status = '0';
    escreveCabecalhoVeiculoNoBIN(cabecalho, arquivoBIN);

    // Posicionando o cursor no fim do arquivo:
    fseek(arquivoBIN, 0, SEEK_END);

    // Inserindo os registros lidos da entrada padrão:
    for (int i = 0; i < numeroRegistros; i++) {
        RegistroVeiculo *registroAtual = carregaRegistroVeiculoDaStdin();
        escreveRegistroVeiculoNoBIN(registroAtual, arquivoBIN);
        cabecalho->nroRegistros += 1;
        free(registroAtual);
    }
    
    // Atualizando o registro de cabeçalho no arquivo binário:
    cabecalho->status = '1';
    cabecalho->byteProxReg = ftell(arquivoBIN);
    escreveCabecalhoVeiculoNoBIN(cabecalho, arquivoBIN);

    // Fechando arquivo binário e liberando memória alocada:
    fclose(arquivoBIN);
    free(cabecalho);

    // Imprimindo o resultado do binário na tela:
    binarioNaTela(arquivoEntrada);
}
