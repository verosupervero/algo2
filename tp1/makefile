CC = gcc
CFLAGS = -c -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
LFLAGS = -Wall

all: grep dc

grep: grep.o procesar_subcadena.o strutil.o cola.o
	$(CC) $(LFLAGS) -o grep grep.o procesar_subcadena.o strutil.o cola.o

dc: dc.o strutil.o pila.o calc.o operaciones.o
	$(CC) $(LFLAGS) -o dc dc.o strutil.o pila.o calc.o operaciones.o

grep.o: grep.c procesar_subcadena.h
	$(CC) $(CFLAGS) -o dc.o dc.c

procesar_subcadena.o: procesar_subcadena.c procesar_subcadena.h
	$(CC) $(CFLAGS) -o procesar_subcadena procesar_subcadena.c

strutil.o: strutil.c strutil.h
	$(CC) $(CFLAGS) -o strutil.o strutil.c

cola.o: cola.c cola.h
	$(CC) $(CFLAGS) -o cola.o cola.c

dc.o: dc.c calc.h
	$(CC) $(CFLAGS) -o dc.o dc.c

pila.o: pila.c pila.h
	$(CC) $(CFLAGS) -o cola.o cola.c

calc.o: calc.c calc.h pila.h strutil.h operaciones.h
	$(CC) $(CFLAGS) -o calc.o calc.c

operaciones.o: operaciones.c operaciones.h
	$(CC) $(CFLAGS) -o operaciones.o operaciones.c
