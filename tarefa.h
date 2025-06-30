//
// Created by bruno on 09/06/25.
//


#ifndef TAREFA_H
#define TAREFA_H

#include <time.h>
#include <stdbool.h>

#include "categoria.h"

#define MAX_TAREFAS 10000

#define MAX_T_DESCRICAO 81

typedef struct Tarefa {
    int id;
    char descricao[MAX_T_DESCRICAO];
    struct tm data_limite;
    int prioridade;
    int status;
    categoria *categoria;
} tarefa;

extern tarefa *tarefas[MAX_TAREFAS];
extern int t_ultimo_id;

// Adicionar, remover, marcar como concluido, alterar, buscar por palavra chave, listar pendentes ordernados por prioridade e data,
// persistencia em arquivo,

void inicializar_tarefas();

void salvar_tarefas();

tarefa *criar_tarefa(int id, char *descricao, char *data_limite, int status, int prioridade,
                     categoria *categoria);

bool adicionar_tarefa(tarefa *tarefa);

bool alterar_prazo(tarefa *tarefa, char data_limite[10]);

bool alterar_categoria(tarefa *tarefa, int id_categoria);

bool remover_tarefa(int id);

tarefa *buscar_tarefa_id(int id);

tarefa *buscar_tarefa_palavra(char *busca);

bool ordernar_por_prioridade(bool decrescente);

bool ordernar_por_data(bool decrescente);

#endif //TAREFA_H
