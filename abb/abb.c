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
void desemparentar_padre_e_hijo(abb_nodo_t * padre, abb_nodo_t * hijo,hijo_t * parentezco_anterior){

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
void emparentar_padre_e_hijo(abb_nodo_t * padre, abb_nodo_t * hijo,hijo_t tipo_hijo){
  if(tipo_hijo==HIJO_DERECHO){
      padre->hijo_derecho=hijo;
      return;
  }
  else if(tipo_hijo==HIJO_IZQUIERDO){
    padre->hijo_izquierdo=hijo;
    return
  }
  else{
    fprintf(stderr, "%s\n","No son parientes" );
  }
}

/******************************************************************************
Borra un nodo sin hijos
PRE: Recibe el nodo a borrar y su padre
POST: Borra el nodo y devuelve el dato que contenia, su padre apunta a NULL
en donde estaba el nodo.
*******************************************************************************/
void * abb_borrar_nodo_sin_hijos(abb_nodo_t * nodo_a_borrar, abb_nodo_t * padre){
  if(!nodo_a_borrar || !padre)
    return NULL;
  desemparentar_padre_e_hijo(padre,nodo_a_borrar,NULL);
  dato=destruir_nodo(nodo_a_borrar);
  return dato;
}

void * abb_borrar_nodo_1_hijo(abb_nodo_t * nodo_a_borrar, abb_nodo_t * padre){
  if(!nodo_a_borrar || !padre)
    return NULL;
}


/******************************************************************************
Borra un nodo del arbol
PRE: Recibe el arbol y una clave
POST: Borro la clave y reconstruyo el arbol.
*******************************************************************************/
void * abb_borrar(abb_t *arbol, const char *clave){
  abb_nodo_t * padre= NULL;
  abb_nodo_t * nodo_buscado=abb_buscar_nodo_y_padre(arbol->raiz,clave,arbol->cmp,&padre);
  if(!nodo_buscado)
    return NULL;
  size_t cantidad_de_hijos=obtener_cantidad_de_hijos(nodo_buscado);
  void * dato=NULL;

  /*Borro el nodo*/
  if(cantidad_de_hijos==0){
    dato=abb_borrar_nodo_sin_hijos(nodo,padre,destruir_dato);
  }
  else if(cantidad_de_hijos==1){
    dato=abb_borrar_nodo_1_hijo(nodo,padre,destruir_dato);
  }
  else{
    dato=abb_borrar_nodo_2_hijos(nodo,padre,destruir_dato);
  }
  /*Si rescato el dato disminuye la cantidad de nodos del arbol*/
  if(dato){
    arbol->cantidad_nodos--;
  }
  return dato;
}

void abb_destruir(abb_t *arbol){

}


/* ******************************************************************
*                    PRIMITIVAS DEL ITERADOR EXTERNO
* *****************************************************************/
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);
bool abb_iter_in_avanzar(abb_iter_t *iter);
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);
bool abb_iter_in_al_final(const abb_iter_t *iter);
void abb_iter_in_destruir(abb_iter_t* iter);

/* ******************************************************************
*                    PRIMITIVAS DEL ITERADOR INTERNO
* *****************************************************************/
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);
