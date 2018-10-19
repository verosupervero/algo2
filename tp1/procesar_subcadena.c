#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "strutil.h"

bool encontrar_subpalabra(char * subpalabra, char * linea){

  if(subpalabra==NULL || linea==NULL){
    return false;
  }

  size_t n=strlen(subpalabra);
  size_t m=strlen(linea);
  char * sublinea=NULL;

  for(int i=0; i<m-n;i++){
      sublinea=str_extract(linea,i,i+n-1) // Hay que ver como no ponerla en el .h de strutil.h
      if(!strcmp(subpalabra,sublinea)){
        free(sublinea);
        return true;
      }
      free(sublinea);
  }
  return false;
}

bool mostrar_subcadena_en_archivo(char *subcadena, size_t N, FILE * archivo){

  char * linea=NULL;
  size_t tamanio_linea=0;
  cola_t * conj_lineas =cola_crear();
  size_t leyo=0;
  if(cola==NULL)
    return false;

  /*Cuando el archivo no termino:*/
  bool hay_error=false;
  int contador=0;

  leyo=getline(&linea,&tamanio_linea,archivo);
  if(leyo==-1){
    free(linea);
    hay_error=true;
    return hay_error;
  }

  while(leyo!=-1){     /*Leo una línea del archivo*/

    /*No puedo almacenar mas de N+1 lineas en memoria*/
    if(contador>N+1){
      contador=0;
      cola_destruir(conj_lineas,free_strv);
      conj_lineas =cola_crear();
       if(cola==NULL){
         hay_error=true;
         return;
       }
    }
    /*encolo la linea*/
    if(!cola_encolar(conj_lineas,linea)){
      hay_error=true;
      return;
    }
    if(encontrar_subpalabra(subpalabra,linea)){
      encontro=true;
      char * dato_actual;

      for(i=0;i<N;i++){
        dato_actual=(char *) cola_desencolar(cola);
        if(dato_actual==NULL){
          hay_error=true;
          return;
        }
        fprintf(stdout, "%s\n",dato_actual);
        free(dato_actual);
      }

      return;
    }
    tamanio_linea=0;
    linea=NULL;
    leyo=getline(&linea,&tamanio_linea,archivo); //aca getline me tira
                                  //distintas pos de memoria tengo entendido
    if(leyo==-1){
      free(linea);
      hay_error=true;
      return;
    }
  }
  cola_destruir(conj_lineas,free_strv);
  return hay_error;
}
