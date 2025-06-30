//
// Created by bruno on 14/06/25.
//

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "utilidades.h"

int _eh_numero(char *numero) {
    for (int i = 0; i < strlen(numero); i++) {
        if (!isdigit(numero[i])) {
            return 0;
        }
    }

    return 1;
}

void limpar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void ler_string(char string[], int tamanho) {
    fgets(string, tamanho, stdin);
    size_t len = strlen(string);

    if (len > 0 && string[len - 1] == '\n') {
        string[len - 1] = '\0';
    } else {
        limpar_buffer_entrada();
    }
}

bool validar_data(char *data) {
    if (data[4] != '/' || data[7] != '/') {
        return 0;
    }

    char str_dia[3];
    char str_mes[3];
    char str_ano[4];
    strncpy(str_ano, data, 4);
    str_ano[3] = '\0';
    strncpy(str_mes, data + 5, 2);
    str_mes[2] = '\0';
    strncpy(str_dia, data + 8, 2);
    str_dia[2] = '\0';

    if (!_eh_numero(str_dia) || !_eh_numero(str_mes) || !_eh_numero(str_ano)) {
        return false;
    }

    int dia = atoi(str_dia);
    int mes = atoi(str_mes);
    int ano = atoi(str_ano);


    short int eh_bissexto = 0;

    if (mes < 1 || mes > 12) {
        return false;
    }

    if ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0)) {
        eh_bissexto = 1;
    }

    // Checa se dia de fevereiro eh valido em anos não bissextos
    if (!eh_bissexto && mes == 2 && dia == 29) {
        return false;
    }

    int dias_limite_por_mes[12] = {31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (dia > dias_limite_por_mes[mes - 1]) {
        return false;
    }

    return true;
}

bool str_data_para_tm(char *data, struct tm *tm_data) {
    if (!validar_data(data)) {
        return false;
    }
    char str_dia[3];
    char str_mes[3];
    char str_ano[5];
    strncpy(str_ano, data, 4);
    str_ano[4] = '\0';
    strncpy(str_mes, data + 5, 2);
    str_mes[2] = '\0';
    strncpy(str_dia, data + 8, 2);
    str_dia[2] = '\0';

    int dia = atoi(str_dia);
    int mes = atoi(str_mes);
    int ano = atoi(str_ano);

    tm_data->tm_year = ano - 1900;
    tm_data->tm_mon = mes - 1;
    tm_data->tm_mday = dia;

    return true;
}

void esperar_para_continuar() {
    printf("\nContinuar...");
    getchar();
}

bool data_maior_que(struct tm *data1, struct tm *data2) {
    if (data1->tm_year != data2->tm_year) return data2->tm_year > data2->tm_year;
    if (data1->tm_mon != data2->tm_mon) return data2->tm_mon > data2->tm_mon;
    if (data1->tm_mday != data2->tm_mday) return data2->tm_mday > data2->tm_mday;

    return false;
}

bool data_menor_que(struct tm *data1, struct tm *data2) {
    if (data1->tm_year != data2->tm_year) return data2->tm_year < data2->tm_year;
    if (data1->tm_mon != data2->tm_mon) return data2->tm_mon < data2->tm_mon;
    if (data1->tm_mday != data2->tm_mday) return data2->tm_mday < data2->tm_mday;

    return false;
}
