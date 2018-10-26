#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "strutil.h"
#include "testing.h"


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
	print_test("saltos y tabs", !strcmp(tmp, "el\t poshito exploto"));

	return 0;
}
