#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */
typedef struct nodo{
  void * dato;
  struct nodo * proximo_nodo;
}nodo_t;

struct lista{
  nodo_t * primer_nodo;
  nodo_t * ultimo_nodo;
  size_t largo;
};


/* ******************************************************************
 *                FUNCIONES AUXILIARES TDA_NODO
 * *****************************************************************/

void * nodo_eliminar(nodo_t * nodo){
  if(nodo==NULL)
    return NULL;

  void * valor= nodo->dato;
  free(nodo);
  return valor;
}

nodo_t* nodo_crear(void* valor){
  nodo_t* nodo = malloc(sizeof(nodo_t));
  if (nodo==NULL)
    return NULL;
  nodo->dato= valor;
  nodo->proximo_nodo= NULL;
  return nodo;
}

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void){
  lista_t * lista=malloc(sizeof(lista_t));
  if(lista==NULL)
    return NULL;
  lista->primer_nodo= NULL;
  lista->ultimo_nodo= NULL;
  lista->largo=0;
  return lista;
}

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void*)){

  while(lista_esta_vacia(lista)==false){
    void * dato_actual;
    dato_actual= lista_borrar_primero(lista);
    if(destruir_dato!=NULL)
      destruir_dato(dato_actual);
    lista->largo--;
  }
  free(lista);
}

// Devuelve verdadero o falso, según si la lista tiene o no elementos enlistados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista){
  return (lista->primer_nodo==NULL) && (lista->ultimo_nodo==NULL);
}


// Agrega un nuevo elemento a la lista al inicio de la misma. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista.
bool lista_insertar_primero(lista_t *lista, void* valor){
  nodo_t * nodo = nodo_crear(valor);
  if(nodo==NULL)
    return false;

  if(lista_esta_vacia(lista)){
    lista->primer_nodo=nodo;
    lista->ultimo_nodo= nodo;
  }
  else{
    void * nuevo_primero= nodo;
    void * anterior_primero= lista->primer_nodo;
    nodo->proximo_nodo= anterior_primero;
    lista->primer_nodo= nuevo_primero;
  }
  lista->largo++;
  return true;
}

// Agrega un nuevo elemento a la lista al final de la misma. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista al final de esta.
bool lista_insertar_ultimo(lista_t *lista, void* valor){

  void * nodo = nodo_crear(valor);
  if(nodo==NULL)
    return false;

  if(lista_esta_vacia(lista)){
    lista->primer_nodo=nodo;
  }
  else{
    lista->ultimo_nodo->proximo_nodo= nodo;
  }
  lista->ultimo_nodo= nodo;
  lista->largo++;
  return true;
}

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primer_nodo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista){
  if(lista_esta_vacia(lista)==true)
    return NULL;
  return lista->primer_nodo->dato;
}

// Obtiene el valor del último elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el último elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t *lista){
  if(lista_esta_vacia(lista)==true)
    return NULL;
  return lista->ultimo_nodo->dato;
}


// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primer_nodo de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void* lista_borrar_primero(lista_t *lista){
  if(lista_esta_vacia(lista))
    return NULL;

  void * nuevo_primer_nodo= lista->primer_nodo->proximo_nodo;
  void * valor= nodo_eliminar(lista->primer_nodo);
  lista->primer_nodo= nuevo_primer_nodo;
  lista->largo--;

  // Si la lista queda vacía, ultimo nodo debe ser NULL
  if (nuevo_primer_nodo == NULL){
    lista->ultimo_nodo = NULL;
  }
  return valor;
}


//Devuelve el largo de la lista
//Pre: La lista fue creada
//Post: se devolvió tamaño de la lista
size_t lista_largo(const lista_t *lista){
  return lista->largo;
}
