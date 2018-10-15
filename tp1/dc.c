#include <stdio.h>
#include "pila.h"
#include "strutil.h"
#define ANSI_COLOR_LGH_RED	   "\x1b[1m\x1b[31m"
#define ANSI_COLOR_LGH_GREEN   "\x1b[1m\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*******FUNCIONES DE CUENTAS*****************/

int potencia(int n,int e){
  int restante=0;
  if(e==0)
    return 1;
  int potencia_mitad= potencia(n,e/2);
  if(e%2==1){
    restante=n;
  }
  else{
    restante=1;
  }
  return potencia_mitad*potencia_mitad*restante;
}

int logaritmo(int b, int n){
  if(b==n)
    return 1;
  int potencia= 1;
  while(n/base < 1){
    potencia++;
    n= n/base;
  }
  return potencia;
}

bool es_entero(char * literal){
  char * endptr=NULL;
  strtol(literal, &endptr, 10);
  return (*endptr != '\0');
}
/*Pre: la pila fue creada
Post: Se apilo el literal en la pila*/
bool procesar_entero (pila_t * pila, char * literal){
  fprintf(stderr, "%s\n","procesando entero, apilando");
  bool apile= pila_apilar(pila,literal);
  fprintf(stderr, "%s: %d\n","procesando entero, apilando",apile?1:0);
  return apile;
}


bool procesar_literales(pila_t * pila,char * literal){
  /*Es un nro?*/
    //agrego a la pila
  /*Es una operacion?*/
    //verifico que es una operacion de la lista de operaciones
    //aplico operacion(pila,puntero a funcion a la operacion[nro op])
      //si la operacion no se pudo aplicar, resultado=error, return
  if(es_entero(literal)){
    fprintf(stderr, "%s%s%s\n", "El literal",literal, "es un entero");
    return procesar_entero(pila,literal);
  }
  if(es_operacion(literal)){
    fprintf(stderr, "%s%s%s\n", "El literal",literal, "es una operacion");
    return procesar_operacion(pila,literal);
  }
  return false;
}

bool procesar_calculo_polaco_inverso (char * linea, int * resultado){

  if(linea==NULL || resultado==NULL){
    fprintf(stderr, "%s\n", "No hay linea o resultado");
    return false;
  }

  /*Genero un vector de literales para procesarlos por separado*/
  char ** vector_literales= split(linea, ' ');
  if(!vector_literales){
    fprintf(stderr, "%s\n", "No pude procesar los literales");
    return false;
  }

  /*Creo una pila para ir almacenando los resultados parciales
  de la calculadora*/
  pila_t * pila=pila_crear();

  /*Proceso el calculo polaco en el vector de literales*/
  bool proceso_calculo_polaco=false;
  size_t i=0;
  for(size_t i=0; vector_literales[i]!=NULL; i++){
    proceso_literales=procesar_literales(pila,vector_literales[i]);
    if(!proceso_literales){
      fprintf(stderr, "%s %d: %sERROR%s\n", "Literal",i,ANSI_COLOR_LGH_RED,ANSI_COLOR_RESET);
      proceso_calculo_polaco=false;
      return;
    }
    else{
      proceso_calculo_polaco=true;
      fprintf(stderr, "%s %d: %sOK%s\n", "Literal",i,ANSI_COLOR_LGH_GREEN,ANSI_COLOR_RESET);
    }
  }

  fprintf(stderr, "%s\n", "Todo OK con procesar literales");
  /*Reviso que exista solo un resultado final en la pila y no más elementos*/
  int * resultado_a_priori=NULL;
  if(proceso_calculo_polaco){
    resultado_a_priori=pila_desapilar(pila);
    fprintf(stderr, "%s\n", "Calculé el resultado a priori");
  }
  if(resultado_a_priori==NULL){
    fprintf(stderr, "%s\n", "El resultado a priori es NULL");
    proceso_calculo_polaco=false;
  }
  if(!pila_esta_vacia(pila)){
    fprintf(stderr, "%s\n", "No se vació la pila");
    proceso_calculo_polaco=false;
  }

  /*Libero la memoria dinámica pedida*/
  free_strv(vector_literales);
  pila_destruir(pila);

  /*Devuelvo el resultado y si se realizó el cálculo*/
  resultado=resultado_a_priori;
  return proceso_calculo_polaco;
}



//Necesito:
  //Diccionario de tipos de operaciones
  //Enum de operaciones
  //Diccionario de punteros a operaciones

int main (int argc, char * argv []){

  /*Leo la entrada estandar*/


  char * linea=NULL;
  size_t tamanio_linea=0;
  int resultado=0;

  /*Cuando el archivo no termino:*/
  while(!feof(fi)){     /*Leo una línea del archivo*/
    linea=getline(&linea,&tamanio_linea,fi);
    proceso=procesar_calculo_polaco_inverso(linea,&resultado);
    if(!proceso){
      fprintf(stdout, "ERROR\n");
    }
    else{
      fprintf(stdout, "%d\n",resultado);
    }
  }
  free(linea);

    /*Hago split a la linea y la guardo en un vector dinamico*/
    /*creo una pila vacia*/
    /*Para cada elemento del vector:*/
      /*Es un nro?*/
        //agrego a la pila
      /*Es una operacion?*/
        //verifico que es una operacion de la lista de operaciones
        //aplico operacion(pila,puntero a funcion a la operacion[nro op])
          //si la operacion no se pudo aplicar, resultado=error, return
    //Desapilo un elemento de la pila -> lo guardo
      //si la pila esta vacia esta todo ok y resultado=lo que guarde
      //si la pila no esta vacia entonces resultado=error
    //Muestro el resultado de la linea
    /*destruyo la pila*/
}
