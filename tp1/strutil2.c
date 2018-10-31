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
