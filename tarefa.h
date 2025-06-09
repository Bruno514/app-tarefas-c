//
// Created by bruno on 09/06/25.
//


#ifndef TAREFA_H
#define TAREFA_H

#include <time.h>
#include "categoria.h"

#define MAX_TAREFAS 10000

#define MAX_DESCRICAO 81

typedef struct Tarefa{
    int id;
    char descricao[MAX_DESCRICAO];
    time_t data_limite;
    int prioridade; // Perf
    int status;
    categoria categoria;
}tarefa;

typedef tarefa *p_tarefa;

extern p_tarefa tarefas[MAX_TAREFAS];

// Adicionar, remover, marcar como concluido, alterar, buscar por palavra chave, listar pendentes ordernados por prioridade e data,
// persistencia em arquivo,

void inicializarTarefas();

void salvarTarefas();

void adicionarTarefa();

void alterarTarefa();

void removerTarefa();

void fazerConclusao();

void desfazerConclusao();

void listarPendentes(int desc);

void avisarSobrePrazo();

void buscarTarefa();

#endif //TAREFA_H
