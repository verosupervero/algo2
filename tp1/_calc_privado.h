#ifndef __CALC_PRIVADO_H__
#define __CALC_PRIVADO_H__

/* .h para compilacion y testeo de calc.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"
#include "strutil.h"
#include "operaciones.h"

#define ANSI_COLOR_LGH_RED	   "\x1b[1m\x1b[31m"
#define ANSI_COLOR_LGH_GREEN   "\x1b[1m\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef (bool)(*function_t)(pila_t * pila);

bool aplicar_operador_ternario(pila_t * pila);
bool aplicar_raiz_cuadrada(pila_t * pila);
bool aplicar_logaritmo(pila_t * pila);
bool aplicar_potencia(pila_t * pila);
bool aplicar_division(pila_t * pila);
bool aplicar_multiplicacion(pila_t * pila);
bool aplicar_resta(pila_t * pila);
bool aplicar_suma(pila_t * pila);
bool validar_entero(char * literal, int ** pp_entero);
bool validar_operacion(char * literal,function_t *operacion);
bool procesar_literales(pila_t * pila,char * literal);
bool procesar_calculo_polaco_inverso (char * linea, int * resultado);

#endif __CALC_PRIVADO_H__
