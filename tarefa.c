//
// Created by bruno on 09/06/25.
//

#include <stdio.h>
#include <stdlib.h>

#include "tarefa.h"
#include "utilidades.h"


tarefa *tarefas[MAX_TAREFAS];

void adicionar_tarefa() {
    int posicao = -1;

    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) {
            posicao = i;
        }
    }

    tarefa *tarefa = malloc(sizeof(tarefa));

    printf("Informe a descrição da tarefa: ");
    fgets(tarefa->descricao, sizeof(tarefa->descricao), stdin);

    printf("Informe a data limite da tarefa (dd/mm/aa): ");
    ler_string(tarefa->data_limite);

    while (!validar_data(tarefa->data_limite)) {
        printf("Data limite invalida!\n");
        printf("Informe a data limite da tarefa (dd/mm/aa): ");
        ler_string(tarefa->data_limite);
    }

    tarefas[posicao] = tarefa;
}