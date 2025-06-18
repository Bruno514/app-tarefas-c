//
// Created by bruno on 09/06/25.
//

#include "categoria.h"
#include "utilidades.h"

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

categoria *categorias[MAX_CATEGORIAS];

void inicializar_categorias() {
    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        categorias[i] = NULL;
    }
}

void adicionar_categoria() {
    int posicao = -1;

    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        if (categorias[i] == NULL) {
            posicao = i;
            break;
        }
    }

    categoria *categoria = malloc(sizeof(categoria));

    printf("Informe a descrição da categoria: ");
    ler_string(categoria->descricao, MAX_C_DESCRICAO);

    if (posicao != -1) {
        categorias[posicao] = categoria;

        printf("Categoria adicionada com sucesso!\n\n");
    } else {
        printf("Não há espaço para mais categorias\n\n");
    }

    esperar_para_continuar();
}

void remover_categoria() {
    printf("Continuar...\n");
    getchar();
}

int listar_categorias() {
    printf("Categorias disponíveis: \n\n");
    for (int j = 0; j < MAX_CATEGORIAS; j++) {
        if (categorias[j] == NULL) {
            if (j == 0) {
                printf("Não há categorias\n");
                return 0;
            }

            break;
        }

        printf("%d - ", j + 1);
        puts(categorias[j]->descricao);
        printf("\n");
    }

    esperar_para_continuar();

    return 1;
}

categoria *selecionar_categoria(int index) {
    for (int j = 0; j < MAX_CATEGORIAS; j++) {
        if (categorias[j] == NULL) {
            return NULL;
        }
        if (index == j) {
            return categorias[j];
        }
    }

    return NULL;
}
