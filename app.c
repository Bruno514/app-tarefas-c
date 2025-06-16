#include "tarefa.h"
#include "categoria.h"
#include "utilidades.h"

int main(void) {
    inicializar_tarefas();
    inicializar_categorias();

    adicionar_categoria();
    adicionar_tarefa();

    return 0;
}