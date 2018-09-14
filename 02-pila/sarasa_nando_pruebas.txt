#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define CAPACIDAD_INICIAL       128
#define VOLUMEN                 1000000

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
 pruebas_apilamiento_null();
 pruebas_apilar(1,10);

///////////// CREAR PILA //////////////
void pruebas_pila_crear() {
    pila_t* pila = pila_crear();

    pila_destruir(pila);
}


///////////// APILAMIENTO //////////////
// Se puedan apilar elementos, que al desapilarlos se mantenga el invariante de pila.
void pruebas_apilar(void * dato, long unsigned int volumen){

    pila_t * pila = pila_crear();

    for (int i=0;i<volumen;i++){
      vector[i]= dato;
      pila_apilar(pila,vector[i]);
    }


    print_test("Apilar gran volumen",true);

    pila_destruir(pila);
    free(vector);

}

//bool condicion= pila->capacidad > CAPACIDAD_INICIAL;
//bool condicion2=  pila-> cantidad <= CAPACIDAD_INICIAL;
//    for (int i=0;i<VOLUMEN;i++){
  //    pila_desapilar(pila);
//    }

  //  print_test("Desapilar gran volumen", *capacidad > CAPACIDAD_INICIAL && *cantidad ==0);

///////////// VOLUMEN //////////////
// Se pueden apilar muchos elementos
/* void pruebas_volumen(void){

  pila_t * pila = pila_crear();

  int * vector = malloc(VOLUMEN* sizeof(int));
  for (int i=0;i<VOLUMEN;i++){
    vector[i]=i;
    pila_apilar(pila,&vector[i]);
  }
  bool condicion= pila->capacidad > CAPACIDAD_INICIAL;
  bool condicion2=  pila-> cantidad <= CAPACIDAD_INICIAL;
  print_test("Apilar gran volumen",);

  for (int i=0;i<VOLUMEN;i++){
    pila_desapilar(pila);
  }

  print_test("Desapilar gran volumen", *capacidad > CAPACIDAD_INICIAL && *cantidad ==0);

  pila_destruir(pila);
  free(vector);

} */

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
void pruebas_desapilar_pila_desapilada_(void){

}
