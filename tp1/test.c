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

  char * cadenasS[]={"Hola","soy","Vero",NULL};
  char *v1=join(cadenasS,',');
  fprintf(stderr, "%s\n", v1);
  free(v1);
*/
  // Ejemplo de uso de join
  // char **strv = split("abc,def,ghi", ',');
  // char *resultado = join(strv, ';');  // "abc;def;ghi"
  // fprintf(stderr, "%s\n", resultado);
  // free(resultado);
  // free_strv(strv);
  //
  // char **palabras = split("Hola mundo", ' ');
  // char *otro_resultado = join(palabras, ',');  // "Hola,mundo"
  // fprintf(stderr, "%s\n", otro_resultado);
  // free(otro_resultado);
  // free_strv(palabras);
  //
  // char* m[]={"",NULL};
  // char * otro_resultado2 = join(m, ',');
  // fprintf(stderr, "%s\n", otro_resultado2);
  // free(otro_resultado2);
  //
  // char* m2[]={"abc",NULL};
  // char * otro_resultado3 = join(m2, ',');
  // fprintf(stderr, "%s\n", otro_resultado3);
  // free(otro_resultado3);
  //
  // char* m3[]={"","",NULL};
  // otro_resultado3 = join(m3, ',');
  // fprintf(stderr, "%s\n", otro_resultado3);
  // free(otro_resultado3);
  //
  // char* m4[]={NULL,NULL};
  // otro_resultado3 = join(m4, ',');
  // fprintf(stderr, "imprime NULL:%s:\n", otro_resultado3);
  // free(otro_resultado3);

 // char ** vectores=split("abc,,def", ',');
 // for(size_t i=0; vectores[i]!=NULL; i++){
 //    fprintf(stderr, "%s\n", vectores[i]);
 // }
 // free_strv(vectores);
 //
 // char ** vectores2=split("abc,def,", ',');
 // for(size_t i=0; vectores2[i]!=NULL; i++){
 //    fprintf(stderr, "%s\n", vectores2[i]);
 // }
 // free_strv(vectores2);
 //
 // char ** vectores21=split(",abc,def", ',');
 // for(size_t i=0; vectores21[i]!=NULL; i++){
 //    fprintf(stderr, "%s\n", vectores21[i]);
 // }
 // free_strv(vectores21);
 //
 // char ** vectores213=split("abc", '\0');
 // for(size_t i=0; vectores213[i]!=NULL; i++){
 //    fprintf(stderr, "%s\n", vectores213[i]);
 // }
 // free_strv(vectores213);

 // char ** vectores213=split(",", ',');
 // for(size_t i=0; vectores213[i]!=NULL; i++){
 //    fprintf(stderr, "%s\n", vectores213[i]);
 // }
 // free_strv(vectores213);
  return 0;


}
