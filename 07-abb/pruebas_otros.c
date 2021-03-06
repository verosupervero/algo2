#include "abb.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int strcmp_for_integers(const char *aa, const char *bb){
    char aa2[11] = "";
    char bb2[11] = "";
    int answer;

    sprintf(aa2, "%010d", atoi(aa));
    sprintf(bb2, "%010d", atoi(bb));
    answer = strcmp(aa2, bb2);

    return answer;
}

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
// ESTRUCTURAS; VARIABLES Y DEFINICIONES AUXILARES
// char* clave1 = "a";
// char* clave2 = "b";
// char* clave3 = "c";
// char* clave4 = "d";
// char* clave5 = "e";
// char* clave6 = "f";
// char* clave7 = "g";
// char* clave8 = "h";
// char* clave9 = "i";
// char* clave10 = "j";

char* clave1 = "1";
char* clave2 = "2";
char* clave3 = "3";
char* clave4 = "4";
char* clave5 = "5";
char* clave6 = "6";
char* clave7 = "7";
char* clave8 = "8";
char* clave9 = "9";
char* clave10 = "10";

bool imprimir_clave(const char* clave, void* dato, void* extra) {
	if (clave != NULL){
		printf("%s\n", clave);
    	return true;
    }
    return false;
 }


static void prueba_abb_iter_interno(abb_t* abb2) {
    abb_in_order(abb2, imprimir_clave, NULL);
}

static void prueba_abb_volumen(size_t largo, bool debug)
{
    abb_t* abb3 = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb3, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb3) == largo);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb3, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb3, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb3) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb3, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb3) == 0);

    /* Destruye el abb y crea uno nuevo que sí libera */
    abb_destruir(abb3);
    abb3 = abb_crear(strcmp, free);

    /* Inserta 'largo' parejas en el abb */
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb3, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);

    /* Destruye el abb - debería liberar los enteros */
    abb_destruir(abb3);

}
void pruebas_abb_vacio(){
	//ABB VACIO
	abb_t* abb1 = abb_crear(strcmp, NULL);
	print_test("El ABB fue creado exitosamente", abb1 != NULL);
	print_test("El ABB esta vacio inicialmente", abb_cantidad(abb1) == 0);
	print_test("Existe nodo con clave 'Prueba' es false", abb_pertenece(abb1, "Prueba") == false );
	print_test("Obtener dato de nodo con clave 'Prueba' es NULL", abb_obtener(abb1, "Prueba") == NULL );
	abb_iter_t* iter1 = abb_iter_in_crear(abb1);
	print_test("El iterador fue creado", iter1 != NULL);
	print_test("Avanzar con el iterador es false", abb_iter_in_avanzar(iter1) == false);
	print_test("Ver actual con el iterador es NULL", abb_iter_in_ver_actual(iter1) == NULL);
	print_test("El iterador esta al final", abb_iter_in_al_final(iter1) == true);
		abb_iter_in_destruir(iter1);
		abb_destruir(abb1);
}

bool imprimir_claves_strings(const char* clave, void* valor, void* extra){
	if(valor){
		printf ("[%s,%s]->", clave,(char*) valor);
		return true;
	}
	printf ("[%s,%s]->", clave,"NULL");
	return true;
}

void pruebas_un_elemento(){
	//ABB 1 ELEMENTO
	abb_t* abb1 = abb_crear(strcmp, NULL);
	print_test("El ABB fue creado exitosamente", abb1 != NULL);
print_test("El ABB esta vacio inicialmente", abb_cantidad(abb1) == 0);
print_test("Existe nodo con clave 'Prueba' es false", abb_pertenece(abb1, "Prueba") == false );
print_test("Obtener dato de nodo con clave 'Prueba' es NULL", abb_obtener(abb1, "Prueba") == NULL );
print_test("Guardar clave1 fue logrado exitosamente", abb_guardar(abb1, clave1, NULL) == true );
print_test("abb2 tiene 1 nodo", abb_cantidad(abb1) == 1);
bool borrar= abb_borrar(abb1, clave1)==NULL;
	print_test("Borrar clave 1", borrar);
	print_test("abb2 tiene 0 nodos", abb_cantidad(abb1) == 0);

abb_in_order(abb1, imprimir_claves_strings, NULL);
printf("\n");
print_test("Clave 1 no pertenece", abb_pertenece(abb1, clave1) == false);
print_test("Obtener clave 1 es NULL", abb_obtener(abb1, clave1) == NULL);
abb_destruir(abb1);

}

void pruebas_abb_funcion_destructora(){
	  //ABB FUNCIÓN DESTRUCTORA
  abb_t* abb1 = abb_crear(strcmp_for_integers, free);
  print_test("El ABB fue creado exitosamente (con funcion destructora)", abb1 != NULL);
	print_test("El ABB esta vacio inicialmente", abb_cantidad(abb1) == 0);
	print_test("Existe nodo con clave 'Prueba' es false", abb_pertenece(abb1, "Prueba") == false );
	print_test("Obtener dato de nodo con clave 'Prueba' es NULL", abb_obtener(abb1, "Prueba") == NULL );
	int* dato1 = malloc(sizeof(int));
	int* dato2 = malloc(sizeof(int));
	print_test("Guardar clave1 fue logrado exitosamente", abb_guardar(abb1, clave1, dato1) == true );
	print_test("Obtener dato de nodo con clave 'Prueba' es dato 1", abb_obtener(abb1, "Prueba") == NULL );
	print_test("Guardar clave1 con nueva clave fue logrado exitosamente", abb_guardar(abb1, clave1, dato2) == true );
	print_test("Obtener dato de nodo con clave 'Prueba' es dato 2", abb_obtener(abb1, "Prueba") == NULL );
	print_test("abb2 tiene 1 nodo", abb_cantidad(abb1) == 1);
	  print_test("Borrar clave 1", abb_borrar(abb1, clave1) == dato2);
	  free(dato2); //Dato recuperado en la prueba anterior, lo borro...
		print_test("Clave 1 no pertenece", abb_pertenece(abb1, clave1) == false);
		print_test("Obtener clave 1 es NULL", abb_obtener(abb1, clave1) == NULL);
	  abb_destruir(abb1);

}

void pruebas_abb_alumno() {
	//	pruebas_abb_vacio();
	//	pruebas_un_elemento();
	//	pruebas_abb_funcion_destructora();
	//ABB 8 ELEMENTOS
	abb_t* abb2 = abb_crear(strcmp_for_integers, NULL);
  int dummy = 22;
	print_test("El ABB fue creado exitosamente", abb2 != NULL);
	print_test("El ABB esta vacio inicialmente", abb_cantidad(abb2) == 0);
	print_test("Existe nodo con clave 'Prueba' es false", abb_pertenece(abb2, "Prueba") == false );
	print_test("Obtener dato de nodo con clave 'Prueba' es NULL", abb_obtener(abb2, "Prueba") == NULL );
	print_test("Guardar clave7 fue logrado exitosamente", abb_guardar(abb2, clave7, &dummy) == true );
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


	print_test("Guardar clave1 fue logrado exitosamente", abb_guardar(abb2, clave1, &dummy) == true );
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


	print_test("Guardar clave4 fue logrado exitosamente", abb_guardar(abb2, clave4, &dummy) == true );
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


	print_test("Guardar clave10 fue logrado exitosamente", abb_guardar(abb2, clave10, &dummy) == true );
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


	print_test("Guardar clave9 fue logrado exitosamente", abb_guardar(abb2, clave9, &dummy) == true );
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


	print_test("Guardar clave2 fue logrado exitosamente", abb_guardar(abb2, clave2, &dummy) == true );

	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");

	print_test("Guardar clave6 fue logrado exitosamente", abb_guardar(abb2, clave6, &dummy) == true );
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


	print_test("Guardar clave8 fue logrado exitosamente", abb_guardar(abb2, clave8, &dummy) == true );
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");



	print_test("Guardar clave5 fue logrado exitosamente", abb_guardar(abb2, clave5, &dummy) == true );
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


	print_test("Guardar clave3 fue logrado exitosamente", abb_guardar(abb2, clave3, &dummy) == true );
	print_test("abb2 tiene 10 nodos", abb_cantidad(abb2) == 10);
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


	//fprintf(stderr, "la raiz del abb2 es: %s\n",abb_obtener_clave_raiz(abb2));
	abb_iter_t* iter2 = abb_iter_in_crear(abb2);
	print_test("El iterador fue creado", iter2 != NULL);
	print_test("Primer clave es 'a'", strcmp_for_integers(abb_iter_in_ver_actual(iter2), clave1) == 0);
	print_test("Avanzo con el iterador", abb_iter_in_avanzar(iter2) == true);
	print_test("Segunda clave es 'b'", strcmp_for_integers(abb_iter_in_ver_actual(iter2), clave2) == 0);
	print_test("Avanzo con el iterador", abb_iter_in_avanzar(iter2) == true);
	print_test("Tercera clave es 'c'", strcmp_for_integers(abb_iter_in_ver_actual(iter2), clave3) == 0);
	print_test("Avanzo con el iterador", abb_iter_in_avanzar(iter2) == true);
	print_test("Cuarta clave es 'd'", strcmp_for_integers(abb_iter_in_ver_actual(iter2), clave4) == 0);
	print_test("Avanzo con el iterador", abb_iter_in_avanzar(iter2) == true);
	print_test("Quinta clave es 'e'", strcmp_for_integers(abb_iter_in_ver_actual(iter2), clave5) == 0);
	print_test("Avanzo con el iterador", abb_iter_in_avanzar(iter2) == true);
	print_test("Sexta clave es 'f'", strcmp_for_integers(abb_iter_in_ver_actual(iter2), clave6) == 0);
	print_test("Avanzo con el iterador", abb_iter_in_avanzar(iter2) == true);
	print_test("Septima clave es 'g'", strcmp_for_integers(abb_iter_in_ver_actual(iter2), clave7) == 0);
	print_test("Avanzo con el iterador", abb_iter_in_avanzar(iter2) == true);
	print_test("Octava clave es 'h'", strcmp_for_integers(abb_iter_in_ver_actual(iter2), clave8) == 0);
	print_test("Avanzo con el iterador", abb_iter_in_avanzar(iter2) == true);
	print_test("Octava clave es 'i'", strcmp_for_integers(abb_iter_in_ver_actual(iter2), clave9) == 0);
	print_test("Avanzo con el iterador", abb_iter_in_avanzar(iter2) == true);
	print_test("Octava clave es 'j'", strcmp_for_integers(abb_iter_in_ver_actual(iter2), clave10) == 0);
	print_test("Avanzar con el iterador es true", abb_iter_in_avanzar(iter2) == true);
	print_test("Ver actual con el iterador es NULL", abb_iter_in_ver_actual(iter2) == NULL);
	print_test("El iterador esta al final", abb_iter_in_al_final(iter2) == true);
	print_test("Avanzar con el iterador es false", abb_iter_in_avanzar(iter2) == false);
	prueba_abb_iter_interno(abb2);
  abb_iter_in_destruir(iter2);
  print_test("Borrar clave 10: j", abb_borrar(abb2, clave10) == &dummy);
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	////print_t(abb2);
	printf("___________________________________________________________\n");


  print_test("Borrar clave 9: i", abb_borrar(abb2, clave9) == &dummy);
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


  print_test("Borrar clave 1: a", abb_borrar(abb2, clave1) == &dummy);
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


  print_test("Borrar clave 6: f", abb_borrar(abb2, clave6) == &dummy);
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


  print_test("Borrar clave 4 :d", abb_borrar(abb2, clave4) == &dummy);

	abb_in_order(abb2, imprimir_claves_strings, NULL);
		printf("\n");

	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");



	print_test("Borrar clave 7: g", abb_borrar(abb2, clave7) == &dummy);

	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");



  print_test("Borrar clave 5: e", abb_borrar(abb2, clave5) == &dummy);

	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


	print_test("Borrar clave 8: h", abb_borrar(abb2, clave8) == &dummy);
	fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");


	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	print_test("Borrar clave 3 : c", abb_borrar(abb2, clave3) == &dummy);

  fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
	abb_in_order(abb2, imprimir_claves_strings, NULL);
	printf("\n");
	// Dibujito del abb2
	//print_t(abb2);
	printf("___________________________________________________________\n");

  print_test("Borrar clave 2 : b", abb_borrar(abb2, clave2) == &dummy);
  fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
  abb_in_order(abb2, imprimir_claves_strings, NULL);
  printf("\n");
  // Dibujito del abb2
  //print_t(abb2);
  printf("___________________________________________________________\n");

	print_test("El ABB tiene 0 nodos", abb_cantidad(abb2) == 0);
	printf("%d\n", (int)abb_cantidad(abb2));
	print_test("Clave 7 no pertenece", abb_pertenece(abb2, clave7) == false);
  fprintf(stderr, "%s\n","Recorrido del abb2 inorder:" );
  abb_in_order(abb2, imprimir_claves_strings, NULL);
  printf("\n");
  // Dibujito del abb2
  //print_t(abb2);
  printf("___________________________________________________________\n");
  print_test("Obtener clave 7 es NULL", abb_obtener(abb2, clave7) == NULL);
	print_test("Clave 4 no pertenece", abb_pertenece(abb2, clave4) == false);
  print_test("Obtener clave 4 es NULL", abb_obtener(abb2, clave4) == NULL);
	print_test("Clave 1 no pertenece", abb_pertenece(abb2, clave1) == false);
	print_test("Obtener clave 1 es NULL", abb_obtener(abb2, clave1) == NULL);
	print_test("Clave 8 no pertenece", abb_pertenece(abb2, clave8) == false);
	print_test("Obtener clave 8 es NULL", abb_obtener(abb2, clave8) == NULL);

  print_test("Clave 6 no pertenece", abb_pertenece(abb2, clave6) == false);
	print_test("Obtener clave 6 es NULL", abb_obtener(abb2, clave6) == NULL);
	print_test("Clave 5 no pertenece", abb_pertenece(abb2, clave5) == false);
	print_test("Obtener clave 5 es NULL", abb_obtener(abb2, clave5) == NULL);
	print_test("Clave 10 no pertenece", abb_pertenece(abb2, clave10) == false);
	print_test("Obtener clave 10 es NULL", abb_obtener(abb2, clave10) == NULL);
	print_test("Clave 3 no pertenece", abb_pertenece(abb2, clave9) == false);
	print_test("Obtener clave 3 es NULL", abb_obtener(abb2, clave9) == NULL);
	print_test("Clave 2 no pertenece", abb_pertenece(abb2, clave2) == false);
	print_test("Obtener clave 2 es NULL", abb_obtener(abb2, clave2) == NULL);
	print_test("Clave 4 no pertenece", abb_pertenece(abb2, clave4) == false);
	print_test("Obtener clave 4 es NULL", abb_obtener(abb2, clave4) == NULL);
	abb_destruir(abb2);

	//Prueba de volumen modificada del abb
    prueba_abb_volumen(500, true);

}


int main(int argc, char *argv[])
{
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_abb_alumno();

    return failure_count() > 0;
}
