#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "testing.h"
#include "calc.h"

int main (){
	printf("INICIO DE PRUEBAS DE CALC\n");
	char* vector[4] = {"2", "3", "+", NULL};
	int resultado = 0;
	print_test("2+3 retorno ok", procesar_vector_polaco_inverso(vector, &resultado));
	print_test("2+3 resultado 5", resultado == 5);
	
	return 0;
}