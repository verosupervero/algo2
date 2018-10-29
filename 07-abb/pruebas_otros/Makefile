#Makefile - Arbol Binario de Busqueda

#Variables:
EXEC=abb
CC=gcc
CFLAGS= -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
OBJECTS= abb.o pruebas_abb_alumno.o pila.o main.o testing.o
VALGRIND= valgrind --leak-check=full --track-origins=yes

all: $(EXEC)

abb.o: abb.c abb.h
	$(CC) $(CFLAGS) -c abb.c

pruebas_abb_alumno.o: pruebas_abb_alumno.c
	$(CC) $(CFLAGS) -c pruebas_abb_alumno.c

pila.o: pila.c pila.h
	$(CC) $(CFLAGS) -c pila.c

main.o: main.c testing.h
	$(CC) $(CFLAGS) -c main.c

testing.o: testing.c testing.h
	$(CC) $(CFLAGS) -c testing.c

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

valgrind: $(EXEC)
	$(VALGRIND) ./$(EXEC)

clean:
		rm -f *.o $(EXEC)
