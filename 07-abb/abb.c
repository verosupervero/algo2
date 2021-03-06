#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "abb.h"
#include "pila.h"

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/
typedef enum {NO_ES_HIJO,HIJO_IZQUIERDO,HIJO_DERECHO} hijo_t;

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
};

 struct abb_iter{
  const abb_t * arbol;
  pila_t * pila;
};

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

char * abb_obtener_clave_raiz(abb_t* arbol){
  if(!arbol)
    return NULL;

  return arbol->raiz->clave;
}
/******************************************************************************
Crea un nuevo nodo con una clave y un valor.
PRE: Recibe una clave y un valor.
POST: Copio la clave al nodo creado y la asocia al dato. Sino devuelve NULL.
*******************************************************************************/
static abb_nodo_t * crear_nodo(const char * clave, void * dato){

  abb_nodo_t * nodo = malloc(sizeof(abb_nodo_t));
  if(!nodo)
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
PRE: Recibe un nodo y una funcion de destruccion de dato/NULL.
POST: Devuelve el dato o NULL si el dato es NULL o la funcion de destruccion
destruyo el dato.
*******************************************************************************/
static void* destruir_nodo(abb_nodo_t* nodo, abb_destruir_dato_t destruir_dato ){

 free(nodo->clave);
 void* dato=NULL;
 if(destruir_dato){
   destruir_dato(nodo->dato);
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
al nodo_padre, guarda el padre del nodo actual en mi_padre.
POST: Devuelve por parametro el nodo o NULL y por referencia el padre o NULL
*******************************************************************************/
abb_nodo_t * _abb_buscar_nodo_y_padre(const abb_t *arbol, const char * clave,
                                      abb_nodo_t ** nodo_padre,
                                      abb_nodo_t * raiz, abb_nodo_t * mi_padre){
  if(!raiz || !arbol->raiz)
    return NULL;

  int cmp=arbol->comparar_clave(raiz->clave,clave);
  if(cmp==0){
    if(nodo_padre!=NULL){
      *nodo_padre= mi_padre;
    }
    return raiz;
  }
  else if(cmp>0){
    return _abb_buscar_nodo_y_padre(arbol,clave,nodo_padre,raiz->hijo_izquierdo,raiz);
  }
   return _abb_buscar_nodo_y_padre(arbol,clave,nodo_padre,raiz->hijo_derecho,raiz);
}

/******************************************************************************
 Obtiene el tipo de hijo.
PRE: Recibe un padre y su hijo
POST: Devuelve si es hijo_derecho, hijo_izquierdo o si no es hijo.
*******************************************************************************/
hijo_t obtener_parentezco(const abb_nodo_t * padre, const abb_nodo_t * hijo){
  if(!padre)
    return NO_ES_HIJO;
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

  hijo_t tipo_hijo=obtener_parentezco(padre,hijo);

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
bool emparentar_padre_e_hijo(abb_nodo_t * padre, abb_nodo_t * hijo,hijo_t parentezco){
  if(!padre)
    return false;

  if(parentezco==HIJO_DERECHO){
      if(padre->hijo_derecho!=NULL){
        return false;
      }
      padre->hijo_derecho=hijo;
      return true;
  }
  else if(parentezco==HIJO_IZQUIERDO){
    if(padre->hijo_izquierdo!=NULL){
      return false;
    }
    padre->hijo_izquierdo=hijo;
    return true;
  }
  return true;
}
/******************************************************************************
Busca los hijos de un nodo y los devuelve por referencia. El nodo fue creado.
PRE: Recibe el nodo y dos punteros para guardar la referencia a los hijos o NULL.
POST: Devuelve ambos hijos por referencia.
*******************************************************************************/
int contar_hijos(abb_nodo_t* nodo){
  if(!nodo)
    return 0;
  return 0+((nodo->hijo_izquierdo!=NULL)?1:0)+((nodo->hijo_derecho!=NULL)?1:0);
}
/******************************************************************************
Busca un reemplazante para el nodo.
PRE: Recibe el nodo y un puntero donde referenciar al padre reemplazante.
Además recibe una referencia al padre del nodo en cuestion.
POST: Devuelve el reemplazante y por referencia su padre.
*******************************************************************************/
abb_nodo_t * _abb_buscar_reemplazante(abb_nodo_t * nodo,abb_nodo_t** padre_reemplazante, abb_nodo_t * mi_padre){

  if(!nodo)
    return NULL;

  if (!nodo->hijo_izquierdo){
    *padre_reemplazante= mi_padre;
    return nodo;
  }
  return _abb_buscar_reemplazante(nodo->hijo_izquierdo,padre_reemplazante,nodo);
}
/******************************************************************************
Borra un nodo sin hijos
PRE: Recibe el nodo a borrar y su padre.Deben existir.
POST: Borra el nodo y devuelve el dato que contenia, su padre apunta a NULL
en donde estaba el nodo.
*******************************************************************************/
void * abb_borrar_nodo_sin_hijos(abb_nodo_t * nodo, abb_nodo_t * padre){
  if (!nodo)
    return NULL;

  if(padre)
    desemparentar_padre_e_hijo(padre,nodo,NULL);
  void * dato=destruir_nodo(nodo,NULL);
  return dato;
}
/******************************************************************************
Borra un nodo con un hijo
PRE: Recibe el nodo a borrar, su hijo y su padre. Deben existir.
POST: Borra el nodo y devuelve el dato que contenia, su padre se quedo con la
tenencia de su hijo.
*******************************************************************************/
void * abb_borrar_nodo_1_hijo(abb_nodo_t * nodo, abb_nodo_t * hijo_nodo, abb_nodo_t * padre_nodo, abb_t *arbol){

  if(!nodo )
    return NULL;

  hijo_t parentezco;
  if(padre_nodo){
    desemparentar_padre_e_hijo(padre_nodo,nodo,&parentezco);
    //fprintf(stderr, "%s->%s\n parentezco: %d (1) HI (2) HD \n",nodo->clave,hijo_nodo->clave,(int) parentezco );
  }

  desemparentar_padre_e_hijo(nodo,hijo_nodo,NULL);
  void * dato=destruir_nodo(nodo,NULL);
  if(padre_nodo){
    emparentar_padre_e_hijo(padre_nodo,hijo_nodo,parentezco);
  }
  else{
    arbol->raiz=hijo_nodo;
  }
  return dato;
}

/******************************************************************************
Borra un nodo con dos hijos
PRE: Recibe el nodo a borrar y su padre. Deben existir.
POST: El padre del nodo hereda sus nietos.
*******************************************************************************/
void * abb_borrar_nodo_2_hijos(abb_nodo_t * nodo, abb_nodo_t * padre_nodo){

  if(!nodo )
    return NULL;

  /*Busco al reemplazante y me guardo su clave*/
  abb_nodo_t * padre_reemplazante=NULL;
  abb_nodo_t * reemplazante = _abb_buscar_reemplazante(nodo->hijo_derecho,&padre_reemplazante,nodo);
  char* clave_reemplazante=str_dup(reemplazante->clave);

  /*Desemparento padre reemplazante con el nodo reemplazante */
  hijo_t parentezco_reemplazante=HIJO_IZQUIERDO;
  desemparentar_padre_e_hijo(padre_reemplazante,reemplazante,&parentezco_reemplazante);
  if(padre_reemplazante!=nodo){
    if(parentezco_reemplazante!=HIJO_IZQUIERDO){
      return NULL;
    }
  }
  abb_nodo_t* hijo_derecho_reemplazante=NULL;

  /*Busco si el reemplazante tiene hijos*/
  if(reemplazante)
    hijo_derecho_reemplazante=reemplazante->hijo_derecho;

  /*Borro el reemplazante y me guardo su dato*/
  void* dato_reemplazante=destruir_nodo(reemplazante,NULL);

  /*Si el reemplazante tenia un hijo se lo paso al padre del reemplazante,
  a lo sumo tiene un hijo derecho */
  if(hijo_derecho_reemplazante!=NULL)
    emparentar_padre_e_hijo(padre_reemplazante,hijo_derecho_reemplazante,parentezco_reemplazante);

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

  if(!comparar_clave)
    return NULL;

  abb_t * arbol=malloc(sizeof(abb_t));
  if(!arbol)
    return NULL;
  arbol->raiz=NULL;
  arbol->comparar_clave=comparar_clave;
  arbol->destruir_dato=destruir_dato;
  arbol->cantidad_nodos=0;
  return arbol;
}
/******************************************************************************
Guarda un nodo en el arbol
PRE: recibe la raiz del arbol, el dato, la clave y el arbol
POST: Recorre el arbol hasta encontrar donde guardar el nodo y lo guarda.
Devuelve false si no pudo almacenar el nodo en memoria, true en caso contrario.
*******************************************************************************/
bool _abb_guardar(abb_nodo_t ** raiz,const char *clave, void *dato,abb_t * arbol,
                  abb_nodo_t ** padre, bool * existia_clave){

  if(!raiz)
    return false;

  if(!(*raiz)){ /*Caso Base*/
    abb_nodo_t * nuevo_nodo=crear_nodo(clave,dato);
    if(!nuevo_nodo)
      return false;
    *raiz=nuevo_nodo;
    *existia_clave=false;
    return true;
  }

  int cmp= arbol->comparar_clave(clave,(*raiz)->clave);

  if(cmp>0){
    return _abb_guardar(&(*raiz)->hijo_derecho,clave,dato,arbol,raiz,existia_clave);
  }
  else if(cmp<0){
    return _abb_guardar(&(*raiz)->hijo_izquierdo,clave,dato,arbol,raiz,existia_clave);
  }
  /*si la clave ya existe*/
  if(arbol->destruir_dato)
    arbol->destruir_dato((*raiz)->dato);
  (*raiz)->dato=dato;
  *existia_clave=true;

  return true;
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

  abb_nodo_t * padre=NULL;
  bool existia_clave=false;
  bool guardo=_abb_guardar(&arbol->raiz,clave,dato,arbol,&padre,&existia_clave);
  if(guardo && !existia_clave)
    arbol->cantidad_nodos++;
  return guardo;
}

/******************************************************************************
Brinda la cantidad de nodos del arbol.
PRE: El árbol fue creado
POST: Se devolvió la cantidad de nodos del arbol
*******************************************************************************/
size_t abb_cantidad(abb_t * arbol){
  return arbol->cantidad_nodos;
}
/******************************************************************************
Obtiene el dato del nodo que contiene la clave o NULL.
PRE: Recibe el arbol y la clave
POST: Devuelve el dato asociado a la clave o NULL.
*******************************************************************************/
void * abb_obtener(const abb_t *arbol, const char *clave){
  if(!arbol)
    return NULL;
  abb_nodo_t * nodo=_abb_buscar_nodo_y_padre(arbol,clave, NULL,arbol->raiz,NULL);
  return nodo?nodo->dato:NULL;
}
/******************************************************************************
Revisa si la clave pertenece al arbol
PRE: Recibe clave y arbol
POST: Devuelve true si pertenece, false en caso contrario.
*******************************************************************************/

bool abb_pertenece(const abb_t *arbol, const char *clave){
  if(!arbol)
    return NULL;
  abb_nodo_t * nodo=_abb_buscar_nodo_y_padre(arbol,clave, NULL,arbol->raiz,NULL);
  return nodo?true:false;
}
/******************************************************************************
Borra un nodo del arbol
PRE: Recibe el arbol y una clave
POST: Borro la clave y reconstruyo el arbol.
*******************************************************************************/
void * abb_borrar(abb_t *arbol, const char *clave){
  abb_nodo_t * padre_nodo= NULL;
  abb_nodo_t * nodo=_abb_buscar_nodo_y_padre(arbol,clave,&padre_nodo,arbol->raiz,NULL);
  if(!nodo)
    return NULL;

  int cantidad_de_hijos=contar_hijos(nodo);
  void * dato=NULL;

  /*Borro el nodo*/
  if(cantidad_de_hijos==0){
    dato=abb_borrar_nodo_sin_hijos(nodo,padre_nodo);
  }
  else if(cantidad_de_hijos==1){
    if(nodo->hijo_izquierdo!=NULL)
      dato=abb_borrar_nodo_1_hijo(nodo,nodo->hijo_izquierdo,padre_nodo,arbol);
    else{
      dato=abb_borrar_nodo_1_hijo(nodo,nodo->hijo_derecho,padre_nodo,arbol);
    }
  }
  else{
    dato=abb_borrar_nodo_2_hijos(nodo,padre_nodo);
  }


  /*Disminuye la cantidad de nodos del arbol*/
  arbol->cantidad_nodos--;

  /* Si elimine el nodo raiz, debo cambiar el puntero*/
   if(arbol->cantidad_nodos == 0){
     arbol->raiz = NULL;
   }
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

  if (nodo->hijo_izquierdo)
    _destruir_familia(nodo->hijo_izquierdo, destruir_dato);
	if (nodo->hijo_derecho)
    _destruir_familia(nodo->hijo_derecho, destruir_dato);
	destruir_nodo(nodo,destruir_dato);
}

/******************************************************************************
Destruye el arbol desde la raiz.
PRE: Recibe el arbol.
POST: NO hay mas arbol.
*******************************************************************************/
void abb_destruir(abb_t *arbol){
  if(!arbol)
    return;
  if(arbol->raiz)
    _destruir_familia(arbol->raiz, arbol->destruir_dato);
  free(arbol);
}

/* ******************************************************************
*                    PRIMITIVAS DEL ITERADOR EXTERNO
* *****************************************************************/

bool _abb_apilar_nodo_e_hijos_izquierdos(pila_t * pila, abb_nodo_t* nodo){
  if(!pila || !nodo)
    return false;
  abb_nodo_t * nodo_actual=nodo;
  while(nodo_actual!=NULL){
    pila_apilar(pila,nodo_actual);
    nodo_actual=nodo_actual->hijo_izquierdo;
  }
  return true;
}

/******************************************************************************
Crea el iterador del arbol
PRE: Recibe el arbol.
POST: Crea el iterador si hay memoria, sino devuelve NULL
*******************************************************************************/
abb_iter_t *abb_iter_in_crear(const abb_t *arbol){

  abb_iter_t* iter = malloc(sizeof(abb_iter_t));
  if (!iter)
    return NULL;

  /*Creo la pila del iterador*/
  iter->pila = pila_crear();
  if (!iter->pila){
    free(iter);
    return NULL;
  }
  /*Apilo la raiz y todos sus hijos izquierdos*/
  if(arbol-> raiz)
    _abb_apilar_nodo_e_hijos_izquierdos(iter->pila,arbol->raiz);
  return iter;
}

/******************************************************************************
Avanza en el arbol con el iterador.
PRE: Recibe el iterador.
POST: Devuelve si pudo avanzar el iterador.
*******************************************************************************/
bool abb_iter_in_avanzar(abb_iter_t *iter){
  /*El iterador no puede avanzar si esta al final*/
  if (abb_iter_in_al_final(iter))
    return false;
  abb_nodo_t * nodo_desapilado = pila_desapilar(iter->pila);
  if(!nodo_desapilado)
    return false;

  /*Si el nodo_desapilado tiene hijo derecho, apilo hijo derecho
  y todos los hijos izquierdos que existan (sus nietos izquierdos)*/
  if(nodo_desapilado->hijo_derecho)
    _abb_apilar_nodo_e_hijos_izquierdos(iter->pila,nodo_desapilado->hijo_derecho);

  return true;
}
/******************************************************************************
Muestra la clave del elemento actual.
PRE: Recibe el iterador.
POST: Devuelve la clave del nodo actual.
*******************************************************************************/
const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	abb_nodo_t * nodo_actual = pila_ver_tope(iter->pila);
  return nodo_actual?(nodo_actual->clave):NULL;
}
/******************************************************************************
Revisa si el iterador esta al final
PRE: Recibe el iterador.
POST: Devuelve si esta al final.
*******************************************************************************/
bool abb_iter_in_al_final(const abb_iter_t *iter){
   return pila_esta_vacia(iter->pila);
}
/******************************************************************************
Destruye el iterador del arbol.
PRE: Recibe el iterador.
POST: NO hay mas iterador.
*******************************************************************************/
void abb_iter_in_destruir(abb_iter_t* iter){
  pila_destruir(iter->pila);
  free(iter);
}
/* ******************************************************************
*                    PRIMITIVAS DEL ITERADOR INTERNO
* *****************************************************************/
/******************************************************************************
Recorre el ABB IN order
PRE: Recibe la raiz y la funcion de visita.
POST: Visito cada nodo con la funcion pasada por parametro.
*******************************************************************************/
bool _abb_in_order(abb_nodo_t * nodo, bool visitar(const char *, void *, void *), void *extra){
  if(!nodo)
    return true;

  if(!_abb_in_order(nodo->hijo_izquierdo, visitar,extra))
    return false;

  if(!visitar(nodo->clave,nodo->dato,extra))
    return false;

  return _abb_in_order(nodo->hijo_derecho, visitar,extra);
}
/******************************************************************************
Recorre el ABB IN order
PRE: Recibe el arbol y la funcion de visita.
POST: Visito cada nodo con la funcion pasada por parametro.
*******************************************************************************/
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
  if(!arbol || !arbol->raiz)
    return;
  _abb_in_order(arbol->raiz,visitar,extra);
}
