#include "registrosVeiculos.h"

/*
    Aloca memória e preenche dados uma estrutura do tipo CabecalhoVeiculo a partir de um arquivo csv
    @param arquivoCSV: fluxo do arquivo csv de onde as informações do registro de cabeçalho serão extraídas
    @return CabecalhoVeiculo* ponteiro para a região de memória em que os dados foram armazenados 
*/
CabecalhoVeiculo *carregaCabecalhoVeiculoDoCSV(FILE *arquivoCSV) {

    // Alocando memória para uma estrutura do tipo CabecalhoVeiculo:
    CabecalhoVeiculo *cabecalho = malloc(sizeof(CabecalhoVeiculo));

    // Lendo o vetor de descrições dos campos do cabeçalho do arquivo CSV:
    char **descricoesCabecalho = leDescricoesCabecalhoCSV(arquivoCSV);

    // Atribuindo os valores das descrições lidas do csv à estrutura cabeçalho:
    strcpy(cabecalho->descrevePrefixo, descricoesCabecalho[0]);
    strcpy(cabecalho->descreveData, descricoesCabecalho[1]);
    strcpy(cabecalho->descreveLugares, descricoesCabecalho[2]);
    strcpy(cabecalho->descreveLinha, descricoesCabecalho[3]);
    strcpy(cabecalho->descreveModelo, descricoesCabecalho[4]);
    strcpy(cabecalho->descreveCategoria, descricoesCabecalho[5]);
    
    // Inicializando os demais campos da estrutura cabeçalho:
    cabecalho->status = '0';
    cabecalho->byteProxReg = 0;
    cabecalho->nroRegistros = 0;
    cabecalho->nroRegRemovidos = 0;

    // Liberando a memória alocada leitura das descricoes:
    for (int i = 0; i < 6; i++)
        free(descricoesCabecalho[i]);
    free(descricoesCabecalho);

    return cabecalho;
}

/*
    Lê o prefixo de um registro de dados de um arquivo csv
    @param arquivoCSV: fluxo do arquivo csv a partir do qual o prefixo será lido 
    @return char* prefixo lido 
*/
char *lePrefixoDoCSV(FILE *arquivoCSV) {

    // Lendo o prefixo e calculando seu tamanho:
    char *prefixo = leStringDoCSV(arquivoCSV);
    int tamanhoPrefixo = strlen(prefixo);

    // Preenchendo '\0's caso necessário:
    if (tamanhoPrefixo < 5) {
        prefixo = realloc(prefixo, 6);
        for (int i = tamanhoPrefixo; i < 6; i++)
            prefixo[i] = '\0';
    }

    return prefixo;
}

/*  
    Lê a data de um registro de dados de um arquivo csv
    @param arquivoCSV: fluxo do arquivo csv a partir do qual a data será lida
    @return char* data lida
*/
char *leDataDoCSV(FILE *arquivoCSV) {
    
    // Lendo a data:
    char *data = leStringDoCSV(arquivoCSV);

    // Se a data for nula, é preenchido lixo:
    if (strcmp(data, "NULO") == 0) {
        data = realloc(data, 11);
        for (int i = 0; i < 10; i++)
            data[i] = '@';
        data[10] = '\0';
    }

    return data;
}

/*
    Aloca memória e preenche dados uma estrutura do tipo RegistroVeiculo a partir de um arquivo csv
    @param arquivoCSV: fluxo do arquivo csv de onde as informações do registro de dados serão extraídas
    @return RegistroVeiculo* ponteiro para a região de memória em que os dados foram armazenados 
*/
RegistroVeiculo *carregaRegistroVeiculoDoCSV(FILE *arquivoCSV) {

    // Alocando memória para uma estrutura do tipo RegistroVeiculo:
    RegistroVeiculo *registro = malloc(sizeof(RegistroVeiculo));

    // Marcando o campo removido:
    if (registroDoCSVEhRemovido(arquivoCSV))
        registro->removido = '0';
    else
        registro->removido = '1';

    // Lendo e marcando os demais campos:
    char *prefixo = lePrefixoDoCSV(arquivoCSV);
    strcpy(registro->prefixo, prefixo);

    char *data = leDataDoCSV(arquivoCSV);
    strcpy(registro->data, data);
    registro->data[0] = registro->data[0] == '@' ? '\0' : registro->data[0]; // lixos devem começar com '\0'

    registro->quantidadeLugares = leIntDoCSV(arquivoCSV);
    registro->codLinha = leIntDoCSV(arquivoCSV);

    char *modelo = leStringDoCSV(arquivoCSV);
    strcpy(registro->modelo, modelo);
    registro->modelo[0] = strcmp(modelo, "NULO") == 0 ? '\0' : registro->modelo[0];
    registro->tamanhoModelo = strlen(registro->modelo);

    char *categoria = leStringDoCSV(arquivoCSV);
    strcpy(registro->categoria, categoria);
    registro->categoria[0] = strcmp(categoria, "NULO") == 0 ? '\0' : registro->categoria[0];
    registro->tamanhoCategoria = strlen(registro->categoria);

    registro->tamanhoRegistro = 31 + registro->tamanhoModelo + registro->tamanhoCategoria; 

    // Liberando memória alocada para leitura dos campos:
    free(prefixo);
    free(data);
    free(modelo);
    free(categoria);

    return registro;
}

/*
    Escreve os dados de uma estrutura do tipo CabecalhoVeiculo* em um arquivo binário
    @param cabecalho: ponteiro para a região de memória onde o registro de cabeçalho está armazenado 
    @param arquivoBIN: fluxo do arquivo binário em que os dados serão escritos
*/
void escreveCabecalhoVeiculoNoBIN(CabecalhoVeiculo *cabecalho, FILE *arquivoBIN) {
    // Pulando para o início do arquivo binário
    fseek(arquivoBIN, 0, SEEK_SET);
    // Escrevendo os campos do registro de cabeçalho no binário:
    fwrite(&cabecalho->status, 1, 1, arquivoBIN);
    fwrite(&cabecalho->byteProxReg, sizeof(long long), 1, arquivoBIN);
    fwrite(&cabecalho->nroRegistros, sizeof(int), 1, arquivoBIN);
    fwrite(&cabecalho->nroRegRemovidos, sizeof(int), 1, arquivoBIN);
    fwrite(cabecalho->descrevePrefixo, 1, 18, arquivoBIN);
    fwrite(cabecalho->descreveData, 1, 35, arquivoBIN);
    fwrite(cabecalho->descreveLugares, 1, 42, arquivoBIN);
    fwrite(cabecalho->descreveLinha, 1, 26, arquivoBIN);
    fwrite(cabecalho->descreveModelo, 1, 17, arquivoBIN);
    fwrite(cabecalho->descreveCategoria, 1, 20, arquivoBIN);
}

/*
    Escreve os dados de uma estrutura do tipo RegistroVeiculo* em um arquivo binário
    @param registroVeiculo: ponteiro para a região de memória onde o registro de dados está armazenado 
    @param arquivoBIN: fluxo do arquivo binário em que os dados serão escritos
*/
void escreveRegistroVeiculoNoBIN(RegistroVeiculo *registroVeiculo, FILE *arquivoBIN) {
    // Escrevendo os campos do registro de dados no binário:
    fwrite(&registroVeiculo->removido, 1, 1, arquivoBIN);
    fwrite(&registroVeiculo->tamanhoRegistro, sizeof(int), 1, arquivoBIN);
    fwrite(registroVeiculo->prefixo, 1, 5, arquivoBIN);
    fwrite(registroVeiculo->data, 1, 10, arquivoBIN);
    fwrite(&registroVeiculo->quantidadeLugares, sizeof(int), 1, arquivoBIN);
    fwrite(&registroVeiculo->codLinha, sizeof(int), 1, arquivoBIN);
    fwrite(&registroVeiculo->tamanhoModelo, sizeof(int), 1, arquivoBIN);
    fwrite(registroVeiculo->modelo, registroVeiculo->tamanhoModelo, 1, arquivoBIN);
    fwrite(&registroVeiculo->tamanhoCategoria, sizeof(int), 1, arquivoBIN);
    fwrite(registroVeiculo->categoria, registroVeiculo->tamanhoCategoria, 1, arquivoBIN);
}

/*
    Aloca memória e preenche dados uma estrutura do tipo CabecalhoVeiculo a partir de um arquivo binário 
    @param arquivoBIN: fluxo do arquivo binário de onde as informações do registro de cabeçalho serão extraídas
    @return CabecalhoVeiculo* ponteiro para a região de memória em que os dados foram armazenados 
*/
CabecalhoVeiculo *carregaCabecalhoVeiculoDoBIN(FILE *arquivoBIN) {

    // Pulando para o início do arquivo binário
    fseek(arquivoBIN, 0, SEEK_SET);

    // Alocando memória para uma estrutura do tipo CabecalhoVeiculo:
    CabecalhoVeiculo *cabecalho = malloc(sizeof(CabecalhoVeiculo));

    // Lendo os campos do registro de cabeçalho do binário:
    fread(&cabecalho->status, 1, 1, arquivoBIN);
    fread(&cabecalho->byteProxReg, sizeof(long long), 1, arquivoBIN);
    fread(&cabecalho->nroRegistros, sizeof(int), 1, arquivoBIN);
    fread(&cabecalho->nroRegRemovidos, sizeof(int), 1, arquivoBIN);
    fread(cabecalho->descrevePrefixo, 1, 18, arquivoBIN);
    fread(cabecalho->descreveData, 1, 35, arquivoBIN);
    fread(cabecalho->descreveLugares, 1, 42, arquivoBIN);
    fread(cabecalho->descreveLinha, 1, 26, arquivoBIN);
    fread(cabecalho->descreveModelo, 1, 17, arquivoBIN);
    fread(cabecalho->descreveCategoria, 1, 20, arquivoBIN);

    // Finalizando os campos string com '\0':
    cabecalho->descrevePrefixo[18] = '\0';
    cabecalho->descreveData[35] = '\0';
    cabecalho->descreveLugares[42] = '\0';
    cabecalho->descreveLinha[26] = '\0';
    cabecalho->descreveModelo[17] = '\0';
    cabecalho->descreveCategoria[20] = '\0';

    return cabecalho;
}

/*
    Aloca memória e preenche dados uma estrutura do tipo RegistroVeiculo a partir de um arquivo binário 
    @param arquivoBIN: fluxo do arquivo binário de onde as informações do registro de dados serão extraídas
    @return RegistroVeiculo* ponteiro para a região de memória em que os dados foram armazenados 
*/
RegistroVeiculo *carregaRegistroVeiculoDoBIN(FILE *arquivoBIN) {

    // Alocando memória para uma estrutura do tipo RegistroVeiculo:
    RegistroVeiculo *registroVeiculo = malloc(sizeof(RegistroVeiculo));

    fread(&registroVeiculo->removido, 1, 1, arquivoBIN);
    fread(&registroVeiculo->tamanhoRegistro, sizeof(int), 1, arquivoBIN);
    fread(registroVeiculo->prefixo, 5, 1, arquivoBIN);
    fread(registroVeiculo->data, 10, 1, arquivoBIN);
    fread(&registroVeiculo->quantidadeLugares, sizeof(int), 1, arquivoBIN);
    fread(&registroVeiculo->codLinha, sizeof(int), 1, arquivoBIN);
    fread(&registroVeiculo->tamanhoModelo, sizeof(int), 1, arquivoBIN);
    fread(registroVeiculo->modelo, registroVeiculo->tamanhoModelo, 1, arquivoBIN);
    fread(&registroVeiculo->tamanhoCategoria, sizeof(int), 1, arquivoBIN);
    fread(registroVeiculo->categoria, registroVeiculo->tamanhoCategoria, 1, arquivoBIN);

    // Finalizando os campos string com '\0':
    registroVeiculo->prefixo[5] = '\0';
    registroVeiculo->data[10] = '\0';
    registroVeiculo->modelo[registroVeiculo->tamanhoModelo] = '\0';
    registroVeiculo->categoria[registroVeiculo->tamanhoCategoria] = '\0';

    return registroVeiculo;
}
