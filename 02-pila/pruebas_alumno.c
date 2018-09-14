#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define VOLUMEN_GRANDE          1000000
#define VOLUMEN_CHICO           10
#define VOLUMEN_MEDIO           1000
#define CAPACIDAD_INICIAL       128

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
bool pruebas_apilar_vector_numeros_aleatorios(pila_t * pila, size_t volumen){

  if(pila==NULL)
    return false;
 int vector[volumen];
  for(int i=0;i<volumen;i++){
    vector[i]=i;
    pila_apilar(pila, &vector[i]);
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
void pruebas_pila_vacia_es_nueva(void){
  pila_t* pila;
  pila = pila_crear();
  char c= 'v';

  printf("INICIO DE PRUEBAS DE PILA VACIA == PILA NUEVA\n");

  print_test("Pila apilar char:", pila_apilar(pila,&c)==true);
  print_test("Pila desapilar char:", pila_desapilar(pila)!=NULL);
  print_test("Pila ahora vacía:",pila_esta_vacia(pila)==true );
  print_test("Pila no se puede ver tope:",pila_ver_tope(pila)==NULL );
  pila_destruir(pila);
  print_test("Pila de null destruida:",true);
}

void pruebas_puntero_null(void){
  pila_t* pila;
  pila = pila_crear();

  printf("INICIO DE PRUEBAS DE APILAR NULL\n");

  print_test("Pila apilar NULL:", pila_apilar(pila,NULL)==true);
  print_test("Pila desapilar NULL:", pila_desapilar(pila)==NULL);
  pila_destruir(pila);
  print_test("Pila de null destruida:",true);
}

void pruebas_apilar_enteros(void){
  pila_t* pila;
  pila = pila_crear();

  printf("INICIO DE PRUEBAS DE APILAR ENTEROS\n");

  print_test("Pila apilar volumen medio de enteros:", pruebas_apilar_vector_numeros_aleatorios(pila,VOLUMEN_MEDIO)==true);
  print_test("Pila apilada no es vacía:", pila_esta_vacia(pila)==false );
  print_test("Pila apilada se puede ver tope:", pila_ver_tope(pila)!=NULL);
  print_test("Pila apilada destruida:", true);
}

void pruebas_pila_nueva(void){

  pila_t* pila;
  pila = pila_crear();

  printf("INICIO DE PRUEBAS DE PILA NUEVA\n");

  print_test("Pila nueva creada:", pila!=NULL);
  print_test("Pila nueva es vacía:",pila_esta_vacia(pila)==true );
  print_test("Pila nueva ver tope:",pila_ver_tope(pila)==NULL );
  pila_destruir(pila);
  print_test("Pila nueva destruida:", true);

}
/*
void pruebas_volumen(pila_t * pila){
  pila_t* pila;
  pila = pila_crear();
  char c='a';

  printf("INICIO DE PRUEBAS DE VOLUMEN\n");


  print_test("Pila apilar volumen grande de caracteres:", pruebas_apilar_volumen(pila,&c,VOLUMEN_GRANDE)==true);
  print_test("Pila apilada no es vacía:", pila_esta_vacia(pila)==false );
  print_test("Pila apilada se puede ver tope:", pila_ver_tope(pila)!=NULL);
  print_test("Pila desapilar volumen enteros:", pruebas_desapilar_volumen(pila,VOLUMEN_GRANDE)==true);
  pila_destruir(pila);
  print_test("Pila de enteros grande destruida:", pila_esta_vacia(pila)==true  && pila_ver_tope(pila)==NULL);
}*/
void pruebas_pila_alumno(void) {

  //pruebas_pila_nueva();
  pruebas_apilar_enteros();
  // pruebas_puntero_null();
  //pruebas_pila_vacia_es_nueva();
  //  pruebas_volumen(pila);

}
