#include "arvoreB.h"

/*
Descrição: Aloca espaço na memória para uma estrutura do tipo RegistroDadosAB, 
inicializando o campo byteOffset com VALOR_NULO (-1) 
@param chave: chave que será preenchida no campo chave da estrutura alocada
@return um ponteiro para a região de memória em que o registro de dados foi alocado
*/
RegistroDadosAB *alocaRegistroDadosAB(int chave) {

    RegistroDadosAB *registroDados = malloc(sizeof(RegistroDadosAB));

    registroDados->chave = chave;
    registroDados->byteOffset = VALOR_NULO;

    return registroDados;
}

/*
Descrição: Aloca espaço na memória para um vetor de ponteiros para estruturas do tipo RegistroDadosAB, 
inicializando os campos de cada registro de dados com valores nulos pela função alocaRegistroDadosAB
@param nroRegistros: tamanho do vetor a ser alocado
@return um ponteiro para a região de memória em que o vetor foi alocado
*/
RegistroDadosAB **alocaVetorRegistroDadosAB(int nroRegistros) {

    RegistroDadosAB **vetor = malloc(nroRegistros * sizeof(RegistroDadosAB *));

    for (int i = 0; i < nroRegistros; i++)
        vetor[i] = alocaRegistroDadosAB(VALOR_NULO);
    
    return vetor;
}

/*
Descrição: Aloca espaço na memória para uma estrutura do tipo NoDadosAB, 
inicializando os campos folha com '1' (verdadeiro), nroChavesIndexadas com 0,  
RRNdoNo com VALOR_NULO (-1), registros com ponteiros preenchidos pela função 
alocaRegistoDados e filhos com VALOR_NULO
@return Um ponteiro para a região de memória em que o no de dados foi alocado
*/
NoDadosAB *alocaNoDadosAB(void) {

    NoDadosAB *noDados = malloc(sizeof(NoDadosAB));

    noDados->folha = '1';
    noDados->nroChavesIndexadas = 0;
    noDados->RRNdoNo = VALOR_NULO;

    for (int i = 0; i < ORDEM_ARVORE - 1; i++)
        noDados->registros[i] = alocaRegistroDadosAB(VALOR_NULO);

    memset(noDados->filhos, VALOR_NULO, (ORDEM_ARVORE * sizeof(int)));

    return noDados;
}

/*
Descrição: Aloca espaço na memória para uma estrutura do tipo NoCabecalhoAB, 
inicializando os campos RRNraiz com VALOR_NULO (-1), RRNproxNo com 0, status 
com '0' (arquivo inconsistente) e lixo com 68 bytes '\@' 
@return Um ponteiro para a região de memória em que o no de cabecalho foi alocado
*/
NoCabecalhoAB *alocaNoCabecalhoAB(void) {

    NoCabecalhoAB *noCabecalho = malloc(sizeof(NoCabecalhoAB));

    noCabecalho->RRNraiz = VALOR_NULO;
    noCabecalho->RRNproxNo = 0;
    noCabecalho->status = '0';
    memset(noCabecalho->lixo, '@', 68);

    return noCabecalho;
}

/*
Descrição: Aloca espaço na memória para uma estrutura do tipo ChavePromovida, 
inicializando todos os seus campos com VALOR_NULO (-1)
@return Um ponteiro para a região de memória em que o a chave promovida foi alocada
*/
ChavePromovida *alocaChavePromovidaAB(void) {

    ChavePromovida *chavePromovida = malloc(sizeof(ChavePromovida));

    chavePromovida->chave = VALOR_NULO;
    chavePromovida->byteOffset = VALOR_NULO;
    chavePromovida->RRNfilhoDireita = VALOR_NULO;

    return chavePromovida;
}

/*
Descrição: Verifica se o arquivo passado por parâmetro é vazio
@param arquivoIndice: arquivo de índice que será verificado
@return int 1 se verdadeiro ou 0 se falso
*/
bool arquivoIndiceEhVazio(FILE *arquivoIndice) {

    char byteAtual;
    fread(&byteAtual, 1, 1, arquivoIndice);

    if (feof(arquivoIndice))
        return true;

    fseek(arquivoIndice, -1, SEEK_CUR);
    return false;
}

/*
Descrição: Obtém o nó de cabeçalho de um arquivo de índice
@param arquivoIndice: arquivo de índice do qual o cabeçalho será extraído
@return Um ponteiro para a região de memória em que o cabeçalho foi armazenado 
*/
NoCabecalhoAB *carregaNoCabecalhoDaAB(FILE *arquivoIndice) {

    NoCabecalhoAB *noCabecalho = alocaNoCabecalhoAB();

    fseek(arquivoIndice, 0, SEEK_SET);

    if (!arquivoIndiceEhVazio(arquivoIndice)) {
        fread(&noCabecalho->status, 1, 1, arquivoIndice);
        fread(&noCabecalho->RRNraiz, sizeof(int), 1, arquivoIndice);
        fread(&noCabecalho->RRNproxNo, sizeof(int), 1, arquivoIndice);
    }

    return noCabecalho;
}

/*
Descrição: Obtém um nó de dados de um arquivo de índice a partir de seu RRN
@param arquivoIndice: arquivo de índice do qual o no de dados será extraído
@param rrn: rrn do no de dados no arquivo de índice 
@return Um ponteiro para a região de memória em que o no de dados foi armazenado 
*/
NoDadosAB *carregaNoDadosDaAB(FILE *arquivoIndice, int rrn) {

    NoDadosAB *noDados = alocaNoDadosAB();

    fseek(arquivoIndice, (rrn + 1) * TAM_PAGINA, SEEK_SET); // (rrn + 1) por conta do no de cabeçalho

    fread(&noDados->folha, 1, 1, arquivoIndice);
    fread(&noDados->nroChavesIndexadas, sizeof(int), 1, arquivoIndice);
    fread(&noDados->RRNdoNo, sizeof(int), 1, arquivoIndice);
    fread(&noDados->filhos[0], sizeof(int), 1, arquivoIndice);

    for (int i = 0; i < ORDEM_ARVORE - 1; i++) {
        fread(&noDados->registros[i]->chave, sizeof(int), 1, arquivoIndice);
        fread(&noDados->registros[i]->byteOffset, sizeof(long long), 1, arquivoIndice);
        fread(&noDados->filhos[i+1], sizeof(int), 1, arquivoIndice);
    }

    return noDados;
}

/*
Descrição: Escreve o nó de cabeçalho em seu arquivo de índice
@param arquivoIndice: arquivo de índice em que o nó de cabeçalho será escrito 
@param noCabecalho: no de cabecalho a ser escrito 
*/
void escreveNoCabecalhoNaAB(FILE *arquivoIndice, NoCabecalhoAB *noCabecalho) {

    fseek(arquivoIndice, 0, SEEK_SET);

    fwrite(&noCabecalho->status, 1, 1, arquivoIndice);
    fwrite(&noCabecalho->RRNraiz, sizeof(int), 1, arquivoIndice);
    fwrite(&noCabecalho->RRNproxNo, sizeof(int), 1, arquivoIndice);
    fwrite(noCabecalho->lixo, 1, 68, arquivoIndice);
}

/*
Descrição: Escreve um nó de dados em um arquivo de índice
@param arquivoIndice: arquivo de índice em que o nó de dados será escrito 
@param noCabecalho: no de dados a ser escrito 
*/
void escreveNoDadosNaAB(FILE *arquivoIndice, NoDadosAB *noDados) {

    fseek(arquivoIndice, (noDados->RRNdoNo + 1) * TAM_PAGINA, SEEK_SET); // (RRNdoNo + 1) por conta do no de cabeçalho

    // Escrevendo campos folha, nroChavesIndexada, RRNdoNo e primeiro filho:
    fwrite(&noDados->folha, 1, 1, arquivoIndice);
    fwrite(&noDados->nroChavesIndexadas, sizeof(int), 1, arquivoIndice);
    fwrite(&noDados->RRNdoNo, sizeof(int), 1, arquivoIndice);
    fwrite(&noDados->filhos[0], sizeof(int), 1, arquivoIndice);

    // Escrevendo chaves, bytes offsets e filhos da direita não nulos:
    for (int i = 0; i < noDados->nroChavesIndexadas; i++) {
        fwrite(&noDados->registros[i]->chave, sizeof(int), 1, arquivoIndice);
        fwrite(&noDados->registros[i]->byteOffset, sizeof(long long), 1, arquivoIndice);
        fwrite(&noDados->filhos[i+1], sizeof(int), 1, arquivoIndice);
    }

    int chaveNula = VALOR_NULO, filhoNulo = VALOR_NULO;
    long long byteOffsetNulo = VALOR_NULO;

    // Escrevendo chaves, bytes offsets e filhos da direita nulos (não preenchidos):
    for (int i = noDados->nroChavesIndexadas; i < ORDEM_ARVORE - 1; i++) {
        fwrite(&chaveNula, sizeof(int), 1, arquivoIndice);
        fwrite(&byteOffsetNulo, sizeof(long long), 1, arquivoIndice);
        fwrite(&filhoNulo, sizeof(int), 1, arquivoIndice);
    }
}


void imprimeNoCabecalho(NoCabecalhoAB *noCabecalho) {
    printf("Status: %c\n", noCabecalho->status);
    printf("NoRaiz: %d\n", noCabecalho->RRNraiz);
    printf("Rrn prox no: %d\n", noCabecalho->RRNproxNo);
    printf("Lixo: ");
    for (int i = 0; i < 68; i ++)
        printf("%c", noCabecalho->lixo[i]);
}

void imprimeNo(NoDadosAB *noDados) {
    printf("RRN: %d | Folha: %c | NroChaves: %d | %d ", noDados->RRNdoNo, noDados->folha, noDados->nroChavesIndexadas, noDados->filhos[0]);
    for (int i = 0; i < ORDEM_ARVORE - 1; i++) {
        printf("[%d] %d ", noDados->registros[i]->chave, noDados->filhos[i+1]);
    }
}

void imprimeArvore(FILE *arquivoIndice) {
    NoCabecalhoAB *cabecalho = carregaNoCabecalhoDaAB(arquivoIndice);
    imprimeNoCabecalho(cabecalho);
    printf("\n");
    int rrnAtual = 0;
    while (!fimDoArquivoBIN(arquivoIndice)) {
        NoDadosAB *dados = carregaNoDadosDaAB(arquivoIndice, rrnAtual++);
        imprimeNo(dados);
        printf("\n");
    }
    printf("\n");
}

//void split(FILE *arquivoIndice, int chaveInserida, long long byteOffset,
void split(FILE *arquivoIndice, NoDadosAB *paginaAtual, NoDadosAB *paginaNova, ChavePromovida *chavePromovida) {

    ////printf("Declarando copias\n");
    RegistroDadosAB **copiaRegistros = alocaVetorRegistroDadosAB(ORDEM_ARVORE);
    int copiaFilhos[(ORDEM_ARVORE+1)];
    memset(copiaFilhos, VALOR_NULO, (ORDEM_ARVORE+1) * sizeof(int));

    ////printf("Copiando 1\n");
    copiaFilhos[0] = paginaAtual->filhos[0];
    for (int i = 0; i < ORDEM_ARVORE - 1; i++) {
        copiaRegistros[i]->chave = paginaAtual->registros[i]->chave;
        copiaRegistros[i]->byteOffset = paginaAtual->registros[i]->byteOffset;
        copiaFilhos[i+1] = paginaAtual->filhos[i+1];
    }

    ////printf("Encontrando idx insercao\n");
    int indiceInsercao;
    for (indiceInsercao = 0; indiceInsercao < ORDEM_ARVORE - 1; indiceInsercao++) {
        //if (chavePromovida->chave < copiaRegistros[indiceInsercao]->chave)
        if (chavePromovida->chave < copiaRegistros[indiceInsercao]->chave)
            break;
    }

    ////printf("shiftando\n");
    for (int i = (ORDEM_ARVORE-1); i > indiceInsercao; i--) {
        copiaRegistros[i]->chave = copiaRegistros[i-1]->chave;
        copiaRegistros[i]->byteOffset = copiaRegistros[i-1]->byteOffset;
        copiaFilhos[i+1] = copiaFilhos[i];
    }

    ////printf("Atribuindo chave\n");
    copiaRegistros[indiceInsercao]->chave = chavePromovida->chave;
    copiaRegistros[indiceInsercao]->byteOffset = chavePromovida->byteOffset;
    copiaFilhos[indiceInsercao+1] = chavePromovida->RRNfilhoDireita;

    //printf("Na copia, o indice de cp é %d e seu valor é %d\n", indiceInsercao, chavePromovida->chave);

    //printf("Preenchendo promovida\n");
    chavePromovida->chave = copiaRegistros[(ORDEM_ARVORE/2)]->chave;
    chavePromovida->byteOffset = copiaRegistros[(ORDEM_ARVORE/2)]->byteOffset;
    chavePromovida->RRNfilhoDireita = paginaNova->RRNdoNo;

    //printf("Copia metade 1\n");
    paginaAtual->filhos[0] = copiaFilhos[0];
    for (int i = 0; i < (ORDEM_ARVORE/2); i++) {
        paginaAtual->registros[i]->chave = copiaRegistros[i]->chave;
        paginaAtual->registros[i]->byteOffset = copiaRegistros[i]->byteOffset;
        paginaAtual->filhos[i+1] = copiaFilhos[i+1];
    }

    //printf("Copia metade 2\n");
    paginaNova->filhos[0] = copiaFilhos[(ORDEM_ARVORE/2+1)];
    for (int i = (ORDEM_ARVORE/2+1), j = 0; i < (ORDEM_ARVORE); i++, j++) {
        paginaNova->registros[j]->chave = copiaRegistros[i]->chave;
        paginaNova->registros[j]->byteOffset = copiaRegistros[i]->byteOffset;
        paginaNova->filhos[j+1] = copiaFilhos[i+1];
    }

    //printf("Atribuindo nroChavesIndexadas\n");
    paginaAtual->nroChavesIndexadas = (ORDEM_ARVORE/2);
    paginaNova->nroChavesIndexadas = (ORDEM_ARVORE/2);
}


bool insereRegistroDadosNaABrec(FILE *arquivoIndice, NoCabecalhoAB *noCabecalho, int RRNatual,
                                int chaveInserida, long long byteOffset, ChavePromovida *chavePromovida)
{
    if (RRNatual == VALOR_NULO) {
        chavePromovida->chave = chaveInserida;
        chavePromovida->byteOffset = byteOffset;
        chavePromovida->RRNfilhoDireita = VALOR_NULO;
        return true;
    }

    NoDadosAB *noAtual = carregaNoDadosDaAB(arquivoIndice, RRNatual);

    int indiceInsercao;
    for (indiceInsercao = 0; indiceInsercao < noAtual->nroChavesIndexadas; indiceInsercao++) {
        int chaveAtual = noAtual->registros[indiceInsercao]->chave;
        if (chaveInserida < chaveAtual)
            break;
    }

    bool promocao = insereRegistroDadosNaABrec(arquivoIndice, noCabecalho, noAtual->filhos[indiceInsercao],
                                            chaveInserida, byteOffset, chavePromovida);

    // Se houver promoção a ser feita, não há mais nada a ser feito e a função deve retornar falso ao nível anterior:
    if (!promocao)
        return false;
    
    if (noAtual->nroChavesIndexadas < (ORDEM_ARVORE - 1)) {
        for (int i = noAtual->nroChavesIndexadas; i > indiceInsercao; i--) {
            noAtual->registros[i]->chave = noAtual->registros[i-1]->chave;
            noAtual->registros[i]->byteOffset = noAtual->registros[i-1]->byteOffset;
            noAtual->filhos[i+1] = noAtual->filhos[i];
        }
        noAtual->registros[indiceInsercao]->chave = chavePromovida->chave;
        noAtual->registros[indiceInsercao]->byteOffset = chavePromovida->byteOffset;
        noAtual->filhos[indiceInsercao+1] = chavePromovida->RRNfilhoDireita;
        noAtual->nroChavesIndexadas += 1;

        noAtual->folha = noAtual->filhos[0] == VALOR_NULO ? '1' : '0';

        escreveNoDadosNaAB(arquivoIndice, noAtual);
        //printf("Coube %d no no de rrn %d\n", chaveInserida, RRNatual);
        return false;
    }

    NoDadosAB *noNovo = alocaNoDadosAB();
    noNovo->RRNdoNo = noCabecalho->RRNproxNo++;
    noNovo->folha = noAtual->folha;

    //insereRegistroDadosNaABsplit(arquivoIndice, chaveInserida, byteOffset, noAtual, noNovo, chavePromovida);
    split(arquivoIndice, noAtual, noNovo, chavePromovida);

    escreveNoDadosNaAB(arquivoIndice, noAtual);
    escreveNoDadosNaAB(arquivoIndice, noNovo);

    //printf("Fiz um split para inserir %d. Rrn atual eh %d e o novo %d.\n", chaveInserida, RRNatual, noNovo->RRNdoNo);

    return true;
}

void insereRegistroDadosNaAB(FILE *arquivoIndice, NoCabecalhoAB *noCabecalho, int chaveInserida, long long byteOffset) {

    if (noCabecalho->RRNraiz == VALOR_NULO) {
        NoDadosAB *primeiraRaiz = alocaNoDadosAB();
        primeiraRaiz->nroChavesIndexadas += 1;
        primeiraRaiz->RRNdoNo = noCabecalho->RRNproxNo++;
        primeiraRaiz->registros[0]->chave = chaveInserida;
        primeiraRaiz->registros[0]->byteOffset = byteOffset;
        noCabecalho->RRNraiz = primeiraRaiz->RRNdoNo;
        escreveNoCabecalhoNaAB(arquivoIndice, noCabecalho);
        escreveNoDadosNaAB(arquivoIndice, primeiraRaiz);
        //printf("Inseri a primeira raiz\n");
        //imprimeArvore(arquivoIndice);
        return;
    }

    ChavePromovida *chavePromovida = alocaChavePromovidaAB();

    bool promocao = insereRegistroDadosNaABrec(arquivoIndice, noCabecalho, noCabecalho->RRNraiz,
                                               chaveInserida, byteOffset, chavePromovida);

    if (promocao) {
        NoDadosAB *novoNoRaiz = alocaNoDadosAB();
        novoNoRaiz->folha = '0';
        novoNoRaiz->nroChavesIndexadas = 1;
        novoNoRaiz->RRNdoNo = noCabecalho->RRNproxNo++;
        //printf("A raiz foi trocada, seu novo RRN vale %d\n", novoNoRaiz->RRNdoNo);
        novoNoRaiz->registros[0]->chave = chavePromovida->chave;
        novoNoRaiz->registros[0]->byteOffset = chavePromovida->byteOffset;
        novoNoRaiz->filhos[0] = noCabecalho->RRNraiz;
        novoNoRaiz->filhos[1] = chavePromovida->RRNfilhoDireita;
        noCabecalho->RRNraiz = novoNoRaiz->RRNdoNo;
        escreveNoCabecalhoNaAB(arquivoIndice, noCabecalho);
        escreveNoDadosNaAB(arquivoIndice, novoNoRaiz);
    }

    //imprimeArvore(arquivoIndice);
}


int buscaRegistroDadosNaAB(FILE *arquivoIndice, NoCabecalhoAB *cabecalho, int chaveBuscada);