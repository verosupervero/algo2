#Makefile - Arbol Binario de Busqueda

#Variables:
CC=gcc
CFLAGS= -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
OBJECTS= abb.o pruebas_abb_alumno.o pila.o main.o testing.o
VALGRIND= valgrind --leak-check=full --track-origins=yes

all: pruebas_abb_alumno pruebas_otros pruebas_manu_p

abb.o: abb.c abb.h
	$(CC) $(CFLAGS) -c abb.c

pruebas_abb_alumno.o: pruebas_abb_alumno.c
	$(CC) $(CFLAGS) -c pruebas_abb_alumno.c

pila.o: pila.c pila.h
	$(CC) $(CFLAGS) -c pila.c

pruebas_abb_alumno: pruebas_abb_alumno.c testing.o pila.o abb.o
	$(CC) $(CFLAGS) -o $@ $^

pruebas_otros: pruebas_otros.c testing.o pila.o abb.o
	$(CC) $(CFLAGS) -o $@ $^

pruebas_manu_p: pruebas_manu_p.c testing.o pila.o abb.o
		$(CC) $(CFLAGS) -o $@ $^

testing.o: testing.c testing.h
	$(CC) $(CFLAGS) -c testing.c

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

valgrind: $(EXEC)
	$(VALGRIND) ./pruebas_abb_alumno
	$(VALGRIND) ./pruebas_otros

clean:
		rm -f *.o $(EXEC)
