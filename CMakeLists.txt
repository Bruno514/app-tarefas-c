cmake_minimum_required(VERSION 3.31)
project(app_tarefas C)

set(CMAKE_C_STANDARD 11)

add_executable(app_tarefas app.c
        tarefa.c
        tarefa.h
        categoria.c
        categoria.h)
