#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "municipios.h"

// funcoes auxiliares para AVL
int alt_NO(struct NO* no) {
    if (no == NULL) return -1;
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no) {
    return labs(alt_NO(no->esq) - alt_NO(no->dir));
}

int maior(int x, int y) {
    if (x > y) return x;
    else return y;
}

void RotacaoLL(Arv *A) {
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(alt_NO((*A)->esq), alt_NO((*A)->dir)) + 1;
    B->altura = maior(alt_NO(B->esq), (*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(Arv *A) {
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = *A;
    (*A)->altura = maior(alt_NO((*A)->esq), alt_NO((*A)->dir)) + 1;
    B->altura = maior(alt_NO(B->dir), (*A)->altura) + 1;
    *A = B;
}

void RotacaoLR(Arv *A) {
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(Arv *A) {
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

// funcoes basicas

Arv* criarArvore() {
    Arv* raiz = (Arv*) malloc(sizeof(Arv));
    if (raiz != NULL) *raiz = NULL;
    return raiz;
}

void liberarNo(struct NO* no) {
    if (no == NULL) return;
    liberarNo(no->esq);
    liberarNo(no->dir);
    free(no);
}

void liberarArvore(Arv* raiz) {
    if (raiz == NULL) return;
    liberarNo(*raiz);
    free(raiz);
}

int inserir(Arv* raiz, struct Municipio valor) {
    int res;
    if (*raiz == NULL) {
        struct NO* novo = (struct NO*) malloc(sizeof(struct NO));
        if (novo == NULL) return 0;
        novo->dados = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO* atual = *raiz;
    if (strcmp(valor.nome, atual->dados.nome) < 0) {
        if ((res = inserir(&(atual->esq), valor)) == 1) {
            if (fatorBalanceamento_NO(atual) >= 2) {
                if (strcmp(valor.nome, (*raiz)->esq->dados.nome) < 0) RotacaoLL(raiz);
                else RotacaoLR(raiz);
            }
        }
    } else if (strcmp(valor.nome, atual->dados.nome) > 0) {
        if ((res = inserir(&(atual->dir), valor)) == 1) {
            if (fatorBalanceamento_NO(atual) >= 2) {
                if (strcmp(valor.nome, (*raiz)->dir->dados.nome) > 0) RotacaoRR(raiz);
                else RotacaoRL(raiz);
            }
        }
    } else {
        return 0; 
    }

    atual->altura = maior(alt_NO(atual->esq), alt_NO(atual->dir)) + 1;
    return res;
}

void percorrerEmOrdem(Arv* raiz) {
    if (raiz == NULL || *raiz == NULL) return;
    percorrerEmOrdem(&((*raiz)->esq));
    
    float densidade = (*raiz)->dados.populacao / (*raiz)->dados.area;
    printf("Nome: %s | População: %d | Área: %.2f km2 | Densidade: %.2f hab/km2\n", 
           (*raiz)->dados.nome, (*raiz)->dados.populacao, (*raiz)->dados.area, densidade);
    
    percorrerEmOrdem(&((*raiz)->dir));
}

// funcoes especificas

int contarMunicipios(Arv* raiz) {
    if (raiz == NULL || *raiz == NULL) return 0;
    return (contarMunicipios(&((*raiz)->esq)) + contarMunicipios(&((*raiz)->dir)) + 1);
}

void mostrarPopulacaoMaiorQue(Arv* raiz, int X) {
    if (raiz == NULL || *raiz == NULL) return;
    mostrarPopulacaoMaiorQue(&((*raiz)->esq), X);
    if ((*raiz)->dados.populacao > X) {
        printf("- %s (Pop: %d)\n", (*raiz)->dados.nome, (*raiz)->dados.populacao);
    }
    mostrarPopulacaoMaiorQue(&((*raiz)->dir), X);
}

void mostrarDensidade(Arv* raiz) {
    if (raiz == NULL || *raiz == NULL) return;
    mostrarDensidade(&((*raiz)->esq));
    float densidade = (float)(*raiz)->dados.populacao / (*raiz)->dados.area;
    printf("- %s: %.2f hab/km2\n", (*raiz)->dados.nome, densidade);
    mostrarDensidade(&((*raiz)->dir));
}

float somarArea(Arv* raiz) {
    if (raiz == NULL || *raiz == NULL) return 0;
    return (*raiz)->dados.area + somarArea(&((*raiz)->esq)) + somarArea(&((*raiz)->dir));
}

void exibirEstatisticasArea(Arv* raiz) {
    float areaTotalArv = somarArea(raiz);
    float percentual = (areaTotalArv / 8510000.0) * 100.0;
    printf("Área total cadastrada: %.2f km2\n", areaTotalArv);
    printf("Percentual do território nacional: %.4f%%\n", percentual);
}

void auxiliarMaiorPop(Arv* raiz, struct NO** maiorN) {
    if (raiz == NULL || *raiz == NULL) return;
    auxiliarMaiorPop(&((*raiz)->esq), maiorN);
    if (*maiorN == NULL || (*raiz)->dados.populacao > (*maiorN)->dados.populacao) {
        *maiorN = *raiz;
    }
    auxiliarMaiorPop(&((*raiz)->dir), maiorN);
}

struct Municipio cidadeMaiorPopulacao(Arv* raiz) {
    struct NO* maiorN = NULL;
    auxiliarMaiorPop(raiz, &maiorN);
    if (maiorN != NULL) return maiorN->dados;
    
    struct Municipio vazia = {"", 0.0, 0};
    return vazia;
}

// funcoes extras (bonus)

struct NO* buscarPorNome(Arv* raiz, char* nome) {
    if (raiz == NULL || *raiz == NULL) return NULL;
    if (strcmp(nome, (*raiz)->dados.nome) == 0) return *raiz;
    if (strcmp(nome, (*raiz)->dados.nome) < 0)
        return buscarPorNome(&((*raiz)->esq), nome);
    else
        return buscarPorNome(&((*raiz)->dir), nome);
}

long somarPopulacao(Arv* raiz) {
    if (raiz == NULL || *raiz == NULL) return 0;
    return (*raiz)->dados.populacao + somarPopulacao(&((*raiz)->esq)) + somarPopulacao(&((*raiz)->dir));
}

float calcularMediaPopulacional(Arv* raiz) {
    int total = contarMunicipios(raiz);
    if (total == 0) return 0;
    return (float)somarPopulacao(raiz) / total;
}

struct NO* procuraMenor(struct NO* atual) {
    struct NO* no1 = atual;
    struct NO* no2 = atual->esq;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int removerMunicipio(Arv* raiz, char* nome) {
    if (*raiz == NULL) return 0;
    int res;

    if (strcmp(nome, (*raiz)->dados.nome) < 0) {
        if ((res = removerMunicipio(&(*raiz)->esq, nome)) == 1) {
            if (fatorBalanceamento_NO(*raiz) >= 2) {
                if (alt_NO((*raiz)->dir->esq) <= alt_NO((*raiz)->dir->dir)) RotacaoRR(raiz);
                else RotacaoRL(raiz);
            }
        }
    } else if (strcmp(nome, (*raiz)->dados.nome) > 0) {
        if ((res = removerMunicipio(&(*raiz)->dir, nome)) == 1) {
            if (fatorBalanceamento_NO(*raiz) >= 2) {
                if (alt_NO((*raiz)->esq->dir) <= alt_NO((*raiz)->esq->esq)) RotacaoLL(raiz);
                else RotacaoLR(raiz);
            }
        }
    } else {
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
            struct NO* oldNode = (*raiz);
            if ((*raiz)->esq != NULL) *raiz = (*raiz)->esq;
            else *raiz = (*raiz)->dir;
            free(oldNode);
        } else {
            struct NO* temp = procuraMenor((*raiz)->dir);
            (*raiz)->dados = temp->dados;
            removerMunicipio(&(*raiz)->dir, (*raiz)->dados.nome);
            if (fatorBalanceamento_NO(*raiz) >= 2) {
                if (alt_NO((*raiz)->esq->dir) <= alt_NO((*raiz)->esq->esq)) RotacaoLL(raiz);
                else RotacaoLR(raiz);
            }
        }
        if (*raiz != NULL) (*raiz)->altura = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
        return 1;
    }
    (*raiz)->altura = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
    return res;
}

void carregarDeCSV(Arv* raiz, const char* nomeArquivo) {
    FILE* file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Aviso: Arquivo %s nao encontrado.\n", nomeArquivo);
        return;
    }
    char linha[256];
    int cont = 0;
    while (fgets(linha, sizeof(linha), file)) {
        struct Municipio m;
        char* token = strtok(linha, ",");
        if (token) strcpy(m.nome, token);
        
        token = strtok(NULL, ",");
        if (token) m.area = atof(token);
        
        token = strtok(NULL, ",");
        if (token) m.populacao = atoi(token);
        
        if (inserir(raiz, m)) cont++;
    }
    fclose(file);
    printf("=> %d municipios importados do CSV '%s'!\n", cont, nomeArquivo);
}