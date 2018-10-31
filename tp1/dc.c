#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "calc.h"


int main (int argc, char * argv []){

  /*Leo la entrada estandar*/
  char * linea=NULL;
  size_t tamanio_linea=0;
  int resultado=0;
  size_t leyo=getline(&linea,&tamanio_linea,stdin);
  if(leyo==-1){
    free(linea);
  }
  size_t i=1;
  /*Cuando el archivo no termino:*/
  while(leyo!=-1){     /*Leo una línea del archivo*/
    //fprintf(stderr, "%s %ld\n","Estoy leyendo la linea del archivo n. ",i );
    //fprintf(stderr, "%s\n", linea);
    bool proceso=procesar_calculo_polaco_inverso(linea,&resultado);
    if(!proceso){
      fprintf(stdout, "ERROR\n");
    }
    else{
      fprintf(stdout, "%d\n",resultado);
    }
    free(linea);

    //fprintf(stderr, "\n-----------------------------\n\n");

    tamanio_linea=0;
    linea=NULL;
    leyo=getline(&linea,&tamanio_linea,stdin);
    i++;
  }
  free(linea);

  return 0;
}
