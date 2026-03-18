#ifndef MUNICIPIOS_H
#define MUNICIPIOS_H

// --- sctruct do municipio
struct Municipio {
    char nome[100];
    float area; 
    int populacao;
};

struct NO {
    struct Municipio dados;
    int altura; // para AVL
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO* Arv;

// funcoes basicas
Arv* criarArvore();
void liberarArvore(Arv* raiz);
int inserir(Arv* raiz, struct Municipio valor);
void percorrerEmOrdem(Arv* raiz);

// funcoes especificas
int contarMunicipios(Arv* raiz);
void mostrarPopulacaoMaiorQue(Arv* raiz, int X);
void mostrarDensidade(Arv* raiz);
float somarArea(Arv* raiz);
void exibirEstatisticasArea(Arv* raiz);
struct Municipio cidadeMaiorPopulacao(Arv* raiz);

// funcoes extras(bonus)
struct NO* buscarPorNome(Arv* raiz, char* nome);
float calcularMediaPopulacional(Arv* raiz);
int removerMunicipio(Arv* raiz, char* nome);
void carregarDeCSV(Arv* raiz, const char* nomeArquivo);

#endif