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
  if(nodo_abb=NULL || *nodo_abb==NULL)
    return false;
    destruir
  *nodo_abb->dato=dato;
  return true;
}

bool _abb_guardar(abb_nodo_t ** nodo_abb,const char *clave, void *dato,abb_t * arbol){
  if(nodo_abb=NULL)
    return false;

  if(*nodo_abb==NULL){ /*Caso Base*/
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
  bool guardo=_abb_guardar(abb->raiz,clave,dato,arbol);
  if(guardo)
    arbol->cantidad++;
  return guardo;
}

void *abb_borrar(abb_t *arbol, const char *clave);
void *abb_obtener(const abb_t *arbol, const char *clave);
bool abb_pertenece(const abb_t *arbol, const char *clave);
size_t abb_cantidad(abb_t *arbol);
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
