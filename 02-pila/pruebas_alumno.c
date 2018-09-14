#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

#define VOLUMEN_GRANDE    1000000
#define VOLUMEN_CHICO      10
#define VOLUMEN_MEDIO     1000
#define CAPACIDAD_INICIAL       128

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
bool pruebas_apilar_volumen(pila_t * pila, void* valor,int volumen){

  bool apilado;

  if(pila==NULL)
    return false;

  for(int i=0;i<volumen;i++){
    apilado= pila_apilar(pila, valor);
    if(apilado==false)
      return false;
  }

  return true;
}

bool pruebas_desapilar_volumen(pila_t * pila, int volumen){

  void * desapilado;

  if(pila==NULL)
    return false;

  for(int i=0;i<volumen;i++){
    desapilado= pila_desapilar(pila);
  }
  return (desapilado==NULL);
}

//print_test("Pila apilar NULL:", pruebas_apilar(pila,NULL)==true);

//print_test("Pila desapilar volumen NULLS:", pruebas_desapilar_volumen(pila,VOLUMEN_CHICO+VOLUMEN_MEDIO-1)==true);
void pruebas_pila_vacia_es_nueva(pila_t * pila){
  print_test("Pila desapilar volumen enteros:", pruebas_desapilar_volumen(pila,VOLUMEN_CHICO+VOLUMEN_MEDIO)==true);
  print_test("Pila ahora vacía:",pila_esta_vacia(pila)==true );
  print_test("Pila no se puede ver tope:",pila_ver_tope(pila)==NULL );
}

void pruebas_puntero_null(pila_t * pila){
  printf("INICIO DE PRUEBAS DE APILAR NULLS\n");
  print_test("Pila apilar NULL:", pila_apilar(pila,NULL)==true);
  print_test("Pila desapilar NULL:", pila_desapilar(pila)==NULL);
}

void pruebas_apilar_enteros(pila_t * pila){
  printf("INICIO DE PRUEBAS DE APILAR ENTEROS\n");
  int i=1; //busco apilar un mismo elemento en la pila para probar porque es sencillo
  print_test("Pila apilar volumen chico de enteros:", pruebas_apilar_volumen(pila,&i,VOLUMEN_CHICO)==true);
  print_test("Pila apilar volumen chico + medio de enteros:", pruebas_apilar_volumen(pila,NULL,VOLUMEN_MEDIO)==true);
  print_test("Pila apilada no es vacía:", pila_esta_vacia(pila)==false );
  print_test("Pila apilada se puede ver tope:", pila_ver_tope(pila)!=NULL);
}

void pruebas_pila_nueva(pila_t * pila){
  print_test("Pila nueva creada:", pila!=NULL);
  print_test("Pila nueva es vacía:",pila_esta_vacia(pila)==true );
  print_test("Pila nueva ver tope:",pila_ver_tope(pila)==NULL );
  pila_destruir(pila);
  print_test("Pila nueva destruida:", pila_esta_vacia(pila)==true  && pila_ver_tope(pila)==NULL);

}

void pruebas_volumen(pila_t * pila){
  char c='a';
  print_test("Pila apilar volumen grande de caracteres:", pruebas_apilar_volumen(pila,&c,VOLUMEN_GRANDE)==true);
  print_test("Pila apilada no es vacía:", pila_esta_vacia(pila)==false );
  print_test("Pila apilada se puede ver tope:", pila_ver_tope(pila)!=NULL);
  print_test("Pila desapilar volumen enteros:", pruebas_desapilar_volumen(pila,VOLUMEN_CHICO+VOLUMEN_MEDIO)==true);
}
void pruebas_pila_alumno(void) {
    pila_t* pila;
    pila = pila_crear();
    pruebas_pila_nueva(pila);
    pila = pila_crear();
    pruebas_apilar_enteros(pila);
    pruebas_puntero_null(pila);
    pruebas_pila_vacia_es_nueva(pila);
    pruebas_volumen(pila);

}
