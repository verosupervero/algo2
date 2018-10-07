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
 *                   FUNCIONES AUXILIARES DE PRUEBAS
 * *****************************************************************/
 //Pre: Recibe un dato y un puntero extra
 //Post: Imprime el dato
 bool imprimir_entero(void * dato,void* extra){
   printf("*------*\n");
   if(*( (int*)dato)>=10){
     printf("|..%d..|\n",*( (int*)dato));
   }
   else{
     printf("|..%d...|\n",*( (int*)dato));
   }
   printf("|......|\n");
   printf("*------*\n");
   printf("...|...\n");
   printf("...v...\n");
   return true;
 }
//Pre: Recibe un dato y un puntero extra
//Post: Imprime el dato
 bool imprimir_ingredientes(void * dato,void* extra){
   if(extra==NULL){
     printf("%s\n",*((char**)dato));
   }
   return true;
 }
//Pre: Imprime una lista si el volumen no supera al volumen chico, recibe un puntero a imprimir y un puntero extra
//Post: Imprime la lista con un formato dadoñ
 void imprimir_lista (size_t volumen, lista_t* lista, bool imprimir(void *dato, void *extra), void *extra){
   if(volumen<=VOLUMEN_CHICO){
     printf("Voy a probar el iterador interno, tenes que poder ver la lista...\n");
     printf("NOTA: Si la lista es menor a 10 elementos (mucho scroll)\n");
     lista_iterar (lista, imprimir,extra);
     printf("..GND..\n\n");
   }
 }

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
   imprimir_lista (volumen,lista, imprimir_entero,NULL);

   printf("INICIO DE PRUEBAS DE ITERAR UNA LISTA RELLENA %s (%ld elementos)\n",nombre_volumen,volumen);
   iter= lista_iter_crear(lista);
   print_test("Cantidad de elementos correctos:", lista_largo(lista)==volumen);
   print_test("Puede avanzar iterador en lista:", lista_iter_avanzar(iter)==true);

   /*PRUEBAS AL INSERTAR ELEMENTOS DE LA LISTA EN POSICION DADA*/


   printf("A ver los datos...\n");

   int * valor_actual= (int *) lista_iter_ver_actual(iter);
   int valor_elegido= 1;
   int valor_a_insertar= 39;
   bool checkear_valor= *valor_actual==valor_elegido;
   int * ultimo_de_la_lista=(int*) lista_ver_ultimo(lista);

   printf("El último de la lista es: %d\n",*ultimo_de_la_lista);


   print_test("Iterador en la lista tiene datos (y es el esperado):", checkear_valor );
   print_test("Iterador de lista no está al final:", lista_iter_al_final(iter)==false);
   print_test("El iterador en la lista puede insertar elementos:", lista_iter_insertar(iter,&valor_a_insertar)==true);

   printf("Veamos que se insertó el elemento...\n");
   imprimir_lista (volumen,lista, imprimir_entero,NULL);
   ultimo_de_la_lista=(int*) lista_ver_ultimo(lista);
   printf("El último de la lista es: %d\n",*ultimo_de_la_lista);


   /*PRUEBAS AL BORRAR ELEMENTOS DE LA LISTA EN POSICION DADA*/
   print_test("El iterador en la lista puede borrar elementos:", lista_iter_borrar(iter)==&valor_a_insertar);
   imprimir_lista (volumen,lista, imprimir_entero,NULL);
   ultimo_de_la_lista=(int*) lista_ver_ultimo(lista);
   printf("El último de la lista es: %d\n",*ultimo_de_la_lista);

   /*PRUEBAS AL BORRAR ELEMENTOS DE LA LISTA AL FINAL*/
   print_test("Puede avanzar iterador en lista:", lista_iter_avanzar(iter)==true);
   print_test("El iterador en la lista puede borrar elementos:", lista_iter_borrar(iter)==&valor[2]);
   imprimir_lista (volumen,lista, imprimir_entero,NULL);
   ultimo_de_la_lista=(int*) lista_ver_ultimo(lista);
   printf("El último de la lista es: %d\n",*ultimo_de_la_lista);


   /*PRUEBAS CON ITERADOR AL FINAL DE LA LISTA (SI ES VECTOR MINI)*/
   print_test("El iterador en la lista puede insertar elementos:", lista_iter_insertar(iter,&valor_a_insertar)==true);
   imprimir_lista (volumen,lista, imprimir_entero,NULL);
   ultimo_de_la_lista=(int*) lista_ver_ultimo(lista);
   printf("El último de la lista es: %d\n",*ultimo_de_la_lista);


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

  printf("Vamos a ver los ingredientes con el ingrediente nuevo:\n\n\n");
  lista_iterar (lista, imprimir_ingredientes,NULL);
  printf("Compré 3 de los ingredientes de la lista, debo sacarlos de ella:\n\n\n");
  for(int i=0;i<3;i++){
    print_test("El iterador en la lista puede borrar elementos:", lista_iter_borrar(iter)!=NULL);
    printf("Imprimiendo lista borrando el [%d] ingrediente\n",i+1);
    lista_iterar (lista, imprimir_ingredientes,NULL);
    printf("\n");
  }
  printf("Compré el cacao, lo saco:\n\n\n");
  print_test("El iterador en la lista puede avanzar en ella:", lista_iter_avanzar(iter)==true);
  print_test("El iterador en la lista puede borrar el cacao:", lista_iter_borrar(iter)== &ingredientes[3]);
  printf("\n Imprimiendo lista borrando el cacao\n");
  lista_iterar (lista, imprimir_ingredientes,NULL);
  printf("Compré el resto de los ingredientes de la lista, la destruyo junto con el iterador.\n\n\n");

  lista_iter_destruir(iter);
  lista_destruir(lista,NULL);
  print_test("Lista nueva destruida:", true);
  print_test("Iterador destruido:", true);
}

void pruebas_iterar_lista_borde(){
  int a=1;
  int b=2;
  int c= 3;
  lista_t* lista;
  lista_iter_t * iter;
  lista = lista_crear();
  iter= lista_iter_crear(lista);

  imprimir_lista (lista_largo(lista),lista, imprimir_entero,NULL);

  print_test("El iterador en la lista puede insertar elementos:", lista_iter_insertar(iter,&a)==true);
  imprimir_lista (lista_largo(lista),lista, imprimir_entero,NULL);

  print_test("El iterador en la lista puede borrar elementos en principio:",lista_iter_borrar(iter)==&a);
  imprimir_lista (lista_largo(lista),lista, imprimir_entero,NULL);
  print_test(" Remover el último/primer elemento con el iterador cambia el último/primero de la lista:",lista_iter_ver_actual(iter)==NULL);

  print_test("El iterador en la lista puede volver a insertar elementos:", lista_iter_insertar(iter,&a)==true);
  print_test("Verifico que el iterador apunta al ppio de la lista:", lista_iter_ver_actual(iter)==&a);
  print_test("El iterador en la lista puede insertar elementos al inicio:", lista_iter_insertar(iter,&b)==true);
  imprimir_lista (lista_largo(lista),lista, imprimir_entero,NULL);

  print_test("Verifico que el iterador apunta al último elemento colocado:", lista_iter_ver_actual(iter)==&b);
  print_test("El iterador en la lista puede avanzar en ella:", lista_iter_avanzar(iter)==true);
  print_test("El iterador en la lista puede insertar elementos en el medio:", lista_iter_insertar(iter,&c)==true);
  imprimir_lista (lista_largo(lista),lista, imprimir_entero,NULL);

  print_test("El iterador en la lista puede borrar elementos en el medio:",lista_iter_borrar(iter)==&c);
  imprimir_lista (lista_largo(lista),lista, imprimir_entero,NULL);

  print_test("El iterador en la lista puede borrar el último elemento:",lista_iter_borrar(iter)==&a);
  imprimir_lista (lista_largo(lista),lista, imprimir_entero,NULL);
  print_test("Verifico que el iterador apunta al final de la lista:", lista_iter_al_final(iter)==true);

  lista_iter_destruir(iter);
  lista_destruir(lista,NULL);
  print_test("Lista nueva destruida:", true);
  print_test("Iterador destruido:", true);
}


void pruebas_lista_alumno(void) {
  pruebas_lista_nueva();
  pruebas_insertar_ultimo_enteros(VOLUMEN_CHICO, "Volumen chico");
  pruebas_insertar_ultimo_enteros(VOLUMEN_MEDIO,"Volumen medio");
  pruebas_insertar_ultimo_enteros(VOLUMEN_GRANDE,"Volumen grande");
  prueba_destruir_dinamico(VOLUMEN_GRANDE);
  prueba_destruir_estatico(VOLUMEN_CHICO);
  pruebas_puntero_null();
  pruebas_lista_vacia_es_nueva();
  pruebas_iterar_lista_nueva();
  pruebas_iterar_lista_rellena(VOLUMEN_MINI, "Volumen Mini");
  pruebas_iterar_lista_rellena(VOLUMEN_CHICO,"Volumen Chico");
  pruebas_iterar_lista_rellena(VOLUMEN_MEDIO,"Volumen Medio");
  pruebas_receta_de_bizcochuelo();
  pruebas_iterar_lista_borde();
}
