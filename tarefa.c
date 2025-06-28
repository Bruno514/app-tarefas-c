//
// Created by bruno on 09/06/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "tarefa.h"

#include <string.h>

#include "categoria.h"
#include "utilidades.h"


tarefa *tarefas[MAX_TAREFAS];
int t_ultimo_id = 0;

void inicializar_tarefas() {
    FILE *stream = fopen("/home/bruno/tarefas.csv", "a+");

    char linha[256];
    int tarefas_contador = 0;

    while (fgets(linha, 256, stream) != NULL) {
        tarefa *tarefa = malloc(sizeof(tarefa));

        tarefa->id = atoi(strtok(linha, ","));
        if (tarefa->id > t_ultimo_id) {
            t_ultimo_id = tarefa->id;
        }

        strcpy(tarefa->descricao, strtok(NULL, ","));
        str_data_para_tm(strtok(NULL, ","), &tarefa->data_limite);
        tarefa->prioridade = atoi(strtok(NULL, ","));
        tarefa->status = atoi(strtok(NULL, ","));
        tarefa->categoria = selecionar_categoria(atoi(strtok(NULL, ",")));
        strtok(NULL, ",");

        tarefas[tarefas_contador++] = tarefa;
    }

    for (; tarefas_contador < MAX_TAREFAS; tarefas_contador++) {
        tarefas[tarefas_contador] = NULL;
    }

    fclose(stream);
}

void adicionar_tarefa() {
    int posicao = -1;
    char data_limite_string[10];

    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) {
            posicao = i;
            break;
        }
    }

    tarefa *tarefa = malloc(sizeof(tarefa));

    tarefa->id = ++t_ultimo_id;

    printf("Informe a descrição da tarefa: ");
    ler_string(tarefa->descricao, MAX_T_DESCRICAO);

    printf("Informe a data limite da tarefa (aaaa/mm/dd): ");
    ler_string(data_limite_string, 11);

    memset(&tarefa->data_limite, 0, sizeof(tarefa->data_limite));

    while (!str_data_para_tm(data_limite_string, &tarefa->data_limite)) {
        printf("\nData inválida\n");
        printf("Informe a data limite da tarefa (aaaa/mm/dd): ");
        ler_string(data_limite_string, 11);
    }

    printf("\n");

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

void listar_tarefas() {
    int tem_tarefas = 0;
    int opcao = 1;

    printf("1 - Ordem decrescente (prioridade)\n");
    printf("2 - Ordem decrescente (data)\n");
    printf("3 - Ordem crescente (prioridade)\n");
    printf("4 - Ordem crescente (data)\n\n");

    printf("Como deseja listar? ");
    scanf("%d", &opcao);
    limpar_buffer_entrada();

    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) {
            continue;
        }

        tem_tarefas = 1;
        printf("ID %d - ", tarefas[i]->id);
        puts(tarefas[i]->descricao);
        printf("Prioridade: %d\n", tarefas[i]->prioridade);
        printf("Prazo para %d/%d/%d\n", tarefas[i]->data_limite.tm_year + 1900, tarefas[i]->data_limite.tm_mon + 1,
               tarefas[i]->data_limite.tm_mday);
        printf("Status: %s\n", tarefas[i]->status == 1 ? "Concluída" : "Não concluída");
        if (tarefas[i]->categoria != NULL) {
            printf("Categoria: ");
            puts(tarefas[i]->categoria->descricao);
        }
    }

    if (!tem_tarefas) {
        printf("Nenhuma tarefa encontrada\n\n");
    }

    esperar_para_continuar();
}

void ordernar_tarefas_por_prioridade() {
    bool trocado;
    for (int i = 0; i < MAX_TAREFAS - 1; i++) {
        trocado = false;
        for (int j = 0; j < MAX_TAREFAS - i - 1; j++) {
            if (tarefas[j]->prioridade > tarefas[j + 1]->prioridade || tarefas[j] == NULL) {
                tarefa *temporario = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = temporario;
                trocado = true;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (trocado == false)
            break;
    }
}
