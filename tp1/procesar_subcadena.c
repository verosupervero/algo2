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
      if(!strcmp(subpalabra,sublinea)){
        free(sublinea);
        return true;
      }
      free(sublinea);
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

bool mostrar_subcadena_en_archivo(char *subcadena, size_t N, FILE * archivo){

  char * linea=NULL;
  size_t tamanio_linea=0;
  lista_t * lista_lineas =lista_crear();
  size_t leyo=0;
  if(lista_lineas==NULL)
    return false;

  /* Leo el archivo línea a línea */
  bool todo_ok=true;
  leyo=getline(&linea,&tamanio_linea,archivo);
  if(leyo==-1)
    todo_ok=false;

  while(leyo!=-1){     /*Leo una línea del archivo*/

    /* Almaceno las últimas N+1 líneas leídas*/
    if(lista_largo(lista_lineas)>N){
      char * elemento_a_borrar = lista_borrar_primero(lista_lineas);
      if(elemento_a_borrar ==  NULL){
        // Error eliminando nodo
        todo_ok=false;
        break;
      }else{
        // Libero memeoria pedida por getline
        free(elemento_a_borrar);
        elemento_a_borrar = NULL; // Por seguridad
      }
    }

    //fprintf(stderr, "La cantidad de lineas en el vector es: %ld\n", lista_largo(lista_lineas));
    /*inserto la linea*/
    if(!lista_insertar_ultimo(lista_lineas,linea)){
      //fprintf(stderr, "%s\n","no pude insertar la linea" );
      todo_ok=false;
      break;
    }
    //fprintf(stderr, "Inserte esta linea: :::%s:::",linea);

    if(encontrar_subpalabra(subcadena,linea)){
      //fprintf(stderr, "La ultima linea del archivo es: :::%s:::\n",(char *)lista_ver_ultimo(lista_lineas) );
      lista_iterar (lista_lineas, imprimir_lineas,NULL);
      todo_ok&=true;
      vaciar_lista(lista_lineas);
    }
    //fprintf(stdout, "%s\n","termine de recorrer una linea y no esta" );
    tamanio_linea=0;
    linea=NULL;
    leyo=getline(&linea,&tamanio_linea,archivo); //aca getline me tira
                                  //distintas pos de memoria tengo entendido
  }
  //fprintf(stderr, "%s\n","sali del while" );
  free(linea);
  //fprintf(stderr, "%s\n","le hice free a linea");
  lista_destruir(lista_lineas,free);
  return todo_ok;
}
