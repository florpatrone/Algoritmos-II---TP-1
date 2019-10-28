#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "strutil.h"
#include "pila.h"

int main(int argc, const char* argv[]){
    FILE* archivo = NULL;

    if (argc == 0){
        archivo = stdin;
    }else if (argc == 1){
        archivo = fopen(argv[0],"r");
        if (!archivo){
            return fprintf(stderr,"%s","No se pudo leer el archivo indicado\n");
        }
    }else{
        return fprintf(stderr,"%s","Cantidad de parametros erronea\n");
    }

    char* linea = NULL;
	size_t n = 0;

    while ((getline(&linea, &n, archivo)) > 0){
        char** entrada = split(linea,' ');
        if (!entrada){
            fclose(archivo);
            return fprintf(archivo,"%s","Error de memoria\n");
        }
        calcular(entrada);
        free_strv(entrada);
    }
    free(linea);
    fclose(archivo);
    return 0;
}