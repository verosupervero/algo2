#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"
#include "operaciones.h"

bool validar_entero(char * literal, int ** pp_entero);
bool validar_operacion(char * literal,function_t operacion);
bool procesar_literales(pila_t * pila,char * literal);
#endif // PROCESAMIENTO_H
