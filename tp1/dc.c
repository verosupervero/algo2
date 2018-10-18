#include <stdio.h>
#include "calc.h"

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
}
