//
// Created by bruno on 14/06/25.
//

#include <string.h>
#include <stdlib.h>
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
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void ler_string(char string[], int tamanho) {
    fgets(string, tamanho, stdin);
    size_t len = strlen(string);

    if (len > 0 && string[len-1] == '\n') {
        string[len-1] = '\0';
    } else {
        limpar_buffer_entrada();
    }
}

int str_data_para_tm(char *data, struct tm *tm_data) {
    int dia = 0, mes, ano;

    if(sscanf(data, "%d/%d/%d", &ano, &mes, &dia) != EOF){
        // tm_year is years since 1900
        tm_data->tm_year = ano - 1900;
        // tm_months is months since january
        tm_data->tm_mon = mes - 1;
        tm_data->tm_mday = dia;
    }

    // if (!_eh_numero(str_dia) || !_eh_numero(str_mes) || !_eh_numero(str_ano)) {
    //     return 0;
    // }
    //
    // short int dia = atoi(str_dia);
    // short int mes = atoi(str_mes);
    // int ano = atoi(str_ano) + 2000;
    // short int eh_bissexto = 0;
    //
    // if (mes < 1 || mes > 12) {
    //     return 0;
    // }
    //
    // if ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0)) {
    //     eh_bissexto = 1;
    // }
    //
    // // Checa se dia de fevereiro eh valido em anos não bissextos
    // if (!eh_bissexto && mes == 2 && dia == 29) {
    //     return 0;
    // }
    //
    // int dias_limite_por_mes[12] = {31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //
    // if (dia > dias_limite_por_mes[mes - 1]) {
    //     return 0;
    // }

    return 1;
}

void esperar_para_continuar() {
    printf("\nContinuar...");
    getchar();
}