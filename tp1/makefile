CC = gcc
CFLAGS = -g  -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
LFLAGS = -Wall
VALGRIND = valgrind
VALGRIND_FLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

# Chirimbolos raros sacados de: Practical Makefiles, by example
# Autor: John Tsiombikas <nuclear@member.fsf.org>
# link: http://nuclear.mutantstargoat.com/articles/make/mktut.pdf

.PHONY: all
all: grep dc

# Por simplicidad, listo las dependencias en esta variables
GREP_OBJS = procesar_subcadena.o strutil.o lista.o strutil2.o

grep: grep.o $(GREP_OBJS)
	$(CC) $(LFLAGS) -o $@ $^

# Por simplicidad, listo las dependencias en esta variables
DC_OBJS = strutil.o strutil2.o pila.o calc.o operaciones.o

dc: dc.o $(DC_OBJS)
	$(CC) $(LFLAGS) -o $@ $^

dc.o: dc.c calc.h
	$(CC) $(CFLAGS) -c $<

grep.o: grep.c procesar_subcadena.h
	$(CC) $(CFLAGS) -c $<

procesar_subcadena.o: procesar_subcadena.c procesar_subcadena.h strutil.h strutil2.h
	$(CC) $(CFLAGS) -c $<

strutil.o: strutil.c strutil.h strutil2.h
	$(CC) $(CFLAGS) -c $<

strutil2.o: strutil2.c strutil2.h
	$(CC) $(CFLAGS) -c $<

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) -c $<


pila.o: pila.c pila.h
	$(CC) $(CFLAGS) -c $<

calc.o: calc.c calc.h pila.h strutil.h operaciones.h
	$(CC) $(CFLAGS) -c $<

operaciones.o: operaciones.c operaciones.h
	$(CC) $(CFLAGS) -c $<

calc.c: pila.h operaciones.h strutil.h strutil2.h


######################## SECCION DE TESTING ################################
# make check-valgrind: compila y corre tests con valgrind
# make check: compila y corre tests
# make tests: compila tests

# Recordar linkear la libreria de testing:
TESTING_LIB = testing.o

# Agregar tests en esta lista:
TESTS = test_strutil test_calc

test_strutil: test_strutil.c strutil.o strutil2.o $(TESTING_LIB)
	$(CC) $(LFLAGS) -o $@ $^

test_calc: test_calc.c $(DC_OBJS) $(TESTING_LIB)
	$(CC) $(LFLAGS) -lm -o $@ $^

########## COMPILACION DE TESTS (NO DEBERIAS TOCAR AQUI ABAJO) ##############
# https://www.brendanlong.com/running-make-check-tests-with-valgrind.html

.PHONY: check
check: tests
	@for test in $$(echo $(TESTS)) ; do \
			 ./$${test} ; \
	done

.PHONY: check-valgrind
check-valgrind: tests
	@for test in $$(echo $(TESTS)) ; do \
			 $(VALGRIND) $(VALGRIND_FLAGS) $${test} ; \
	done

.PHONY: tests
tests: $(TESTS)


# Biblioteca de testing de la catedra
testing: testing.c testing.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o
