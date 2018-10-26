
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutil.h"
#include "testing.h"

  void pruebas_split_unica_palabra(void){
  char * palabra_1="";

  //char * palabra_3="salame";
  //char * palabra_4="estofadodecorderito";

  char ** palabra_salida;
  palabra_salida=split(palabra_1,',');

  bool spliteo_ok=true;
  for(size_t i=0;i<strlen(palabra_1);i++)
    spliteo_ok&=(palabra_salida[0][i]==palabra_1[i]);

  print_test("Split ok palabra1:",spliteo_ok );

  /*char * palabra_2="mortadela";
  spliteo_ok=true;
  for(size_t i=0;i<strlen(palabra_2);i++)
    spliteo_ok&=(palabra_salida[0][i]==palabra_2[i]);
  print_test("Split ok palabra2:",spliteo_ok );*/

}


void pruebas_lista_alumno(void) {
  pruebas_split_unica_palabra();
}
