#include "abb.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/
typedef struct abb_nodo{
  char * clave;
  void * dato;
  struct abb_nodo * hijo_izquierdo;
  struct abb_nodo * hijo_derecho;
}abb_nodo_t;

struct abb{
  abb_nodo_t * raiz;
  size_t cantidad_nodos;
  abb_destruir_dato_t destruir_dato;
  abb_comparar_clave_t comparar_clave;
}
typedef enum {NO_ES_HIJO,HIJO_IZQUIERDO,HIJO_DERECHO}hijo_t;

/* ******************************************************************
 *                FUNCIONES AUXILIARES DE ABB
 * *****************************************************************/
char * str_dup(const char * cadena){
  size_t i;
  size_t n= strlen(cadena) + 1;
  char * copia=malloc((n)*sizeof(char));
  if (!copia)
   return NULL;

  for(i=0; (copia[i]=cadena[i]);i++);
  return copia;
}
/******************************************************************************
Crea un nuevo nodo con una clave y un valor.
PRE: Recibe una clave y un valor.
POST: Copio la clave al nodo creado y la asocia al dato. Sino devuelve NULL.
*******************************************************************************/
abb_nodo_t * crear_nodo(char * clave, void * dato){

  abb_nodo_t * nodo = malloc(sizeof(abb_nodo_t));
  if(!nodo_abb)
    return NULL;

  char * copia_clave = str_dup(clave);
  if(!copia_clave){
    free(nodo);
    return NULL;
  }

  nodo->clave = copia_clave;
  nodo->dato = dato;
  nodo->hijo_izquierdo = NULL;
  nodo->hijo_derecho = NULL;
  return nodo;
}


/******************************************************************************
Destruye el nodo y devuelve o no el dato segun los parametros pasados.
PRE: Recibe un nodo y una funcion de destruccion de dato/NULL. El nodo fue creado.
POST: Devuelve el dato o NULL si el dato es NULL o la funcion de destruccion
destruyo el dato.
*******************************************************************************/
void* destruir_nodo(abb_nodo_t* nodo, abb_destruir_dato_t destruir_dato ){
 free(nodo->clave);
 void* dato;
 if(destruir_dato){
   destruir_dato(nodo);
   dato=NULL;
 }
 else{
   dato=nodo->dato;
 }
 free(nodo);
 return dato;
}

/******************************************************************************
Busca recursivamente un nodo en el arbol por clave y su nodo_padre
PRE: Recibe la raiz del arbol, la clave del nodo buscado, el arbol y una puntero
al nodo_padre.
POST: Devuelve por parametro el nodo o NULL y por referencia el padre o NULL
*******************************************************************************/
abb_nodo_t * _abb_buscar_nodo_y_padre(abb_t * raiz,const char * clave,
                                 const abb_t *arbol, abb_nodo_t ** nodo_padre){
 /*Si el nodo no tiene hijos*/
 if(!raiz)
   return NULL;

 /*Si el nodo actual es el padre:*/
 if(!arbol->comparar_clave(raiz->hijo_izquierdo->clave,clave)){
   if(*padre)
     *padre=raiz;
   return raiz->hijo_izquierdo;
 }
 if(!arbol->comparar_clave(raiz->hijo_derecho->clave,clave)){
   if(*padre)
     *padre=raiz;
   return raiz->hijo_derecho;
 }

 /*Si no es el padre:*/
 /*Si la clave es mas grande que la que estoy viendo actualmente*/
 if(arbol->comparar_clave(raiz->clave,clave)>0){
   return _abb_buscar_nodo_y_padre(raiz->hijo_derecho,clave,arbol,padre);
 }
 /*Si la clave es mas chica*/
 return _abb_buscar_nodo_y_padre(raiz->hijo_izquierdo,clave,arbol,padre);
}

/******************************************************************************
 Obtiene el tipo de hijo.
PRE: Recibe un padre y su hijo
POST: Devuelve si es hijo_derecho, hijo_izquierdo o si no es hijo.
*******************************************************************************/
size_t obtener_parentezco(const abb_nodo_t * padre, const abb_nodo_t * hijo){
  if(padre->hijo_derecho == hijo)
    return HIJO_DERECHO;
  else if(padre->hijo_izquierdo==hijo)
    return HIJO_IZQUIERDO;
  return NO_ES_HIJO;
}

/******************************************************************************
Desemparenta un nodo padre de su nodo hijo
PRE: Recibe padre e hijo y un puntero si se desea saber de que tipo era.
Ambos existen.
POST: El padre apunta a NULL en la direccion que apuntaba a su hijo.
Se guarda el parentezco anterior de ambos
*******************************************************************************/
void desemparentar_padre_e_hijo(abb_nodo_t * padre, abb_nodo_t * hijo, hijo_t * parentezco_anterior){

  tipo_hijo=obtener_parentezco(padre,hijo);

  if(tipo_hijo==HIJO_DERECHO){
      padre->hijo_derecho=NULL;
      if(parentezco_anterior!=NULL)
        *parentezco_anterior=HIJO_DERECHO;
      return;
  }
  else if(tipo_hijo==HIJO_IZQUIERDO){
    padre->hijo_izquierdo=NULL;
    if(parentezco_anterior!=NULL)
      *parentezco_anterior=HIJO_IZQUIERDO;
  }
  else{
    if(parentezco_anterior!=NULL)
      *parentezco_anterior=NO_ES_HIJO;
  }
}

/******************************************************************************
Emparenta un nodo padre de su nodo hijo
PRE: Recibe padre e hijo y el tipo de emparentamiento que se desea.
POST: Emparento padre con hijo o no lo emparento si se paso que no era hijo.
*******************************************************************************/
void emparentar_padre_e_hijo(abb_nodo_t * padre, abb_nodo_t * hijo,hijo_t parentezco){
  if(parentezco==HIJO_DERECHO){
      padre->hijo_derecho=hijo;
      return;
  }
  else if(parentezco==HIJO_IZQUIERDO){
    padre->hijo_izquierdo=hijo;
    return
  }
  else{
    fprintf(stderr, "%s\n","No son parientes" );
  }
}
/******************************************************************************
Busca los hijos de un nodo y los devuelve por referencia. El nodo fue creado.
PRE: Recibe el nodo y dos punteros para guardar la referencia a los hijos o NULL.
POST: Devuelve ambos hijos por referencia.
*******************************************************************************/
void buscar_hijos(abb_nodo_t* nodo,abb_nodo_t** hijo_izquierdo,abb_nodo_t** hijo_derecho){
  if(nodo->hijo_izquierdo!=NULL){
    *hijo_izquierdo=nodo->hijo_izquierdo;
  }
  else{
    *hijo_izquierdo=NULL;
  }
  if(nodo->hijo_derecho!=NULL){
    *hijo_derecho=nodo->hijo_derecho;
  }
  else{
    *hijo_derecho=NULL;
  }
}

/******************************************************************************
Borra un nodo sin hijos
PRE: Recibe el nodo a borrar y su padre.Deben existir.
POST: Borra el nodo y devuelve el dato que contenia, su padre apunta a NULL
en donde estaba el nodo.
*******************************************************************************/
void * abb_borrar_nodo_sin_hijos(abb_nodo_t * nodo, abb_nodo_t * padre){
  desemparentar_padre_e_hijo(padre,nodo,NULL);
  void * dato=destruir_nodo(nodo);
  return dato;
}
/******************************************************************************
Borra un nodo con un hijo
PRE: Recibe el nodo a borrar, su hijo y su padre. Deben existir.
POST: Borra el nodo y devuelve el dato que contenia, su padre se quedo con la
tenencia de su hijo.
*******************************************************************************/
void * abb_borrar_nodo_1_hijo(abb_nodo_t * nodo, abb_nodo_t * hijo_nodo, abb_nodo_t * padre_nodo){
  hijo_t parentezco=NULL;
  desemparentar_padre_e_hijo(padre_nodo,nodo,&parentezco);
  void * dato=destruir_nodo(nodo,NULL);
  emparentar_padre_e_hijo(padre_nodo,hijo_nodo,parentezco);
  return dato;
}

/******************************************************************************
Borra un nodo con dos hijos
PRE: Recibe el nodo a borrar y su padre. Deben existir.
POST: El padre del nodo hereda sus nietos.
*******************************************************************************/
void * abb_borrar_nodo_2_hijos(abb_nodo_t * nodo, abb_nodo_t * padre_nodo){

  /*Busco al reemplazante y me guardo su clave*/
  abb_t * padre_reemplazante=NULL;
  abb_nodo_t * reemplazante = abb_buscar_reemplazante(nodo->hijo_derecho,&padre_reemplazante);
  char* clave_reemplazante=str_dup(reemplazante->clave);

  /*Desemparento padre reemplazante con el nodo reemplazante */
  hijo_t parentezco_reemplazante=NO_ES_HIJO;
  desemparentar_padre_e_hijo(padre_reemplazante,reemplazante,&parentezco_reemplazante);

  /*Busco si el reemplazante tiene hijos*/
  abb_nodo_t** hijo_izquierdo_reemplazante;
  abb_nodo_t** hijo_derecho_reemplazante;
  buscar_hijos(reemplazante,&hijo_izquierdo_reemplazante,& hijo_derecho_reemplazante);

  /*Borro el reemplazante y me guardo su dato*/
  void* dato_reemplazante=destruir_nodo(reemplazante,NULL);

  /*Si el reemplazante tenia un hijo se lo paso al padre del reemplazante,
  a lo sumo tiene un solo hijo*/

  if(hijo_izquierdo_reemplazante!=NULL){
    emparentar_padre_e_hijo(padre_reemplazante,hijo_izquierdo_reemplazante,parentezco_reemplazante);
  }
  else{
    emparentar_padre_e_hijo(padre_reemplazante,hijo_derecho_reemplazante,parentezco_reemplazante);
  }
  /*Piso los datos del nodo con los datos del reemplazante
  y me guardo el dato anterior del nodo*/

  free(nodo->clave);
  nodo->clave=clave_reemplazante;
  void * anterior_dato_nodo=nodo->dato;
  nodo->dato=dato_reemplazante;

  /*Devuelvo el dato anterior del nodo*/
  return anterior_dato_nodo;
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ABB Y FUNCIONES PRIVADAS
 * *****************************************************************/

 /******************************************************************************
 Crea un arbol.
 PRE: Recibe una funcion de comparar claves, una funcion de destruir datos.
 POST: Creo el arbol si habia suficiente memoria, sino devuelve NULL.
 *******************************************************************************/
abb_t* abb_crear(abb_comparar_clave_t comparar_clave,abb_destruir_dato_t destruir_dato){

  abb_t * arbol=malloc(sizeof(abb_t));
  if(!arbol)
    return NULL;
  abb->raiz=NULL;
  abb->comparar_clave=NULL;
  abb->destruir_dato=NULL;
  abb->cantidad_nodos=0;
  return abb;
}
/******************************************************************************
Guarda un nodo en el arbol
PRE: recibe la raiz del arbol, el dato, la clave y el arbol
POST: Recorre el arbol hasta encontrar donde guardar el nodo y lo guarda.
Devuelve false si no pudo almacenar el nodo en memoria, true en caso contrario.
*******************************************************************************/
bool _abb_guardar(abb_nodo_t * raiz,const char *clave, void *dato,abb_t * arbol){

  if(!raiz){ /*Caso Base*/
    abb_nodo_t * nuevo_nodo=crear_nodo(clave,dato);
    if(!nuevo_nodo)
      return false;
    raiz=nuevo_nodo;
    return true;
  }

  int cmp= arbol->comparar_clave(clave,raiz->clave);

  if(cmp>0){
    return _abb_guardar(raiz->hijo_derecho,clave,dato,arbol);
  }
  else if(cmp<0){
    return _abb_guardar(raiz->hijo_izquierdo,clave,dato,arbol);
  }
  else{
    if(arbol->destruir)
      arbol->destruir(raiz->dato);
    raiz->dato=dato;
  }
}
/******************************************************************************
Guarda un nodo en el arbol, es wrapper de una funcion recursiva
PRE: recibe el dato, la clave y el arbol
POST: Recorre el arbol hasta encontrar donde guardar el nodo y lo guarda.
Devuelve false si no pudo almacenar el nodo en memoria, true en caso contrario.
*******************************************************************************/
bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
  if(!arbol)
    return false;

  bool guardo=_abb_guardar(&abb->raiz,clave,dato,arbol);
  if(guardo)
    arbol->cantidad++;
  return guardo;
}

/******************************************************************************
Brinda la cantidad de nodos del arbol.
PRE: El árbol fue creado
POST: Se devolvió la cantidad de nodos del arbol
*******************************************************************************/
size_t abb_cantidad(abb_t * arbol){
  return arbol->cantidad;
}
/******************************************************************************
Obtiene el dato del nodo que contiene la clave o NULL.
PRE: Recibe el arbol y la clave
POST: Devuelve el dato asociado a la clave o NULL.
*******************************************************************************/
void * abb_obtener(const abb_t *arbol, const char *clave){
  if(!arbol)
    return NULL;
  abb_nodo_t * nodo=_abb_buscar_nodo_y_padre(arbol->raiz,clave,arbol,NULL);
  return nodo?nodo->dato:NULL;
}
/******************************************************************************
Revisa si la clave pertenece al arbol
PRE: Recibe clave y arbol
POST: Devuelve true si pertenece, false en caso contrario.
*******************************************************************************/
bool abb_pertenece(const abb_t *arbol, const char *clave){
  return !abb_obtener(arbol, clave)?false:true;
}
/******************************************************************************
Borra un nodo del arbol
PRE: Recibe el arbol y una clave
POST: Borro la clave y reconstruyo el arbol.
*******************************************************************************/
void * abb_borrar(abb_t *arbol, const char *clave){
  abb_nodo_t * padre_nodo= NULL;
  abb_nodo_t * nodo=abb_buscar_nodo_y_padre(arbol->raiz,clave,arbol->cmp,&padre_nodo);
  if(!nodo)
    return NULL;
  abb_nodo_t * hijo_izquierdo=NULL;
  abb_nodo_t * hijo_derecho=NULL;

  size_t cantidad_de_hijos=buscar_hijos(nodo,&hijo_izquierdo,&hijo_derecho);
  void * dato=NULL;

  /*Borro el nodo*/
  if(cantidad_de_hijos==0){
    dato=abb_borrar_nodo_sin_hijos(nodo,padre_nodo);
  }
  else if(cantidad_de_hijos==1){
    if(hijo_izquierdo!=NULL)
      dato=abb_borrar_nodo_1_hijo(nodo,hijo_izquierdo,padre_nodo);
    else{
      dato=abb_borrar_nodo_1_hijo(nodo,hijo_derecho,padre_nodo);
    }
  }
  else{
    dato=abb_borrar_nodo_2_hijos(nodo,padre_nodo);
  }
  /*Si rescato el dato disminuye la cantidad de nodos del arbol*/

  arbol->cantidad_nodos--;
  return dato;
}
/******************************************************************************
Destruye el nodo y sus hijos.
PRE: Recibe el nodo.
POST: NO hay mas nodo ni hijos.
*******************************************************************************/
void _destruir_familia(abb_nodo_t *nodo, abb_destruir_dato_t destruir_dato){
	if(!nodo)/*Caso base*/
    return;

	_destruir_familia(nodo->hijo_izquierdo, destruir_dato);
	_destruir_familia(nodo->hijo_derecho, destruir_dato);
	nodo_destruir(nodo, destruir_dato);
}

/******************************************************************************
Destruye el arbol desde la raiz.
PRE: Recibe el arbol.
POST: NO hay mas arbol.
*******************************************************************************/
void abb_destruir(abb_t *arbol){
  _destruir_familia(arbol->raiz, arbol->destruir_dato);
  free(arbol);
}
/* ******************************************************************
*                    PRIMITIVAS DEL ITERADOR EXTERNO
* *****************************************************************/
/******************************************************************************
Crea el iterador del arbol
PRE: Recibe el arbol.
POST: Crea el iterador si hay memoria, sino devuelve NULL
*******************************************************************************/
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);
/******************************************************************************
Avanza en el arbol con el iterador.
PRE: Recibe el iterador.
POST: Devuelve si pudo avanzar el iterador.
*******************************************************************************/
bool abb_iter_in_avanzar(abb_iter_t *iter);
/******************************************************************************
Muestra la clave del elemento actual.
PRE: Recibe el iterador.
POST: Devuelve la clave del nodo actual.
*******************************************************************************/
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);
/******************************************************************************
Revisa si el iterador esta al final
PRE: Recibe el iterador.
POST: Devuelve si esta al final.
*******************************************************************************/
bool abb_iter_in_al_final(const abb_iter_t *iter);
/******************************************************************************
Destruye el iterador del arbol.
PRE: Recibe el iterador.
POST: NO hay mas iterador.
*******************************************************************************/
void abb_iter_in_destruir(abb_iter_t* iter);
/* ******************************************************************
*                    PRIMITIVAS DEL ITERADOR INTERNO
* *****************************************************************/
/******************************************************************************
Recorre el ABB IN order
PRE: Recibe el arbol y la funcion de visita.
POST: Visito cada nodo con la funcion pasada por parametro.
*******************************************************************************/
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);
