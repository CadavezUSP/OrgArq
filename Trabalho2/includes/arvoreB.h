#ifndef __ARVORE_B__
    #define __ARVORE_B__

    #define TAM_PAGINA 77
    #define ORDEM_ARVORE 5
    #define VALOR_NULO -1

    typedef struct {
        char status; // '0' = inconsistente e '1' = consistente
        int noRaiz;
        int RRNproxNo;
    }RegistroCabecalhoAB;

    typedef struct {
        int chave;
        long long byteOffset;
    }RegistroDadosAB;

    typedef struct {
        char folha; // '0' = nao e '1' = sim
        int nroChavesIndexadas;
        int RRNdoNo;
        RegistroDadosAB registros[(ORDEM_ARVORE-1)];
        int filhos[ORDEM_ARVORE];
    }No;

#endif