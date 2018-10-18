#ifndef __CALC_H__
#define __CALC_H__

/* .h para la distribución de la biblioteca calc.c*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"
#include "strutil.h"
#include "operaciones.h"

bool procesar_calculo_polaco_inverso (char * linea, int * resultado);

#endif __CALC_H__
