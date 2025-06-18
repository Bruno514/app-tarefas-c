#include <stdio.h>

#include "app.h"
#include "tarefa.h"
#include "categoria.h"
#include "utilidades.h"

int main(void) {
    inicializar_tarefas();
    inicializar_categorias();

    int opcao = -1;

    while (opcao != 0) {
        mostrar_menu();
        printf("Escolha um opção: ");

        scanf("%d", &opcao);
        limpar_buffer_entrada();

        printf("\n");
        switch (opcao) {
            case 1:
                listar_tarefas(1);
                break;
            case 2:
                adicionar_tarefa();
                break;
            case 3:
                remover_tarefa();
                break;
            case 4:
                adicionar_categoria();
                break;
            case 5:
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
    printf("4 - Adicionar categoria\n\n");
    printf("0 - Sair\n\n");
}