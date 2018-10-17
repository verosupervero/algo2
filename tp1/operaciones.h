#ifndef OPERACIONES_H
#define OPERACIONES_H

#include <stdbool.h>

bool sumar(int a, int b, int * resultado);
bool restar(int a, int b, int * resultado);
bool dividir(int a, int b,int * resultado);
bool operador_ternario(int a,int b, int c, int *resultado);
bool raiz_cuadrada(int n, int* resultado);
bool potencia(int n, int e, int *resultado);
bool logaritmo(int b, int n,int * resultado);

#endif // OPERACIONES_H
