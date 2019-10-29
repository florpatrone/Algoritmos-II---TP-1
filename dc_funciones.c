#include "dc.h"
#include "strutil.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SUMA "+"
#define RESTA "-"
#define PRODUCTO "*"
#define DIVISION "/"
#define POTENCIA "^"
#define LOGARITMO "log"
#define RAIZ_CUAD "sqrt"
#define OP_TERNARIO "?"

bool es_numero(const char* str){
    int i = 0;
    while (str[i] != '\0'){
        if (!isdigit(str[i])){
            if (!((str[i] == '-')&&(i == 0))) return false;
        }
        i++;
    }
    if ((i == 1)&&(str[0] == '-')){
        return false;
    }
    return i != 0;
}

void destruir_pila(pila_t* pila){
    while (!pila_esta_vacia(pila)){
        free(pila_desapilar(pila));
    }
    pila_destruir(pila);
}

void remover_salto_linea(char** vector){
    int i = 0;
    
    while (vector[i] != NULL) i++;
    if (i == 0) return;
    
    char* str = vector[i-1];
    int j = 0;
    
    while(str[j] != '\n'){
        if (str[j] == '\0') return;
        j++;
    }

    char* nuevo_str = substr(str,j);
    vector[i-1] = nuevo_str;
    free(str);
}

int* numero_convertido(char* str){
    int* n = malloc(sizeof(int));
    if (!n) return NULL;
    *n = atoi(str);
    return n;
}

f_operacion obtener_operacion(const char* operacion){
   if (strcmp(operacion,SUMA) == 0){
      return &suma;
   }
   if (strcmp(operacion,RESTA) == 0){
      return &resta;
   }
   if (strcmp(operacion,PRODUCTO) == 0){
      return &producto;
   }
   if (strcmp(operacion,DIVISION) == 0){
      return &division;
   }
   if (strcmp(operacion,LOGARITMO) == 0){
      return &logaritmo;
   }
   if (strcmp(operacion,POTENCIA) == 0){
      return &potencia;
   }
   return NULL;
}

void calcular(char** entrada){
    pila_t* pila = pila_crear();
    if (!pila){
        fprintf(stdout,"%s","ERROR\n");
        return;
    }
    int* resultado = NULL;
    int i = 0;
    bool errores = false;

    while ( (entrada[i] != NULL) && (!errores) ){
        char* simbolo = entrada[i];

        if (simbolo[0] == '\0'){
            i++;
            continue;
        }
        if (es_numero(simbolo)){
            int* n = numero_convertido(simbolo);
            if ((!n) || (!pila_apilar(pila,n))){
                errores = true;
            }
            i++;
            continue;
        }else if (strcmp(simbolo,RAIZ_CUAD) == 0){    
            resultado = raiz_cuadrada(pila);
        }else if (strcmp(simbolo,OP_TERNARIO) == 0){
            resultado = operador_ternario(pila);
        }else{
            f_operacion operacion = obtener_operacion(simbolo);
            if (!operacion){
                errores = true;
                break;
            }
            bool es_logaritmo = logaritmo == operacion;
            bool es_potencia = potencia == operacion;
            bool es_division = division == operacion;
            resultado = otras_operaciones(pila,operacion,es_logaritmo,es_potencia,es_division);
        }   
        if (!resultado){
            errores = true;
        }else{
            if (!pila_apilar(pila,resultado)) errores = true;
        }
        i++;
    }
    if (pila_esta_vacia(pila)){
        errores = true;
    }
    if (!errores){
        resultado = pila_desapilar(pila);
        if (!pila_esta_vacia(pila)) errores = true;
    }
    destruir_pila(pila);
    if (errores){
        fprintf(stdout,"%s","ERROR\n");
    }else{
        fprintf(stdout,"%i%c",*(int*)resultado,'\n');
    }
    free(resultado);
}