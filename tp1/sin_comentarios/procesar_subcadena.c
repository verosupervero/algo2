
#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lista.h"
#include "procesar_subcadena.h"

void vaciar_lista(lista_t * lista_lineas){
  void * linea;
  while( (linea = lista_borrar_primero(lista_lineas)) != NULL ){
    free(linea);
  }
}


bool encontrar_subpalabra(char * subpalabra, char * linea){

  if(!subpalabra || !linea)
    return false;

  size_t n=strlen(subpalabra);
  size_t m=strlen(linea);
  bool exito=false;

  if(m<n) //subpalabra mas larga que linea
    return false;

  for(int i=0; i<m-n;i++){
      if(strncmp(subpalabra,linea+i, n) == 0){
        exito=true;
        break;
      }
  }
  return exito;
}

bool imprimir_lineas(void *dato, void *extra){
  if(!extra)
    fprintf(stdout, "%s",(char*)dato);
  return true;
}

bool guardar_linea(lista_t* lista_lineas, char* linea, size_t N){
  if (!lista_lineas)
    return true;

  // Agrego linea a la lista
  if(!lista_insertar_ultimo(lista_lineas,linea)) return false;

  // Si hay más lineas de las pedida, elimino
  while(lista_largo(lista_lineas)>N){ // uso whie por robustez
    free(lista_borrar_primero(lista_lineas));
  }

  return true;
}


bool mostrar_subcadena_en_archivo(char *subcadena, size_t N, FILE * archivo){

  char * linea=NULL;
  lista_t * lista_lineas = lista_crear();
  bool todo_ok = true;
  size_t memoria_alocada = 0;
  if(lista_lineas==NULL)
    return false;

  /* Leo el archivo línea a línea */
  while( getline(&linea,&memoria_alocada,archivo) !=-1){
    if(encontrar_subpalabra(subcadena,linea)){
      lista_iterar (lista_lineas, imprimir_lineas,NULL);
      imprimir_lineas((void *)linea, NULL);
      vaciar_lista(lista_lineas);
      free(linea);
    } else {
      if(!guardar_linea(lista_lineas, linea, N)){
        todo_ok = false;
        break;
      }
      linea = NULL; // Copie el puntero, borro la referencia
    }
    linea = NULL; // Lo necesito para que getline pida memoria
  }

  // Terminé de leer, al fallar getline necesito liberar la memoria del buffer
  free(linea);

  // Por otro lado, libero la lista con las lineas anteriores
  lista_destruir(lista_lineas,free);
  return todo_ok;
}
