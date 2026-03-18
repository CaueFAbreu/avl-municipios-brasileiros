# 🌳 BST Municípios Brasileiros

![C](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=white)
![Data Structure](https://img.shields.io/badge/Estrutura-AVL%20Tree-blue?style=for-the-badge)
![Interface](https://img.shields.io/badge/Interface-Console-lightgrey?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Concluído-brightgreen?style=for-the-badge)

> Implementação de uma **Árvore AVL** em C para armazenar e gerenciar informações sobre municípios brasileiros, com ordenação alfabética por nome e suporte a importação via arquivo CSV.

---

## 📋 Índice

- [Sobre o Projeto](#-sobre-o-projeto)
- [Funcionalidades](#-funcionalidades)
- [Estrutura de Dados](#-estrutura-de-dados)
- [Pré-requisitos](#-pré-requisitos)
- [Como Compilar e Executar](#-como-compilar-e-executar)
- [Como Usar](#-como-usar)
- [Estrutura do Projeto](#-estrutura-do-projeto)
- [Autor](#-autor)

---

## 📖 Sobre o Projeto

Sistema de gerenciamento de municípios implementado em C utilizando uma **Árvore AVL** — variante balanceada da Árvore Binária de Busca (BST). A chave de ordenação é o **nome do município** (ordem alfabética via `strcmp()`). O balanceamento automático garante que a árvore não degenere em lista encadeada mesmo quando os dados são inseridos em ordem alfabética.

---

## ✅ Funcionalidades

**Obrigatórias:**
- [x] Criar e liberar árvore com gerenciamento de memória
- [x] Inserção ordenada pelo nome com balanceamento AVL (rotações LL, RR, LR, RL)
- [x] Listagem em ordem alfabética com todos os dados
- [x] Contagem total de municípios cadastrados
- [x] Exibição de municípios com população acima de um limite (padrão: 100.000 hab.)
- [x] Densidade demográfica de cada município (`população / área`)
- [x] Área total cadastrada e percentual em relação ao território nacional (8.510.000 km²)
- [x] Município com maior população

**Bônus implementados:**
- [x] Busca por nome (O log n graças ao AVL)
- [x] Remoção de município com rebalanceamento
- [x] Média populacional
- [x] Importação de dados via arquivo `.csv`
- [x] Carga inicial com 10 municípios de Minas Gerais

---

## 🏗️ Estrutura de Dados

```c
struct Municipio {
    char nome[100];
    float area;       // em km²
    int populacao;
};

struct NO {
    struct Municipio dados;
    int altura;       // campo para balanceamento AVL
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO* Arv;
```

A ordenação é feita com `strcmp()` sobre o campo `nome`. O campo `altura` é mantido atualizado a cada inserção/remoção para garantir o balanceamento da AVL.

---

## ⚙️ Pré-requisitos

- Compilador **GCC** (ou compatível com C99+)

```bash
gcc --version
```

---

## 🚀 Como Compilar e Executar

**1. Clone o repositório:**
```bash
git clone https://github.com/CaueFAbreu/bst-municipios-brasileiros.git
cd bst-municipios-brasileiros
```

**2. Compile:**
```bash
gcc main.c municipios.c -o sistema_municipios
```

**3. Execute:**
```bash
./sistema_municipios
```

> 💡 Para usar a importação via CSV, certifique-se de que o arquivo `municipios.csv` está no mesmo diretório do executável.

---

## 🖥️ Como Usar

O sistema apresenta um menu interativo com as seguintes opções:

| Opção | Ação |
|---|---|
| `1` | Inserir município manualmente (nome, área, população) |
| `2` | Carregar 10 municípios de Minas Gerais (carga inicial) |
| `3` | Importar dados de arquivo `.csv` |
| `4` | Listar todos os municípios em ordem alfabética |
| `5` | Buscar município pelo nome |
| `6` | Remover município |
| `7` | Exibir estatísticas (total, área, média, maior população) |
| `8` | Sair |

**Formato do CSV** (`municipios.csv`):
```
Nome,Area,Populacao
Sao Paulo,1521.110,11451245
Rio de Janeiro,1200.329,6211423
```

---

## 📁 Estrutura do Projeto

```
📦 bst-municipios-brasileiros
 ┣ 📄 main.c           # Menu interativo e ponto de entrada
 ┣ 📄 municipios.c     # Implementação de todas as funções da AVL
 ┣ 📄 municipios.h     # Definição das structs e protótipos de funções
 ┗ 📄 municipios.csv   # Base de dados com 10 capitais brasileiras
```

---

## 👤 Autor

**Cauê F. Abreu**

[![GitHub](https://img.shields.io/badge/GitHub-CaueFAbreu-181717?style=flat&logo=github)](https://github.com/CaueFAbreu)

---

<p align="center">Feito com ☕ e C</p>
