#include <stdlib.h>
#include <stdio.h>
#include "procesar_subcadena.h"

int main (int argc, char * argv []){
  if(argc!=3 || argc!=4){
    fprintf(stderr, "%s\n", "Cantidad de parámetros errónea");
    return 1;
  }
  if(atoi(argv[2])<0){
    fprintf(stderr, "%s\n","Tipo de parámetro incorrecto");
    return 1;
  }

  char * subcadena= argv[1];
  int cant_lineas= atoi(argv[2]);
  FILE * archivo;

  if(argc==4){
    char * nombre_archivo= argv[3];
    archivo= fopen(nombre_archivo, "r");
    if(!archivo){
      fprintf(stderr, "%s\n","No se pudo leer el archivo indicado");
      return 1;
    }
  }
  else{ archivo= stdin; }

  bool mostro=mostrar_subcadena_en_archivo(subcadena,(size_t)cant_lineas,archivo);
  if(argc==4)
    fclose(archivo);
  return !mostro;
}
