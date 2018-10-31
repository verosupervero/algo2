#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "testing.h"
#include "calc.h"
#include "operaciones.h"


double logg(int n, int b){
	double nn= (double) n;
	double bb= (double) b;
	double res1= log(nn);
	double res2= log(bb);
	return res2?res1/res2:0;
}
int main (){
	printf("INICIO DE PRUEBAS DE CALC\n");
	char* vector[4] = {"2", "3", "+", NULL};
	int resultado = 0;
	print_test("2+3 retorno ok", procesar_vector_polaco_inverso(vector, &resultado));
	print_test("2+3 resultado 5", resultado == 5);

	puts("Probando parseo");
	char* linea = " 2  3\t +  log\n";
	char** tokens = parsear_literales(linea, ' ');

 char* tokens_ok[] = {"2", "3", "+", "log", NULL};
 print_test("largo vector string", strv_len(tokens)==4);
 for (size_t i=0; tokens_ok[i]!=NULL; i++){
   print_test(tokens[i], !strcmp(tokens[i], tokens_ok[i]) && !strcmp(tokens_ok[i], tokens[i]));
 }

for(int i=0;i<17;i++){
	int resultado_log=0;
  logaritmo(16,i,&resultado_log);
  fprintf(stderr, " el resultado del logaritmo es:  %d y el de log posta es: %.1lf\n", resultado_log,logg(16,i));

	logaritmo(5,i,&resultado_log);
  fprintf(stderr, " el resultado del logaritmo es: %d y el de log posta es: %.1lf\n", resultado_log,logg(5,i));


  logaritmo(3,i,&resultado_log);
  fprintf(stderr, " el resultado del logaritmo es: %d  y el de log posta es: %.1lf\n", resultado_log,logg(3,i));

  logaritmo(4,i,&resultado_log);
  fprintf(stderr, " el resultado del logaritmo es: %d  y el de log posta es: %.1lf\n", resultado_log,logg(4,i));


}


	return 0;
}
