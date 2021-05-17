#include "funcionalidadesVeiculos.h"

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

/*Funcao: selectFromVeiculos
Descricao: Le os veiculos do arquivo binario e printa na tela os registros
Parâmetros: arquivoEntrada = nome do arquivo de entrada
Variáveis: arquivoBin = arquivo binario que sera aberto para a leitura
           Reg = ponteiro para armazenar as informacoes dos registros
           fimDeArquivo = verifica se é o fim do arquivo
*/
void selectFromVeiculos(char *arquivoEntrada) { //Cadavez
/*    FILE* arquivoBin = fopen(arquivoEntrada, "rb");
    RegistroVeiculo *Reg;
    char fimDeArquivo=0;
    fseek(arquivoBin, sizeof(CabecalhoVeiculo), SEEK_SET);
    fread(&fimDeArquivo, sizeof(char), 1, arquivoBin);
    while (fimDeArquivo != -1)
    {
        Reg = malloc(sizeof(RegistroVeiculo));
        fseek(arquivoBin, -1, SEEK_CUR);
        fread(&Reg->removido, sizeof(Reg->removido), 1, arquivoBin);
        fread(&Reg->tamanhoRegistro, sizeof(Reg->tamanhoRegistro), 1, arquivoBin);
        if (Reg->removido == '1'){
            fseek(arquivoBin, Reg->tamanhoRegistro, SEEK_CUR);
        }
        else{
            fread(&Reg->prefixo, sizeof(Reg->prefixo), 1, arquivoBin);
            fread(&Reg->data, sizeof(Reg->data), 1, arquivoBin);
            fread(&Reg->quantidadeLugares, sizeof(Reg->quantidadeLugares), 1, arquivoBin);
            fread(&Reg->codLinha, sizeof(Reg->codLinha), 1, arquivoBin);
            fread(&Reg->tamanhoModelo, sizeof(Reg->tamanhoModelo), 1, arquivoBin);
            if (Reg->tamanhoModelo == 0) {
                fread(&Reg->modelo, sizeof(char), 1, arquivoBin);
                fseek(arquivoBin, 99, SEEK_CUR);
            }
            else{
                fread(&Reg->modelo, sizeof(char), Reg->tamanhoModelo, arquivoBin);
                fseek(arquivoBin, 100 - Reg->tamanhoModelo, SEEK_CUR);
            }
            fread(&Reg->tamanhoCategoria, sizeof(Reg->tamanhoCategoria), 1, arquivoBin);
            if (Reg->tamanhoCategoria == 0) {
                fread(&Reg->categoria, sizeof(char), 1, arquivoBin);
                fseek(arquivoBin, 99, SEEK_CUR);
            }
            else{
                fread(&Reg->categoria, sizeof(char), Reg->tamanhoModelo, arquivoBin);
                fseek(arquivoBin, 100 - Reg->tamanhoCategoria, SEEK_CUR);
            }
            fread(&Reg->categoria, sizeof(char), Reg->tamanhoCategoria, arquivoBin);

            // impressao na tela e verificação de arquivo nulo
            printf("Prefixo do veiculo:");
            for(int i=0;i<5;i++) printf("%c", Reg->prefixo[i]);
            printf("\nModelo do veiculo: ");
            if (Reg->modelo[0] != '\0') printf("%s\n", Reg->modelo);
            else printf("campo com  valor  nulo\n");
            printf ("Categoria do veiculo: ");
            if (Reg->categoria[0] != '\0') printf("%s\n", Reg->categoria);
            else printf("campo com  valor  nulo\n");
            printf("Data de entrada do veiculona frota: ");
            if (Reg->data[0] != '\0'){
                int ano = atoi (Reg->data);
                int auxMes = atoi (Reg->data+5);
                int dia = atoi (Reg->data+8);
                char *mes = VerMes(auxMes);
                printf("%d de %s de %d\n", dia, mes, ano);
            }
            else printf("campo com  valor  nulo\n");
            printf("Quantidade de lugares sentados disponiveis: ");
            if (Reg->quantidadeLugares != -1){
                printf ("%d", Reg->quantidadeLugares);
            }
            else printf("campo com  valor  nulo\n");
        }
        fread(&fimDeArquivo, sizeof(char), 1, SEEK_CUR);
        printf("\n");
        free (Reg);
    }*/
}

void selectWhereVeiculos(char *arquivoEntrada, char *campo, char *valor) {//Cadavez

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
