#include "leitorCSV.h"


bool ehDelimitador(char caractere) {

    if (caractere == DELIMITADOR_CAMPO || caractere == '\n' || caractere == '\r' || caractere == EOF)
        return true;
    
    return false;
}


bool fimDoArquivoCSV(FILE *stream) {

    char caractereAtual = fgetc(stream);

    if (ehDelimitador(caractereAtual))
        return true;

    fseek(stream, -1, SEEK_CUR);

    return false;
}


char **leCabecalhoCSV(FILE *stream) {

    char **cabecalho = NULL;
    char *campoAtual = NULL;
    char *linha = calloc(256, sizeof(char));
    char *enderecoAtual = linha;
    int totalCampos = 0;

    fscanf(stream, "%[^\n] ", linha);

    if (strlen(linha) <= 1) {
        free(linha);
        return NULL;
    }
    
    while ((campoAtual = strtok(enderecoAtual, ",")) != NULL) {
        cabecalho = realloc(cabecalho, (totalCampos + 1) * sizeof(char *));
        cabecalho[totalCampos] = calloc(strlen(campoAtual) + 1, sizeof(char));
        strcpy(cabecalho[totalCampos++], campoAtual);
        enderecoAtual = NULL;
    }

    free(linha);

    return cabecalho;
}


char *leStringCSV(FILE *stream) {

    char caractereAtual = fgetc(stream);

    while (caractereAtual < 32 || caractereAtual == INDICADOR_CAMPO_REMOVIDO) {
        caractereAtual = fgetc(stream);
        if (caractereAtual == EOF)
            return NULL;
    }

    char *string = calloc(1, sizeof(char));
    int tamanhoString = 0;

    while (!ehDelimitador(caractereAtual)) {
        string = realloc(string, tamanhoString + 2);
        string[tamanhoString++] = caractereAtual;
        caractereAtual = fgetc(stream);
    }

    string[tamanhoString] = '\0';

    return string;
}


int leIntCSV(FILE *stream) {

    char *inteiroAscii = leStringCSV(stream);

    if (inteiroAscii == NULL || !isdigit(inteiroAscii[0])) 
        return -1;
    
    int inteiro = atoi(inteiroAscii);
    free(inteiroAscii);

    return inteiro;
}


long long leLongLongCSV(FILE *stream) {

    char *longlongAscii = leStringCSV(stream);

    if (longlongAscii == NULL || !isdigit(longlongAscii[0]))
        return -1;  
    
    long long longlongNumerico = atoll(longlongAscii);
    free(longlongAscii);

    return longlongNumerico;
}


char leCharCSV(FILE *stream) {

    char *string = leStringCSV(stream);

    if (string == NULL)
        return '\0';

    char caractere = string[0];
    free(string);

    return caractere;
}
