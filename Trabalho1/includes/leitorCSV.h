#ifndef __LEITOR_CSV_H__
    #define __LEITOR_CSV_H__

    #ifndef boolean
        #define boolean
    
        #define bool int
        #define true 1
        #define false 0
    #endif

    #define DELIMITADOR_CAMPO ','
    #define STR_TOK_DELIM ","
    #define INDICADOR_CAMPO_REMOVIDO '*'

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    bool fimDoArquivoCSV(FILE *stream);
    char **leCabecalhoCSV(FILE *stream);
    int leIntCSV(FILE *stream);
    long long leLongLongCSV(FILE *stream);
    char leCharCSV(FILE *stream);
    char *leStringCSV(FILE *stream);

#endif