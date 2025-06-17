//
// Created by bruno on 09/06/25.
//


#ifndef TAREFA_H
#define TAREFA_H

#include "categoria.h"

#define MAX_TAREFAS 10000

#define MAX_T_DESCRICAO 81
#define MAX_T_DATA 9

typedef struct Tarefa{
    int id;
    char descricao[MAX_T_DESCRICAO];
    char data_limite[MAX_T_DATA];
    int prioridade;
    int status;
    categoria *categoria;
}tarefa;

extern tarefa *tarefas[MAX_TAREFAS];
extern int contador_id;

// Adicionar, remover, marcar como concluido, alterar, buscar por palavra chave, listar pendentes ordernados por prioridade e data,
// persistencia em arquivo,

void inicializar_tarefas();

void salvar_tarefas();

void adicionar_tarefa();

void alterar_tarefa();

void remover_tarefa();

void fazer_conclusao();

void desfazer_conclusao();

void listar_pendentes(int desc);

void avisar_prazo();

void buscar_tarefa();

#endif //TAREFA_H
