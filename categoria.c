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
    FILE *stream = fopen("categorias.csv", "a+");

    char linha[256];
    int id = 0;
    char descricao[MAX_C_DESCRICAO];

    while (fgets(linha,256, stream) != NULL) {
        id = atoi(strtok(linha, ","));
        if (id > c_ultimo_id) {
            c_ultimo_id = id;
        }

        strcpy(descricao, strtok(NULL, ","));
        descricao[strlen(descricao) - 1] = '\0';
        strtok(NULL, ",");

        categoria *categoria = criar_categoria(id, descricao);
        adicionar_categoria(categoria);
    }

    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        if (categorias[i] != NULL) continue;
        categorias[i] = NULL;
    }

    fclose(stream);
}

void salvar_categorias() {
    FILE *stream = fopen("categorias.csv", "w");

    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        if (categorias[i] == NULL) continue;
        categoria *categoria = categorias[i];

        fprintf(stream, "%d,%s\n", categoria->id, categoria->descricao);
    }

    fclose(stream);
}

categoria* criar_categoria(int id, char *descricao) {
    categoria *categoria = malloc(sizeof(categoria));

    categoria->id = id == -1 ? ++c_ultimo_id : id;
    strcpy(categoria->descricao, descricao);

    return categoria;
}

bool adicionar_categoria(categoria *categoria) {
    int posicao = -1;
    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        if (categorias[i] == NULL) {
            posicao = i;
            break;
        }
    }

    if  (posicao == -1) return false;

    categorias[posicao] = categoria;

    return true;
}

bool remover_categoria(int id) {
    int removeu = 0;

    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        if (categorias[i] == NULL) {
            continue;
        }

        if (categorias[i]->id == id) {
            categorias[i] = NULL;
            removeu = 1;
            break;
        }
    }

    if (!removeu) {
        return false;
    }

    return true;
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
