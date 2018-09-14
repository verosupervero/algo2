#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define VOLUMEN_GRANDE          100000
#define VOLUMEN_CHICO           10
#define VOLUMEN_MEDIO           1000
#define CAPACIDAD_INICIAL       128

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/


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
  print_test("Pila vacia desapilar:",pila_desapilar(pila)==NULL );
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

void pruebas_apilar_enteros(size_t volumen,char * nombre_volumen){
  pila_t* pila;
  pila = pila_crear();
  bool apilado=true;
  int* aux;

  printf("INICIO DE PRUEBAS DE APILAR ENTEROS (%s) \n",nombre_volumen);

  for(int i=0;i<volumen;i++){
    aux = malloc(sizeof(int));
    if(aux==NULL){
      fprintf(stderr, "Out of memory\n");
      return ;
    }
    *aux = i;
    apilado &= pila_apilar(pila, aux);
  }
  print_test("Pila apilar volumen de enteros:", apilado==true);
  print_test("Pila apilada no es vacía:", pila_esta_vacia(pila)==false );
  print_test("Pila apilada se puede ver tope:", pila_ver_tope(pila)!=NULL);

  bool valores_ok = true;
  bool topes_ok=true;
    for(int i= (int)volumen-1;i>=0;i--){
      topes_ok &= (*((int*)pila_ver_tope(pila))==i);
	  aux = pila_desapilar(pila);
      valores_ok &= (*aux==i);
      free(aux);
    }

  print_test("Pila desapilada correctamente (valores):", valores_ok);
  print_test("Pila desapilada correctamente (topes):", topes_ok);
  print_test("Pila desapilada correctamente (pila vacia):", pila_esta_vacia(pila));
  pila_destruir(pila);
  print_test("Pila apilada destruida:", true);
}

void pruebas_pila_nueva(void){

  pila_t* pila;
  pila = pila_crear();

  printf("INICIO DE PRUEBAS DE PILA NUEVA\n");

  print_test("Pila nueva creada:", pila!=NULL);
  print_test("Pila nueva es vacía:",pila_esta_vacia(pila)==true );
  print_test("Pila nueva ver tope:",pila_ver_tope(pila)==NULL );
  print_test("Pila nueva desapilar:",pila_desapilar(pila)==NULL );
  pila_destruir(pila);
  print_test("Pila nueva destruida:", true);

}

void pruebas_pila_alumno(void) {

  //pruebas_pila_nueva();
  pruebas_apilar_enteros(VOLUMEN_CHICO, "Volumen chico");
  //pruebas_apilar_enteros(VOLUMEN_MEDIO,"Volumen medio");
  //pruebas_apilar_enteros(VOLUMEN_GRANDE,"Volumen grande");
  //pruebas_puntero_null();
  //pruebas_pila_vacia_es_nueva();

}
