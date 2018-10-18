#include "cola.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La cola está planteada como una cola de punteros genéricos. */
typedef struct nodo{
  void * dato;
  struct nodo * proximo_nodo;
}nodo_t;

struct cola{
  nodo_t * primer_nodo;
  nodo_t * ultimo_nodo;
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
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

// Crea una cola.
// Post: devuelve una nueva cola vacía.
cola_t* cola_crear(void){
  cola_t * cola=malloc(sizeof(cola_t));
  if(cola==NULL)
    return NULL;
  cola->primer_nodo= NULL;
  cola->ultimo_nodo= NULL;
  return cola;
}

// Destruye la cola. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la cola llama a destruir_dato.
// Pre: la cola fue creada. destruir_dato es una función capaz de destruir
// los datos de la cola, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la cola.
void cola_destruir(cola_t *cola, void destruir_dato(void*)){
  if(cola==NULL)
    return;

  while(cola_esta_vacia(cola)==false){
    void * dato_actual;
    dato_actual= cola_desencolar(cola);
    if(destruir_dato!=NULL)
      destruir_dato(dato_actual);
  }
  free(cola);
}

// Devuelve verdadero o falso, según si la cola tiene o no elementos encolados.
// Pre: la cola fue creada.
bool cola_esta_vacia(const cola_t *cola){
  return (cola->primer_nodo==NULL) && (cola->ultimo_nodo==NULL); 
}

// Agrega un nuevo elemento a la cola. Devuelve falso en caso de error.
// Pre: la cola fue creada.
// Post: se agregó un nuevo elemento a la cola, valor se encuentra al final
// de la cola.
bool cola_encolar(cola_t *cola, void* valor){
  if (cola==NULL)
    return false;

  void * nodo = nodo_crear(valor);
  if(nodo==NULL)
    return false;

  if(cola_esta_vacia(cola)){
    cola->primer_nodo=nodo;
  }
  else{
    cola->ultimo_nodo->proximo_nodo= nodo;
  }
  cola->ultimo_nodo= nodo;
  return true;
}

// Obtiene el valor del primer elemento de la cola. Si la cola tiene
// elementos, se devuelve el valor del primer_nodo, si está vacía devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el primer elemento de la cola, cuando no está vacía.
void* cola_ver_primero(const cola_t *cola){
  if(cola_esta_vacia(cola)==true)
    return NULL;
  return cola->primer_nodo->dato;
}

// Saca el primer elemento de la cola. Si la cola tiene elementos, se quita el
// primer_nodo de la cola, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el valor del primer elemento anterior, la cola
// contiene un elemento menos, si la cola no estaba vacía.
void* cola_desencolar(cola_t *cola){
  if(cola_esta_vacia(cola))
    return NULL;

  void * nuevo_primer_nodo= cola->primer_nodo->proximo_nodo;
  void * valor= nodo_eliminar(cola->primer_nodo);
  cola->primer_nodo= nuevo_primer_nodo;
  
  // Si la cola queda vacía, ultimo nodo debe ser NULL
  if (nuevo_primer_nodo == NULL){
    cola->ultimo_nodo = NULL;  
  }
  
  return valor;
}
