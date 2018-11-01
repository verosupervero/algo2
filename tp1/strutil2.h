#ifndef STRUTIL2_H
#define STRUTIL2_H

#include <stddef.h>

//Obtiene parte de un string pasado por parametro
char * str_extract(const char * cadena, size_t pos_ini,size_t pos_fin);

// Elimina espacios al principio y final de la cadena, y devuelve
// una cadena nueva alocada dinámicamente. Usa isspace()
char * trim (const char * str);

char * str_dup(const char * cadena);

size_t strv_len(char * vector[]);

#endif  // STRUTIL2_H
