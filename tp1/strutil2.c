#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
  /*for(size_t i=pos_ini;i<=pos_fin;i++)
    subcadena[i]=cadena[i];
*/
  subcadena[n-1]='\0'; //agrego el '\0'
  return subcadena;
}

char * trim (const char * str){
	if (!str)
		return NULL;

	//fprintf(stderr, "parseo: {%s}\n",str);
	size_t len = strlen(str);

	// Avanzo todos los espacios al inicio
	int inicio=0;
	for(int i=0; i<len; i++){
		if(!isspace(str[i])){
			//fprintf(stderr, "|%c| no es espacio\n",str[i]);
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

size_t strv_len(char * vector[]){
  if(vector==NULL || *vector==NULL){ //caso base
    return 0;
  }
  return 1+strv_len(vector+1);
}
