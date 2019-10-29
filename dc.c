#define _POSIX_C_SOURCE 200809L
#include "dc.h"
#include "strutil.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]){
    FILE* archivo = NULL;

    if (argc == 1){
        archivo = stdin;
    }else if (argc == 2){
        archivo = fopen(argv[1],"r");
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
            return fprintf(archivo,"%s","ERROR\n");
        }
        remover_salto_linea(entrada);
        calcular(entrada);
        free_strv(entrada);
    }
    free(linea);
    fclose(archivo);
    return 0;
}