#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutil.h"

#define FACTOR_REDIMENSION            2
#define TAMANIO_INICIAL              1000

char * str_dup(const char * cadena)
{
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
  fprintf(stderr, "str_extract %lu %lu\n", pos_ini, pos_fin);
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
  /*for(size_t i=pos_ini;i<=pos_fin;i++)
    subcadena[i]=cadena[i];
*/
  subcadena[n-1]='\0'; //agrego el '\0'
  
  fprintf(stderr, ":::%s:::\n", subcadena);
  return subcadena;
}

char**	split	(const char * cadena,	char sep){
  size_t i=0;
  size_t n=0;
  size_t cant_separadores = 0;
  char * particion;
  char ** vector;

  if(!cadena || sep=='\0')
    return NULL;

  /*Itero para ver cuántos separadores hay, es O(n)*/
  while(cadena[i]!='\0'){
    if(cadena[i]==sep)
        cant_separadores++;
    i++;
  }
  fprintf(stderr, "Hay %lu separadores\n", cant_separadores);

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
	  fprintf(stderr,"separador en char #%lu\n", i);
      /*La posición final de mi cadena es la posición anterior al separador*/
      pos_fin=i-1;

      /*Genero una particion de mi cadena*/
      particion= str_extract(cadena,pos_ini,pos_fin); //es O(largo)
      if(!particion){
		  fprintf(stderr, "gone\n");
        free_strv(vector);
        return NULL;
      }
      /*Guardo la particion en el vector*/
	  fprintf(stderr,"-->%s\n",particion);
      vector[n_contador++]=particion;

      /*La cadena que sigue empieza al final de la otra*/
      pos_ini= pos_fin+2;
    }
	i++;
  }
  /*El último str no lo encontró porque hay /0*/
  particion= str_extract(cadena,pos_ini,i-1); //O(largo)
  fprintf(stderr,"-->%s\n",particion);
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
  size_t separadores= i-1;
  
  // No es necesario pedir memoria (creo)
  int * cant_letras_palabras=calloc(sizeof(int)*cant_palabras);
  if(!cant_letras_palabras)
	  return NULL;
  
  for(size_t j=0;j<=cant_palabras;j++){
	  size_t k=0;
	  cant_letras_palabras[j] = strlen(strv[j]);
	  fprintf(stderr,"-->letras palabra %lu: %lu\n",j, cant_letras_palabras[j]);

  }
  size_t tamanio_cadena=0;
  for(size_t m=0;m<=cant_palabras;m++)
	tamanio_cadena+=cant_letras_palabras[m];
  
  char ** cadena=malloc(sizeof(char *)*tamanio_cadena);
  if(!cadena){
	  free (cant_letras_palabras);
	  return NULL;
  }
	  


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
