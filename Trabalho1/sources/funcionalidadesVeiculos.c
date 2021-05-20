#include "funcionalidadesVeiculos.h"

/*
Descrição: Cria um arquivo binário com dados contidos em um arquivo csv
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
    FILE* arquivoBIN = fopen(arquivoEntrada, "rb"); // arquivo binario

    // Caso nao seja possivel abrir o arquivo retorna falha
    if (arquivoBIN == NULL){
        imprimeMensagemErro(stdout);
        return;
    }

    // Carregando o registro de cabeçalho do arquivo binário para a memória:
    CabecalhoVeiculo *Cabecalho = carregaCabecalhoVeiculoDoBIN(arquivoBIN);

    // Abortando a funcionalidade se o arquivo de entrada estiver inconsistente:
    if (Cabecalho->status == '0') {
        imprimeMensagemErro(stdout);
        fclose(arquivoBIN);
        free(Cabecalho);
    return;
    }
    int printouRegistro = 0;

    //printando os registros
    while (!fimDoArquivoBIN(arquivoBIN))
    {
        RegistroVeiculo *Reg = carregaRegistroVeiculoDoBIN(arquivoBIN);
        if (Reg->removido == '1') veiculoNaTela(Reg, Cabecalho);
        printouRegistro =1;
        free(Reg);
    }

    //verificando se algum registro foi printado
    if (printouRegistro == 0){
        printf("Registro inexistente.\n");
    }
    fclose(arquivoBIN);
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

    // Caso nao seja possivel abrir o arquivo retorna falha
    if (arquivoBIN == NULL){
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
    RegistroVeiculo *reg;
    int printouRegistro = 0;
    
    //buscando e printando os registros
    while (!fimDoArquivoBIN(arquivoBIN)) {
        reg = localizaVeiculo(arquivoBIN, valor, campo);
        if (reg == NULL) break;
        printouRegistro =1;
        veiculoNaTela(reg, cabecalho);
        free(reg);
    }

    // verificando se algum registro foi printado
    if (printouRegistro == 0) {
        printf("Registro inexistente.\n");
    }
    fclose(arquivoBIN);
    free(cabecalho);
}

/*
Descrição: Insere um conjunto de registros em um arquivo binário com dados lidos da entrada padrão 
@param arquivoEntrada nome do arquivo binário em que os registros serão inseridos 
@param numeroRegistros número de registros que serão inseridos
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
