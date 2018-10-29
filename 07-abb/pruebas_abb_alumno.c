#include "abb.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define VOLUMEN_GRANDE          10000
#define VOLUMEN_CHICO           10
#define VOLUMEN_MEDIO           1000

bool imprimir_claves(const char* clave, void* valor, void* extra){
	printf ("[%s,%d]\n", clave, *(int*) valor);
	return true;
}
bool imprimir_claves_strings(const char* clave, void* valor, void* extra){
	printf ("[%s,%s]->", clave,(char*) valor);
	return true;
}
/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_arbol_vacio(){

	printf("INICIO DE PRUEBAS DE ARBOL VACIO\n");

	abb_t* arbol = abb_crear(*strcmp, NULL);

	print_test("Prueba arbol vacio: ", arbol);
	print_test("El arbol tiene 0: ", abb_cantidad(arbol) == 0);

	print_test("NULL no pertenece, ", !abb_pertenece(arbol, NULL));
	print_test("'clave' no pertenece, ", !abb_pertenece(arbol, "clave"));
	print_test("El arbol tiene 0: ", abb_cantidad(arbol) == 0);
	print_test("Clave NULL no tiene valor asociado, ", !abb_obtener(arbol, NULL));
	print_test("Clave 'clave' no tiene valor asociado, ", !abb_obtener(arbol, "clave"));

	// Prueba con iter interno
	abb_in_order(arbol, imprimir_claves, NULL);
	printf("\n");
	print_test("Inorder al arbol vacio, ", true);

	// Prueba con iter externo
	abb_iter_t* iter = abb_iter_in_crear(arbol);
	print_test("Crear iterador externo, ", iter);
	fprintf(stderr, "%s\n","pude crear el iterador" );
	print_test("Iterador esta al final, ", abb_iter_in_al_final(iter));
	print_test("Iterador actual es NULL, ", !abb_iter_in_ver_actual(iter));
	print_test("Iterador no puede avanzar, ", !abb_iter_in_avanzar(iter));
	abb_iter_in_destruir(iter);
	print_test("Destruir iterador, ", true);
	print_test("El arbol tiene 0: ", abb_cantidad(arbol) == 0);

	abb_destruir(arbol);
	print_test("Destruir arbol, ", true);
}

void pruebas_claves_ayudantes_e_in_order() {

	printf("INICIO DE PRUEBAS ABB NOMBRES\n");

	char *valor_martin = "Martin";
	char *valor_dato = "Dato";
	char *valor_agustina = "Agustina";
	char *valor_ezequiel = "Ezequiel";
	char *valor_matias = "Matias";
	char *valor_ignacio = "Ignacio";
	char *valor_federico = "Federico";
	char *valor_camila_d = "Camila D";
	char *valor_anita = "Anita";
	char *valor_jasmina = "Jasmina";
	char *valor_jorge = "Jorge";
	char *valor_olivia= "Olivia";

	abb_t* arbol = abb_crear(*strcmp, NULL);
	if(!arbol)
		return;

	size_t arbol_cantidad=abb_cantidad(arbol);
	print_test("Guardo nodo de clave 72 y valor Martin: ", abb_guardar(arbol, "72", valor_martin));
	print_test("El 72 pertenece al arbol", abb_pertenece(arbol, "72"));
	arbol_cantidad++;
	print_test("Cantidad de nodos ok: ", abb_cantidad(arbol) == arbol_cantidad);
	printf("\n");
	fprintf(stderr, "%s\n","Recorrido del arbol inorder:" );
	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	print_test("Guardo nodo de clave 5 y valor Dato", abb_guardar(arbol, "5", valor_dato));
	print_test("El 5 pertenece al arbol", abb_pertenece(arbol, "5"));
	arbol_cantidad++;
	printf("\n");
	fprintf(stderr, "%s\n","Recorrido del arbol inorder:" );
	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	print_test("Cantidad de nodos ok: ", abb_cantidad(arbol) == arbol_cantidad);

	print_test("Guardo nodo de clave 100 y valor Ezequiel", abb_guardar(arbol, "100", valor_ezequiel));
	print_test("El 100 pertenece al arbol", abb_pertenece(arbol, "100"));
	arbol_cantidad++;
	printf("\n");
	fprintf(stderr, "%s\n","Recorrido del arbol inorder:" );
	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	print_test("Guardo nodo de clave 3 y valor Agustina", abb_guardar(arbol, "3", valor_agustina));
	print_test("El 3 pertenece al arbol", abb_pertenece(arbol, "3"));
	arbol_cantidad++;
	printf("\n");
	fprintf(stderr, "%s\n","Recorrido del arbol inorder:" );
	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	print_test("Guardo nodo de clave 6 y valor Ignacio", abb_guardar(arbol, "6", valor_ignacio));
	print_test("El 6 pertenece al arbol", abb_pertenece(arbol, "6"));
	arbol_cantidad++;
	printf("\n");
	fprintf(stderr, "%s\n","Recorrido del arbol inorder:" );
	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	print_test("Cantidad de nodos ok: ", abb_cantidad(arbol) == arbol_cantidad);

	print_test("Matias da la clase, reemplazo dato (Curioso: reemplazo Dato) de clave 5 por Matias: ", abb_guardar(arbol, "5", valor_matias));
	print_test("Cantidad de nodos ok: ", abb_cantidad(arbol) == arbol_cantidad);

	printf("\n");
	fprintf(stderr, "%s\n","Recorrido del arbol inorder:" );
	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	fprintf(stdout, "%s\n","Obtencion/Busqueda de claves en el arbol" );
	print_test("Busco clave 100 con abb_pertenece, devuelve TRUE: ", abb_pertenece(arbol, "100"));
	print_test("Busco clave 0 con abb_pertenece, devuelve FALSE: ", !abb_pertenece(arbol, "0"));
	print_test("Busca valor de 5, devuelve Matias: ", valor_matias == abb_obtener(arbol, "5"));
	print_test("Busca valor de 1000, devuelve NULL: ", NULL == abb_obtener(arbol, "1000"));
	printf("\n");

	/*Borrado de nodos*/
	print_test("Borro nodo sin hijos, devuelve Agustina: ", abb_borrar(arbol, "3") == valor_agustina);
	arbol_cantidad--;
	print_test("Busco si pertenece el 3, clave asociada previamente a Agustina: ", !abb_pertenece(arbol, "3"));
	print_test("Cantidad de nodos ok: ", abb_cantidad(arbol) == arbol_cantidad);
	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	printf("\n");
	fprintf(stderr, "%s\n","Recorrido del arbol inorder:" );
	print_test("Jorge da la clase, reemplazo Ezequiel en arbol: ", abb_guardar(arbol, "100", valor_jorge));
	print_test("Cantidad de nodos ok: ", abb_cantidad(arbol) == arbol_cantidad);

	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	print_test("Guardo nodo de clave 98 y valor Ezequiel:", abb_guardar(arbol, "98", valor_ezequiel));
	print_test("Guardo nodo de clave 99 y valor Jasmina:", abb_guardar(arbol, "99", valor_jasmina));
	print_test("Guardo nodo de clave 108 y valor Federico:", abb_guardar(arbol, "108", valor_federico));
	print_test("Guardo nodo de clave 107 y valor Camila D: ", abb_guardar(arbol, "107", valor_camila_d));
	print_test("Guardo nodo de clave 106 y valor Anita: ", abb_guardar(arbol, "106", valor_anita));
	arbol_cantidad+=5;

	printf("\n");
	fprintf(stderr, "%s\n","Recorrido del arbol inorder:" );
	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	printf("\n");

	print_test("Olivia viene a la clase, se va Anita en arbol: ", abb_guardar(arbol, "106", valor_olivia));
	print_test("Cantidad de nodos ok: ", abb_cantidad(arbol) == arbol_cantidad);

	printf("\n");
	fprintf(stderr, "%s\n","Recorrido del arbol inorder:" );
	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	printf("\n");

	print_test("Borro nodo 1 hijo, devuelve Ezequiel: ", abb_borrar(arbol, "98") == valor_ezequiel);
	arbol_cantidad--;
	print_test("Busco si pertenece el 98, clave asociada previamente a Ezequiel: ", !abb_pertenece(arbol, "98"));
	print_test("Cantidad de nodos ok: ", abb_cantidad(arbol) == arbol_cantidad);
	printf("\n");

	fprintf(stderr, "%s\n","Recorrido del arbol inorder:" );
	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	printf("\n");
	print_test("Borro nodo 2 hijos, devuelve Jorge: ", abb_borrar(arbol, "100") == valor_jorge);
	arbol_cantidad--;
	print_test("Busco si pertenece el 100, clave asociada previamente a Jorge: ", !abb_pertenece(arbol, "100"));
	print_test("Cantidad de nodos ok: ", abb_cantidad(arbol) == arbol_cantidad);
	printf("\n");

	fprintf(stderr, "%s\n","Recorrido del arbol inorder:" );
	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	print_test("Borro raiz, devuelve Martín, tenía 2 hijos: ", abb_borrar(arbol, "72") == valor_martin);
	arbol_cantidad--;
	print_test("Busco si pertenece el 72, clave asociada previamente a Jorge: ", !abb_pertenece(arbol, "72"));
	print_test("Cantidad de nodos ok: ", abb_cantidad(arbol) == arbol_cantidad);
	printf("\n");

	fprintf(stderr, "%s\n","Recorrido del arbol inorder:" );
	abb_in_order(arbol, imprimir_claves_strings, NULL);
	printf("\n");

	abb_destruir(arbol);
	print_test("Destruir arbol, ", true);
}


void pruebas_iterar_volumen(size_t volumen, char * nombre_volumen){ //aqui
	abb_t* arbol = abb_crear(*strcmp, NULL);
	if(!arbol)
		return;

  const size_t largo_clave = 10;
  char (*claves)[largo_clave] = malloc(volumen * largo_clave);

  size_t valores[volumen];

  /* Inserta 'largo' parejas en el arbol */
  bool ok = true;
  for (unsigned i = 0; i < volumen; i++) {
      sprintf(claves[i], "%08d", i);
      valores[i] = i;
      ok = abb_guardar(arbol, claves[i], &valores[i]);
      if (!ok) break;
  }

	printf("\nINICIO DE PRUEBAS DE ITERAR UN ARBOL RELLENO %s (%ld elementos)\n",nombre_volumen,volumen);
	abb_iter_t* iter = abb_iter_in_crear(arbol);
	print_test("Crear iterador externo, ", iter);

	print_test("Cantidad de elementos correctos:", abb_cantidad(arbol)==volumen);
	print_test("Puede avanzar iterador en arbol:", abb_iter_in_avanzar(iter)==true);

	ok = true;
  const char *clave;
  size_t *valor;

  while(!abb_iter_in_al_final(iter)) {
      clave = abb_iter_in_ver_actual(iter);
      if (!clave){
          ok = false;
          break;
      }
      valor = abb_obtener(arbol, clave);
      if (!valor) {
          ok = false;
          break;
      }
      abb_iter_in_avanzar(iter);
  }
  print_test("Prueba arbol iteración en volumen", ok);
  print_test("Prueba arbol iterador esta al final, es true", abb_iter_in_al_final(iter));
	abb_iter_in_destruir(iter);
	abb_destruir(arbol);
	print_test("Arbol destruido:", true);
	print_test("Iterador destruido:", true);
}
static void prueba_arbol_clave_vacia(){
    abb_t* arbol = abb_crear(*strcmp,NULL);

    char *clave = "", *valor = "";

    print_test("Prueba arbol insertar clave vacia", abb_guardar(arbol, clave, valor));
    print_test("Prueba arbol la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    print_test("Prueba arbol obtener clave vacia es valor", abb_obtener(arbol, clave) == valor);
    print_test("Prueba arbol pertenece clave vacia, es true", abb_pertenece(arbol, clave));
    abb_destruir(arbol);
}

void pruebas_abb_alumno() {
	//pruebas_arbol_vacio();
	pruebas_claves_ayudantes_e_in_order();
	//pruebas_iterar_volumen(VOLUMEN_CHICO, "Volumen chico");
  //pruebas_iterar_volumen(VOLUMEN_MEDIO,"Volumen medio");
  //pruebas_iterar_volumen(VOLUMEN_GRANDE,"Volumen grande");
	prueba_arbol_clave_vacia();
}


int main(int argc, char *argv[])
{
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_abb_alumno();

    return failure_count() > 0;
}
