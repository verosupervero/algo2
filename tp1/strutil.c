#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	for(i=0; copia[i]=cadena[i] ;i++);
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

char * str_extract(char * cadena, size_t pos_ini,size_t pos_fin){
  if(!cadena)
    return NULL;
  size_t n=pos_fin-pos_ini+1;
  n++; //tiene que estar el \0

  /*Pido memoria para la subcadena*/
  char * subcadena= malloc(sizeof(char)*(subcadena_tam));
  if(!subcadena)
    return NULL;

  /*Agrego los caracteres a la subcadena*/
  for(int i=pos_ini;i<=pos_fin;i++)
    subcadena[i]=cadena[i];

  subcadena[n-1]='\0'; //agrego el '\0'
  return subcadena;
}

char**	split	(char * cadena,	char sep){
  int i=0;
  size_t n=0;
  size_t n_contador=0;
  char * particion;
  char ** vector;
  size_t pos_ini=0;
  size_t pos_fin;

  if(!str || sep=='\0')
    return NULL;

  /*Itero para ver cuántos separadores hay, es O(n)*/
  while(cadena[i]!='/0'){
    if(cadena[i]==sep)
        n++;
    i++;
  }
  /*La cantidad de elementos del vector es la cantidad de separadores
  * mas un espacio para una casilla más un espacio para NULL*/
  n=n+2;

  /*Creo el vector vacío para almacenar las cadenas y NULL*/
  char ** vector = malloc(sizeof(char*)*(n+1));
  if (!vector)
    return NULL;

  /*Relleno el vector con las cadenas*/
  i=0;
  while(cadena[i]!='/0'){ //O(n^2) en el peor de los casos
    /*Itero hasta encontrar el primer separador*/
    if(cadena[i]==sep){
      /*La posición final de mi cadena es la posición anterior al separador*/
      pos_fin=i-1;

      /*Genero una particion de mi cadena*/
      particion= str_extract(str,pos_ini,pos_fin); //es O(largo)
      if(!particion){
        free_strv(vector);
        return NULL;
      }
      /*Guardo la particion en el vector*/
      vector[n_contador]=particion;

      /*Aumento el contador de cadenas*/
      n_contador++;

      /*La cadena que sigue empieza al final de la otra*/
      pos_ini= pos_fin+1;
    }
  }
  /*El último str no lo encontró porque hay /0*/
  particion= str_extract(str,pos_ini,pos_fin); //O(largo)
  if(!particion){
    free_strv(vector);
    return NULL;
  }
  /*Guardo la particion final en el vector*/
  vector[n-1]=particion;

  /*El último elemento es NULL*/
  vector[n]=NULL;

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
  int i=0;
  char* str;
  char* srt_copia;

  while(strv[i]!=NULL){

    /*copio el string para no pisarlo con strcat*/
    str_copia=strdup(strv[i]);
    if(!str_copia)
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
