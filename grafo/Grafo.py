#!/usr/bin/env python
"""Clase para representar y procesar grafos"""
import numpy as np
from scipy import sparse
import warnings

import unittest
from unittest import TestCase
from collections import deque

import heapq

class nodo_max_heap(object):
    def __init__(self,dato):
        self.dato = dato
    def obtener_valor():
        return dato
    def __lt__(self, other):
        return self.dato>other.dato
    def __gt__(self, other):
        return self.dato<other.dato
    def __eq__(self, other):
        return self.dato==other.dato
    def __str__(self):
        return str(self.dato)
    def __repr__(self):
        return str(self.dato)

class nodo_min_heap(object):
    def __init__(self,dato):
        self.dato = dato
    def obtener_valor():
        return dato
    def __lt__(self, other):
        return self.dato<other.dato
    def __gt__(self, other):
        return self.dato>other.dato
    def __eq__(self, other):
        return self.dato==other.dato
    def __str__(self):
        return str(self.dato)
    def __repr__(self):
        return str(self.dato)


class Grafo(object):
    """Voy a implementar un grafo como una matriz (sparse) de adyacencias y un diccionario de vertices"""
    def __init__(self):
        """Crea un grafo vacio"""
        self.grafo={}
    def __iter__(self):
        """Iterador sobre los vertices del grafo"""
        # Ver https://docs.python.org/3/tutorial/classes.html#generators
        return iter(self.obtener_vertices())

    def __len__(self):
        """Cantidad de vertices del grafo"""
        return len(self.grafo.keys())
    def ver_diccionario(self):
        print(self.grafo)

    def agregar_vertice(self, nombre_vertice=None):
        """Agrego un vertice al grafo, no lo enlazo"""
        if nombre_vertice in self.obtener_vertices():
            return
        self.grafo[nombre_vertice]={}

    def agregar_arista(self, padre=None, hijo=None, peso=1, no_dirigido=False):
        """Agrega una arista desde el vertice padre hacia el vertice hijo, con un peso dado.
        Si el vértice ya existía, lo reemplaza.
        Si no se especifica el hijo, se crean dos vértices, uno en cada sentido, de peso dado.
        Si el peso no se especifica, se asigna el valor 1."""
        if peso==0:
            print("peso cero")
            self.eliminar_arista(padre,hijo,no_dirigido)
            return

        self.grafo[padre][hijo]=peso
        if no_dirigido:
            self.grafo[hijo][padre]=peso


    def obtener_vertices(self):
        """Devuelve una lista de los vertices, ordenados según su aparición en la matriz de adyacencias"""
        return self.grafo.keys()

    def obtener_arista(self, padre=None, hijo=None):
        if padre in self.grafo:
            if hijo in self.grafo[padre]:
                return self.grafo[padre][hijo]
        return 0

    def son_adyacentes(self, padre=None, hijo=None, no_dirigido=False):
        """Devuelve si el vertice padre posee una arista hacia el vertice hijo.
        Si se usa no_dirigido=True, se verifica la existencia de la arista entre vertices, no así su sentido"""
        if no_dirigido:
            return hijo in self.grafo[padre] and padre in self.grafo[hijo]
        return hijo in self.grafo[padre]

    def eliminar_arista(self, padre=None, hijo=None, no_dirigido=False):
        """Elimina la arista desde el vertice padre al vertice hijo.
        Si se usa no_dirigido=True, se eliminan ambas aristas"""
        del self.grafo[padre][hijo]
        print("borre la arista")
        if no_dirigido:
            del self.grafo[hijo][padre]

    def eliminar_vertice(self, vertice=None,no_dirigido=False):
        """Elimina el vertice del grafo."""
        #Elimino los adyacentes que puedan tenerlo a el si es no_dirigido
        if no_dirigido:
            for w in self.obtener_adyacentes(vertice):
                del self.grafo[w][vertice]

        del self.grafo[vertice]

    def obtener_adyacentes(self, padre=None):
        """Devuelvo una lista con todos los nodos adyacentes del vertice padre"""
        return self.grafo[padre].keys()

    def vertice_en_grafo(self,vertice):
        """Revisa si el vertice esta en el grafo"""
        return vertice in self.grafo.keys()


class TestGrafo(TestCase):
    def setUp(self):
        """Creación del grafo a utilizar en cada prueba de esta clase"""
        self.grafito = Grafo()
        self.obtener_vertices = ["A","B","C","I","F"]
        self.lista_aristas = [("A","B"), ("B","C"), ("C","A"), ("I","A"), ("C","F")]

        for k in self.obtener_vertices:
            self.grafito.agregar_vertice(k)

        for a,b in self.lista_aristas:
            self.grafito.agregar_arista(a,b)

    def test_aarmado(self):
        """Check de vertices y aristas en grafo dirigido"""
        vertices = self.grafito.obtener_vertices()
        for vertice in vertices:
            self.assertTrue(vertice in self.obtener_vertices, "vertice "+vertice+" no encontrado")

        # Comparo cardinalidad
        self.assertEqual(len(vertices), len(self.obtener_vertices), "Cantidad de vertices invalida")

        # Chequeo parentezco
        for a in self.obtener_vertices:
            for b in self.obtener_vertices:
                self.assertEqual(self.grafito.son_adyacentes(a,b), (a,b) in self.lista_aristas, "Error en parentezco ("+a+","+b+").")

    def test_valor_arista_inexistente(self):
        """Setear arista con peso cero provoca no adyacencia"""
        self.assertEqual(self.grafito.obtener_arista("I","F"), 0, "La arista no existente I-F no devuelve 0")

    def test_arista_no_definida(self):
        """Dos nodos no vinculados tienen peso 0"""
        self.grafito.agregar_arista("A","B",0)
        self.assertFalse(self.grafito.son_adyacentes("A","B"))

    def test_arista_peso_arbitrario(self):
        """Setear peso 0.1 a una arista provoca adyacencia"""
        self.grafito.agregar_arista("A","F",0.1)
        self.assertTrue(self.grafito.son_adyacentes("A","F"))

    def test_eliminar_arista(self):
        """Eliminar una arista provoca no adyacencia y no modifica vertices"""
        self.grafito.eliminar_arista("A","B")
        self.assertFalse(self.grafito.son_adyacentes("A","B"))
        vertices = self.grafito.obtener_vertices()
        self.assertTrue("A" in vertices, "A eliminado inesperadamente")
        self.assertTrue("B" in vertices, "B eliminado inesperadamente")

    def test_eliminar_vertice(self):
        """Elimiación de un vertice"""
        self.grafito.eliminar_vertice("A")
        vertices = self.grafito.obtener_vertices()
        self.assertFalse("A" in vertices, "A no fue eliminado")

    def eliminar_todos_los_vertices(self):
        """Eliminar todos los vertices del grafo lo vacia"""
        vertices = self.grafito.obtener_vertices()
        for vertice in vertices:
            self.grafito.eliminar_vertice(vertice)

        self.assertEqual(len(self.grafito.obtener_vertices()), 0)

class TestGrafoNoDirigido(TestCase):
    def setUp(self):
        """Creación del grafo a utilizar en cada prueba de esta clase"""
        self.grafito = Grafo()
        self.obtener_vertices = ["A","B","C","I","F"]
        self.lista_aristas = [("A","B"), ("B","C"), ("C","A"), ("I","A"), ("C","F")]

        for k in self.obtener_vertices:
            self.grafito.agregar_vertice(k)

        for a,b in self.lista_aristas:
            self.grafito.agregar_arista(a,b, no_dirigido=True)

    def test_aarmado(self):
        """Check aristas y vertices en grafo no dirigido"""
        vertices = self.grafito.obtener_vertices()
        for vertice in vertices:
            self.assertTrue(vertice in self.obtener_vertices, "vertice "+vertice+" no encontrado")

        # Comparo cardinalidad
        self.assertEqual(len(vertices), len(self.obtener_vertices), "Cantidad de vertices invalida")

        # Chequeo parentezco
        for a in self.obtener_vertices:
            for b in self.obtener_vertices:
                unidos = ((a,b) in self.lista_aristas) or ((b,a) in self.lista_aristas)
                self.assertEqual(self.grafito.son_adyacentes(a,b), unidos, "Error en parentezco ("+a+","+b+").")


if __name__ == '__main__':
    unittest.main(verbosity=2)
