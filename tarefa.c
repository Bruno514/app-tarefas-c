//
// Created by bruno on 09/06/25.
//

#include <stdio.h>
#include <stdlib.h>

#include "tarefa.h"
#include "categoria.h"
#include "utilidades.h"


tarefa *tarefas[MAX_TAREFAS];
int contador_id = 0;

void inicializar_tarefas() {
    for (int i = 0; i < MAX_TAREFAS; i++) {
        tarefas[i] = NULL;
        break;
    }
}

void adicionar_tarefa() {
    int posicao = -1;

    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) {
            posicao = i;
            break;
        }
    }

    tarefa *tarefa = malloc(sizeof(tarefa));

    tarefa->id = contador_id++;

    printf("Informe a descrição da tarefa: ");
    ler_string(tarefa->descricao, MAX_T_DESCRICAO);

    printf("Informe a data limite da tarefa (dd/mm/aa): ");
    ler_string(tarefa->data_limite, MAX_T_DATA);

    printf("\n");

    while (!validar_data(tarefa->data_limite)) {
        printf("Data limite invalida!\n");
        printf("Informe a data limite da tarefa (dd/mm/aa): ");
        ler_string(tarefa->data_limite, MAX_T_DATA);
    }

    printf("Prioridade padrão eh 5\n\n");
    printf("Escolher prioridade para a tarefa? (s\\n): ");
    char escolha = (char) getchar();
    limpar_buffer_entrada();

    if (escolha == 's' || escolha == 'S') {
        printf("Selecione 1-5 (maior prioridade para menor): ");
        scanf("%d", &tarefa->prioridade);
        limpar_buffer_entrada();
        while (tarefa->prioridade < 1 || tarefa->prioridade > 5) {
            printf("Valor inválido!\n\n");
            printf("Selecione 1-5 (maior prioridade para menor): ");
            scanf("%d", &tarefa->prioridade);
            limpar_buffer_entrada();
        }
    } else {
        tarefa->prioridade = 5;
    }

    printf("\n");

    printf("Adicionar categoria? (s\\n): ");
    escolha = (char) getchar();
    limpar_buffer_entrada();

    if (escolha == 's' || escolha == 'S') {
        int categoria_index;

        printf("\n");

        if (listar_categorias()) {
            printf("Qual sua escolha? ");
            scanf("%d", &categoria_index);
            limpar_buffer_entrada();

            categoria *categoria = selecionar_categoria(categoria_index - 1);

            while (categoria == NULL) {
                printf("Escolha inválida! \n");
                printf("Qual sua escolha? ");
                scanf("%d", &categoria_index);
                limpar_buffer_entrada();

                categoria = selecionar_categoria(categoria_index - 1);
            }

            tarefa->categoria = categoria;
        } else {
            tarefa->categoria = NULL;
        };
    } else {
        tarefa->categoria = NULL;
    }

    tarefa->status = 0;
    printf("\nTarefa adicionada com sucesso\n");

    tarefas[posicao] = tarefa;

    esperar_para_continuar();
}

void remover_tarefa() {
    int id;
    int removeu = 0;

    printf("Digite o ID da tarefa que deseja remover: ");
    scanf("%d", &id);

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
        printf("Tarefa não foi encontrada\n\n");
    }

    esperar_para_continuar();
}

void listar_tarefas(int listar_concluidas) {
    int tem_tarefas = 0;
    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) {
            continue;
        }
        if (!listar_concluidas && tarefas[i]->status == 1) {
            continue;
        }

        tem_tarefas = 1;
        printf("ID %d - ", tarefas[i]->id);
        puts(tarefas[i]->descricao);
        printf("Prioridade: %d\n", tarefas[i]->prioridade);
        printf("Prazo para %s\n", tarefas[i]->data_limite);
        printf("Status: %s\n\n", tarefas[i]->status == 1 ? "Concluída" : "Não concluída");
    }

    if (!tem_tarefas) {
        printf("Nenhuma tarefa encontrada\n\n");
    }

    esperar_para_continuar();
}
