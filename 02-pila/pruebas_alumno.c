#include "pila.h"
#include "testing.h"
#include <stddef.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/


///////////// CREAR PILA //////////////
void pruebas_pila_crear() {
    pila_t* pila = pila_crear();

    pila_destruir(pila);
}


///////////// APILAMIENTO //////////////
// Se puedan apilar elementos, que al desapilarlos se mantenga el invariante de pila.
void pruebas_apilamiento(void){

}

///////////// VOLUMEN //////////////
// Se pueden apilar muchos elementos
void pruebas_volumen(void){

}

///////////// APILAMIENTO NULL //////////////
// El apilamiento del elemento NULL es válido.

//aca pongo las funciones
void apilamiento_null_medio(void){
  int a = 1, b = 2, c = 3;
  int *a_ret, *b_ret, *c_ret, *null_ret;

  pila_t * pila = pila_crear();

  pila_apilar(pila, &a);
  pila_apilar(pila, &b);
  pila_apilar(pila, NULL);
  pila_apilar(pila, &c);

  // Desapilo
  c_ret = pila_desapilar(pila);
  null_ret = pila_desapilar(pila);
  b_ret = pila_desapilar(pila);
  a_ret = pila_desapilar(pila);

  print_test("Desapilar NULL en medio", c_ret!=NULL && *c_ret == c && null_ret == NULL && b_ret!=NULL && *b_ret == b && a_ret!=NULL && *a_ret );
  pila_destruir(pila);
}

void apilamiento_null_arriba(void){
  int a = 1;
  int *a_ret, *null_ret;

  pila_t * pila = pila_crear();

  pila_apilar(pila, &a);
  pila_apilar(pila, NULL);

  // Desapilo
  null_ret = pila_desapilar(pila);
  a_ret = pila_desapilar(pila);

  print_test("Desapilar NULL arriba", null_ret == NULL && a_ret!=NULL && *a_ret );
  pila_destruir(pila);
}

void apilamiento_null_abajo(void){
  int a = 1;
  int *a_ret, *null_ret;

  pila_t * pila = pila_crear();

  pila_apilar(pila, NULL);
  pila_apilar(pila, &a);

  // Desapilo
  a_ret = pila_desapilar(pila);
  null_ret = pila_desapilar(pila);

  print_test("Desapilar NULL abajo", null_ret == NULL && a_ret!=NULL && *a_ret );
  pila_destruir(pila);
}


void pruebas_apilamiento_null(){
  // y aca abajo las llamo
  apilamiento_null_medio();
  apilamiento_null_arriba();
  apilamiento_null_abajo();
}

///////////// APILAMIENTO NULL //////////////
// El apilamiento del elemento NULL es válido.

//aca pongo las funciones

void pruebas_pila_nueva_igual_desapilada(void){
// y aca abajo las llamo
}

///////////// APILAMIENTO NULL //////////////
// El apilamiento del elemento NULL es válido.
void pruebas_pila_nueva_desapilar(void){

}

///////////// APILAMIENTO NULL //////////////
// El apilamiento del elemento NULL es válido.
void pruebas_pila_nueva_es_vacia(void){

}

///////////// APILAMIENTO NULL //////////////
// El apilamiento del elemento NULL es válido.
void pruebas_pila_desapilada_desapilar(void){

}
