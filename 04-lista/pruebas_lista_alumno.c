#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define VOLUMEN_MINI            3
#define VOLUMEN_CHICO           10
#define VOLUMEN_MEDIO           1000
#define VOLUMEN_GRANDE          100000
#define CAPACIDAD_INICIAL       128

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/


 /* ******************************************************************
  *                    PRUEBAS DE LA LISTA
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
    lista_insertar_ultimo(lista, &valor[i]);
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

/* ******************************************************************
 *                    PRUEBAS DEL ITERADOR EXTERNO
 * *****************************************************************/
 void pruebas_iterar_lista_nueva(void){
   lista_t* lista;
   lista_iter_t * iter;

   lista = lista_crear();
   iter= lista_iter_crear(lista);

   printf("INICIO DE PRUEBAS DE ITERAR UNA LISTA NUEVA\n");
   print_test("Lista nueva creada:", lista!=NULL);
   print_test("No puede avanzar iterador en lista nueva :", lista_iter_avanzar(iter)==false);
   print_test("Iterador en la lista nueva no tiene datos:", lista_iter_ver_actual(iter)==NULL);
   print_test("Iterador de lista nueva está al final:", lista_iter_al_final(iter)==true);
   print_test("El iterador en la lista nueva no puede borrar elementos, está vacía:", lista_iter_borrar(iter)==NULL);

   lista_iter_destruir(iter);

   lista_destruir(lista,NULL);
   print_test("Lista nueva destruida:", true);
   print_test("Iterador destruido:", true);
 }

/*void mostrar_lista (void imprimir(void *dato),lista_iter_t *iter){
  void * dato=lista_iter_ver_actual(iter);
  while(dato!=NULL){
    imprimir(dato);
    dato=lista_iter_avanzar(iter);
  }
  printf("\t___\n");
  printf("\t\t__\n");
  printf("\t\t\t_\n");

}*/


bool imprimir_entero(void * dato,void* extra){
  printf("*------*\n");
  printf("|..%d...|\n",*( (int*)dato));
  printf("|......|\n");
  printf("*------*\n");
  printf("...|...\n");
  printf("...v...\n");
  return true;
}

bool imprimir_ingredientes(void * dato,void* extra){
  printf("%s\n",*((char**)dato));
  return true;
}

 void pruebas_iterar_lista_rellena(size_t volumen, char * nombre_volumen){ //aqui
   lista_t* lista;
   lista_iter_t * iter;
   lista = lista_crear();
   int valor[volumen];

   printf("Llenando la lista...\n\n");
   for(int i=0;i<volumen;i++){
     valor[i] = i;
     lista_insertar_ultimo(lista, &valor[i]);
   }
   if(volumen<=VOLUMEN_CHICO){
     printf("Voy a probar el iterador interno, tenes que poder ver la lista...\n");
     printf("NOTA: Si la lista es menor a 10 elementos (mucho scroll)\n");
     lista_iterar (lista, imprimir_entero,NULL);
     printf("..GND..\n\n");
   }

   printf("INICIO DE PRUEBAS DE ITERAR UNA LISTA RELLENA %s (%ld elementos)\n",nombre_volumen,volumen);
   iter= lista_iter_crear(lista);
   print_test("Cantidad de elementos correctos:", lista_largo(lista)==volumen);
   print_test("Puede avanzar iterador en lista:", lista_iter_avanzar(iter)==true);

   printf("A ver los datos...\n");

   int * valor_actual= (int *) lista_iter_ver_actual(iter);
   int valor_elegido= 1;
   bool checkear_valor= *valor_actual==valor_elegido;

   print_test("Iterador en la lista tiene datos (y es el esperado):", checkear_valor );
   print_test("Iterador de lista no está al final:", lista_iter_al_final(iter)==false);
   print_test("El iterador en la lista puede borrar elementos:", lista_iter_borrar(iter)==&valor[1]);
   print_test("El iterador en la lista puede insertar elementos:", lista_iter_insertar(iter,&valor_elegido)==true);

   if(volumen<=VOLUMEN_CHICO){
     printf("Veamos que se insertó el elemento...\n");
     printf("NOTA: Si la lista es menor a 10 elementos (mucho scroll)\n");
     lista_iterar (lista, imprimir_entero,NULL);
     printf("..GND..\n\n");
   }

   lista_iter_destruir(iter);

   lista_destruir(lista,NULL);
   print_test("Lista nueva destruida:", true);
   print_test("Iterador destruido:", true);
 }

void pruebas_receta_de_bizcochuelo(void){
  lista_t* lista;
  lista_iter_t * iter;
  lista = lista_crear();

  char* ingredientes[5]={"6 huevos",
                        "120 g de harina",
                        "150g de azúcar",
                        "25 g de cacao",
                        "35 g de manteca derretida"};
    printf("Escribiendo ingredientes...\n\n");

  for(int i=0;i<5;i++){
    lista_insertar_ultimo(lista, &ingredientes[i]);
  }
  printf("Vamos a ver los ingredientes");
  lista_iterar (lista, imprimir_ingredientes,NULL);

  iter= lista_iter_crear(lista);
  printf("¡Me olvidé de algo!\n\n");

  char* chocolate="Mucho chocolate";

  print_test("Verifico que el iterador apunta al ppio de la lista:", lista_iter_ver_actual(iter)==&ingredientes[0]);
  print_test("Pude poner lo que me olvidé:", lista_iter_insertar(iter,&chocolate)==true);

  printf("Vamos a ver los ingredientes con el ingrediente nuevo\n");
  lista_iterar (lista, imprimir_ingredientes,NULL);

  lista_iter_destruir(iter);
  lista_destruir(lista,NULL);
}


void pruebas_lista_alumno(void) {
  /*pruebas_lista_nueva();
  pruebas_insertar_ultimo_enteros(VOLUMEN_CHICO, "Volumen chico");
  pruebas_insertar_ultimo_enteros(VOLUMEN_MEDIO,"Volumen medio");
  pruebas_insertar_ultimo_enteros(VOLUMEN_GRANDE,"Volumen grande");
  prueba_destruir_dinamico(VOLUMEN_GRANDE);
  prueba_destruir_estatico(VOLUMEN_CHICO);
  pruebas_puntero_null();
  pruebas_lista_vacia_es_nueva();
  pruebas_iterar_lista_nueva();
  */pruebas_iterar_lista_rellena(VOLUMEN_MINI, "Volumen Mini");
  pruebas_iterar_lista_rellena(VOLUMEN_CHICO,"Volumen Chico");
  pruebas_iterar_lista_rellena(VOLUMEN_MEDIO,"Volumen Medio");
  pruebas_receta_de_bizcochuelo();
}
