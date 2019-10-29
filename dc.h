#include "pila.h"
#include <stdbool.h>
#include <stddef.h>

typedef int(*f_operacion)(int,int);

//Recibe una cadena y devuelve true si es equivalente a un numero entero,
//false en caso contrario.
bool es_numero(const char* str);

//Destruye una pila y elimina sus elementos
//Pre: la pila fue creada; los elementos se encuentran en memoria dinamica.
void destruir_pila(pila_t* pila);

//Recibe un vector de cadenas terminado en NULL.
//y remueve, si lo hay, el salto de linea de la ultima cadena.
//Pre: el vector contiene cadenas en memoria dinamica y termina en NULL.
//Post: la ultima cadena del vector es identica pero sin el salto de linea.
void remover_salto_linea(char** vector);

//Dado una cadena, devuelve la operacion asociada a esa cadena,
//NULL si no corresponde a ninguna operacion.
f_operacion obtener_operacion(const char* operacion);

//Dada una cadena de numeros y operaciones, realiza calculos
//utilizando notacion polaca inversa
//e imprime el resultado o un mensaje de error
void calcular(char** entrada);

//Devuelve la suma de dos enteros.
int suma(int a,int b);

//Devuelve la resta de dos enteros.
int resta(int a,int b);

//Devuelve el producto de dos enteros.
int producto(int a,int b);

//Devuelve la division de dos enteros.
//Pre: el segundo entero debe ser distinto a 0.
int division(int a,int b);

//Devuelve la potencia de un entero elevado al otro.
//Pre: el segundo entero debe ser mayor o igual a 0.
int potencia(int a, int b);

//Devuelve el logaritmo de un entero en base del segundo.
//Pre: el primer entero debe ser mayor estricto a 0,
//el segundo entero debe ser mayor estricto a 1.
int logaritmo(int a,int b);

//Dada una pila de enteros, aplica la operacion 'raiz_cuadrada'
//a el ultimo elemento de la pila,
//y devuelve un puntero al resultado (un entero) en memoria dinamica
//o NULL en caso de error.
//Pre: la pila fue creada.
int* raiz_cuadrada(pila_t* pila);

//Dada una pila de enteros, aplica la operacion 'operador_ternario'
//a los ultimos tres elementos de la pila,
//y devuelve un puntero al resultado (un entero) en memoria dinamica
//o NULL en caso de error.
//Pre: la pila fue creada.
int* operador_ternario(pila_t* pila);

//Dada una pila de enteros y una operacion,
//aplica esa operacion a los ultimos dos elementos de la pila
//y devuelve un puntero al resultado (un entero) en memoria dinamica
//o NULL en caso de error.
//Pre: la operacion debe recibir 2 enteros y devolver un entero, la pila fue creada.
int* otras_operaciones(pila_t* pila, f_operacion operacion, bool logaritmo, bool potencia, bool division);