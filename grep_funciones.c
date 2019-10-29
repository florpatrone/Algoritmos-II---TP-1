#define _POSIX_C_SOURCE 200809L
#include "grep.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool es_numero(const char* str){
    int i = 0;
    while (str[i] != '\0'){
        if (!isdigit(str[i])) return false;
        i++;
    }
    return i != 0;
}

bool contiene_substr(const char* str, const char* substr){
    int i = 0;
    int j = 0;
    size_t len = strlen(substr);

    while (str[i] != '\0'){
        if (str[i] == substr[j]){
            j++;
            for (; j < len; j++){
                if (str[i+j] != substr[j]){
                    j = 0;
                    break;
                }
            }
            if (j != 0) return true;
        }
        i++;
    }
    return false;
}

bool imprimir_linea(lista_t* lista, const char* linea, const char* substr, int contexto){
    if (contiene_substr(linea,substr)){
        for (int i = 0; i < contexto; i++){
            if (lista_esta_vacia(lista)) break;
            char* anterior = lista_borrar_primero(lista);
            fprintf(stdout,"%s",anterior);
            free(anterior);
        }
        fprintf(stdout,"%s",linea);
    }else if (contexto > 0){
        if (lista_largo(lista) == contexto){
                lista_borrar_primero(lista);
        }
        if (!lista_insertar_ultimo(lista,strdup(linea))){
            fprintf(stderr,"%s","Error de memoria.\n");
            return false;
        }
    }
    return true;
}