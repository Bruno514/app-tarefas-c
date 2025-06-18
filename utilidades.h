//
// Created by bruno on 14/06/25.
//

#ifndef UTILIDADES_H
#define UTILIDADES_H
#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

void ler_string(char *string, int tamanho);

void limpar_buffer_entrada();

void esperar_para_continuar();

int validar_data(char *data);

#endif //UTILIDADES_H
