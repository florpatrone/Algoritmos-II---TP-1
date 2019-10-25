#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <stdbool.h>

bool contiene_substr(const char* str, const char* substr){
    return true;
}

bool es_numero(const char* str){
    return true;
}

int main(int argc, char const *argv[]){

    if (! ((argc == 3) || (argc == 4)) ){
        return fprintf(stderr,"%s","Cantidad de parametros erronea.\n");
    }

    const char* substr = argv[1];
    const char* contexto = argv[2];
    //int contexto = atoi(argv[2]);

    if (!es_numero(contexto)){
        return fprintf(stderr,"%s","Tipo de parametro incorrecto.\n");
    }

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
        if (!lista) return -1; //ERROR
    }

    char* linea = NULL;
	size_t n = 0;

    while ((getline(&linea, &n, archivo)) > 0){
        if (contiene_substr(linea,substr)){
            for (int i = 0; i < contexto; i++){
                char* anterior = lista_borrar_primero(lista);
                fprintf(stdout,"%s",anterior);
            }
            fprintf(stdout,"%s",linea);
        }

        else if (contexto > 0){
            if (lista_largo(lista) == contexto){
                lista_borrar_primero(lista);
            }
            lista_insertar_ultimo(lista,linea); //revisar
        }
    }

	free(linea);
	fclose(archivo);
    
    return 0;
}


