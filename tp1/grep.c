#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "procesar_subcadena.h"

/*
Modos de invocación

./programa <string> <nro lineas>  # lee de stdin
./programa <string> <nro lineas> <archivo>  # lee de archivo
*/

void mostrar_ayuda(char * prog_name){
  if (prog_name == NULL){
    prog_name = "./grep";
  }

  printf("%s imprime las lineas de un archivo que contengan la cadena indicada\n\
  \n\
  Modos de invocación:\n\
  \t%s <string> <nro lineas>  # lee de stdin\n\
  \t%s <string> <nro lineas> <archivo>  # lee de archivo\n\
  \n\
  El programa devolvera las las lineas que contengan <string>, precedida por las\n\
  <nro lineas> anteriores y posteriores a cada match.\n\
  \n\
  Si no se especifica <archivo> se lee de stdin.\n", prog_name, prog_name, prog_name);
}

int main (int argc, char * argv []){
  // Mostrar ayuda
  if(argc >1 && !strcmp(argv[1], "--help")){
    mostrar_ayuda(argv[0]);
    exit(0);
  }

  // Validacion cantidad parametros
  if(argc!=3 && argc!=4){
    fprintf(stderr, "%s\n", "Cantidad de parametros erronea");
    exit(1);
  }

  // El segundo parámetro debe ser un numero
  if(atoi(argv[2])<0){
    fprintf(stderr, "%s\n","Tipo de parametro incorrecto");
    exit(1);
  }

  char * subcadena= argv[1];
  int cant_lineas= atoi(argv[2]);
  FILE * archivo;

  if(argc==4){
    char * nombre_archivo= argv[3];
    archivo= fopen(nombre_archivo, "r");
    if(!archivo){
      fprintf(stderr, "%s\n","No se pudo leer el archivo indicado");
      exit(1);
    }
  }
  else{
    archivo= stdin;
  }

  //fprintf(stderr, "Lineas: %d, string: %s\n", cant_lineas, subcadena);

  bool mostro=mostrar_subcadena_en_archivo(subcadena,(size_t)cant_lineas,archivo);

  if(argc==4)
    fclose(archivo);
  exit(!mostro);
}
