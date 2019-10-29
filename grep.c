#define _POSIX_C_SOURCE 200809L
#include "grep.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
    if (! ((argc == 3) || (argc == 4)) ){
        return fprintf(stderr,"%s","Cantidad de parametros erronea\n");
    }
    
    const char* substr = argv[1];
    
    if (!es_numero(argv[2])){
        return fprintf(stderr,"%s","Tipo de parametro incorrecto\n");
    }
    
    int contexto = atoi(argv[2]);
    FILE* archivo = NULL;

    if (argc == 3){
        archivo = stdin;
    }else{
        archivo = fopen(argv[3],"r");
        if (!archivo){
            return fprintf(stderr,"%s","No se pudo leer el archivo indicado\n");
        }
    }
    
    lista_t* lista = NULL;

    if (contexto > 0){
        lista = lista_crear();
        if (!lista){
        	fclose(archivo);
            return fprintf(stderr,"%s","ERROR\n");
        }
    }
    
    char* linea = NULL;
	size_t n = 0;
    
    while ((getline(&linea, &n, archivo)) > 0){
        if (!imprimir_linea(lista, linea, substr, contexto)) break;
    }
	free(linea);
    if (lista) lista_destruir(lista,free);
	fclose(archivo);    
    return 0;
}