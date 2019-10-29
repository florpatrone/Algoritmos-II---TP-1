#include "dc.h"
#include <stdlib.h>

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