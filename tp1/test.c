#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutil.h"

int main (void){
  /*char * cadenas[]={"The memcpy() function copies n bytes from memory area src to memory area dest. The memory areas must not overlap. Use memmove(3) if the memory areas do overlap. ","soy nando","bcopy(3), memccpy(3), memmove(3), mempcpy(3), strcpy(3), strncpy(3), wmemcpy(3)"};
  char separadores[]={' ', ' ', ','};

  for(size_t i=0; i<3;i++){
	  char** v= split(cadenas[i],separadores[i]);
	  puts("");
	  puts("resultados");
	  for(size_t i=0; v[i]!=NULL; i++){
		  puts(v[i]);
	  }
	  free_strv(v);
  }
*/
  char * cadenasS[]={"Hola","soy","Vero"};
  char * v1=join(cadenasS,' ');
  fprintf(stderr, "%s\n", v1);
  free(v1);


  return 0;
}
