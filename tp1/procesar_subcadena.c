#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "strutil.h"
#include "lista.h"
#include "procesar_subcadena.h"

bool encontrar_subpalabra(char * subpalabra, char * linea){

  if(subpalabra==NULL || linea==NULL){
    return false;
  }

  size_t n=strlen(subpalabra);
  size_t m=strlen(linea);
  char * sublinea=NULL;

  for(int i=0; i<m-n;i++){
      sublinea=str_extract(linea,i,i+n-1); // Hay que ver como no ponerla en el .h de strutil.h
      if(!strcmp(subpalabra,sublinea)){
        free(sublinea);
        return true;
      }
      free(sublinea);
  }
  return false;
}

bool imprimir_lineas_archivo(lista_t * lista_lineas){
  if(!lista_lineas)
    return false;

  char * dato_actual;
  for(int i=0;i<lista_largo(lista_lineas);i++){
    dato_actual=(char *) lista_borrar_primero(lista_lineas);
    if(!dato_actual)
      return false;

    fprintf(stdout, "%s\n",dato_actual);
    free(dato_actual);
  }
  return true;
}

bool mostrar_subcadena_en_archivo(char *subcadena, size_t N, FILE * archivo){

  char * linea=NULL;
  size_t tamanio_linea=0;
  lista_t * lista_lineas =lista_crear();
  size_t leyo=0;
  if(lista_lineas==NULL)
    return false;

  /*Cuando el archivo no termino:*/
  bool todo_ok=true;
  int contador=0;

  leyo=getline(&linea,&tamanio_linea,archivo);
  if(leyo==-1)
    todo_ok=false;

  while(leyo!=-1){     /*Leo una línea del archivo*/

    /*No puedo almacenar mas de N+1 lineas en memoria*/
    if(lista_largo(lista_lineas)>=N+1){
      if(!lista_borrar_primero(lista_lineas)){
        todo_ok=false;
        break;
      }
    }
    /*inserto la linea*/
    if(!lista_insertar_ultimo(lista_lineas,linea)){
      todo_ok=false;
      break;
    }

    if(contador<=N)
      contador++;

    if(encontrar_subpalabra(subcadena,linea)){
      todo_ok= imprimir_lineas_archivo(lista_lineas);
      break; //ya encontré lo que quería o no si no tuve memoria
    }
    tamanio_linea=0;
    linea=NULL;
    leyo=getline(&linea,&tamanio_linea,archivo); //aca getline me tira
                                  //distintas pos de memoria tengo entendido
  }
  free(linea);
  lista_destruir(lista_lineas,free_strv);
  return todo_ok;
}
