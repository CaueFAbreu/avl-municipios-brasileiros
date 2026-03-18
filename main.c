#include <stdio.h>
#include "fila.h"

int main() {
    
    Fila *fila_de_registros = criar_fila();

    printf("### Iniciando Registros de Software no INPI ###\n\n");

    RegistroSoftware r1 = {"Sistema de Gestao Academica", "Ana Silva", "Java", 2022};
    RegistroSoftware r2 = {"App de Mobilidade Urbana", "Bruno Costa", "Kotlin", 2023};
    RegistroSoftware r3 = {"Software de Analise de Dados", "Carla Dias", "Python", 2021};
    RegistroSoftware r4 = {"E-commerce de Roupas", "Daniel Farias", "JavaScript", 2023};
    RegistroSoftware r5 = {"Game 2D Plataforma", "Elisa Borges", "C++", 2024};

    inserir_na_fila(fila_de_registros, r1);
    inserir_na_fila(fila_de_registros, r2);
    inserir_na_fila(fila_de_registros, r3);
    inserir_na_fila(fila_de_registros, r4);
    inserir_na_fila(fila_de_registros, r5);

    imprimir_fila(fila_de_registros);

    retirar_da_fila(fila_de_registros);

    printf("\nEstado da fila apos a retirada de um registro:");
    imprimir_fila(fila_de_registros);

    liberar_fila(fila_de_registros);
    int var;
    scanf("%d",&var);

    return 0;
}