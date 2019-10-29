#include "lista.h"
#include <stdbool.h>
#include <stddef.h>

//Dada una cadena, devuelve true si es equivalente a
//un numero entero postivo, false en caso contrario.
bool es_numero(const char* str);

//Dada una cadena y una subcadena, devuelve true si 
//la subcadena se encuentra dentro de la cadena,
//false en caso contrario.
bool contiene_substr(const char* str, const char* substr);

//Dada una lista de cadenas, una cadena, una subcadena y un numero entero,
//si la subcadena se encuentra en la cadena, la imprime,
//si ademas el numero es mayor a cero imprime esa cantidad de lineas
//sacadas de la lista.
//En caso de error, devuelve false, caso contrario devuevle true.
bool imprimir_linea(lista_t* lista, const char* linea, const char* substr, int contexto);   