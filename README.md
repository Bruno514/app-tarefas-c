# Projeto: Gerenciador de Tarefas Pessoais
Este é um projeto desenvolvido para a disciplina de Linguagem de Programação da Fatec Arthur de Azevedo – Mogi Mirim, sob a orientação do Prof. Me. Marcos Roberto de Moraes. O objetivo é aplicar conceitos de estruturas de dados, manipulação de arquivos e práticas de desenvolvimento de software em C.
## Tema Escolhido

Este projeto implementa um sistema de gerenciamento de tarefas pessoais, permitindo que o usuário organize suas atividades diárias por categorias e tenha facilidade para buscar.

## Funcionalidades Implementadas

- Criação e alteração de tarefas
- Prazos com datas
- Categorização  
- Status de conclusão  
- Busca por palavra-chave
- Ordenar por prioridade e data
- Reagendamentos  

## Estrutura de Dados

Os dados são armazenados em memória utilizando um vetor global de ponteiros para registros, com alocação dinâmica. A persistência dos dados é realizada em um arquivo CSV.

## Como Baixar e Compilar

1. **Clone o repositório:**
```bash
git clone https://github.com/Bruno514/app-tarefas-c
cd app-tarefas-c
```

2. **Compile o código:**
```bash
gcc -o app_tarefas app.c tarefa.c categoria.c utilidades.c -Wall
```

## Como Testar

1. **Execute o programa compilado:**
```bash
./app-tarefas
```

2. Siga as instruções do menu interativo no console para realizar as operações de gerenciamento das suas tarefas.

## Autores

- Adriana Messias
- Bruno Silva Oliveira
- Filipe de Caroli
- Gabriel Henrique Martins Gomes

