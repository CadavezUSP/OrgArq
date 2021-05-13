#include "funcionalidadesVeiculos.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct CabecalhoVeiculo //cabecalho soh na hr de abrir e fechar 
{
    char status;
    long long int byteProxReg; //ftell
    int nroRegistros; // complementar de Removidos
    int nroRegRemovidos; // complementar de registros
    char descrevePrefixo[18];
    char descreveData [35];
    char descreveLugares[42];
    char descreveLinha[26];
    char descreveModelo[17];
    char descreveCategoria[20];
}CabecalhoVeiculo;

typedef struct RegistroVeiculo
{
    char removido; // eh um char!! '0' ou '1'
    int tamanhoRegistro;
    char prefixo[5]; // nao pode assumir valor nulo e nem se repetir
    char data[10]; // AAAA - MM - DD
    int quantidadeLugares;
    int codLinha;
    int tamanhoModelo;
    char modelo[100];
    int tamanhoCategoria;
    char categoria[100];
}RegistroVeiculo;

char* VerMes(int num){
    char *mes = malloc(15*sizeof(char));
    switch (num)
    {
        case 1:
            mes  = "janeiro";
            break;
        case 2:
            mes  = "fevereiro";
            break;
        case 3:
            mes  = "março";
            break;
        case 4:
            mes  = "abril";
            break;
        case 5:
            mes  = "maio";
            break;
        case 6:
            mes  = "junho";
            break;
        case 7:
            mes  = "julho";
            break;
        case 8:
            mes  = "agosto";
            break;
        case 9:
            mes  = "setembro";
            break;
        case 10:
            mes  = "outubro";
            break;
        case 11:
            mes  = "novembro";
            break;
        case 12:
            mes  = "dezembro";
            break;

        default:
            mes = NULL;
            break;
    }
    return mes;
}

void createTableVeiculos(char *arquivoEntrada, char *arquivoSaida) {

}

/*Funcao: selectFromVeiculos
Descricao: Le os veiculos do arquivo binario e printa na tela os registros
Parâmetros: arquivoEntrada = nome do arquivo de entrada
Variáveis: arquivoBin = arquivo binario que sera aberto para a leitura
           Reg = ponteiro para armazenar as informacoes dos registros
           fimDeArquivo = verifica se é o fim do arquivo
*/
void selectFromVeiculos(char *arquivoEntrada) { //Cadavez
    FILE* arquivoBin = fopen(arquivoEntrada, "rb");
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
    }
    
}


void selectWhereVeiculos(char *arquivoEntrada, char *arquivoSaida) {//Cadavez

}


void insertIntoVeiculos(char *arquivoEntrada, char *arquivoSaida) {

}
