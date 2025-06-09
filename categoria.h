//
// Created by bruno on 09/06/25.
//

#ifndef CATEGORIA_H
#define CATEGORIA_H

#define MAX_CATEGORIAS 100
#define MAX_DESCRICAO 41

typedef struct Categoria {
    char descricao[MAX_DESCRICAO];
}categoria;

typedef categoria *p_categoria;

extern p_categoria categorias[];

// categorizar tarefas (trabalho, escola, saúde, casa, lazer, mercado), opção de adiconar/remover uma categoria, avisar 2 dias em antes ao rodar o programa, persistencia em arquivos

void adicionarCategoria();

void removerCategoria();

#endif //CATEGORIA_H
