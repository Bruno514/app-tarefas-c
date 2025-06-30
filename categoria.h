//
// Created by bruno on 09/06/25.
//

#ifndef CATEGORIA_H
#define CATEGORIA_H

#include <stdbool.h>

#define MAX_CATEGORIAS 100
#define MAX_C_DESCRICAO 41

typedef struct Categoria {
    int id;
    char descricao[MAX_C_DESCRICAO];
}categoria;

extern categoria *categorias[MAX_CATEGORIAS];
extern int c_ultimo_id;

// categorizar tarefas (trabalho, escola, saúde, casa, lazer, mercado), opção de adiconar/remover uma categoria, avisar 2 dias em antes ao rodar o programa, persistencia em arquivos

void inicializar_categorias();

void salvar_categorias();

categoria* criar_categoria(int id, char *descricao);

bool adicionar_categoria(categoria *categoria);

bool remover_categoria(int id);

categoria* selecionar_categoria(int id);

#endif //CATEGORIA_H
