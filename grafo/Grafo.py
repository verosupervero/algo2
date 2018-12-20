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

    # def _compactar(self):
    #     """Elimina las columnas extra en la matriz de adyacencias, correspondientes a vertices eliminados"""
    #     # Lista de columnas válidas (no eliminadas)
    #     indices = list(self._indices.values())
    #
    #     # Lista de vertices e indices validos, ordenados
    #     indices = list(sorted(self._indices.values()))
    #     vertices = sorted(self._indices, key=self._indices.__getitem__)
    #
    #     # Filtro solo las columnas usadas
    #     M_filtrada = self._mat_ady[:,indices][indices,:]
    #
    #     # Asigno mis nuevos indices incrementalmente
    #     self._indices = {v:i for i,v in enumerate(vertices)}
    #     #print(self._indices)
    #
    #     # Asigno nueva matriz
    #     self._mat_ady = M_filtrada

    # def mat_adyacencias(self):
    #     """Devuelve la matriz de adyacencias , la lista de vertices se obtiene con obtener_vertices()"""
    #     # Compacto la matriz para eliminar filas y columnas que no representan vertices
    #     self._compactar()
    #
    #     # Devuelvo la matriz densa
    #     return self._mat_ady.copy()


    def obtener_arista(self, padre=None, hijo=None):
        return self.grafo[padre][hijo]

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
            return vertice in self.grafo.keys()

    def bfs(self,origen=None,dest=None, imprimir=False):
        visitados=[]
        predecesores={}
        distancia_al_origen={}

        for vertice in self.obtener_vertices():
            distancia_al_origen[vertice]= float("inf")
            predecesores[vertice]=None

        distancia_al_origen[origen]=0

        cola=deque([])
        cola.append(origen)
        while cola:

            if dest is not None and dest in visitados:
                break

            # Desencolo un nodo y lo agrego a visitados
            origen=cola.popleft()
            visitados.append(origen)
            #print("levanto: "+origen)

            # Encolo todos sus hijos que no hayan sido visitados previamente
            adyacentes=self.obtener_adyacentes(origen)
            for w in adyacentes:
                if not w in visitados or not w in cola:
                    cola.append(w)
                    predecesores[w]=origen
                    distancia_al_origen[w]=distancia_al_origen[origen]+1
                    #print("encolo: "+nodo)

        return visitados,predecesores,distancia_al_origen

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
            adyacentes=self.obtener_adyacentes(origen)
            for nodo in adyacentes:
                 if not (nodo in visitados or nodo in pila): #FIXME
                     pila.insert(0,nodo)
                     #print("inserto: "+nodo)
        return visitados


    def camino_minimo(self,origen,dest=None):
        """Calcula el camino minimo desde un origen dado a un vértice o
        a todo el grafo.
        Devuelve un diccionario con la distancia desde el orignen
        hacia cada vertice, y otro diccionario con el predecesor
        en el recorrido minimo de cada vértice en cuestión."""

        distancia={}
        predecesores={}

        for vertice in self:
            distancia[vertice]=float("inf")

        distancia[origen]=0
        predecesores[origen]=None

        heap=[]
        heapq.heapify(heap)
        heapq.heappush(heap,(distancia[origen],origen))

        while heap:
            [distancia_al_origen, vertice]= heapq.heappop(heap)
            if vertice==dest:
                break

            for w in self.obtener_adyacentes(vertice):
                if distancia[vertice]+ self.obtener_arista(vertice,w)< distancia[w]:
                    distancia[w]= distancia[vertice]+ self.obtener_arista(vertice,w)
                    predecesores[w]=vertice
                    heapq.heappush(heap,(distancia[w],w))

        return distancia,predecesores

    def centralidad(self,cantidad_aeropuertos):
        """Mediante Betweeness Centrality genera un vector con los vertices ordenados
        por importancia"""

        # WIP: bozquejo
        centralidad={}
        for vertice in self:
            centralidad[vertice]=0

        for vertice in self:
            centralidad_auxiliar= {}
            distancia,predecesor= self.camino_minimo(vertice)

            for w in self:
                centralidad_auxiliar[w]=0

            distancias_filtradas= {k: v for k, v in distancia.items() if v<float("inf")}

            for w in sorted(distancias_filtradas, key=distancias_filtradas.__getitem__,reverse=True):
                if w==vertice: continue
                centralidad_auxiliar[predecesor[w]]+=1
                centralidad_auxiliar[predecesor[w]]+=centralidad_auxiliar[w]

            for w in self:
                if w==vertice: continue
                centralidad[w]+=centralidad_auxiliar[w]

        print(','.join(map(str,sorted(centralidad, key=centralidad.get, reverse=True)[0:cantidad_aeropuertos])))
        return centralidad

    def nlugares(self,largo,origen, destino= None):
        ruta = []
        if(destino==None):
            destino=origen

        # declaro funcion wrappeada
        def _nlugares(origen, destino, largo, ruta=[]):
            ruta.append(origen)
            if largo==0:
                if origen==destino:
                    return True
                else:
                    ruta.pop()
                    return False

            for v in self.obtener_adyacentes(origen):
                if not v in ruta:
                    if _nlugares(v, destino, largo-1, ruta):
                        return True

            ruta.pop()
            return False

        # inicio recursion
        _nlugares(origen, destino, largo, ruta)
        return ruta

    def pagerank(self,cantidad_iteraciones=100,imprimir=False):
        """"""
        #Para obtener el pagerank de cada pagina necesitamos:

        #La matriz de adyacencias tiene pesos, se que tan fuerte es la union entre nodos y como se conectan,
        #lo que hago es transponer la matriz y luego llevar sus columnas a que tengan como suma probabilidad=1,
        #dado que Pagerank(A)=sum Pagerank(i)/L(i) con L(i)= cantidad de links en las paginas.
        # Debe ser una matriz estocastica por eso se piden estas condiciones,
        #una matriz estocastica cuenta con esta caracteristica.
        M=self.mat_adyacencias().transpose()
        M/= M.sum(axis=0)
        cant_vertices=len(self)
        d=0.85 #duping factor, sino se queda oscilando entre links
        M= d*M + (1-d)/cant_vertices

        #Me genero un vector aleatorio (o sea un vector que tiene valores entre 0 y 1)
        x=np.random.rand(cant_vertices)

        #Sabemos que dado un vector v, lim n->oo A^k*v converge a sum lambda_i^k*v, con lambda_i cada ava.
        #Con lo cual convergera a los aves de la matriz A.
        #En este caso serán M y x nuestra matriz y vector.
        p=0.3
        for k in range (0,cantidad_iteraciones):
            y=d*M@x+(1-d)*x.sum()
            y/=y.sum()
            y_array=np.squeeze(np.asarray(y))
            if(np.linalg.norm(x-y_array)<0.01):
                x=y_array
                break
            else:
                r=(np.sign(np.random.rand()-p)+np.ones(cant_vertices))/2
                x= x*r + y_array*(1-r)
        pagerank={}
        i=0
        for vertice in self:
            pagerank[vertice]=x[i]
            i=i+1

        #Imprimo el pagerank y lo devuelvo
        if imprimir:
            print(','.join(map(str,sorted(pagerank, key=pagerank.get, reverse=True))))
        return sorted(pagerank, key=pagerank.get, reverse=True)

# class TestPagerankNoDirigido(TestCase):
#     """Creación del grafo no dirigido"""
#
#     def setUp(self):
#         self.grafito = Grafo()
#
#         self.obtener_vertices = ["A","B","C","D","BA","BB"]
#         # aristas no dirigidas
#         self.lista_aristas = [("A","B",1), ("A","C",1), ("A","D",1), ("B","BA",1), ("B","BB",1),("BB","C",0.1)]
#
#         for k in self.obtener_vertices:
#             self.grafito.agregar_vertice(k)
#
#         for a,b,peso in self.lista_aristas:
#             self.grafito.agregar_arista(a,b,peso=peso, no_dirigido=True)
#
#     def test_pagerank_grafo_no_dirigido(self):
#         pagerank=self.grafito.pagerank()
#         pagerank_ok= ['B', 'A', 'C', 'BB', 'D', 'BA']
#         self.assertEqual(pagerank, pagerank_ok, f"Los pagerank coinciden")


# class TestRecorridosNoDirigidos(TestCase):
#     """ Prueba recorridos sobre el siguiente grafo no dirigido:
#              A
#              |
#         -----------
#        /     |      \
#       B      C       E
#     /  \     |       |
#    D    F    G       |
#         |____________|
#     """
#     def setUp(self):
#         """Creación del grafo a utilizar en cada prueba de esta clase"""
#         self.grafito = Grafo()
#         self.obtener_vertices = ["A","B","C","D","E","F","G"]
#         self.lista_aristas = [("A","B"), ("B","D"), ("B","F"), ("F","E"), #
#         ("A","C"),("C","G"), #
#         ("A","E")]
#
#         for k in self.obtener_vertices:
#             self.grafito.agregar_vertice(k)
#
#         for a,b in self.lista_aristas:
#             self.grafito.agregar_arista(a,b,no_dirigido=True)
#
#     def test_recorridos(self):
#         algoritmos =[("BFS", self.grafito.bfs), ("DFS", self.grafito.dfs)]
#
#         for padre in self.obtener_vertices:
#             for nombre,algoritmo in algoritmos:
#                 # Corro el algoritmo arrancando por el vertice padre
#                 recorrido = algoritmo(padre)
#                 # Verifico que haya recorrido todos los vertices
#                 faltantes = [n for n in self.obtener_vertices if not n in recorrido]
#                 error_help = f"{self.__doc__}\n Raiz: {padre}\n Aclanzables: {self.obtener_vertices}\n Recorrido: {recorrido}\n"
#                 self.assertEqual(len(faltantes), 0, f"Falta recorrer vertices por {nombre}\n {error_help}")
#
#                 # Verifico cardinalidad por duplicados
#                 self.assertEqual(len(recorrido), len(self.obtener_vertices), f"Sobran vertices al recorrer por {nombre}\n {error_help}")

# class TestRecorridosDirigidos(TestCase):
#     """ Prueba recorridos sobre el siguiente grafo dirigido:
#              A
#              v
#         -----------
#        v     v      v
#       B      C       E
#     v  v     v       ^
#    D    F    G       |
#         v____________|
#     """
#     def setUp(self):
#         """Creación del grafo a utilizar en cada prueba de esta clase"""
#         self.grafito = Grafo()
#         self.obtener_vertices = ["A","B","C","D","E","F","G"]
#         self.lista_aristas = [("A","B"), ("B","D"), ("B","F"), ("F","E"), #
#         ("A","C"),("C","G"), #
#         ("A","E")]
#
#         for k in self.obtener_vertices:
#             self.grafito.agregar_vertice(k)
#
#         for a,b in self.lista_aristas:
#             self.grafito.agregar_arista(a,b)
#
#     def test_recorridos(self):
#         algoritmos =[("BFS", self.grafito.bfs), ("DFS", self.grafito.dfs)]
#         tests = [ #(padre, lista de vertices alcanzables)
#             ("A", {"A","B","C","D","E","F","G"}),
#             ("B", {"B","D","F","E"}),
#             ("D", {"D"}),
#             ("F", {"F","E"}),
#             ("C", {"C","G"}),
#             ("G", {"G"}),
#             ("E", {"E"})
#         ]
#
#         for padre, alcanzables in tests:
#             for nombre,algoritmo in algoritmos:
#                 # Corro el algoritmo arrancando por el vertice padre
#                 recorrido = algoritmo(padre)
#                 # Verifico que haya recorrido todos los vertices alcanzables
#                 faltantes = [n for n in alcanzables if not n in recorrido]
#                 error_help = f"{self.__doc__}\n Raiz: {padre}\n Aclanzables: {self.obtener_vertices}\n Recorrido: {recorrido}\n"
#                 self.assertEqual(len(faltantes), 0, f"Falta recorrer vertices por {nombre}\n {error_help}")
#
#                 # Verifico cardinalidad por duplicados
#                 self.assertEqual(len(recorrido), len(alcanzables), f"Sobran vertices al recorrer por {nombre}\n {error_help}")

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

# class TestGrafoNoDirigido(TestCase):
#     def setUp(self):
#         """Creación del grafo a utilizar en cada prueba de esta clase"""
#         self.grafito = Grafo()
#         self.obtener_vertices = ["A","B","C","I","F"]
#         self.lista_aristas = [("A","B"), ("B","C"), ("C","A"), ("I","A"), ("C","F")]
#
#         for k in self.obtener_vertices:
#             self.grafito.agregar_vertice(k)
#
#         for a,b in self.lista_aristas:
#             self.grafito.agregar_arista(a,b, no_dirigido=True)
#
#     def test_aarmado(self):
#         """Check aristas y vertices en grafo no dirigido"""
#         vertices = self.grafito.obtener_vertices()
#         for vertice in vertices:
#             self.assertTrue(vertice in self.obtener_vertices, "vertice "+vertice+" no encontrado")
#
#         # Comparo cardinalidad
#         self.assertEqual(len(vertices), len(self.obtener_vertices), "Cantidad de vertices invalida")
#
#         # Chequeo parentezco
#         for a in self.obtener_vertices:
#             for b in self.obtener_vertices:
#                 unidos = ((a,b) in self.lista_aristas) or ((b,a) in self.lista_aristas)
#                 self.assertEqual(self.grafito.son_adyacentes(a,b), unidos, "Error en parentezco ("+a+","+b+").")

# class TestCaminoMinimo(TestCase):
#     # WIP -- hacer
#     def setUp(self):
#         """Creación del grafo a utilizar en cada prueba de esta clase"""
#         self.grafito = Grafo()
#         self.obtener_vertices = ["A","B","C","I","F"]
#         self.lista_aristas = [("A","B"), ("B","C"), ("C","A"), ("I","A"), ("C","F")]
#
#         for k in self.obtener_vertices:
#             self.grafito.agregar_vertice(k)
#
#         for a,b in self.lista_aristas:
#             self.grafito.agregar_arista(a,b, no_dirigido=True)
#
#     def test_nodirigido(self):
#         """Dijstra en no dirigido"""
#
#         grafito = Grafo()
#         obtener_vertices = ["A","B","C","D","F","H","I"]
#         lista_aristas = [("A","B",5), ("B","F",1), ("C","A",7), ("D","F",6), ("A","F",8), ("C","D",8), ("H","I",1)]
#
#         for k in obtener_vertices:
#             grafito.agregar_vertice(k)
#
#         for a,b,peso in lista_aristas:
#             grafito.agregar_arista(a,b,peso=peso, no_dirigido=True)
#
#
#         pesos, padres = grafito.camino_minimo(origen="A")
#
#         pesos_ok = {'A': 0, 'B': 5.0, 'C': 7.0, 'D': 12.0, 'F': 6.0, 'H': float("inf"), 'I': float("inf")}
#         padres_ok = {'A': None, 'B': 'A', 'C': 'A', 'F': 'B', 'D': 'F'}
#
#         self.assertEqual(pesos, pesos_ok, "Los caminos minimos no coinciden")
#         self.assertEqual(padres, padres_ok, "Los predecesores no coinciden")
#
#     def test_dirigido(self):
#
#         grafito = Grafo()
#
#         obtener_vertices = ["A","B","C","D","F","H","I"]
#         # aristas no dirigidas
#         lista_aristas = [("A","B",5), ("C","A",7), ("A","F",8), ("D","F",6), ("C","D",8), ("H","I",1)]
#
#         for k in obtener_vertices:
#             grafito.agregar_vertice(k)
#
#         for a,b,peso in lista_aristas:
#             grafito.agregar_arista(a,b,peso=peso, no_dirigido=True)
#
#         # arista dirigida
#         grafito.agregar_arista("F", "B", peso=1)
#
#         pesos,padres= grafito.camino_minimo(origen="A")
#
#         pesos_ok = {'A': 0, 'B': 5.0, 'C': 7.0, 'D': 14.0, 'F': 8.0, 'H': float("inf"), 'I': float("inf")}
#         padres_ok = {'A': None, 'B': 'A', 'C': 'A', 'F': 'A', 'D': 'F'}
#
#         self.assertEqual(pesos, pesos_ok, "Los caminos minimos no coinciden")
#         self.assertEqual(padres, padres_ok, "Los predecesores no coinciden")

if __name__ == '__main__':
    unittest.main(verbosity=2)
