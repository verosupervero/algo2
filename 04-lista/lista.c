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

struct lista_iter{
  nodo_t * nodo_actual;
  nodo_t * nodo_anterior;
  lista_t * lista;
};

/* ******************************************************************
 *                FUNCIONES AUXILIARES TDA_NODO
 * *****************************************************************/
 // Destruye un nodo.
 //Pre: el nodo fue creado
 // Post: Se destruyó el nodo y se devolvió un puntero al dato.
void * nodo_eliminar(nodo_t * nodo){
  if(nodo==NULL)
    return NULL;

  void * valor= nodo->dato;
  free(nodo);
  return valor;
}
// Crea un nodo.
// Post: devuelve un nuevo nodo con un puntero a un dato.
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
  }
  free(lista);
}

// Devuelve verdadero o falso, según si la lista tiene o no elementos enlistados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista){
  return lista->largo == 0;
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
  if(lista_esta_vacia(lista))
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

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

 // Crea un iterador.
 // Post: devuelve un nuevo iterador vacío.
lista_iter_t *lista_iter_crear(lista_t *lista){
  lista_iter_t * lista_iter=malloc(sizeof(lista_iter_t));
  if(lista_iter==NULL)
    return NULL;

  lista_iter->nodo_anterior= NULL;
  lista_iter->nodo_actual= lista->primer_nodo;
  lista_iter->lista=lista;
  return lista_iter;
}

// El iterador avanza una posición en la lista.
// Pre: El iterador fue creado.
// Post: se devolvió true si pudo avanzar o false si llego al final de la lista.
bool lista_iter_avanzar(lista_iter_t *iter){
  if(lista_iter_al_final(iter))
    return false;

  nodo_t * nuevo_actual=    iter-> nodo_actual->proximo_nodo;
  nodo_t * nuevo_anterior=  iter-> nodo_actual;

  iter->nodo_actual= nuevo_actual;
  iter->nodo_anterior= nuevo_anterior;
  return true;
}

// Obtiene el valor del dato al que apunta el iterador.
// Pre: El iterador fue creado.
// Post: Devolvió el valor del dato al que apunta el iterador o NULL si la lista
// estaba vacía o si el iterador apuntaba al final de la lista
void * lista_iter_ver_actual(const lista_iter_t *iter){
  if (lista_iter_al_final(iter))
      return NULL;
  return iter->nodo_actual->dato;
}

// Constata si el iterador apunta al final de la lista.
// Pre: La lista fue creada y el iterador fue creado
// Post: Devolvió true si llegó al final de la lista, false en caso contrario.
bool lista_iter_al_final(const lista_iter_t *iter){
  return iter->nodo_actual == NULL;
}

// Destruye el iterador.
// Pre: El iterador fue creado.
// Post: Se destruyó el iterador.
void lista_iter_destruir(lista_iter_t *iter){
  free(iter);
}
// Inserta un elemento en la lista en la posición actual
// Pre: El iterador fue creado.
// Post: Devolvió true si se insertó el elemento en la lista, false en caso contrario.
bool lista_iter_insertar(lista_iter_t *iter, void *dato){

  if(lista_esta_vacia(iter->lista) || iter->nodo_actual ==iter->lista->primer_nodo){
    if(!lista_insertar_primero(iter->lista,dato))
      return false;
    iter->nodo_actual=iter->lista->primer_nodo;
  }
  else{
    nodo_t* nuevo_nodo = nodo_crear(dato);
    if(nuevo_nodo==NULL)
      return false;
    nuevo_nodo->proximo_nodo= iter->nodo_actual;

    iter->nodo_anterior->proximo_nodo= nuevo_nodo;
    iter->nodo_actual=nuevo_nodo; //nodo anterior no null
    iter->lista->largo++;
  }
  return true;
}

// Borra un elemento en la lista en la posición actual
// Pre: El iterador fue creado.
// Post: Devolvió el dato o NULL en caso de que el iterador apunte a NULL.
void * lista_iter_borrar(lista_iter_t *iter){
  if(lista_esta_vacia(iter->lista) || lista_iter_al_final(iter))
    return NULL;

  nodo_t * nodo_a_borrar= iter->nodo_actual;

  if( nodo_a_borrar ==iter->lista->primer_nodo){
      nodo_a_borrar= lista_borrar_primero(iter->lista);
      iter->nodo_actual= iter->lista->primer_nodo;
      return nodo_a_borrar;
  }
  else{

    iter->nodo_anterior->proximo_nodo= iter->nodo_actual->proximo_nodo;
    iter->nodo_actual= iter->nodo_anterior->proximo_nodo;

    if(nodo_a_borrar == iter->lista->ultimo_nodo){
      iter->lista->ultimo_nodo = iter->nodo_anterior;
    }

    void * valor_nodo_borrado= nodo_eliminar(nodo_a_borrar);
    iter->lista->largo--;
    return valor_nodo_borrado;
  }
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

// Itera una posicion en la lista. Visitar recibe el dato y un puntero extra.
// Devuelve true si se debe seguir iterando, false en caso contrario.
// Pre: La lista fue creada.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
  nodo_t * nodo=lista->primer_nodo;
  while(nodo!=NULL){
    visitar(nodo->dato,extra);
    nodo=nodo->proximo_nodo;
  }
}
