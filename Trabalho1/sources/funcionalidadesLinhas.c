#include "funcionalidadesLinhas.h"

/*
Descrição: Cria um arquivo binário com dados contidos em um arquivo csv
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

    // Liberando memória do cabeçalho:
    free(cabecalho);
    
    // Imprimindo o resultado do binário na tela:
    binarioNaTela(arquivoSaida);
}

/*
Descricao: Le os veiculos do arquivo binario e printa na tela os registros
@param arquivoEntrada  nome do arquivo de entrada
*/
void selectFromLinhas(char *arquivoEntrada) {
    FILE* arquivoBin = fopen(arquivoEntrada, "rb"); //arquivo binario
    CabecalhoLinha *Cabecalho = carregaCabecalhoLinhaDoBIN(arquivoBin);
    int printouRegistro = 0;
    // enquanto nao for fim de aqruivo ler o registro e printar na tela
    while (!fimDoArquivoBIN(arquivoBin))
    {
        RegistroLinha *Reg = carregaRegistroLinhaDoBIN(arquivoBin);
        if (Reg->removido == '1') linhaNaTela(Reg, Cabecalho);
        free(Reg);
        printouRegistro =1;
    }
    if (printouRegistro == 0){
        printf("Registro inexistente.\n");
    }
    free(Cabecalho);
    fclose(arquivoBin);
    return;
}

/*
Descricao: faz uma busca sequencial no binario da Linha e retorna em todos os arquivos que satisfazem a condicao da busca
@param arquivoEntrada nome do arquivo binario
@param campo nome do campo buscado
@param valor valor do campo buscado
*/
void selectWhereLinhas(char *arquivoEntrada, char *campo, char *valor) {// Cadavez
    FILE *arquivoBIN = fopen(arquivoEntrada, "rb");
    CabecalhoLinha *cabecalho = carregaCabecalhoLinhaDoBIN(arquivoBIN);
    int printouRegistro = 0;
    do {
        RegistroLinha *reg = localizaLinha(arquivoBIN, valor, campo);
        if (reg == NULL) break;
        linhaNaTela(reg, cabecalho);
        printouRegistro =1;
        free(reg);
    } while (!fimDoArquivoBIN(arquivoBIN));
    if (printouRegistro == 0){
        printf("Registro inexistente.\n");
    }
    fclose(arquivoBIN);
    free (cabecalho);
    return;
}

/*
Descrição: Insere um conjunto de registros em um arquivo binário com dados lidos da entrada padrão 
@param arquivoEntrada nome do arquivo binário em que os registros serão inseridos 
@param numeroRegistros numero de registros que serão inseridos
*/
void insertIntoLinhas(char *arquivoEntrada, int numeroRegistros) {

    // Abrindo o arquivo binário para leitura e escrita:
    FILE *arquivoBIN = fopen(arquivoEntrada, "r+b");

    // Abortando a funcionalidade se o arquivo de entrada não existir:
    if (arquivoBIN == NULL) {
        imprimeMensagemErro(stdout);
        return;
    }

    // Carregando o registro de cabeçalho do arquivo binário para a memória:
    CabecalhoLinha *cabecalho = carregaCabecalhoLinhaDoBIN(arquivoBIN);

    // Abortando a funcionalidade se o arquivo de entrada estiver inconsistente:
    if (cabecalho->status == '0') {
        imprimeMensagemErro(stdout);
        fclose(arquivoBIN);
        free(cabecalho);
        return;
    }

    // Atualizando o registro de cabeçalho no arquivo binário:
    cabecalho->status = '0';
    escreveCabecalhoLinhaNoBIN(cabecalho, arquivoBIN);

    // Posicionando o cursor no fim do arquivo:
    fseek(arquivoBIN, 0, SEEK_END);

    // Inserindo os registros lidos da entrada padrão:
    for (int i = 0; i < numeroRegistros; i++) {
        RegistroLinha *registroAtual = carregaRegistroLinhaDaStdin();
        escreveRegistroLinhaNoBIN(registroAtual, arquivoBIN);
        cabecalho->nroRegistros += 1;
        free(registroAtual);
    }
    
    // Atualizando o registro de cabeçalho no arquivo binário:
    cabecalho->status = '1';
    cabecalho->byteProxReg = ftell(arquivoBIN);
    escreveCabecalhoLinhaNoBIN(cabecalho, arquivoBIN);

    // Fechando arquivo binário e liberando memória alocada:
    fclose(arquivoBIN);
    free(cabecalho);

    // Imprimindo o resultado do binário na tela:
    binarioNaTela(arquivoEntrada);
}
