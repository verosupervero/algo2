CC = gcc
CFLAGS = -g  -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
LFLAGS = -Wall

all: grep dc

grep: grep.o procesar_subcadena.o strutil.o lista.o
	$(CC) $(LFLAGS) -o grep grep.o procesar_subcadena.o strutil.o lista.o

dc: dc.o strutil.o pila.o calc.o operaciones.o
	$(CC) $(LFLAGS) -o dc dc.o strutil.o pila.o calc.o operaciones.o

dc.o: dc.c calc.h
	$(CC) $(CFLAGS) -c dc.c

grep.o: grep.c procesar_subcadena.h
	$(CC) $(CFLAGS) -c grep.c

procesar_subcadena.o: procesar_subcadena.c procesar_subcadena.h strutil.h
	$(CC) $(CFLAGS) -c procesar_subcadena.c

strutil.o: strutil.c strutil.h
	$(CC) $(CFLAGS) -c strutil.c

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) -c lista.c


pila.o: pila.c pila.h
	$(CC) $(CFLAGS) -c pila.c

calc.o: calc.c calc.h pila.h strutil.h operaciones.h
	$(CC) $(CFLAGS) -c calc.c

operaciones.o: operaciones.c operaciones.h
	$(CC) $(CFLAGS) -c operaciones.c

calc.h: pila.h operaciones.h strutil.h
