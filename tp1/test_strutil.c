#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "strutil.h"
#include "strutil2.h"
#include "testing.h"

bool imprimir_vector_cadenas(char * vector[]){
	if(!vector){
	  //fprintf(stdout, "%s\n","no hay vectores" );
	  return false;
	}
	size_t len_tokens = strv_len(vector);

	fprintf(stdout, "{" );
	for(size_t i=0; i<len_tokens; i++){
	    fprintf(stdout, "\"%s\"", vector[i]);
			if(i!=len_tokens-1)
				fprintf(stdout, ",");
	 }
	 fprintf(stdout, "}\n" );
	 return true;
}

void test_trim (char ** vector){

	fprintf(stderr, "---------------------------\n" );
	fprintf(stderr, "%s\n","el vector de cadenas inicial fue:" );
	imprimir_vector_cadenas(vector);
	size_t len_tokens = strv_len(vector);

	char** literales = calloc(len_tokens+1, sizeof(char*));
	size_t ultimo_literal=0;

	for(size_t i=0; i<len_tokens; i++){
		// Elimino caracteres blancos
		char* aux_literal = trim(vector[i]);
		//fprintf(stderr, "parsee: {%s}. obtuve:{%s}\n",vector[i],aux_literal);
    literales[ultimo_literal++] = aux_literal;
	}

	fprintf(stderr, "%s\n","el vector de cadenas final resulto:" );
	imprimir_vector_cadenas(literales);
	fprintf(stderr, "---------------------------\n");
	free_strv(literales);
}

int main (){
	printf("INICIO DE PRUEBAS DE STRUTIL\n");

	char ** vec;

	vec = split("split uno dos", ' ');
	print_test("split", !strcmp(vec[0],"split"));
	print_test("split", !strcmp(vec[1],"uno"));
	print_test("split", !strcmp(vec[2],"dos"));
	print_test("split", vec[3] == NULL);


	// trim
	printf("TRIM\n");
	char *str1 = " el\t poshito exploto\n ";
	char *tmp = trim(str1);
	fprintf(stderr, "//%s//\n//%s//",str1,tmp );
	print_test("saltos y tabs", !strcmp(tmp, "el\t poshito exploto"));

	fprintf(stderr, "el tamanio de salto de linea: %ld\n",strlen("\n"));

	fprintf(stderr, "isspace barra cero: %d\n",isspace('\0'));

	char * trimee=trim ("\n");
	printf("%s\n",trimee );

	char * vector[]={"\n","",NULL};
	char * vector2[]={"Hola\n","Hola    ",NULL};
	char * vector3[]={" Hola","Hola",NULL};
	char * vector4[]={" Hola ","Hola",NULL};
	char * vector5[]={"","",NULL};

	test_trim(vector);
	test_trim(vector2);
	test_trim(vector3);
	test_trim(vector4);
	test_trim(vector5);


	return 0;
}
