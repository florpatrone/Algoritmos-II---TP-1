#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "strutil.h"
#include "pila.h"

typedef int(*f_operacion)(int,int);

void calcular(char** entrada){
    pila_t* pila = pila_crear();
    int* resultado = NULL;
    int i = 0;
    bool errores = false;

    while ( (entrada[i] != NULL) && (!errores) ){
        char* simbolo = entrada[i];

        if (es_numero(simbolo)){
            int* n = malloc(sizeof(int));
            *n = atoi(simbolo);
            pila_apilar(pila,n);
            continue;
        }
        
        if (strcmp(simbolo,"sqrt") == 0){    
            resultado = raiz_cuadrada(pila);
        }else if (strcmp(simbolo,"?") == 0){
            resultado = operador_ternario(pila);
        }else{
            f_operacion operacion = obtener_operacion(simbolo);
            if (!operacion) break;
            bool es_logaritmo = logaritmo == operacion;
            bool es_potencia = potencia == operacion;
            bool es_division = division == operacion;
            resultado = otras_operaciones(pila,operacion,es_logaritmo,es_potencia,es_division);
        }   
        if (!resultado){
            errores = true;
        }else{
            pila_apilar(pila,resultado);
        }
    }
    if (pila_esta_vacia(pila)){
        errores = true;
    }
    if (!errores){
        resultado = pila_desapilar(pila);
        if (!pila_esta_vacia(pila)){
            errores = true;
        }
    }
    pila_destruir(pila);
    if (errores){
        fprintf(stdout,"%s","ERROR");
    }else{
        fprintf(stdout,"%i",*(int*)resultado);
    }
}

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