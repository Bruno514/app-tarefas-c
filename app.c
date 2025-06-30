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
#define ALTERAR_CATEGORIA 6
#define ADICIONAR_CATEGORIA 7
#define LISTAR_CONCLUIDAS 8
#define SAIR 0

int id_categoria_selecionada = -1;

int main(void) {
    inicializar_categorias();
    inicializar_tarefas();

    int opcao = -1;

    while (opcao != 0) {
        m_mostrar_menu();
        printf("Escolha um opção: ");

        scanf("%d", &opcao);
        limpar_buffer_entrada();

        printf("\n");
        switch (opcao) {
            case LISTAR_TAREFA:
                clrscr();
                m_mostrar_tarefas();
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
            case ALTERAR_CATEGORIA:
                clrscr();
                m_mudar_categoria();
                break;
            case ADICIONAR_CATEGORIA:
                clrscr();
                m_adicionar_categoria();
                break;
            case LISTAR_CONCLUIDAS:
                clrscr();
                m_ver_tarefas_concluidas();
            default:
                printf("Salvando...");
                break;
        }
    }

    return 0;
}

void m_mostrar_menu() {
    clrscr();
    printf("===============================\n");
    printf("|        MENU PRINCIPAL       |\n");
    printf("===============================\n\n");
    printf("1 - Listar tarefas\n");
    printf("2 - Adicionar tarefa\n");
    printf("3 - Remover tarefa\n");
    printf("4 - Completar tarefa\n");
    printf("5 - Alterar prioridade\n");
    printf("6 - Mudar categoria\n");
    printf("7 - Adicionar categoria\n");
    printf("8 - Ver tarefas feitas\n");
    printf("0 - Sair\n\n");
}

void m_mostrar_tarefas() {
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

        printf("(%d tarefas)\n", tarefas_por_categoria);
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
        if (tarefas[i]->status == 1) continue;

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
        if (tarefas[i]->status == 1) continue;

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

void m_mudar_categoria() {
    int id = -1;
    printf("===============================\n");
    printf("       MUDAR CATEGORIA         \n");
    printf("===============================\n\n");
    printf("Categorias disponíveis:\n\n");

    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        if (categorias[i] == NULL) {
            continue;
        }

        categoria *categoria = categorias[i];
        printf("ID %d - ", categoria->id);
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

        printf("(%d tarefas)\n", tarefas_por_categoria);
    }
    printf("\nInforme o ID da categoria: ");
    scanf("%d", &id);
    limpar_buffer_entrada();

    categoria *categoria = selecionar_categoria(id);

    if (categoria == NULL) {
        printf("Categoria indisponível!\n\n");
        esperar_para_continuar();
        return;
    }

    id_categoria_selecionada = id;

    printf("Mudou para categoria: ");
    puts(categoria->descricao);
    printf("\n");

    esperar_para_continuar();
}

void m_adicionar_categoria() {
    int id = -1;
    char descricao[MAX_C_DESCRICAO];

    printf("===============================\n");
    printf("       ADICIONAR CATEGORIA     \n");
    printf("===============================\n\n");
    printf("Categorias disponíveis:\n\n");

    for (int i = 0; i < MAX_CATEGORIAS; i++) {
        if (categorias[i] == NULL) {
            continue;
        }

        categoria *categoria = categorias[i];
        printf(" - ");
        fputs(categoria->descricao, stdout);
        printf("\n");
    }

    printf("\nInforme a descrição da categoria: ");
    ler_string(descricao, MAX_C_DESCRICAO);

    printf("\n");

    categoria *categoria = criar_categoria(-1, descricao);
    if (!adicionar_categoria(categoria)) {
        printf("Não foi possível adicionar a categoria!\n\n");
        esperar_para_continuar();
        return;
    }

    char mudar;

    printf("\nDeseja mudar para essa categoria? (s/n): ");
    scanf("%c", &mudar);
    limpar_buffer_entrada();

    printf("\n");

    if (mudar != 'S' && mudar != 's') {
        esperar_para_continuar();
        return;
    }

    id_categoria_selecionada = categoria->id;

    printf("Mudou para categoria: ");
    puts(categoria->descricao);
    printf("\n");

    esperar_para_continuar();
}

void m_ver_tarefas_concluidas() {
    printf("===============================\n");
    printf("       TAREFAS COMPLETAS       \n");
    printf("===============================\n\n");

    categoria *categoria_selecionada = selecionar_categoria(id_categoria_selecionada);

    printf("Categoria selecionada: ");
    puts(categoria_selecionada == NULL ? "Todas" : categoria_selecionada->descricao);
    printf("\n");

    bool tem_tarefas = false;
    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) continue;
        if (tarefas[i]->status == 0) continue;

        tem_tarefas = true;

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
        printf("OK (ID %d)", tarefa->id);
        printf(" - %d/%02d/%02d", data->tm_year + 1900, data->tm_mon + 1, data->tm_mday);
        printf("\n");
    }

    if (!tem_tarefas) {
        printf("Não há tarefas completadas.\n\n");
        esperar_para_continuar();
        return;
    }

    printf("\n");

    char escolha;
    printf("Deseja limpar essas tarefas? (s/n): ");
    scanf("%c", &escolha);
    limpar_buffer_entrada();

    if (escolha != 's' && escolha != 'S') {
        esperar_para_continuar();
        return;
    }

    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (tarefas[i] == NULL) continue;
        if (tarefas[i]->status == 0) continue;

        tarefa *tarefa = tarefas[i];

        if (categoria_selecionada != NULL) {
            if (tarefa->categoria != categoria_selecionada) {
                continue;
            }
        }

        tarefas[i] = NULL;
    }

    printf("\n\n");

    esperar_para_continuar();
}

void salvar_e_sair() {
}

void m_ordernar() {
}
