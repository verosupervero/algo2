#include "lista.h"
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
void pruebas_lista_vacia_es_nueva(void){
  lista_t* lista;
  lista = lista_crear();
  char c= 'v';

  printf("INICIO DE PRUEBAS DE LISTA VACIA == LISTA NUEVA\n");

  print_test("Lista insertar_ultimo char estático:", lista_insertar_ultimo(lista,&c)==true);
  print_test("Lista largo es 1:",lista_largo(lista)==1 );
  print_test("Lista borrar char:", lista_borrar_primero(lista)!=NULL);
  print_test("Lista ahora vacía:",lista_esta_vacia(lista)==true );
  print_test("Lista largo es 0:",lista_largo(lista)==0 );
  print_test("Lista vacía, primero es NULL:",lista_ver_primero(lista)==NULL );
  print_test("Lista vacia borrar_primero:",lista_borrar_primero(lista)==NULL );
  lista_destruir(lista,NULL);
  print_test("Lista de null destruida:",true);
}

void pruebas_puntero_null(void){
  lista_t* lista;
  lista = lista_crear();

  printf("INICIO DE PRUEBAS DE INSERTAR ULTIMO NULL\n");

  print_test("Lista insertar un NULL a lo ultimo:", lista_insertar_ultimo(lista,NULL)==true);
  print_test("Lista borrar NULL:", lista_borrar_primero(lista)==NULL);
  print_test("Lista insertar un NULL al inicio:", lista_insertar_primero(lista,NULL)==true);
  print_test("Lista largo es 1:",lista_largo(lista)==1 );
  lista_destruir(lista,NULL);
  print_test("Lista de null destruida:",true);
}

void pruebas_insertar_ultimo_enteros(size_t volumen,char * nombre_volumen){
  lista_t* lista;
  lista = lista_crear();
  bool enlistado=true;
  int* valor_encontrado;
  int* valor;

  printf("INICIO DE PRUEBAS DE INSERTAR ENTEROS AL INICIO Y FINAL DE LA LISTA(%s) \n",nombre_volumen);

  for(int i=0;i<volumen;i++){
    valor = malloc(sizeof(int));
    if(valor==NULL){
      fprintf(stderr, "Out of memory\n");
      return ;
    }
    *valor = i;
    enlistado &= lista_insertar_ultimo(lista, valor);
  }
  print_test("Lista insertar_ultimo volumen de enteros:", enlistado==true);
  print_test("Lista inserté elemento no es vacía:", lista_esta_vacia(lista)==false );
  printf("La lista tiene %ld elementos\n", volumen);
  print_test("Lista tiene todos los elementos:", lista_largo(lista)==volumen );
  print_test("Lista con elemento se puede ver primero:", lista_ver_primero(lista)!=NULL);
  print_test("Lista con elemento se puede ver último:", lista_ver_ultimo(lista)!=NULL);

  bool valores_ok = true;
  bool topes_ok=true;
    for(int i=0;i<volumen;i++){
      valor= (int *) lista_ver_primero(lista);
      topes_ok &= (*valor==i);
      valor_encontrado = lista_borrar_primero(lista);
      valores_ok &= (*valor_encontrado==i);
      free(valor_encontrado);
    }

  print_test("Lista borrar_primero correctamente (valores):", valores_ok);
  print_test("Lista borrar_primero correctamente (primeros):", topes_ok);
  print_test("Lista borrar_primero correctamente (lista vacia):", lista_esta_vacia(lista)==true);
  lista_destruir(lista,NULL);
  print_test("Lista destruida:", true);
}

void prueba_destruir_dinamico(size_t volumen){
  lista_t* lista;
  lista = lista_crear();
  int* valor;

  printf("INICIO DE PRUEBA DE DESTRUIR LISTA CON ELEMENTOS DINAMICOS\n");
  printf("Creando elementos... \n");

  for(int i=0;i<volumen;i++){
    valor = malloc(sizeof(int));
    if(valor==NULL){
      fprintf(stderr, "Out of memory\n");
      return ;
    }
    *valor = i;
    lista_insertar_ultimo(lista, valor);
  }
  print_test("Lista tiene todos los elementos:", lista_largo(lista)==volumen);
  lista_destruir(lista, &free);
  print_test("Lista destruida:", true);
}

void prueba_destruir_estatico(size_t volumen){
  lista_t* lista;
  lista = lista_crear();
  int valor[volumen];

  printf("INICIO DE PRUEBA DE DESTRUIR LISTA CON ELEMENTOS ESTATICOS\n");
  printf("Creando elementos... \n");

  for(int i=0;i<volumen;i++){
    valor[i] = i;
    lista_insertar_ultimo(lista, valor);
  }
  lista_destruir(lista, NULL);
  print_test("Lista destruida:", true);
}

void pruebas_lista_nueva(void){
  lista_t* lista;
  lista = lista_crear();
  printf("INICIO DE PRUEBAS DE LISTA NUEVA\n");
  print_test("Lista nueva creada:", lista!=NULL);
  print_test("Lista nueva es vacía:",lista_esta_vacia(lista)==true );
  print_test("Lista nueva ver primero:",lista_ver_primero(lista)==NULL );
  print_test("Lista nueva ver ultimo:",lista_ver_ultimo(lista)==NULL );
  lista_destruir(lista,NULL);
  print_test("Lista nueva destruida:", true);
}

void pruebas_lista_alumno(void) {
  pruebas_lista_nueva();
  pruebas_insertar_ultimo_enteros(VOLUMEN_CHICO, "Volumen chico");
  pruebas_insertar_ultimo_enteros(VOLUMEN_MEDIO,"Volumen medio");
  pruebas_insertar_ultimo_enteros(VOLUMEN_GRANDE,"Volumen grande");
  prueba_destruir_dinamico(VOLUMEN_GRANDE);
  prueba_destruir_estatico(VOLUMEN_GRANDE);
  pruebas_puntero_null();
  pruebas_lista_vacia_es_nueva();
}
