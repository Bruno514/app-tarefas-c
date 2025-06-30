//
// Created by bruno on 14/06/25.
//

#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdbool.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

void ler_string(char *string, int tamanho);

void limpar_buffer_entrada();

void esperar_para_continuar();

bool validar_data(char *data);

bool str_data_para_tm(char *data, struct tm *tm_data);

bool data_maior_que(struct tm *data1, struct tm *data2);

bool data_menor_que(struct tm *data1, struct tm *data2);

#endif //UTILIDADES_H
