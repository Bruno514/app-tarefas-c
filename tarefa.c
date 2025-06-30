//
// Created by bruno on 09/06/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "tarefa.h"

#include <threads.h>

#include "categoria.h"
#include "utilidades.h"


tarefa *tarefas[MAX_TAREFAS];
int t_ultimo_id = 0;

void inicializar_tarefas() {
    FILE *stream = fopen("/home/bruno/tarefas.csv", "a+");

    char linha[256];
    char descricao[MAX_T_DESCRICAO];
    char data_limite[11];
    categoria *categoria = NULL;

    while (fgets(linha, 256, stream) != NULL) {
        int id = atoi(strtok(linha, ","));
        if (id > t_ultimo_id) {
            t_ultimo_id = id;
            printf("%d", t_ultimo_id);
        }

        strcpy(descricao, strtok(NULL, ","));
        descricao[strlen(descricao)] = '\0';
        strcpy(data_limite, strtok(NULL, ","));
        int prioridade = atoi(strtok(NULL, ","));
        int status = atoi(strtok(NULL, ","));
        int id_categoria = atoi(strtok(NULL, ","));
        if (id_categoria == 0) {
            id_categoria = -1;
        }
        strtok(NULL, ",");

        categoria = selecionar_categoria(id_categoria);

        tarefa *tarefa = criar_tarefa(id, descricao, data_limite, status, prioridade, categoria);
        adicionar_tarefa(tarefa);
    }

    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] != NULL) continue;
        tarefas[i] = NULL;
    }

    fclose(stream);
}

void salvar_tarefas() {
}

tarefa *criar_tarefa(int id, char *descricao, char *data_limite, int status, int prioridade, categoria *categoria) {
    tarefa *tarefa = malloc(sizeof(tarefa));

    // ID pode ser informado ou não (nesse caso um id será dado automaticamente)
    tarefa->id = id == -1 ? ++t_ultimo_id : id;
    strcpy(tarefa->descricao, descricao);
    str_data_para_tm(data_limite, &tarefa->data_limite);
    tarefa->status = status;
    tarefa->prioridade = prioridade;
    tarefa->categoria = categoria;

    return tarefa;
}

bool adicionar_tarefa(tarefa *tarefa) {
    int posicao = -1;

    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) {
            posicao = i;
            break;
        }
    }
    if (posicao == -1) return false;

    tarefas[posicao] = tarefa;

    return true;
}

bool alterar_prazo(tarefa *tarefa, char data_limite[11]) {
    if (!str_data_para_tm(data_limite, &tarefa->data_limite)) {
        return false;
    }
    return true;
};

bool alterar_categoria(tarefa *tarefa, int id_categoria) {
    categoria *categoria = selecionar_categoria(id_categoria);
    tarefa->categoria = categoria;
    if (categoria == NULL) {
        return false;
    }
    return true;
};

bool remover_tarefa(int id) {
    int removeu = 0;

    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) {
            continue;
        }

        if (tarefas[i]->id == id) {
            tarefas[i] = NULL;
            removeu = 1;
            break;
        }
    }

    if (!removeu) {
        return false;
    }

    return true;
}

tarefa *buscar_tarefa_id(int id) {
    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) {
            continue;
        }
        if (tarefas[i]->id == id) {
            return tarefas[i];
        }
    }

    return NULL;
}

tarefa *buscar_tarefa_palavra(char *busca) {
    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) {
            continue;
        }
        if (strstr(tarefas[i]->descricao, busca) != NULL) {
            return tarefas[i];
        }
    }

    return NULL;
}

bool ordernar_por_prioridade(bool decrescente) {
    bool trocado;
    for (int i = 0; i < MAX_TAREFAS - 1; i++) {
        trocado = false;
        for (int j = 0; j < MAX_TAREFAS - i - 1; j++) {
            if (!decrescente) {
                if (tarefas[j]->prioridade > tarefas[j + 1]->prioridade || tarefas[j] == NULL) {
                    tarefa *temporario = tarefas[j];
                    tarefas[j] = tarefas[j + 1];
                    tarefas[j + 1] = temporario;
                    trocado = true;
                }
            } else {
                if (tarefas[j]->prioridade < tarefas[j + 1]->prioridade || tarefas[j + 1] == NULL) {
                    tarefa *temporario = tarefas[j];
                    tarefas[j] = tarefas[j + 1];
                    tarefas[j + 1] = temporario;
                    trocado = true;
                }
            }
        }

        if (trocado == false)
            break;
    }
}

bool ordernar_por_data(bool decrescente) {
    bool trocado;
    for (int i = 0; i < MAX_TAREFAS - 1; i++) {
        trocado = false;
        for (int j = 0; j < MAX_TAREFAS - i - 1; j++) {
            if (!decrescente) {
                if (data_maior_que(&tarefas[j]->data_limite, &tarefas[j + 1]->data_limite) || tarefas[j] == NULL) {
                    tarefa *temporario = tarefas[j];
                    tarefas[j] = tarefas[j + 1];
                    tarefas[j + 1] = temporario;
                    trocado = true;
                }
            } else {
                if (data_menor_que(&tarefas[j]->data_limite, &tarefas[j + 1]->data_limite) || tarefas[j] == NULL) {
                    tarefa *temporario = tarefas[j];
                    tarefas[j] = tarefas[j + 1];
                    tarefas[j + 1] = temporario;
                    trocado = true;
                }
            }
        }

        if (trocado == false)
            break;
    }
}
