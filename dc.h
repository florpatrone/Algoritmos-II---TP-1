#define _POSIX_C_SOURCE 200809L
#include "pila.h"
#include "strutil.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef int(*f_operacion)(int,int);

bool es_numero(const char* str);

void destruir_pila(pila_t* pila);

void remover_salto_linea(char** vector);

f_operacion obtener_operacion(const char* operacion);

void calcular(char** entrada);

int suma(int a,int b);

int resta(int a,int b);

int producto(int a,int b);

int division(int a,int b);

int potencia(int a, int b);

int* raiz_cuadrada(pila_t* pila);

int logaritmo(int a,int b);

int* operador_ternario(pila_t* pila);

int* otras_operaciones(pila_t* pila, f_operacion operacion, bool logaritmo, bool potencia, bool division);
