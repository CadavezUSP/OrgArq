#include "registrosLinhas.h"

/*
    Aloca memória e preenche dados uma estrutura do tipo CabecalhoLinha a partir de um arquivo csv
    @param arquivoCSV: fluxo do arquivo csv de onde as informações do registro de cabeçalho serão extraídas
    @return CabecalhoLinha* ponteiro para a região de memória em que os dados foram armazenados 
*/
CabecalhoLinha *carregaCabecalhoLinhaDoCSV(FILE *arquivoCSV) {

    // Alocando memória para uma estrutura do tipo CabecalhoLinha:
    CabecalhoLinha *cabecalho = malloc(sizeof(CabecalhoLinha));

    // Lendo o vetor de descrições dos campos do cabeçalho do arquivo CSV:
    char **descricoesCabecalho = leDescricoesCabecalhoCSV(arquivoCSV);

    // Atribuindo os valores das descrições lidas do csv à estrutura cabeçalho:
    strcpy(cabecalho->descreveCodigo, descricoesCabecalho[0]);
    strcpy(cabecalho->descreveCartao, descricoesCabecalho[1]);
    strcpy(cabecalho->descreveNome, descricoesCabecalho[2]);
    strcpy(cabecalho->descreveCor, descricoesCabecalho[3]);
    
    // Inicializando os demais campos da estrutura cabeçalho:
    cabecalho->status = '0';
    cabecalho->byteProxReg = 0;
    cabecalho->nroRegistros = 0;
    cabecalho->nroRegRemovidos = 0;

    // Liberando a memória alocada leitura das descricoes:
    for (int i = 0; i < 4; i++)
        free(descricoesCabecalho[i]);
    free(descricoesCabecalho);

    return cabecalho;
}

/*
    Aloca memória e preenche dados uma estrutura do tipo RegistroLinha a partir de um arquivo csv
    @param arquivoCSV: fluxo do arquivo csv de onde as informações do registro de dados serão extraídas
    @return RegistroLinha* ponteiro para a região de memória em que os dados foram armazenados 
*/
RegistroLinha *carregaRegistroLinhaDoCSV(FILE *arquivoCSV) {

    // Alocando memória para uma estrutura do tipo RegistroLinha:
    RegistroLinha *registro = malloc(sizeof(RegistroLinha));

    // Marcando o campo removido:
    if (registroDoCSVEhRemovido(arquivoCSV))
        registro->removido = '0';
    else
        registro->removido = '1';

    // Lendo e marcando os demais campos:
    registro->codLinha = leIntDoCSV(arquivoCSV);
    registro->aceitaCartao = leCharDoCSV(arquivoCSV);

    char *nome = leStringDoCSV(arquivoCSV);
    strcpy(registro->nomeLinha, nome);
    registro->nomeLinha[0] = strcmp(nome, "NULO") == 0 ? '\0' : registro->nomeLinha[0];
    registro->tamanhoNome = strlen(registro->nomeLinha);

    char *cor = leStringDoCSV(arquivoCSV);
    strcpy(registro->corLinha, cor);
    registro->corLinha[0] = strcmp(cor, "NULO") == 0 ? '\0' : registro->corLinha[0];
    registro->tamanhoCor = strlen(registro->corLinha);

    registro->tamanhoRegistro = 13 + registro->tamanhoNome + registro->tamanhoCor; 

    // Liberando memória alocada para leitura dos campos:
    free(nome);
    free(cor);

    return registro;
}

/*
    Escreve os dados de uma estrutura do tipo CabecalhoLinha* em um arquivo binário
    @param cabecalho: ponteiro para a região de memória onde o registro de cabeçalho está armazenado 
    @param arquivoBIN: fluxo do arquivo binário em que os dados serão escritos
*/
void escreveCabecalhoLinhaNoBIN(CabecalhoLinha *cabecalho, FILE *arquivoBIN) {
    // Pulando para o início do arquivo binário
    fseek(arquivoBIN, 0, SEEK_SET);
    // Escrevendo os campos do registro de cabeçalho no binário:
    fwrite(&cabecalho->status, 1, 1, arquivoBIN);
    fwrite(&cabecalho->byteProxReg, sizeof(long long), 1, arquivoBIN);
    fwrite(&cabecalho->nroRegistros, sizeof(int), 1, arquivoBIN);
    fwrite(&cabecalho->nroRegRemovidos, sizeof(int), 1, arquivoBIN);
    fwrite(cabecalho->descreveCodigo, 1, 15, arquivoBIN);
    fwrite(cabecalho->descreveCartao, 1, 13, arquivoBIN);
    fwrite(cabecalho->descreveNome, 1, 13, arquivoBIN);
    fwrite(cabecalho->descreveCor, 1, 24, arquivoBIN);
}

/*
    Escreve os dados de uma estrutura do tipo RegistroLinha* em um arquivo binário
    @param registroLinha: ponteiro para a região de memória onde o registro de dados está armazenado 
    @param arquivoBIN: fluxo do arquivo binário em que os dados serão escritos
*/
void escreveRegistroLinhaNoBIN(RegistroLinha *registroLinha, FILE *arquivoBIN) {
    // Escrevendo os campos do registro de dados no binário:
    fwrite(&registroLinha->removido, 1, 1, arquivoBIN);
    fwrite(&registroLinha->tamanhoRegistro, sizeof(int), 1, arquivoBIN);
    fwrite(&registroLinha->codLinha, sizeof(int), 1, arquivoBIN);
    fwrite(&registroLinha->aceitaCartao, 1, 1, arquivoBIN);
    fwrite(&registroLinha->tamanhoNome, sizeof(int), 1, arquivoBIN);
    fwrite(registroLinha->nomeLinha, 1, registroLinha->tamanhoNome, arquivoBIN);
    fwrite(&registroLinha->tamanhoCor, sizeof(int), 1, arquivoBIN);
    fwrite(registroLinha->corLinha, 1, registroLinha->tamanhoCor, arquivoBIN);
}

/*
    Aloca memória e preenche dados uma estrutura do tipo CabecalhoLinha a partir de um arquivo binário 
    @param arquivoBIN: fluxo do arquivo binário de onde as informações do registro de cabeçalho serão extraídas
    @return CabecalhoLinha* ponteiro para a região de memória em que os dados foram armazenados 
*/
CabecalhoLinha *carregaCabecalhoLinhaDoBIN(FILE *arquivoBIN) {

    // Pulando para o início do arquivo binário
    fseek(arquivoBIN, 0, SEEK_SET);

    // Alocando memória para uma estrutura do tipo CabecalhoLinha:
    CabecalhoLinha *cabecalho = malloc(sizeof(CabecalhoLinha));

    // Lendo os campos do registro de cabeçalho do binário:
    fread(&cabecalho->status, 1, 1, arquivoBIN);
    fread(&cabecalho->byteProxReg, sizeof(long long), 1, arquivoBIN);
    fread(&cabecalho->nroRegistros, sizeof(int), 1, arquivoBIN);
    fread(&cabecalho->nroRegRemovidos, sizeof(int), 1, arquivoBIN);
    fread(cabecalho->descreveCodigo, 1, 15, arquivoBIN);
    fread(cabecalho->descreveCartao, 1, 13, arquivoBIN);
    fread(cabecalho->descreveNome, 1, 13, arquivoBIN);
    fread(cabecalho->descreveCor, 1, 24, arquivoBIN);

    // Finalizando os campos string com '\0':
    cabecalho->descreveCodigo[15] = '\0';
    cabecalho->descreveCartao[13] = '\0';
    cabecalho->descreveNome[13] = '\0';
    cabecalho->descreveCor[24] = '\0';

    return cabecalho;
}

/*
    Aloca memória e preenche dados uma estrutura do tipo RegistroLinha a partir de um arquivo binário 
    @param arquivoBIN: fluxo do arquivo binário de onde as informações do registro de dados serão extraídas
    @return RegistroLinha* ponteiro para a região de memória em que os dados foram armazenados 
*/
RegistroLinha *carregaRegistroLinhaDoBIN(FILE *arquivoBIN) {

    // Alocando memória para uma estrutura do tipo RegistroLinha:
    RegistroLinha *registroLinha = malloc(sizeof(RegistroLinha));

    fread(&registroLinha->removido, 1, 1, arquivoBIN);
    fread(&registroLinha->tamanhoRegistro, sizeof(int), 1, arquivoBIN);
    fread(&registroLinha->codLinha, sizeof(int), 1, arquivoBIN);
    fread(&registroLinha->aceitaCartao, 1, 1, arquivoBIN);
    fread(&registroLinha->tamanhoNome, sizeof(int), 1, arquivoBIN);
    fread(registroLinha->nomeLinha, 1, registroLinha->tamanhoNome, arquivoBIN);
    fread(&registroLinha->tamanhoCor, sizeof(int), 1, arquivoBIN);
    fread(registroLinha->corLinha, 1, registroLinha->tamanhoCor, arquivoBIN);

    // Finalizando os campos string com '\0':
    registroLinha->nomeLinha[registroLinha->tamanhoNome] = '\0';
    registroLinha->corLinha[registroLinha->tamanhoCor] = '\0';

    return registroLinha;
}
