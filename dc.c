#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "strutil.h"
#include "pila.h"

typedef int(*f_operacion)(int,int);

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

int suma(int a,int b){
    return a+b;
}

int resta(int a,int b){
    return a-b;
}

int producto(int a,int b){
    return a*b;
}

int division(int a,int b){
    return a/b;
}

int potencia(int a, int b){
    if (b == 0) return 1;
    int n = potencia(a,b/2);
    if (b % 2 == 0) return n*n;
    return n*n*a;
}

int _raiz_cuadrada(int a, int inicio, int fin){
    if ( (a == 0) || (a == 1) ) return a;
    int medio = (inicio + fin) / 2;
    if (medio*medio == a) return medio;
    if (medio*medio < a){
        if ( (medio+1)*(medio+1) > a){
            return medio;
        }
        return _raiz_cuadrada(a,medio+1,fin);
    }      
    return _raiz_cuadrada(a,inicio,medio-1);
  
}

int _logaritmo(int a,int b,int l,int c){
    int n = b*l;
    if (n == a) return c;
    if (n > a) return c-1;
    return _logaritmo(a,b,n,c+1);
}

int logaritmo(int a,int b){
    return _logaritmo(a,b,1,1);
}

int _operador_ternario(int a,int b, int c){
    return a ? b : c;
}

int* raiz_cuadrada(pila_t* pila){
    if (pila_esta_vacia(pila)){
        return NULL;
    }
    int* a = pila_desapilar(pila);
    if (*a < 0){
        free(a);
        return NULL;
    }
    int* resultado = malloc(sizeof(int));   
    *resultado = _raiz_cuadrada(*a,0,*a-1);
    return resultado;
}

int* operador_ternario(pila_t* pila){
    int abc[3];

    for (int j = 0; j < 3; j++){
        if (pila_esta_vacia(pila)){
            return NULL;
        }
        int* n = pila_desapilar(pila);
        abc[j] = *n;
        free(n);
    }

    int* resultado = malloc(sizeof(int));
    *resultado = _operador_ternario(abc[2],abc[1],abc[0]);
    return resultado;
    
}

int* otras_operaciones(pila_t* pila, f_operacion operacion, bool logaritmo, bool potencia, bool division){
    int ab[2];

    for (int j = 0; j < 2; j++){
        if (pila_esta_vacia(pila)){
            return NULL;
        }
        int* n = pila_desapilar(pila);
        ab[j] = *n;
        free(n); 
    }

    if (logaritmo){
        if ( (ab[1] <= 1) || (ab[0] <= 0)) return NULL;
    }else if (potencia){
        if (ab[1] < 0) return NULL;
    }else if (division){
        if (ab[1] == 0) return NULL;
    }

    int* resultado = malloc(sizeof(int));
    *resultado = operacion(ab[0],ab[1]);
    return resultado;
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
            return fprintf(archivo,"%s","Error de memoria\n");
        }
        calcular(entrada);
        free_strv(entrada);
    }
    free(linea);
    fclose(archivo);
    return 0;
}