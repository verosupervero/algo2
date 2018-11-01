#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "strutil.h"
#include "strutil2.h"
#include "lista.h"
#include "procesar_subcadena.h"

void vaciar_lista(lista_t * lista_lineas){
  while(!lista_esta_vacia(lista_lineas)){
    void * linea= lista_borrar_primero(lista_lineas);
    free(linea);
  }
}


bool encontrar_subpalabra(char * subpalabra, char * linea){

  if(subpalabra==NULL || linea==NULL){
    //fprintf(stderr, "%s\n","subpalabra o linea son NULL" );
    return false;
  }

  size_t n=strlen(subpalabra);
  size_t m=strlen(linea);
  char * sublinea=NULL;

  if(m<n)
    return false;

  for(int i=0; i<m-n;i++){
      sublinea=str_extract(linea,i,i+n-1); // Hay que ver como no ponerla en el .h de strutil.h
      /*
      if(!strcmp(subpalabra,sublinea)){
        free(sublinea);
        return true;
      }
      free(sublinea);
      */
      if(strncmp(subpalabra,sublinea, n) == 0){
        return true;
      }
  }
  return false;
}

bool imprimir_lineas(void *dato, void *extra){
  if(extra==NULL){
    //fprintf(stdout, "%s\n","estoy imprimiendo lineas");
    fprintf(stdout, "%s",(char*)dato);
  }

  return true;
}

bool guardar_linea(lista_t* lista_lineas, char* linea, size_t N){
  if (!lista_lineas) return true;

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
  while( getline(&linea,&memoria_alocada,archivo) !=-1){ /*Leo una línea del archivo*/
    // Busco el patron en la linea leida
    if(encontrar_subpalabra(subcadena,linea)){
      // Encontrado: muestro las lineas guardadas:
      lista_iterar (lista_lineas, imprimir_lineas,NULL);
      imprimir_lineas((void *)linea, NULL); // Imprimo la linea dato_actual
      vaciar_lista(lista_lineas); // Libero las lineas
      free(linea); // Y el buffer de lectura
    } else {
      // La linea no contiene el patron, la guardo
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
