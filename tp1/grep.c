#include <stdlib.h>
#include <stdio.h>

bool encontrar_subpalabra(char * subpalabra, char * linea){

  if(subpalabra==NULL || linea==NULL){
    return false;
  }

  size_t n=strlen(subpalabra);
  size_t m=strlen(linea);
  char * sublinea=NULL;

  for(int i=0; i<m-n;i++){
      sublinea=str_extract(linea,i,i+n-1)
      if(!strcmp(subpalabra,sublinea)){
        free(sublinea);
        return true;
      }
      free(sublinea);
  }
  return false;
}


bool mostrar_subcadena_en_archivo(char *subcadena, size_t N, FILE * archivo){

  char * linea=NULL;
  size_t tamanio_linea=0;
  cola_t * conj_lineas =cola_crear();
  size_t leyo=0;
  if(cola==NULL)
    return false;

  /*Cuando el archivo no termino:*/
  bool hay_error=false;
  int contador=0;

  leyo=getline(&linea,&tamanio_linea,archivo);
  if(leyo==-1){
    free(linea);
    hay_error=true;
    return hay_error;
  }

  while(leyo!=-1){     /*Leo una línea del archivo*/

    /*No puedo almacenar mas de N+1 lineas en memoria*/
    if(contador>N+1){
      contador=0;
      cola_destruir(conj_lineas,free_strv);
      conj_lineas =cola_crear();
       if(cola==NULL){
         hay_error=true;
         return;
       }
    }
    /*encolo la linea*/
    if(!cola_encolar(conj_lineas,linea)){
      hay_error=true;
      return;
    }
    if(encontrar_subpalabra(subpalabra,linea)){
      encontro=true;
      char * dato_actual;

      for(i=0;i<N;i++){
        dato_actual=(char *) cola_desencolar(cola);
        if(dato_actual==NULL){
          hay_error=true;
          return;
        }
        fprintf(stdout, "%s\n",dato_actual);
        free(dato_actual);
      }

      return;
    }
    tamanio_linea=0;
    linea=NULL;
    leyo=getline(&linea,&tamanio_linea,archivo); //aca getline me tira
                                  //distintas pos de memoria tengo entendido
    if(leyo==-1){
      free(linea);
      hay_error=true;
      return;
    }
  }
  cola_destruir(conj_lineas,free_strv);
  return hay_error;
}


int main (int argc, char * argv []){
  if(argc!=3 || argc!=4){
    fprintf(stderr, "%s\n", "Cantidad de parámetros errónea");
    return 1;
  }
  if(atoi(argv[2])<0){
    fprintf(stderr, "%s\n","Tipo de parámetro incorrecto");
    return 1;
  }

  char * subcadena= argv[1];
  int cant_lineas= atoi(argv[2]);
  FILE * archivo;

  if(argc==4){
    char * nombre_archivo= argv[3];
    FILE * archivo= fopen(nombre_archivo, "r");

    if(!archivo){
      fprintf(stderr, "%s\n","No se pudo leer el archivo indicado");
      return 1;
    }
  }
  else{
    archivo= stdin;
  }


  bool mostro=mostrar_subcadena_en_archivo(subcadena,(size_t)cant_lineas,archivo);
  if(!mostro){
    return 1;
  }
  if(argc==4){
    fclose(archivo);
  }
  return 0;
}
