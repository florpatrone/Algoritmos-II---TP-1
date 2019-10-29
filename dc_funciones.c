#include "dc.h"
#include <ctype.h>

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

f_operacion obtener_operacion(const char* operacion){
   if (strcmp(operacion,"+") == 0){
      return &suma;
   }
   if (strcmp(operacion,"-") == 0){
      return &resta;
   }
   if (strcmp(operacion,"*") == 0){
      return &producto;
   }
   if (strcmp(operacion,"/") == 0){
      return &division;
   }
   if (strcmp(operacion,"log") == 0){
      return &logaritmo;
   }
   if (strcmp(operacion,"^") == 0){
      return &potencia;
   }
   return NULL;
}

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
            i++;
            continue;
        }
        
        if (strcmp(simbolo,"sqrt") == 0){    
            resultado = raiz_cuadrada(pila);
        }else if (strcmp(simbolo,"?") == 0){
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
            pila_apilar(pila,resultado);
        }
        i++;
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
        fprintf(stdout,"%s","ERROR\n");
    }else{
        fprintf(stdout,"%i",*(int*)resultado);
        fprintf(stdout,"%c",'\n');
    }
    free(resultado);
}