#include <stdio.h>
#include "operaciones.h"

int sumar(int a,int b){
  return a+b;
}
int restar(int a,int b){
  return a-b;
}
int multiplicar(int a,int b){
  return a*b;
}
int dividir(int a,int b){
  return a/b;
}

int raiz_cuadrada(int n){
  /*Casos base*/
  if (n==0 || n==1)  //O(1)
    return n;

  /*División*/
  cota_inferior=raiz_cuadrada(n>>2)<<1; //T(n/4) (divido por 4, multiplico por 2)
  cota_superior=mitad_inferior+1;

  /*Recombinación*/ //T(n)=T(n/4)+O(1)
  return (cota_superior*cota_superior>n)?cota_inferior:cota_superior;
}

int potencia(int n,int e){
  int restante=0;
  if(e==0)
    return 1;
  int potencia_mitad= potencia(n,e/2);
  if(e%2==1){
    restante=n;
  }
  else{
    restante=1;
  }
  return potencia_mitad*potencia_mitad*restante;
}

int logaritmo(int b, int n){
  if(b==n)
    return 1;
  int potencia= 1;
  while(n/base < 1){
    potencia++;
    n= n/base;
  }
  return potencia;
}
