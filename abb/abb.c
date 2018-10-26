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
  abb_comparar_clave_t cmp;
}
/* ******************************************************************
 *                FUNCIONES AUXILIARES DE ABB
 * *****************************************************************/

/* ******************************************************************
 *                    PRIMITIVAS DEL ABB Y FUNCIONES PRIVADAS
 * *****************************************************************/
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
  abb_t * arbol=malloc(sizeof(abb_t));
  if(!arbol)
    return NULL;
  abb->raiz=NULL;
  abb->cmp=NULL;
  abb->destruir_dato=NULL;
  abb->cantidad_nodos=0;
  return abb;
}
bool pisar_dato(abb_nodo_t ** nodo_abb, void *dato){
  if(!nodo_abb || !(*nodo_abb))
    return false;
    destruir
  *nodo_abb->dato=dato;
  return true;
}

//es doble puntero a nodo_abb porque voy a cambiarle el puntero a uno de los hijos
bool _abb_guardar(abb_nodo_t ** nodo_abb,const char *clave, void *dato,abb_t * arbol){
  if(!nodo_abb)
    return false;

  if(!(*nodo_abb)){ /*Caso Base*/
    abb_nodo_t * nuevo_nodo=crear_nodo(clave,dato);
    if(!nodo_abb)
      return false;
    *nodo_abb=nuevo_nodo;
    return true;
  }
  if(arbol->cmp(clave,nodo_abb->clave)>0){
    return _abb_guardar(&nodo_abb->hijo_derecho,clave,dato,arbol);
  }
  if(arbol->cmp(clave,nodo_abb->clave)<0){
    return _abb_guardar(&nodo_abb->hijo_izquierdo,clave,dato,arbol);
  }
  return pisar_dato(&nodo_abb,dato,arbol->destruir_dato);
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
 if(!arbol)
  return false;
  bool guardo=_abb_guardar(&abb->raiz,clave,dato,arbol);
  if(guardo)
    arbol->cantidad++;
  return guardo;
}



abb_nodo_t * abb_buscar_nodo_y_padre(abb_t * nodo_abb,const char * clave, abb_comparar_clave_t cmp, abb_nodo_t * nodo_padre){
  if(!nodo_abb)
    return NULL;

  /*Si el nodo actual es el padre:*/
  if(!cmp(nodo_abb->hijo_izquierdo->clave,clave)){
    if(*padre)
      *padre=nodo_abb;
    return nodo_abb->hijo_izquierdo;
  }
  if(!cmp(nodo_abb->hijo_derecho->clave,clave)){
    if(*padre)
      *padre=nodo_abb;
    return nodo_abb->hijo_derecho;
  }
  /*Si la clave es mas grande que la que estoy viendo actualmente*/
  if(cmp(nodo_abb->clave,clave)>0){
    return abb_buscar_nodo_y_padre(nodo_abb->hijo_derecho,clave,arbol->cmp,padre);
  }
  return abb_buscar_nodo_y_padre(nodo_abb->hijo_izquierdo,clave,arbol->cmp,padre);
}

size_t abb_cantidad(abb_t * arbol){
  return arbol?arbol->cantidad:0;
}

void * abb_obtener(const abb_t *arbol, const char *clave){
  if(!arbol)
    return NULL;
  abb_nodo_t * nodo=abb_buscar_nodo_y_padre(arbol->raiz,clave,arbol->cmp,NULL);
  return nodo?nodo->dato:NULL;
}


bool abb_pertenece(const abb_t *arbol, const char *clave){
  if(!arbol)
    return false;
  abb_nodo_t * nodo=abb_buscar_nodo_y_padre(arbol->raiz,clave,arbol->cmp,NULL);
  return nodo?true:false;
}


void * abb_borrar_nodo_sin_hijos(nodo_t * nodo_a_borrar, nodo_t * padre, abb_destruir_dato_t destruir_dato){
  if(!nodo_a_borrar || !padre)
    retun NULL;
  desemparentar_padre_e_hijo(nodo_a_borrar,padre)
  dato=destruir_nodo(nodo_a_borrar);
  return dato;
}


void * abb_borrar(abb_t *arbol, const char *clave){
  nodo_t * padre= NULL;
  nodo_t * nodo_buscado=abb_buscar_nodo_y_padre(arbol->raiz,clave,arbol->cmp,&padre);
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

void abb_destruir(abb_t *arbol);


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
