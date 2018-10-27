CC = gcc
CFLAGS = -g  -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
LFLAGS = -Wall

.PHONY: all
all: grep dc

grep: grep.o procesar_subcadena.o strutil.o lista.o
	$(CC) $(LFLAGS) -o $@ $^

dc: dc.o strutil.o pila.o calc.o operaciones.o
	$(CC) $(LFLAGS) -o $@ $^

dc.o: dc.c calc.h
	$(CC) $(CFLAGS) -c $<

grep.o: grep.c procesar_subcadena.h
	$(CC) $(CFLAGS) -c $<

procesar_subcadena.o: procesar_subcadena.c procesar_subcadena.h strutil.h
	$(CC) $(CFLAGS) -c $<

strutil.o: strutil.c strutil.h
	$(CC) $(CFLAGS) -c $<

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) -c $<


pila.o: pila.c pila.h
	$(CC) $(CFLAGS) -c $<

calc.o: calc.c calc.h pila.h strutil.h operaciones.h
	$(CC) $(CFLAGS) -c $<

operaciones.o: operaciones.c operaciones.h
	$(CC) $(CFLAGS) -c $<

calc.c: pila.h operaciones.h strutil.h



.PHONY: tests
tests: test_strutil test_calc

testing: testing.c testing.h
	$(CC) $(CFLAGS) -c $<

test_strutil: test_strutil.o strutil.o testing.o
	$(CC) $(LFLAGS) -o $@ $^

test_strutil.o: test_strutil.c
	$(CC) $(CFLAGS) -c $<

test_calc: test_calc.o calc.o strutil.o testing.o pila.o operaciones.o
	$(CC) $(LFLAGS) -o $@ $^ && ./test_calc

test_calc.o: test_calc.c
	$(CC) $(CFLAGS) -c $<


.PHONY: clean
clean:
	rm *.o
