#include <stdio.h>
#include <time.h>

#include "app.h"
#include "tarefa.h"
#include "categoria.h"
#include "utilidades.h"

#define LISTAR_TAREFA 1
#define ADICIONAR_TAREFA 2
#define REMOVER_TAREFA 3
#define COMPLETAR_TAREFA 4
#define ALTERAR_PRIORIDADE 5
#define SAIR 0

int id_categoria_selecionada = -1;

int main(void) {
    inicializar_categorias();
    inicializar_tarefas();

    int opcao = -1;

    while (opcao != 0) {
        mostrar_menu();
        printf("Escolha um opção: ");

        scanf("%d", &opcao);
        limpar_buffer_entrada();

        printf("\n");
        switch (opcao) {
            case LISTAR_TAREFA:
                clrscr();
                mostrar_tarefas();
                break;
            case ADICIONAR_TAREFA:
                clrscr();
                m_adicionar_tarefa();
                break;
            case REMOVER_TAREFA:
                clrscr();
                m_remover_tarefa();
                break;
            case COMPLETAR_TAREFA:
                clrscr();
                m_marcar_como_concluida();
                break;
            case ALTERAR_PRIORIDADE:
                clrscr();
                m_alterar_prioridade();
                break;
            default:
                printf("Salvando...");
                break;
        }
    }

    return 0;
}

void mostrar_menu() {
    clrscr();
    printf("===============================\n");
    printf("         MENU PRINCIPAL        \n");
    printf("===============================\n\n");
    printf("1 - Listar tarefas\n");
    printf("2 - Adicionar tarefa\n");
    printf("3 - Remover tarefa\n");
    printf("4 - Completar tarefa\n");
    printf("5 - Alterar prioridade\n");
    printf("0 - Sair\n\n");
}

void mostrar_tarefas() {
    printf("===============================\n");
    printf("         MINHAS TAREFAS        \n");
    printf("===============================\n\n");
    printf("Categorias:\n");
    categoria *categoria_selecionada = selecionar_categoria(id_categoria_selecionada);

    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        if (categorias[i] == NULL) {
            continue;
        }

        categoria *categoria = categorias[i];
        printf("[");
        fputs(categoria->descricao, stdout);
        printf("] ");

        int tarefas_por_categoria = 0;

        for (int j = 0; j < MAX_TAREFAS; j++) {
            if (tarefas[j] == NULL) {
                continue;
            }

            if (tarefas[j]->categoria == categoria) {
                tarefas_por_categoria++;
            }
        }

        printf("(%d tarefas)\t", tarefas_por_categoria);
    }

    printf("\n\n");
    printf("Atualmente visualizando: ");
    puts(categoria_selecionada == NULL ? "Todas" : categoria_selecionada->descricao);
    if (categoria_selecionada != NULL) {
        printf("Tarefas em ");
        puts(categoria_selecionada->descricao);
    } else {
        printf("Todas as tarefas:\n");
    }

    int tarefas_completadas = 0;
    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) continue;
        if (tarefas[i]->status == 1) {
            tarefas_completadas++;
            continue;
        }

        tarefa *tarefa = tarefas[i];

        if (categoria_selecionada != NULL) {
            if (tarefa->categoria != categoria_selecionada) {
                continue;
            }
        }

        struct tm *data = &tarefa->data_limite;

        printf("  %d. [P%d] ", i + 1, tarefa->prioridade);
        if (categoria_selecionada == NULL) {
            if (tarefa->categoria != NULL) {
                printf("[");
                fputs(tarefa->categoria->descricao, stdout);
                printf("] ");
            }
        }
        fputs(tarefa->descricao, stdout);
        printf(" (ID %d)", tarefa->id);
        printf(" - %d/%02d/%02d", data->tm_year + 1900, data->tm_mon + 1, data->tm_mday);
        printf("\n");
    }
    printf("\n");
    printf("Completadas: %d", tarefas_completadas);

    esperar_para_continuar();
}

void m_adicionar_tarefa() {
    int prioridade;
    char data_limite[11];
    char descricao[MAX_T_DESCRICAO];

    categoria *categoria_selecionada = selecionar_categoria(id_categoria_selecionada);

    printf("===============================\n");
    printf("         ADICIONAR TAREFA      \n");
    printf("===============================\n\n");

    printf("Categoria selecionada: ");
    puts(categoria_selecionada == NULL ? "Todas" : categoria_selecionada->descricao);

    printf("\n");

    printf("Informe a descrição da tarefa: \n");
    printf("> ");
    ler_string(descricao, MAX_T_DESCRICAO);
    printf("\n");

    printf("Informe a data limite da tarefa (aaaa/mm/dd): ");
    ler_string(data_limite, 11);

    while (!validar_data(data_limite)) {
        printf("\nData inválida\n");
        printf("Informe a data limite da tarefa (aaaa/mm/dd): ");
        ler_string(data_limite, 11);
    }

    printf("\n");

    printf("Prioridades (1-5): \n\n");
    printf(" 1 - Baixa prioridade\n");
    printf(" 2 - Normal\n");
    printf(" 3 - Média\n");
    printf(" 4 - Alta\n");
    printf(" 5 - Urgente\n\n");
    printf("Escolha a prioridade (1): ");
    scanf("%d", &prioridade);
    limpar_buffer_entrada();

    while (prioridade < 1 || prioridade > 5) {
        printf("Valor inválido!\n\n");
        printf("Escolha a prioridade (1): ");
        scanf("%d", &prioridade);
        limpar_buffer_entrada();
    }
    printf("\n");

    tarefa *tarefa = criar_tarefa(-1, descricao, data_limite, 0, prioridade, categoria_selecionada);

    if (adicionar_tarefa(tarefa)) {
        printf("\nTarefa adicionada com sucesso!\n\n");
        printf(" [P%d] ", tarefa->prioridade);
        if (tarefa->categoria != NULL) {
            printf("[");
            fputs(tarefa->categoria->descricao, stdout);
            printf("] ");
        }
        fputs(tarefa->descricao, stdout);
        printf(" (ID %d)", tarefa->prioridade);
        printf(" - %d/%02d/%02d", tarefa->data_limite.tm_year + 1900, tarefa->data_limite.tm_mon + 1,
               tarefa->data_limite.tm_mday);
        printf("\n");
    } else {
        printf("\nNão foi possivel adicionar a tarefa!\n\n");
    }

    esperar_para_continuar();
};

void m_remover_tarefa() {
    int id = -1;
    printf("===============================\n");
    printf("         REMOVER TAREFA        \n");
    printf("===============================\n\n");

    categoria *categoria_selecionada = selecionar_categoria(id_categoria_selecionada);

    printf("Categoria selecionada: ");
    puts(categoria_selecionada == NULL ? "Todas" : categoria_selecionada->descricao);

    printf("\nQual tarefa gostaria de remover?\n\n");

    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) continue;

        tarefa *tarefa = tarefas[i];

        if (categoria_selecionada != NULL) {
            if (tarefa->categoria != categoria_selecionada) {
                continue;
            }
        }

        struct tm *data = &tarefa->data_limite;

        printf("  %d. [P%d] ", i + 1, tarefa->prioridade);
        if (categoria_selecionada == NULL) {
            if (tarefa->categoria != NULL) {
                printf("[");
                fputs(tarefa->categoria->descricao, stdout);
                printf("] ");
            }
        }
        fputs(tarefa->descricao, stdout);
        printf(" (ID %d)", tarefa->id);
        printf(" - %d/%02d/%02d", data->tm_year + 1900, data->tm_mon + 1, data->tm_mday);
        printf("\n");
    }

    printf("\nInforme o ID da tarefa: ");
    scanf("%d", &id);
    limpar_buffer_entrada();

    char confirmacao;

    printf("\nTem certeza?\n\n");
    printf("Digite 's' para confirmar: ");
    scanf("%c", &confirmacao);
    limpar_buffer_entrada();

    if (confirmacao != 'S' && confirmacao != 's') {
        return;
    }

    if (!remover_tarefa(id)) {
        printf("\nTarefa não foi encontrada\n\n");
        return;
    }

    printf("\nTarefa removida com sucesso\n\n");
}

void m_marcar_como_concluida() {
    int id = -1;
    printf("===============================\n");
    printf("        COMPLETAR TAREFA       \n");
    printf("===============================\n\n");

    categoria *categoria_selecionada = selecionar_categoria(id_categoria_selecionada);

    printf("Categoria selecionada: ");
    puts(categoria_selecionada == NULL ? "Todas" : categoria_selecionada->descricao);

    printf("\nQual tarefa você completou?\n\n");

    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) continue;

        tarefa *tarefa = tarefas[i];

        if (categoria_selecionada != NULL) {
            if (tarefa->categoria != categoria_selecionada) {
                continue;
            }
        }

        struct tm *data = &tarefa->data_limite;

        printf("  %d. [P%d] ", i + 1, tarefa->prioridade);
        if (categoria_selecionada == NULL) {
            if (tarefa->categoria != NULL) {
                printf("[");
                fputs(tarefa->categoria->descricao, stdout);
                printf("] ");
            }
        }
        fputs(tarefa->descricao, stdout);
        printf(" (ID %d)", tarefa->id);
        printf(" - %d/%02d/%02d", data->tm_year + 1900, data->tm_mon + 1, data->tm_mday);
        printf("\n");
    }

    printf("\nInforme o ID da tarefa: ");
    scanf("%d", &id);
    limpar_buffer_entrada();

    printf("\n");

    tarefa *tarefa = buscar_tarefa_id(id);
    if (tarefa == NULL) {
        printf("Tarefa não encontrada!\n\n");
        esperar_para_continuar();
        return;
    }

    tarefa->status = 1;
    printf("Tarefa completada, bom trabalho!\n");

    printf(" OK - [P%d] ", tarefa->prioridade);
    if (categoria_selecionada == NULL) {
        if (tarefa->categoria != NULL) {
            printf("[");
            fputs(tarefa->categoria->descricao, stdout);
            printf("] ");
        }
    }
    fputs(tarefa->descricao, stdout);
    printf(" (ID %d)", tarefa->id);
    printf(" - %d/%02d/%02d", tarefa->data_limite.tm_year + 1900, tarefa->data_limite.tm_mon + 1,
           tarefa->data_limite.tm_mday);
    printf("\n\n");

    esperar_para_continuar();
}

void m_alterar_prioridade() {
    int id = -1;
    printf("===============================\n");
    printf("       ALTERAR PRIORIDADE      \n");
    printf("===============================\n\n");

    categoria *categoria_selecionada = selecionar_categoria(id_categoria_selecionada);

    printf("Categoria selecionada: ");
    puts(categoria_selecionada == NULL ? "Todas" : categoria_selecionada->descricao);

    printf("\nQual tarefa você deseja alterar prioridade?\n\n");

    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) continue;

        tarefa *tarefa = tarefas[i];

        if (categoria_selecionada != NULL) {
            if (tarefa->categoria != categoria_selecionada) {
                continue;
            }
        }

        struct tm *data = &tarefa->data_limite;

        printf("  %d. [P%d] ", i + 1, tarefa->prioridade);
        if (categoria_selecionada == NULL) {
            if (tarefa->categoria != NULL) {
                printf("[");
                fputs(tarefa->categoria->descricao, stdout);
                printf("] ");
            }
        }
        fputs(tarefa->descricao, stdout);
        printf(" (ID %d)", tarefa->id);
        printf(" - %d/%02d/%02d", data->tm_year + 1900, data->tm_mon + 1, data->tm_mday);
        printf("\n");
    }

    printf("\nInforme o ID da tarefa: ");
    scanf("%d", &id);
    limpar_buffer_entrada();

    printf("\n");

    tarefa *tarefa = buscar_tarefa_id(id);
    if (tarefa == NULL) {
        printf("Tarefa não encontrada!\n\n");
        esperar_para_continuar();
        return;
    }

    printf(" Atual - [P%d] ", tarefa->prioridade);
    if (categoria_selecionada == NULL) {
        if (tarefa->categoria != NULL) {
            printf("[");
            fputs(tarefa->categoria->descricao, stdout);
            printf("] ");
        }
    }
    fputs(tarefa->descricao, stdout);
    printf(" (ID %d)", tarefa->id);
    printf(" - %d/%02d/%02d", tarefa->data_limite.tm_year + 1900, tarefa->data_limite.tm_mon + 1,
           tarefa->data_limite.tm_mday);
    printf("\n\n");

    int prioridade;
    printf("Nova Prioridade (1-5): \n\n");
    printf(" 1 - Baixa prioridade\n");
    printf(" 2 - Normal\n");
    printf(" 3 - Média\n");
    printf(" 4 - Alta\n");
    printf(" 5 - Urgente\n\n");
    printf("Escolha a prioridade (1): ");
    scanf("%d", &prioridade);
    limpar_buffer_entrada();

    while (prioridade < 1 || prioridade > 5) {
        printf("Valor inválido!\n\n");
        printf("Escolha a prioridade (1): ");
        scanf("%d", &prioridade);
        limpar_buffer_entrada();
    }
    printf("\n\n");

    tarefa->prioridade = prioridade;

    printf("Prioridade atualizada!\n\n");

    esperar_para_continuar();
}

void m_editar_tarefa() {
}

void m_mudar_categoria() {
}

void m_adicionar_categoria() {
}

void m_remover_categoria() {
}

void m_ordernar() {
}

void m_limpar_tarefas_concluidas() {
}

void m_ver_tarefas_concluidas() {
}

void salvar_e_sair() {
}
