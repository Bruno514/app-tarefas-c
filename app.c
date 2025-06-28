#include <stdio.h>

#include "app.h"
#include "tarefa.h"
#include "categoria.h"
#include "utilidades.h"

#define LIS_TAREFA 1
#define ADC_TAREFA 2
#define REM_TAREFA 3
#define LIS_CATEGORIA 4
#define ADC_CATEGORIA 5
#define REM_CATEGORIA 6
#define SAIR 0

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
            case LIS_TAREFA:
                clrscr();
                listar_tarefas(1);
                break;
            case ADC_TAREFA:
                clrscr();
                adicionar_tarefa();
                break;
            case REM_TAREFA:
                clrscr();
                remover_tarefa();
                break;
            case LIS_CATEGORIA:
                clrscr();
                listar_categorias();
                break;
            case ADC_CATEGORIA:
                clrscr();
                adicionar_categoria();
                break;
            case REM_CATEGORIA:
                clrscr();
                remover_categoria();
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
    printf("\nMenu:\n\n");
    printf("1 - Listar tarefas\n");
    printf("2 - Adicionar tarefa\n");
    printf("3 - Remover tarefa\n");
    printf("4 - Listar categorias\n");
    printf("5 - Adicionar categoria\n");
    printf("6 - Remover categoria\n\n");
    printf("0 - Sair\n\n");
}