#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"

typedef (bool)(*function_t)(pila_t * pila);

bool validar_entero(char * literal, int ** pp_entero){

  char * endptr=NULL;
  int entero= (int) strtol(literal, &endptr, 10);
  if(pp_entero!=NULL){
    *pp_entero=malloc(sizeof(int));
    if(*pp_entero==NULL){
      return false;
    **pp_entero=entero;
    }
  }
  return *endptr != '\0';
}

bool validar_operacion(char * literal,function_t operacion){
  char * lista_operaciones[]={"+","-","*","/","sqrt","^","log","?"};
  function_t funciones[]={aplicar_suma,aplicar_resta,aplicar_multiplicacion,
    aplicar_division,aplicar_raiz_cuadrada,aplicar_potencia,aplicar_logaritmo,
    aplicar_operador_ternario};

  for(i=0;lista_operaciones[i]!=NULL;i++){
    if(strcmp(lista_operaciones[i],literal)==0){
      fprintf(stderr, "%s: %s\n","es la funcion",lista_operaciones[i]);
      operacion=funciones[i];
      return true;
    }
  }
  return false;
}

bool procesar_literales(pila_t * pila,char * literal){
  int * p_entero= NULL;
  function_t p_operacion= NULL;

  if(validar_entero(literal,&p_entero)){
    fprintf(stderr, "%s%s%s\n", "El literal",literal, "es un entero");
    bool apile=  pila_apilar(pila,p_entero);
    fprintf(stderr, "%s: %d\n","Apile",apile?1:0);
    return apile;
  }
  if(validar_operacion(literal,p_operacion)){
    fprintf(stderr, "%s%s%s\n", "El literal",literal, "es una operacion");
    bool aplicar_op= p_operacion(pila,literal);
    fprintf(stderr, "%s: %d\n","Realice operacion",aplicar_op?1:0);
    return aplicar_op;
  }
  return false;
}
