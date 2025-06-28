//
// Created by bruno on 09/06/25.
//

#include "categoria.h"
#include "utilidades.h"

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

categoria *categorias[MAX_CATEGORIAS];

int c_ultimo_id = 0;

void inicializar_categorias() {
    FILE *stream = fopen("/home/bruno/categorias.csv", "a+");

    char linha[256];
    int categorias_contador = 1;

    while (fgets(linha,256, stream) != NULL) {
        categoria *categoria = malloc(sizeof(categoria));

        categoria->id = atoi(strtok(linha, ","));
        if (categoria->id >c_ultimo_id) {
            c_ultimo_id = categoria->id;
        }

        strcpy(categoria->descricao, strtok(NULL, ","));
        strtok(NULL, ",");

        categorias[categorias_contador++] = categoria;
    }

    for (; categorias_contador < MAX_CATEGORIAS; categorias_contador++) {
        categorias[categorias_contador] = NULL;
    }

    fclose(stream);
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

    categoria->id = ++c_ultimo_id;

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
    int id;
    int removeu = 0;

    printf("Digite o numero da categoria que deseja remover: ");
    scanf("%d", &id);

    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        if (categorias[i] == NULL) {
            continue;
        }

        if (i + 1 == id) {
            categorias[i] = NULL;
            removeu = 1;
            break;
        }
    }

    if (!removeu) {
        printf("Categoria não foi encontrada\n\n");
    }

    esperar_para_continuar();
}

int listar_categorias() {
    int tem_categorias = 0;

    printf("Categorias disponíveis: \n\n");

    for (int j = 0; j < MAX_CATEGORIAS; j++) {
        if (categorias[j] == NULL) {
            continue;
        }

        tem_categorias = 1;

        printf("%d - ", categorias[j]->id);
        puts(categorias[j]->descricao);
        printf("\n");
    }

    if (!tem_categorias) {
        printf("Não há categorias\n");
    }

    esperar_para_continuar();

    return 1;
}

categoria *selecionar_categoria(int id) {
    for (int j = 0; j < MAX_CATEGORIAS; j++) {
        if (categorias[j] == NULL) {
            continue;
        }

        if (id == categorias[j]->id) {
            return categorias[j];
        }
    }

    return NULL;
}
