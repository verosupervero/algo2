#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
  return subcadena;
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
	fprintf(stderr, "::%s::\n", "TENGO LA PALABRA");
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


// Elimina espacios al principio y final de la cadena, y devuelve
// una cadena nueva alocada dinámicamente. Usa isspace()
char * trim (const char * str){
	if (str == NULL) return NULL;

	// Avanzo todos los espacios al inicio
	size_t inicio=0;
	for(inicio=0; isspace(str[inicio]); inicio++);

	// Avanzo todos los espacios al final
	size_t final;
	for(final=strlen(str)-1; isspace(str[final]); final--);

	// Creo una copia
	size_t largo_subcadena = 1+final-inicio;
	char *copia = malloc(sizeof(char)*(largo_subcadena+1));
	if (copia == NULL) return NULL;

	memcpy(copia, &str[inicio], largo_subcadena);
	copia[largo_subcadena]='\0';

	return copia;
}
