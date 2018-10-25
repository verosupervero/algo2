#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */
struct lista;
typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(char**));

// Devuelve verdadero o falso, según si la lista tiene o no elementos enlistados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista al inicio de la misma. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista.
bool lista_insertar_primero(lista_t *lista, void* valor);

// Agrega un nuevo elemento a la lista al final de la misma. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista.
bool lista_insertar_ultimo(lista_t *lista, void* valor);


// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista);


// Obtiene el valor del último elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el último elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t *lista);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento de la lista, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void* lista_borrar_primero (lista_t *lista);

//Devuelve el largo de la lista
//Pre: La lista fue creada
//Post: se devolvió tamaño de la lista
size_t lista_largo(const lista_t *lista);

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

 // Crea un iterador.
 // Post: devuelve un nuevo iterador vacío.
lista_iter_t *lista_iter_crear(lista_t *lista);

// El iterador avanza una posición en la lista.
// Pre: El iterador fue creado.
// Post: se devolvió true si pudo avanzar o false si llego al final de la lista.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor del dato al que apunta el iterador.
// Pre: El iterador fue creado.
// Post: Devolvió el valor del dato al que apunta el iterador o NULL si la lista
// estaba vacía o si el iterador apuntaba al final de la lista
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Constata si el iterador apunta al final de la lista.
// Pre: La lista fue creada
// Post: Devolvió true si llegó al final de la lista, false en caso contrario.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: El iterador fue creado.
// Post: Se destruyó el iterador.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un elemento en la lista
// Pre: El iterador fue creado.
// Post: Devolvió true si se insertó el elemento en la lista, false en caso contrario.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Borra un elemento en la lista
// Pre: El iterador fue creado.
// Post: Devolvió true si se insertó el elemento en la lista, false en caso contrario.
void *lista_iter_borrar(lista_iter_t *iter);

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

// Itera una posicion en la lista. Visitar recibe el dato y un puntero extra.
// Devuelve true si se debe seguir iterando, false en caso contrario.
// Pre: La lista fue creada.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_alumno(void);

#endif // LISTA_H
