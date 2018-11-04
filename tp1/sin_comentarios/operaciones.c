#include <stdio.h>
#include "operaciones.h"

bool sumar(int a,int b,int * resultado){
  if(resultado==NULL)
    return false;
  *resultado= a+b;
  return true;
}
bool restar(int a,int b,int * resultado){
  if(resultado==NULL)
    return false;
  *resultado= a-b;
  return true;
}
bool multiplicar(int a,int b,int * resultado){
  if(resultado==NULL)
    return false;
  *resultado= a*b;
  return true;
}
bool dividir(int a,int b, int * resultado){
  if(b==0 || resultado==NULL)
    return false;

  *resultado= a/b;
  return true;
}
bool operador_ternario(int a,int b, int c, int *resultado){
  if(resultado==NULL){
    return false;
  }
  *resultado= (a!=0)?b:c;
  return true;
}

int _raiz_cuadrada(int n){
  /*Casos base*/
  if (n==0 || n==1)  //O(1)
    return n;

  /*División*/
  int cota_inferior=_raiz_cuadrada(n>>2)<<1; //T(n/4) (divido por 4, multiplico por 2)
  int cota_superior=cota_inferior+1;

  /*Recombinación*/ //T(n)=T(n/4)+O(1)
  return (cota_superior*cota_superior>n)?cota_inferior:cota_superior;
}

bool raiz_cuadrada(int n, int* resultado){
  if(resultado==NULL || n<0){
    return false;
  }
  *resultado=_raiz_cuadrada(n);
  return true;
}

int _potencia(int n,int e){
  int restante=0;
  if(e==0)
    return 1;
  int potencia_mitad= _potencia(n,e/2);
  if(e%2==1){
    restante=n;
  }
  else{
    restante=1;
  }
  return potencia_mitad*potencia_mitad*restante;
}

bool potencia(int n, int e, int *resultado){
  if(resultado==NULL || e<0){
    return false;
  }
  *resultado=_potencia(n,e);
  return true;
}



int _logaritmo(int n, int b){
  return (n>b-1)?1+_logaritmo(n/b,b):0;
}

bool logaritmo(int n,int b, int * resultado){
  if(b<=1 || n<0 || resultado==NULL){
    return false;
  }
  *resultado=_logaritmo(n,b);
  return true;
}
