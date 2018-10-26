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
	
	puts("Probando parseo");
	char* linea = " 2  3\t +  log\n";
	char** tokens = parsear_literales(linea, ' ');
 
 char* tokens_ok = {"2", "3", "+", "log", NULL};
 print_test("largo vector string", strv_len(tokens)==4);
 for (size_t i=0; tokens_ok[i]!=NULL; i++){
   print_test(tokens[i], !strcmp(tokens[i], tokens_ok[i]) && !strcmp(tokens_ok[i], tokens[i]));
 }
 
	return 0;
}