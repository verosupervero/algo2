#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "calc.h"
#include "pila.h"
#include "strutil.h"
#include "operaciones.h"

#define ANSI_COLOR_LGH_RED	   "\x1b[1m\x1b[31m"
#define ANSI_COLOR_LGH_GREEN   "\x1b[1m\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char * lista_operaciones[]={"+","-","*","/","sqrt","^","log","?",NULL};
function_t funciones[]={aplicar_suma,aplicar_resta,aplicar_multiplicacion,
  aplicar_division,aplicar_raiz_cuadrada,aplicar_potencia,aplicar_logaritmo,
  aplicar_operador_ternario,NULL};

bool aplicar_operador_ternario(pila_t * pila){
  int* n1;
  int* n2;
  int* n3;

  n1=(int *) pila_desapilar(pila);
  if(n1==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*n1 );

  n2=(int *) pila_desapilar(pila);
  if(n2==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*n2 );

  n3=(int *) pila_desapilar(pila);
  if(n3==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*n3 );

  int * resultado=malloc(sizeof(int));
  bool aplico_operador=operador_ternario(*n1, *n2,*n3,resultado);
  if(!aplico_operador){
    fprintf(stderr, "%s\n","no pude ternarizar");
    return false;
  }
  /*Libero la memoria de los datos que no necesito*/
  free(n1);
  free(n2);
  free(n3);

  bool apilo= pila_apilar(pila,resultado);
  if(apilo){
    fprintf(stderr, "%s%d\n","pude apilar el resultado:",*resultado );
    return true;
  }
  else{
    return false;
  }
}


bool aplicar_raiz_cuadrada(pila_t * pila){
  int* n;
  n=(int *) pila_desapilar(pila);

  if(n==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*n);

  int * resultado=malloc(sizeof(int));
  bool aplico_operador=raiz_cuadrada(*n,resultado);
  if(!aplico_operador){
    fprintf(stderr, "%s\n","no pude sqrt");
    return false;
  }
  /*Libero la memoria de los datos que no necesito*/
  free(n);

  bool apilo= pila_apilar(pila,resultado);
  if(apilo){
    fprintf(stderr, "%s%d\n","pude apilar el resultado del sqrt:",*resultado );
    return true;
  }
  else{
    return false;
  }
}


bool aplicar_logaritmo(pila_t * pila){
  int* b;
  int* n;
  b=(int *) pila_desapilar(pila);

  if(b==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*b );
  n=(int *) pila_desapilar(pila);
  if(n==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*n );

  int * resultado=malloc(sizeof(int));
  bool aplico_operador=logaritmo(*b, *n,resultado);
  if(!aplico_operador){
    fprintf(stderr, "%s\n","no pude logg");
    return false;
  }
  /*Libero la memoria de los datos que no necesito*/
  free(b);
  free(n);

  bool apilo= pila_apilar(pila,resultado);
  if(apilo){
    fprintf(stderr, "%s%d\n","pude apilar el resultado del logaritmo:",*resultado );
    return true;
  }
  else{
    return false;
  }
}

bool aplicar_potencia(pila_t * pila){
  int* n;
  int* e;
  n=(int *) pila_desapilar(pila);

  if(n==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*n );
  e=(int *) pila_desapilar(pila);
  if(e==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*e );

  int * resultado=malloc(sizeof(int));
  bool aplico_operador=potencia(*n, *e,resultado);
  if(!aplico_operador){
    fprintf(stderr, "%s\n","no pude potencia");
    return false;
  }
  /*Libero la memoria de los datos que no necesito*/
  free(n);
  free(e);

  bool apilo= pila_apilar(pila,resultado);
  if(apilo){
    fprintf(stderr, "%s%d\n","pude apilar el resultado de la division:",*resultado );
    return true;
  }
  else{
    return false;
  }
}

bool aplicar_division(pila_t * pila){
  int* numerador;
  int* denominador;
  numerador=(int *) pila_desapilar(pila);

  if(numerador==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*numerador );
  denominador=(int *) pila_desapilar(pila);
  if(denominador==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*denominador );

  int * resultado=malloc(sizeof(int));
  bool aplico_operador=dividir(*numerador, *denominador,resultado);
  if(!aplico_operador){
    fprintf(stderr, "%s\n","no pude dividir");
    return false;
  }
  /*Libero la memoria de los datos que no necesito*/
  free(numerador);
  free(denominador);

  bool apilo= pila_apilar(pila,resultado);
  if(apilo){
    fprintf(stderr, "%s%d\n","pude apilar el resultado de la division:",*resultado );
    return true;
  }
  else{
    return false;
  }
}

bool aplicar_multiplicacion(pila_t * pila){
  int* multiplicando_1;
  int* multiplicando_2;
  multiplicando_1=(int *) pila_desapilar(pila);

  if(multiplicando_1==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*multiplicando_1 );
  multiplicando_2=(int *) pila_desapilar(pila);
  if(multiplicando_2==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*multiplicando_2 );

  int * resultado=malloc(sizeof(int));
  bool aplico_operador=multiplicar(*multiplicando_1, *multiplicando_2,resultado);
  if(!aplico_operador){
    fprintf(stderr, "%s\n","no pude multiplicar");
    return false;
  }

  /*Libero la memoria de los datos que no necesito*/
  free(multiplicando_1);
  free(multiplicando_2);

  bool apilo= pila_apilar(pila,resultado);
  if(apilo){
    fprintf(stderr, "%s%d\n","pude apilar el resultado de la multiplicacion:",*resultado );
    return true;
  }
  else{
    return false;
  }
}


bool aplicar_resta(pila_t * pila){
  int* restando_1;
  int* restando_2;
  restando_1=(int *) pila_desapilar(pila);

  if(restando_1==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*restando_1 );
  restando_2=(int *) pila_desapilar(pila);
  if(restando_2==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*restando_2 );

  int * resultado=malloc(sizeof(int));
  bool aplico_operador=restar(*restando_1, *restando_2,resultado);
  if(!aplico_operador){
    fprintf(stderr, "%s\n","no pude restar");
    return false;
  }
  /*Libero la memoria de los datos que no necesito*/
  free(restando_1);
  free(restando_2);

  bool apilo= pila_apilar(pila,resultado);
  if(apilo){
    fprintf(stderr, "%s%d\n","pude apilar el resultado de la resta:",*resultado );
    return true;
  }
  else{
    return false;
  }
}

bool aplicar_suma(pila_t * pila){
  int* sumando_1;
  int* sumando_2;
  sumando_1=(int *) pila_desapilar(pila);
  if(sumando_1==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*sumando_1 );

  sumando_2=(int *) pila_desapilar(pila);

  if(sumando_2==NULL)
    return false;
  fprintf(stderr, "%s%d\n","pude desapilar:",*sumando_2 );


  int * resultado=malloc(sizeof(int));
  bool aplico_operador=sumar(*sumando_1, *sumando_2,resultado);
  if(!aplico_operador){
    fprintf(stderr, "%s\n","no pude sumar");
    return false;
  }
  /*Libero la memoria de los datos que no necesito*/
  free(sumando_1);
  free(sumando_2);

  bool apilo= pila_apilar(pila,resultado);
  if(apilo){
    fprintf(stderr, "%s%d\n","pude apilar el resultado de la suma:",*resultado );
    return true;
  }
  else{
    return false;
  }
}

/*int validate_input ( char* input )
{
    char *p = input;
    if( !input ) return 0;
    for( p=input; *p && (isdigit(*p) || isspace(*p)); ++p )
    {
    }
    if( *p ) return 0;
    return 1;
}*/

bool validar_entero(char * literal, int ** pp_entero){


  /*valido que el literal sea un numero, poshicosas*/
  char *p;
  for( p=literal; *p && (isdigit(*p) || isspace(*p)); ++p );
  if( *p )  return false;

 /*poshicosas*/
  char * endptr=NULL;
  int entero= (int) strtol(literal, &endptr, 10);
  fprintf(stderr, "%s:%d\n","el entero es",entero );
  if(pp_entero!=NULL){
    fprintf(stderr, "%s\n","ppentero es distinto de null" );
    *pp_entero=malloc(sizeof(int));
    if(*pp_entero==NULL){
      return false;
    **pp_entero=entero;
    }
  }
  return *endptr != '\0';
}

bool validar_operacion(char * literal,function_t *operacion){

  if(operacion==NULL)
    return false;

  for(int i=0;lista_operaciones[i]!=NULL;i++){
    size_t son_distintas_operaciones=strcmp(lista_operaciones[i],literal);
    if(!son_distintas_operaciones){
      fprintf(stderr, "%s: %s\n","es la funcion",lista_operaciones[i]);
      *operacion=funciones[i];
      return true;
    }
  }
  return false;
}

bool procesar_literales(pila_t * pila,char * literal_raw){
  int * p_entero= NULL;
  function_t p_operacion= NULL;
  
  // elimino espacios para evitar lios
  char* literal=trim(literal_raw);
  if(literal==NULL) return false;

  if(validar_operacion(literal,&p_operacion)){
    fprintf(stderr, "%s%s%s\n", "El literal",literal, "es una operacion");
    bool aplicar_op= (*p_operacion)(pila);
    fprintf(stderr, "%s: %d\n","Realice operacion",aplicar_op?1:0);
    free(literal);
    return aplicar_op;
  }
  if(validar_entero(literal,&p_entero)){
    fprintf(stderr, "%s%s%s\n", "El literal",literal, "es un entero");
    bool apile=  pila_apilar(pila,p_entero);
    fprintf(stderr, "%s: %d\n","Apile",apile?1:0);
    free(literal);
    return apile;
  }
  else{
    fprintf(stdout, "%s\n","no pude validar entero" );
  }
  // Literal invalido
  free(literal);
  return false;
}

/*Reviso que exista solo un resultado final en la pila y no más elementos*/
bool  revisar_calculo_polaco(pila_t * pila, int * resultado){

  int * resultado_a_priori=NULL;
  resultado_a_priori=pila_desapilar(pila);
  fprintf(stderr, "%s\n", "Calculé el resultado a priori");

  if(resultado_a_priori==NULL){
    fprintf(stderr, "%s\n", "El resultado a priori es NULL");
    return false;
  }
  if(!pila_esta_vacia(pila)){
    fprintf(stderr, "%s\n", "No se vació la pila");
    return false;
  }
  *resultado=*resultado_a_priori;
  free(resultado_a_priori);
  return true;
}

size_t strv_len(char * vector[]){
  if(vector==NULL || *vector==NULL){ //caso base
    return 1;
  }
  return 1+strv_len(vector+1);
}

char * quitar_salto_linea(char ** literal){
  if(!literal)
    return NULL;

  char * literal_2=str_extract(*literal,0,strlen(*literal)-2);
  if(!literal_2)
    return false;

  free(*literal);
  *literal=literal_2;
  return literal_2;
}

bool imprimir_vector_cadenas(char * vectores[]){
if(!vectores){
  fprintf(stdout, "%s\n","no hay vectores" );
  return false;
}
for(size_t i=0; vectores[i]!=NULL; i++){
    fprintf(stdout, "%s,", vectores[i]);
 }
 fprintf(stdout, "\n" );
 return true;
}


// Recibe una linea de literales separados por <separador>, y devuelve un vector de strings con cada literal
// Segun strutil.c/split() si separador es SEPARAR_BLANCO separa por cualquier caracter blanco (espacio, \t, \n, etc).
// #define SEPARAR_BLANCO 0
char** parsear_literales(const char* linea, char separador){
  if (linea == NULL) return NULL;
  
  // Separo los literales
  char** tokens = split(linea, separador);
  
  // Sanitizo (aka elimino cadenas vacias y blancos)
  return sanitizar_vector_literales(tokens);
}

char** sanitizar_vector_literales(char** tokens){
  /*
  Elimino los caracteres blancos al principio y final de cada literal; luego, elimino los literales vacios (incluidos los literales de caracteres blancos)
  */
  
  // Aloco otro vector (tambien terminado en NULL)
  size_t len_tokens = strv_len(tokens);
  
  char** literales = calloc(len_tokens+1, sizeof(char*));
  if (literales == NULL){
    free_strv(tokens);
    return NULL;
  }
  
  // Copio literales
  size_t ultimo_literal = 0;
  for(size_t i=0; tokens[i]!=NULL; i++){
    // Elimino caracteres blancos
    char* aux_literal = trim(tokens[i]);
    
    // Omito la copia si el literal queda vacio
    if (strlen(aux_literal)==0){
      free(aux_literal);
      continue;
    }
    
    // Agrego el literal al nuevo vector (y postincremento su indice)
    literales[ultimo_literal++] = aux_literal;
  }//end for
  
  // Termino el vector en NULL (redundante con calloc si NULL==0)
  literales[ultimo_literal] = NULL;
  
  /* Aca puede ir un realloc opcional para liberar memoria */
  
  return literales;
}

bool procesar_calculo_polaco_inverso (char * linea, int * resultado){

  fprintf(stderr, "\n............PROCESO LITERALES..........\n\n");
  if(linea==NULL || resultado==NULL){
    fprintf(stderr, "%s\n", "No hay linea o resultado");
    return false;
  }

  /*Genero un vector de literales para procesarlos por separado*/
  // Considerar usar como separador CARACTER_BLANCO
  char ** vector_literales= parsear_literales(linea, ' ');
  if(!vector_literales){
    fprintf(stderr, "%s\n", "No pude procesar los literales");
    return NULL;
  }
  
  puts("Resultado parseo:");
imprimir_vector_cadenas(vector_literales);
  puts("");
  
  bool exito =  procesar_vector_polaco_inverso( vector_literales, resultado);
  
  // Libero memoria
  free_strv(vector_literales);

  return exito;
}


// Recibe un vector de literales sano (use parsear_linea o sanitizar_vector_literales) y realiza el calculo
bool procesar_vector_polaco_inverso(char** vector_literales, int* resultado){
  if (vector_literales==NULL || resultado==NULL) return false;
  
  // Largo del vector (para que?)
  //size_t len_strv=strv_len(vector_literales);

  /*Creo una pila para ir almacenando los resultados parciales
  de la calculadora*/
  puts("creo la pila" );
  pila_t * pila=pila_crear();

  /*Proceso el calculo polaco en el vector de literales*/
  bool proceso_calculo_polaco=false;
  bool proceso_literales=false;
  for(int i=0; vector_literales[i]!=NULL; i++){
  // Considero que tengo un vector sano aca
   
   // Proceso el literal
   proceso_literales = procesar_literales(pila,vector_literales[i]);
    if(!proceso_literales){
      fprintf(stderr, "%s %d: %sERROR%s\n", "Literal",i,ANSI_COLOR_LGH_RED,ANSI_COLOR_RESET);
      proceso_calculo_polaco=false;
      break;
    }
    else{
      proceso_calculo_polaco=true;
      fprintf(stderr, "%s %d: %sOK%s\n", "Literal",i,ANSI_COLOR_LGH_GREEN,ANSI_COLOR_RESET);
    }
  }

  fprintf(stderr, "%s\n", "Procese literales de alguna forma");

  /*Reviso que exista solo un resultado final en la pila y no más elementos*/
  proceso_calculo_polaco= revisar_calculo_polaco(pila,resultado);
  fprintf(stderr, "Proceso calculo polaco %s\n", proceso_calculo_polaco?"OK":"ERROR");

  /*Libero la memoria dinámica pedida*/
  pila_destruir(pila);

  /*Devuelvo el resultado y si se realizó el cálculo*/
  fprintf(stderr, "\n-------------RESULTADO FINAL:-----------\n\n");
  return proceso_calculo_polaco;
}
