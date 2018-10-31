#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "strutil.h"
#include "strutil2.h"

char**	split	(const char * cadena,	char sep){
  size_t i=0;
  size_t n=0;
  size_t cant_separadores = 0;
  char * particion;
  char ** vector;

	if(!cadena)
		return NULL;

  /*Itero para ver cuántos separadores hay, es O(n)*/
  while(cadena[i]!='\0'){
    if(cadena[i]==sep)
        cant_separadores++;
    i++;
  }
  //fprintf(stderr, "Hay %lu separadores\n", cant_separadores);

  /*La cantidad de elementos del vector es la cantidad de separadores
  * mas un espacio para una casilla más un espacio para NULL*/
  n = cant_separadores+2;

  /*Creo el vector vacío para almacenar las cadenas y NULL*/
  vector = malloc(sizeof(char*)*n);
  if (!vector)
    return NULL;

  /*Relleno el vector con las cadenas*/
  i=0;
  size_t n_contador = 0;
  size_t pos_ini=0;
  size_t pos_fin=-1;
  while(cadena[i]!='\0'){
    /*Itero hasta encontrar el primer separador*/
		if(cadena[i]==sep){
			//fprintf(stderr,"separador en char #%lu\n", i);
      /*La posición final de mi cadena es la posición anterior al separador*/
      pos_fin=i-1;

      /*Genero una particion de mi cadena*/
      particion= str_extract(cadena,pos_ini,pos_fin); //es O(largo)
      if(!particion){
        free_strv(vector);
        return NULL;
      }
      /*Guardo la particion en el vector*/
      vector[n_contador++]=particion;

      /*La cadena que sigue empieza al final de la otra*/
      pos_ini= pos_fin+2;
    }
	i++;
  }
  /*El último str no lo encontró porque hay /0*/
  particion= str_extract(cadena,pos_ini,i-1); //O(largo)
  //fprintf(stderr,"-->%s\n",particion);
  if(!particion){
    free_strv(vector);
    return NULL;
  }
  /*Guardo la particion final en el vector*/
  vector[n-2]=particion;

  /*El último elemento es NULL*/
  vector[n-1]=NULL;

  return vector;
}

/*
 * Devuelve una cadena, allocada dinámicamente, resultado de unir todas las
 * cadenas del arreglo terminado en NULL ‘strv’.
 *
 * Quien llama a la función toma responsabilidad de la memoria dinámica de la
 * cadena devuelta. La función devuelve NULL si no se pudo allocar memoria.
 */
char* join(char** strv, char sep){
  if(!strv)
    return NULL;

  size_t i=0;
  while(strv[i]!=NULL){
		//fprintf(stderr, "%s\n",strv[i] );
	  i++;
  }
  size_t cant_palabras= i;
	//fprintf(stderr,"cant_palabras: %lu\n",cant_palabras);

	size_t cant_separadores=0;
	if(i>0)
  	cant_separadores= i-1;
	//fprintf(stderr,"cant separadores: %lu\n",cant_separadores);
	size_t tamanio_cadena=0;

  for(size_t j=0;j<cant_palabras;j++){
	  tamanio_cadena += strlen(strv[j]);
	  //fprintf(stderr,"-->tamanio_cadena iteracion %lu: %lu\n",j, tamanio_cadena);
  }
	tamanio_cadena +=cant_separadores;
	tamanio_cadena++; //va el \0
	//fprintf(stderr,"tamanio_cadena: %lu\n",tamanio_cadena);

  char * cadena=calloc(tamanio_cadena,sizeof(char));
	//memset(cadena, 0, sizeof(char) * tamanio_cadena);

  if(cadena==NULL)
		  return NULL;

	//fprintf(stderr, "%s\n","pude pedir memoria\n");

	size_t inicio_subpalabra=0;
	size_t tam_palabra=0;
	for(size_t k=0;k<cant_palabras;k++){
		tam_palabra=strlen(strv[k]);
		if(!memcpy(cadena+inicio_subpalabra, strv[k],tam_palabra)){
			free(cadena);
			return NULL;
		}
		inicio_subpalabra+=tam_palabra;
		if(k!=cant_palabras-1)
			cadena[inicio_subpalabra]=sep;
		inicio_subpalabra++;
  }
	//fprintf(stderr, "::%s::\n", "TENGO LA PALABRA");
	return cadena;
}

/*
 * Libera un arreglo dinámico de cadenas, y todas las cadenas que contiene.
 */
void free_strv(char* strv[]){
  size_t i=0;
  if(strv == NULL)
    return;

  while(strv[i]!=NULL){
    free(strv[i]);
    i++;
  }
  free (strv);
}
