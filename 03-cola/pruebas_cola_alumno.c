#include "cola.h"
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


//print_test("Cola encolar NULL:", pruebas_encolar(cola,NULL)==true);

//print_test("Cola desencolar volumen NULLS:", pruebas_desencolar_volumen(cola,VOLUMEN_CHICO+VOLUMEN_MEDIO-1)==true);
void pruebas_cola_vacia_es_nueva(void){
  cola_t* cola;
  cola = cola_crear();
  char c= 'v';

  printf("INICIO DE PRUEBAS DE COLA VACIA == COLA NUEVA\n");

  print_test("Cola encolar char estático:", cola_encolar(cola,&c)==true);
  print_test("Cola desencolar char:", cola_desencolar(cola)!=NULL);
  print_test("Cola ahora vacía:",cola_esta_vacia(cola)==true );
  print_test("Cola vacía, primero es NULL:",cola_ver_primero(cola)==NULL );
  print_test("Cola vacia desencolar:",cola_desencolar(cola)==NULL );
  cola_destruir(cola,NULL);
  print_test("Cola de null destruida:",true);
}

void pruebas_puntero_null(void){
  cola_t* cola;
  cola = cola_crear();

  printf("INICIO DE PRUEBAS DE ACOLAR NULL\n");

  print_test("Cola encolar NULL:", cola_encolar(cola,NULL)==true);
  print_test("Cola desencolar NULL:", cola_desencolar(cola)==NULL);
  cola_destruir(cola,NULL);
  print_test("Cola de null destruida:",true);
}

void pruebas_encolar_enteros(size_t volumen,char * nombre_volumen){
  cola_t* cola;
  cola = cola_crear();
  bool encolado=true;
  int* valor_encontrado;
  int* valor;

  printf("INICIO DE PRUEBAS DE ENCOLAR ENTEROS (%s) \n",nombre_volumen);

  for(int i=0;i<volumen;i++){
    valor = malloc(sizeof(int));
    if(valor==NULL){
      fprintf(stderr, "Out of memory\n");
      return ;
    }
    *valor = i;
    encolado &= cola_encolar(cola, valor);
  }
  print_test("Cola encolar volumen de enteros:", encolado==true);
  print_test("Cola encolada no es vacía:", cola_esta_vacia(cola)==false );
  print_test("Cola encolada se puede ver tope:", cola_ver_primero(cola)!=NULL);

  bool valores_ok = true;
  bool topes_ok=true;
    for(int i=0;i<volumen;i++){
      valor= (int *) cola_ver_primero(cola);
      topes_ok &= (*valor==i);
	    valor_encontrado = cola_desencolar(cola);
      //int* primero_nuevo= (int *) cola_ver_primero(cola);
      //if(primero_nuevo!=NULL)
        //printf(" este es el primero nuevo %d \n",*primero_nuevo );
      valores_ok &= (*valor_encontrado==i);
      printf(" este es el valor que se desencolo : %d vs i: %d\n ",*valor_encontrado,i );
      printf(" --------\n ");
      free(valor_encontrado);
    }

  print_test("Cola desencolar correctamente (valores):", valores_ok);
  print_test("Cola desencolar correctamente (topes):", topes_ok);
  print_test("Cola desencolar correctamente (cola vacia):", cola_esta_vacia(cola)==true);
  cola_destruir(cola,NULL);
  print_test("Cola encolada destruida:", true);
}

void pruebas_cola_nueva(void){

  cola_t* cola;
  cola = cola_crear();

  printf("INICIO DE PRUEBAS DE COLA NUEVA\n");

  print_test("Cola nueva creada:", cola!=NULL);
  print_test("Cola nueva es vacía:",cola_esta_vacia(cola)==true );
  print_test("Cola nueva ver tope:",cola_ver_primero(cola)==NULL );
  print_test("Cola nueva desencolar:",cola_desencolar(cola)==NULL );
  cola_destruir(cola,NULL);
  print_test("Cola nueva destruida:", true);

}

void pruebas_cola_alumno(void) {

  //pruebas_cola_nueva();
  //pruebas_encolar_enteros(VOLUMEN_CHICO, "Volumen chico");
  //pruebas_encolar_enteros(VOLUMEN_MEDIO,"Volumen medio");
  //pruebas_encolar_enteros(VOLUMEN_GRANDE,"Volumen grande");
  pruebas_puntero_null();
  //pruebas_cola_vacia_es_nueva();

}
