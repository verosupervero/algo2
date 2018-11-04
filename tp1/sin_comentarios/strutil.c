#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "strutil.h"

char * str_dup(const char * cadena){
	size_t i;
  size_t n;
  char * copia;

  n= strlen(cadena) + 1;
  copia = (char *)malloc((n)*sizeof(char));

  if (!copia)
	 return NULL;

  for(i=0; (copia[i]=cadena[i]) ;i++);
  return copia;
}

/*
 * Devuelve en un arreglo dinámico terminado en NULL con todos los subsegmentos
 * de ‘str’ separados por el carácter ‘sep’. Tanto el arreglo devuelto como las
 * cadenas que contiene son allocadas dinámicamente.
 *
 * Quien llama a la función toma responsabilidad de la memoria dinámica del
 * arreglo devuelto. La función devuelve NULL si falló alguna llamada a
 * malloc(), o si ‘sep’ es '\0'.
 */
char * str_extract(const char * cadena, size_t pos_ini,size_t pos_fin){
  if(!cadena)
    return NULL;
  size_t n=pos_fin-pos_ini+1;
  n++; //tiene que estar el \0

  /*Pido memoria para la subcadena*/
  char * subcadena= malloc(sizeof(char)*(n));
  if(!subcadena)
    return NULL;

  /*Agrego los caracteres a la subcadena*/
  memcpy(subcadena, cadena+pos_ini, n-1);

  subcadena[n-1]='\0'; //agrego el '\0'
  return subcadena;
}

char * trim (const char * str){
	if (!str)
		return NULL;
	size_t len = strlen(str);

	// Avanzo todos los espacios al inicio
	int inicio=0;
	for(int i=0; i<len; i++){
		if(!isspace(str[i])){
			inicio=i;
			break;
		}
	}

	// Avanzo todos los espacios al final
	int final=(int) len;
	int j;
	for(j= (int) len-1; j>=inicio && isspace(str[j]); j--);
	final=j;

	// Creo una copia y la devuelvo
	return str_extract(str, inicio,final);

 }


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
	  i++;
  }
  size_t cant_palabras= i;
	size_t cant_separadores=0;
	if(i>0)
  	cant_separadores= i-1;
	size_t tamanio_cadena=0;

  for(size_t j=0;j<cant_palabras;j++){
	  tamanio_cadena += strlen(strv[j]);
	}
	tamanio_cadena +=cant_separadores;
	tamanio_cadena++; //va el \0
	char * cadena=calloc(tamanio_cadena,sizeof(char));

  if(!cadena)
		  return NULL;

	size_t inicio_subpalabra=0;
	size_t tam_palabra=0;
	bool mem_fail= false;
	for(size_t k=0;k<cant_palabras;k++){
		tam_palabra=strlen(strv[k]);
		if(!memcpy(cadena+inicio_subpalabra, strv[k],tam_palabra)){
			free(cadena);
			mem_fail=true;
			break;
		}
		inicio_subpalabra+=tam_palabra;
		if(k!=cant_palabras-1)
			cadena[inicio_subpalabra]=sep;
		inicio_subpalabra++;
  }
	return !mem_fail?cadena:NULL;
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
