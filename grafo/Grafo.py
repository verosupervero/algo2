#!/usr/bin/env python
"""Clase para representar y procesar grafos"""
import numpy as np
from scipy import sparse
import warnings

import unittest
from unittest import TestCase

from collections import deque

import heapq

class vertice_heap(object):
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

class Grafo(object):
    """Voy a implementar un grafo como una matriz (sparse) de adyacencias y un diccionario de vertices"""
    def __init__(self):
        """Crea un grafo vacio"""
        self._mat_ady = sparse.dok_matrix((0,0))

        # Creo un diccionario con los nombres de los vertices, asociados a su indice
        # la ventaja de esto, es que no necesito eliminar filas y columnas de la matriz
        # solo poner sus valores en 0 y sacarlo de la lista, pero sin "desplazar" los indices
        # del resto.
        # Contra: al eliminar vertices van a quedar filas y columnas nulas, pero las puedo
        # eliminar si quiero
        self._indices = {}

    def agregar_vertice(self, nombre_vertice=None):
        """Agrego un vertice al grafo, no lo enlazo"""
        if nombre_vertice in self._indices:
            raise NameError('vertice ya existe') # esto va o solo return?

        # Agrego el vertice al diccionario, con su nuevo indice
        nuevo_indice = max(self._mat_ady.get_shape()) # +1 implicito
        self._indices[nombre_vertice] = nuevo_indice

        # Agrego una nueva fila y columna a la matriz
        nuevo_tamanio = nuevo_indice+1
        self._mat_ady.resize((nuevo_tamanio, nuevo_tamanio))

    def __repr__(self):
        """Devuelve una representación del grafo"""
        return "<vertices: " + str(self.lista_vertices()) + "\n Adyacencias:\n" + str(self.mat_adyacencias()) +" >"

    def __iter__(self):
        """Iterador sobre los vertices del grafo"""
        # Ver https://docs.python.org/3/tutorial/classes.html#generators
        return iter(self.lista_vertices())

    def __len__(self):
        """Cantidad de vertices del grafo"""
        return len(self._indices)

    def lista_vertices(self):
        """Devuelve una lista de los vertices, ordenados según su aparición en la matriz de adyacencias"""
        return sorted(self._indices, key=self._indices.__getitem__)

    def _compactar(self):
        """Elimina las columnas extra en la matriz de adyacencias, correspondientes a vertices eliminados"""
        # Lista de columnas válidas (no eliminadas)
        indices = list(self._indices.values())

        # Lista de vertices e indices validos, ordenados
        indices = list(sorted(self._indices.values()))
        vertices = sorted(self._indices, key=self._indices.__getitem__)

        # Filtro solo las columnas usadas
        M_filtrada = self._mat_ady[:,indices][indices,:]

        # Asigno mis nuevos indices incrementalmente
        self._indices = {v:i for i,v in enumerate(vertices)}
        print(self._indices)

        # Asigno nueva matriz
        self._mat_ady = M_filtrada

    def mat_adyacencias(self):
        """Devuelve la matriz de adyacencias de forma densa, la lista de vertices se obtiene con lista_vertices()"""
        # Compacto la matriz para eliminar filas y columnas que no representan vertices
        self._compactar()

        # Devuelvo la matriz densa
        return self._mat_ady.todense()

    def agregar_arista(self, padre=None, hijo=None, peso=1, no_dirigido=False):
        """Agrega una arista desde el vertice padre hacia el vertice hijo, con un peso dado.
        Si el vértice ya existía, lo reemplaza.
        Si no se especifica el hijo, se crean dos vértices, uno en cada sentido, de peso dado.
        Si el peso no se especifica, se asigna el valor 1.

        El peso no puede ser negativo.
        Si el peso es 0, el vertice es eliminado."""

        if peso < 0:
            raise ValueError('El peso debe ser no negativo')

        # Busco los índices de los vertices
        idx_padre = self._indices[padre]
        idx_hijo = self._indices[hijo]

        # Agrego peso
        self._mat_ady[idx_padre, idx_hijo] = peso

        if no_dirigido:
            # Simétrico
            self._mat_ady[idx_hijo, idx_padre] = peso

    def peso_vertice(self, padre=None, hijo=None):
        # Busco los índices de los vertices
        idx_padre = self._indices[padre]
        idx_hijo = self._indices[hijo]

        return self._mat_ady[idx_padre, idx_hijo]

    def son_adyacentes(self, padre=None, hijo=None, no_dirigido=False):
        """Devuelve si el vertice padre posee una arista hacia el vertice hijo.
        Si se usa no_dirigido=True, se verifica la existencia de la arista entre vertices, no así su sentido"""

        adyacencia_directa = self.peso_vertice(padre, hijo)!=0

        if no_dirigido:
            adyacencia_inversa =  self.peso_vertice(hijo, padre)!=0
            return adyacencia_directa or adyacencia_inversa

        # Adyacencia dirigida
        return adyacencia_directa

    def eliminar_arista(self, padre=None, hijo=None, no_dirigido=False):
        """Elimina la arista desde el vertice padre al vertice hijo.
        Si se usa no_dirigido=True, se eliminan ambas aristas"""

        self.agregar_arista(padre=padre, hijo=hijo, peso=0, no_dirigido=no_dirigido)

    def eliminar_vertice(self, vertice=None):
        """Elimina el vertice del grafo."""
        # elimino valor del diccionario
        idx_vertice = self._indices.pop(vertice)

        # elimino la fila y columna idx_vertice-ésima (respectivamente)
        self._mat_ady[idx_vertice,:] = 0
        self._mat_ady[:,idx_vertice] = 0

        # No voy a modificar las dimensiones de la matriz de adyacencia porque debería actualizar
        # todos los índices, y al ser sparse no molesta tener más ceros. De todas formas se puede
        # compactar la representación interna usando el método _compactar()

    def listar_hijos(self, padre=None):
        """Devuelvo una lista con todos los hijos del vertice padre"""
        # Busco los índices de los vertices
        idx_padre = self._indices[padre]

        # Obtengo los hijos del vertice, serían aquellas posiciones que no tienen 0 en la columna dada
        idx_hijos = np.where(self._mat_ady[idx_padre,:].todense()!=0)[1]

        # Convierto a una lista de nombres de vertices
        return [nombre for nombre,idx in self._indices.items() if idx in idx_hijos]


    def bfs(self,origen=None):
        visitados=[]
        cola=deque([])
        cola.append(origen)
        while cola:
            # Desencolo un nodo y lo agrego a visitados
            origen=cola.popleft()
            visitados.append(origen)
            #print("levanto: "+origen)

            # Encolo todos sus hijos que no hayan sido visitados previamente
            adyacentes=self.listar_hijos(origen)
            for nodo in adyacentes:
                if not (nodo in visitados or nodo in cola): #FIXME
                    cola.append(nodo)
                    #print("encolo: "+nodo)
        return visitados

    def dfs (self,origen=None):
        visitados=[]
        pila=[]
        pila.append(origen)

        while pila:
            # Saco un nodo de la pila
            origen = pila.pop(0)
            #print("levanto: "+origen)
            visitados.append(origen)

            # Apilo todos sus hijos que no hayan sido visitados
            adyacentes=self.listar_hijos(origen)
            for nodo in adyacentes:
                 if not (nodo in visitados or nodo in pila): #FIXME
                     pila.insert(0,nodo)
                     #print("inserto: "+nodo)
        return visitados


    def camino_minimo(self,origen=None):
        distancia={}
        predecesores={}

        for vertice in self:
            distancia[vertice]=float("inf")

        distancia[origen]=0
        predecesores[origen]=None

        heap=[]
        heapq.heapify(heap)
        heapq.heappush(heap,vertice_heap((distancia[origen],origen)))

        while heap:
                [distancia_al_origen, vertice]= heapq.heappop(heap)

                for w in self.listar_hijos(vertice):
                    if distancia[vertice]+ self.peso_vertice(vertice,w)< distancia[w]:
                        distancia[w]= distancia[vertice]+ self.peso_vertice(vertice,w)
                        predecesores[w]=vertice
                        heapq.heappush(heap,vertice_heap((distancia[w],w)))
        return distancia,predecesores

    def centralidad(self,v=None):
        """Mediante Betweenes Centrality genera un vector con los vertices ordenados
        por importancia"""

        # WIP: bozquejo
        centralidad={}
        for vertice in self:
            centralidad[vertice]=0

        for vertice in self:
            centralidad_vertice_actual= {}
            distancia,predecesores_vertice = self.camino_minimo(vertice)

            for w in self:
                centralidad_vertice_actual[w]=0

            filtrar_infinitos(distancia,predecesores_vertice)





class TestRecorridosNoDirigidos(TestCase):
    """ Prueba recorridos sobre el siguiente grafo no dirigido:
             A
             |
        -----------
       /     |      \
      B      C       E
    /  \     |       |
   D    F    G       |
        |____________|
    """
    def setUp(self):
        """Creación del grafo a utilizar en cada prueba de esta clase"""
        self.grafito = Grafo()
        self.lista_vertices = ["A","B","C","D","E","F","G"]
        self.lista_aristas = [("A","B"), ("B","D"), ("B","F"), ("F","E"), #
        ("A","C"),("C","G"), #
        ("A","E")]

        for k in self.lista_vertices:
            self.grafito.agregar_vertice(k)

        for a,b in self.lista_aristas:
            self.grafito.agregar_arista(a,b,no_dirigido=True)

    def test_recorridos(self):
        algoritmos =[("BFS", self.grafito.bfs), ("DFS", self.grafito.dfs)]

        for padre in self.lista_vertices:
            for nombre,algoritmo in algoritmos:
                # Corro el algoritmo arrancando por el vertice padre
                recorrido = algoritmo(padre)
                # Verifico que haya recorrido todos los vertices
                faltantes = [n for n in self.lista_vertices if not n in recorrido]
                error_help = f"{self.__doc__}\n Raiz: {padre}\n Aclanzables: {self.lista_vertices}\n Recorrido: {recorrido}\n"
                self.assertEqual(len(faltantes), 0, f"Falta recorrer vertices por {nombre}\n {error_help}")

                # Verifico cardinalidad por duplicados
                self.assertEqual(len(recorrido), len(self.lista_vertices), f"Sobran vertices al recorrer por {nombre}\n {error_help}")

class TestRecorridosDirigidos(TestCase):
    """ Prueba recorridos sobre el siguiente grafo dirigido:
             A
             v
        -----------
       v     v      v
      B      C       E
    v  v     v       ^
   D    F    G       |
        v____________|
    """
    def setUp(self):
        """Creación del grafo a utilizar en cada prueba de esta clase"""
        self.grafito = Grafo()
        self.lista_vertices = ["A","B","C","D","E","F","G"]
        self.lista_aristas = [("A","B"), ("B","D"), ("B","F"), ("F","E"), #
        ("A","C"),("C","G"), #
        ("A","E")]

        for k in self.lista_vertices:
            self.grafito.agregar_vertice(k)

        for a,b in self.lista_aristas:
            self.grafito.agregar_arista(a,b)

    def test_recorridos(self):
        algoritmos =[("BFS", self.grafito.bfs), ("DFS", self.grafito.dfs)]
        tests = [ #(padre, lista de vertices alcanzables)
            ("A", {"A","B","C","D","E","F","G"}),
            ("B", {"B","D","F","E"}),
            ("D", {"D"}),
            ("F", {"F","E"}),
            ("C", {"C","G"}),
            ("G", {"G"}),
            ("E", {"E"})
        ]

        for padre, alcanzables in tests:
            for nombre,algoritmo in algoritmos:
                # Corro el algoritmo arrancando por el vertice padre
                recorrido = algoritmo(padre)
                # Verifico que haya recorrido todos los vertices alcanzables
                faltantes = [n for n in alcanzables if not n in recorrido]
                error_help = f"{self.__doc__}\n Raiz: {padre}\n Aclanzables: {self.lista_vertices}\n Recorrido: {recorrido}\n"
                self.assertEqual(len(faltantes), 0, f"Falta recorrer vertices por {nombre}\n {error_help}")

                # Verifico cardinalidad por duplicados
                self.assertEqual(len(recorrido), len(alcanzables), f"Sobran vertices al recorrer por {nombre}\n {error_help}")

class TestGrafo(TestCase):
    def setUp(self):
        """Creación del grafo a utilizar en cada prueba de esta clase"""
        self.grafito = Grafo()
        self.lista_vertices = ["A","B","C","I","F"]
        self.lista_aristas = [("A","B"), ("B","C"), ("C","A"), ("I","A"), ("C","F")]

        for k in self.lista_vertices:
            self.grafito.agregar_vertice(k)

        for a,b in self.lista_aristas:
            self.grafito.agregar_arista(a,b)

    def test_aarmado(self):
        """Check de vertices y aristas en grafo dirigido"""
        vertices = self.grafito.lista_vertices()
        for vertice in vertices:
            self.assertTrue(vertice in self.lista_vertices, "vertice "+vertice+" no encontrado")

        # Comparo cardinalidad
        self.assertEqual(len(vertices), len(self.lista_vertices), "Cantidad de vertices invalida")

        # Chequeo parentezco
        for a in self.lista_vertices:
            for b in self.lista_vertices:
                self.assertEqual(self.grafito.son_adyacentes(a,b), (a,b) in self.lista_aristas, "Error en parentezco ("+a+","+b+").")

    def test_arista_peso_cero(self):
        """Setear arista con peso cero provoca no adyacencia"""
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
        vertices = self.grafito.lista_vertices()
        self.assertTrue("A" in vertices, "A eliminado inesperadamente")
        self.assertTrue("B" in vertices, "B eliminado inesperadamente")

    def test_eliminar_vertice(self):
        """Elimiación de un vertice"""
        self.grafito.eliminar_vertice("A")
        vertices = self.grafito.lista_vertices()
        self.assertFalse("A" in vertices, "A no fue eliminado")

    def eliminar_todos_los_vertices(self):
        """Eliminar todos los vertices del grafo lo vacia"""
        vertices = self.grafito.lista_vertices()
        for vertice in vertices:
            self.grafito.eliminar_vertice(vertice)

        self.assertEqual(len(self.grafito.lista_vertices()), 0)

class TestGrafoNoDirigido(TestCase):
    def setUp(self):
        """Creación del grafo a utilizar en cada prueba de esta clase"""
        self.grafito = Grafo()
        self.lista_vertices = ["A","B","C","I","F"]
        self.lista_aristas = [("A","B"), ("B","C"), ("C","A"), ("I","A"), ("C","F")]

        for k in self.lista_vertices:
            self.grafito.agregar_vertice(k)

        for a,b in self.lista_aristas:
            self.grafito.agregar_arista(a,b, no_dirigido=True)

    def test_aarmado(self):
        """Check aristas y vertices en grafo no dirigido"""
        vertices = self.grafito.lista_vertices()
        for vertice in vertices:
            self.assertTrue(vertice in self.lista_vertices, "vertice "+vertice+" no encontrado")

        # Comparo cardinalidad
        self.assertEqual(len(vertices), len(self.lista_vertices), "Cantidad de vertices invalida")

        # Chequeo parentezco
        for a in self.lista_vertices:
            for b in self.lista_vertices:
                unidos = ((a,b) in self.lista_aristas) or ((b,a) in self.lista_aristas)
                self.assertEqual(self.grafito.son_adyacentes(a,b), unidos, "Error en parentezco ("+a+","+b+").")


if __name__ == '__main__':
    unittest.main(verbosity=2)
