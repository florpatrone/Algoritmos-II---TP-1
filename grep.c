#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"

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

bool es_numero(const char* str){
    int i = 0;
    while (str[i] != '\0'){
        if (!isdigit(str[i])) return false;
        i++;
    }
    return i != 0;
}

int main(int argc, char const *argv[]){
    if (! ((argc == 3) || (argc == 4)) ){
        return fprintf(stderr,"%s","Cantidad de parametros erronea.\n");
    }

    const char* substr = argv[1];

    if (!es_numero(argv[2])){
        return fprintf(stderr,"%s","Tipo de parametro incorrecto.\n");
    }
    
    int contexto = atoi(argv[2]);

    FILE* archivo = NULL;

    if (argc == 3){
        archivo = stdin;
    }else{
        archivo = fopen(argv[3],"r");
        if (!archivo){
            return fprintf(stderr,"%s","No se pudo leer el archivo indicado.\n");
        }
    }
    
    lista_t* lista = NULL;

    if (contexto > 0){
        lista = lista_crear();
        if (!lista){
        	fclose(archivo);
            return fprintf(stderr,"%s","Error de memoria.\n");
        }
    }
    
    char* linea = NULL;
	size_t n = 0;

    while ((getline(&linea, &n, archivo)) > 0){
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
                free(linea);
                lista_destruir(lista,free);
                fclose(archivo);   
                return fprintf(stderr,"%s","Error de memoria.\n");
            }
        }
    }
	free(linea);
    if (lista) lista_destruir(lista,free);
	fclose(archivo);    
    return 0;
    
}