//
// Created by bruno on 09/06/25.
//

#ifndef CATEGORIA_H
#define CATEGORIA_H

#define MAX_CATEGORIAS 100
#define MAX_C_DESCRICAO 41

typedef struct Categoria {
    char descricao[MAX_C_DESCRICAO];
}categoria;

extern categoria *categorias[MAX_CATEGORIAS];

// categorizar tarefas (trabalho, escola, saúde, casa, lazer, mercado), opção de adiconar/remover uma categoria, avisar 2 dias em antes ao rodar o programa, persistencia em arquivos

void inicializar_categorias();

void adicionar_categoria();

int listar_categorias();

void remover_categoria();

categoria* selecionar_categoria();

#endif //CATEGORIA_H
