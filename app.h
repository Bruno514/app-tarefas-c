//
// Created by bruno on 6/18/25.
//

#ifndef APP_H
#define APP_H
#define ORDENADO_DATA_CRES 1
#define ORDENADO_DATA_DECRES 2
#define ORDENADO_PRIORIDADE_CRES 3
#define ORDENADO_PRIORIDADE_DECRES 4

extern int id_categoria_selecionada;
extern int tipo_ordem;

void m_mostrar_menu();

void m_mostrar_tarefas();

void m_adicionar_tarefa();

void m_remover_tarefa();

void m_alterar_prioridade();

void m_marcar_como_concluida();

void m_mudar_categoria();

void m_adicionar_categoria();

void m_ver_tarefas_concluidas();

void m_ordernar();

void m_alterar_prazo();

void m_salvar_e_sair();

void m_notificar();

// Retorna frase baseado no Int do tipo de ordem
char *_obter_frase_ordenacao_atual();

void _ordernar_baseado_no_tipo_selecionado();

#endif //APP_H
