#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

#define CAPACIDAD_INICIAL               128
#define FACTOR_AUMENTAR_CAPACIDAD_PILA   2
#define FACTOR_DISMINUIR_CAPACIDAD_PILA  2
#define FACTOR_ACHICAR_PILA              4

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

// Redimensiona la pila.
// Pre: la pila fue creada.
// Post: se redimensionó la pila con el factor de redimensión pasado.
bool _pila_redimensionar (pila_t* pila, size_t nueva_capacidad){
  void * datos_auxiliar;
  datos_auxiliar = realloc(pila->datos, nueva_capacidad*sizeof(void*));

  if(datos_auxiliar==NULL)
    return false;

  pila->datos=datos_auxiliar;
  pila->capacidad= nueva_capacidad;
  return true;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// Crea una pila.
// Post: devuelve una nueva pila vacía.
pila_t* pila_crear(void){
  pila_t * pila= malloc(sizeof(pila_t));
  if(pila==NULL) return NULL;
  pila->capacidad = CAPACIDAD_INICIAL;
  pila->datos = malloc(CAPACIDAD_INICIAL*sizeof(void *));
  if(pila->datos==NULL){
    free(pila);
    return NULL;
  }
  pila->cantidad=0;
  return pila;
}

// Destruye la pila.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila){
  free(pila->datos);
  free(pila);
}


// Devuelve verdadero o falso, según si la pila tiene o no elementos apilados.
// Pre: la pila fue creada.
bool pila_esta_vacia(const pila_t *pila){
  return pila->cantidad==0;
}

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// Pre: la pila fue creada.
// Post: se agregó un nuevo elemento a la pila, valor es el nuevo tope.
bool pila_apilar(pila_t *pila, void* valor){

  if(pila->cantidad==pila->capacidad){
    if(!_pila_redimensionar(pila, pila->capacidad*FACTOR_AUMENTAR_CAPACIDAD_PILA))
      return false;
  }

  pila->datos[pila->cantidad]=valor;
  pila->cantidad++;
  return true;
}

// Obtiene el valor del tope de la pila. Si la pila tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve NULL.
// Pre: la pila fue creada.
// Post: se devolvió el valor del tope de la pila, cuando la pila no está
// vacía, NULL en caso contrario.
void* pila_ver_tope(const pila_t *pila){
  if(pila_esta_vacia(pila))
      return NULL;
  return pila->datos[pila->cantidad-1];
}

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, y se devuelve ese valor. Si la pila está vacía, devuelve
// NULL.
// Pre: la pila fue creada.
// Post: si la pila no estaba vacía, se devuelve el valor del tope anterior
// y la pila contiene un elemento menos.
void* pila_desapilar(pila_t *pila){
  void * tope = pila_ver_tope(pila);
  if (pila->cantidad>0)
    pila->cantidad--;

  if(pila->cantidad < pila->capacidad/FACTOR_ACHICAR_PILA){
    if(!_pila_redimensionar(pila, pila->capacidad/FACTOR_DISMINUIR_CAPACIDAD_PILA))
        return false;
  }

  return tope;
}

// ...
