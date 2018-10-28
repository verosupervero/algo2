#Makefile - Arbol Binario de Busqueda

#Variables:
EXEC=abb
CC=gcc
CFLAGS= -std=c99 -g -Wall -Wconversion -Wtype-limits -pedantic -Werror
OBJECTS= abb.o pruebas_alumno.o pila.o main_abb.o testing.o
VALGRIND= valgrind --leak-check=full --track-origins=yes

all: $(EXEC)

abb.o: abb.c abb.h
	$(CC) $(CFLAGS) -c abb.c

pruebas_alumno.o: pruebas_alumno.c
	$(CC) $(CFLAGS) -c pruebas_alumno.c

pila.o: pila.c pila.h
	$(CC) $(CFLAGS) -c pila.c

main_abb.o: main_abb.c testing.h
	$(CC) $(CFLAGS) -c main_abb.c

testing.o: testing.c testing.h
	$(CC) $(CFLAGS) -c testing.c

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

valgrind: $(EXEC)
	$(VALGRIND) ./$(EXEC)
