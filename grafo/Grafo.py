import numpy as np
from scipy import sparse
import warnings

import unittest
from unittest import TestCase

class Grafo(object):
    """Voy a implementar un grafo como una matriz (sparse) de adyacencias y un diccionario de nodos"""
    def __init__(self):
        """Crea un grafo vacio"""
        self._mat_ady = sparse.dok_matrix((0,0))

        # Creo un diccionario con los nombres de los nodos, asociados a su indice
        # la ventaja de esto, es que no necesito eliminar filas y columnas de la matriz
        # solo poner sus valores en 0 y sacarlo de la lista, pero sin "desplazar" los indices
        # del resto.
        # Contra: al eliminar nodos van a quedar filas y columnas nulas, pero las puedo
        # eliminar si quiero
        self._indices = {}

    def agregar_nodo(self, nombre_nodo=None):
        """Agrego un nodo al grafo, no lo enlazo"""
        if nombre_nodo in self._indices:
            raise NameError('Nodo ya existe') # esto va o solo return?

        # Agrego el nodo al diccionario, con su nuevo indice
        nuevo_indice = max(self._mat_ady.get_shape()) # +1 implicito
        self._indices[nombre_nodo] = nuevo_indice

        # Agrego una nueva fila y columna a la matriz
        nuevo_tamanio = nuevo_indice+1
        self._mat_ady.resize((nuevo_tamanio, nuevo_tamanio))

    def __repr__(self):
        """Devuelve una representación del grafo"""
        return "<Nodos: " + str(self.lista_nodos()) + "\n Adyacencias:\n" + str(self.mat_adyacencias()) +" >"

    def lista_nodos(self):
        """Devuelve una lista de los nodos, ordenados según su aparición en la matriz de adyacencias"""
        return sorted(self._indices, key=self._indices.__getitem__)

    def _compactar(self):
        """Elimina las columnas extra en la matriz de adyacencias, correspondientes a nodos eliminados"""
        # Lista de columnas válidas (no eliminadas)
        indices = list(self._indices.values())

        # Lista de nodos e indices validos, ordenados
        indices = list(sorted(self._indices.values()))
        nodos = sorted(self._indices, key=self._indices.__getitem__)

        # Filtro solo las columnas usadas
        M_filtrada = self._mat_ady[:,indices][indices,:]

        # Asigno mis nuevos indices incrementalmente
        self._indices = {v:i for i,v in enumerate(nodos)}
        print(self._indices)

        # Asigno nueva matriz
        self._mat_ady = M_filtrada

    def mat_adyacencias(self):
        """Devuelve la matriz de adyacencias de forma densa, la lista de nodos se obtiene con lista_nodos()"""
        # Compacto la matriz para eliminar filas y columnas que no representan nodos
        self._compactar()

        # Devuelvo la matriz densa
        return self._mat_ady.todense()

    def agregar_arista(self, padre=None, hijo=None, peso=1, no_dirigido=False):
        """Agrega una arista desde el nodo padre hacia el nodo hijo, con un peso dado.
        Si el vértice ya existía, lo reemplaza.
        Si no se especifica el hijo, se crean dos vértices, uno en cada sentido, de peso dado.
        Si el peso no se especifica, se asigna el valor 1.

        El peso no puede ser negativo.
        Si el peso es 0, el vertice es eliminado."""

        if peso < 0:
            raise ValueError('El peso debe ser no negativo')

        # Busco los índices de los nodos
        idx_padre = self._indices[padre]
        idx_hijo = self._indices[hijo]

        # Agrego peso
        self._mat_ady[idx_padre, idx_hijo] = peso

        if no_dirigido:
            # Simétrico
            self._mat_ady[idx_hijo, idx_padre] = peso

    def peso_vertice(self, padre=None, hijo=None):
        # Busco los índices de los nodos
        idx_padre = self._indices[padre]
        idx_hijo = self._indices[hijo]

        return self._mat_ady[idx_padre, idx_hijo]

    def son_adyacentes(self, padre=None, hijo=None, no_dirigido=False):
        """Devuelve si el nodo padre posee una arista hacia el nodo hijo.
        Si se usa no_dirigido=True, se verifica la existencia de la arista entre nodos, no así su sentido"""

        adyacencia_directa = self.peso_vertice(padre, hijo)!=0

        if no_dirigido:
            adyacencia_inversa =  self.peso_vertice(hijo, padre)!=0
            return adyacencia_directa or adyacencia_inversa

        # Adyacencia dirigida
        return adyacencia_directa

    def eliminar_arista(self, padre=None, hijo=None, no_dirigido=False):
        """Elimina la arista desde el nodo padre al nodo hijo.
        Si se usa no_dirigido=True, se eliminan ambas aristas"""

        self.agregar_arista(padre=padre, hijo=hijo, peso=0, no_dirigido=no_dirigido)

    def eliminar_nodo(self, nodo=None):
        """Elimina el nodo del grafo."""
        # elimino valor del diccionario
        idx_nodo = self._indices.pop(nodo)

        # elimino la fila y columna idx_nodo-ésima (respectivamente)
        self._mat_ady[idx_nodo,:] = 0
        self._mat_ady[:,idx_nodo] = 0

        # No voy a modificar las dimensiones de la matriz de adyacencia porque debería actualizar
        # todos los índices, y al ser sparse no molesta tener más ceros. De todas formas se puede
        # compactar la representación interna usando el método _compactar()

    def listar_hijos(self, padre=None):
        """Devuelvo una lista con todos los hijos del nodo padre"""
        # Busco los índices de los nodos
        idx_padre = self._indices[padre]

        # Obtengo los hijos del nodo, serían aquellas posiciones que no tienen 0 en la columna dada
        idx_hijos = np.where(self._mat_ady[idx_padre,:].todense()!=0)[1]

        # Convierto a una lista de nombres de nodos
        return [nombre for nombre,idx in self._indices.items() if idx in idx_hijos]

    def bfs(self,origen=None):
        visitados=[]
        cola=[]
        cola.append(origen)
        while cola:
            visitados.append(origen)
            adyacentes=grafo.listar_hijos(origen)
            for a in adyacentes:
                if not a in cola:
                    cola.append(origen)
            origen=cola.pop(0)

        visitados.append(origen)
        return visitados

    def dfs (self,origen=None):
        visitados=[]
        pila=[]
        pila.append(origen)

        while pila:
            adyacente=grafo.obtener_adyacente(origen)

            if not adyacente or adyacente in visitados:
                pila.pop(0)
                origen=pila[0]

            if adyacente not in visitados:
                pila.insert(0,adyacente)
                visitados.append(adyacente)

        return visitados


class TestGrafo(TestCase):
    def setUp(self):
        """Creación del grafo a utilizar en cada prueba de esta clase"""
        self.grafito = Grafo()
        self.lista_nodos = ["A","B","C","I","F"]
        self.lista_aristas = [("A","B"), ("B","C"), ("C","A"), ("I","A"), ("C","F")]

        for k in self.lista_nodos:
            self.grafito.agregar_nodo(k)

        for a,b in self.lista_aristas:
            self.grafito.agregar_arista(a,b)

    def test_aarmado(self):
        """Check de nodos y aristas en grafo dirigido"""
        nodos = self.grafito.lista_nodos()
        for nodo in nodos:
            self.assertTrue(nodo in self.lista_nodos, "Nodo "+nodo+" no encontrado")

        # Comparo cardinalidad
        self.assertEqual(len(nodos), len(self.lista_nodos), "Cantidad de nodos invalida")

        # Chequeo parentezco
        for a in self.lista_nodos:
            for b in self.lista_nodos:
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
        """Eliminar una arista provoca no adyacencia y no modifica nodos"""
        self.grafito.eliminar_arista("A","B")
        self.assertFalse(self.grafito.son_adyacentes("A","B"))
        nodos = self.grafito.lista_nodos()
        self.assertTrue("A" in nodos, "A eliminado inesperadamente")
        self.assertTrue("B" in nodos, "B eliminado inesperadamente")

    def test_eliminar_nodo(self):
        """Elimiación de un nodo"""
        self.grafito.eliminar_nodo("A")
        nodos = self.grafito.lista_nodos()
        self.assertFalse("A" in nodos, "A no fue eliminado")

    def eliminar_todos_los_nodos(self):
        """Eliminar todos los nodos del grafo lo vacia"""
        nodos = self.grafito.lista_nodos()
        for nodo in nodos:
            self.grafito.eliminar_nodo(nodo)

        self.assertEqual(len(self.grafito.lista_nodos()), 0)

class TestGrafoNoDirigido(TestCase):
    def setUp(self):
        """Creación del grafo a utilizar en cada prueba de esta clase"""
        self.grafito = Grafo()
        self.lista_nodos = ["A","B","C","I","F"]
        self.lista_aristas = [("A","B"), ("B","C"), ("C","A"), ("I","A"), ("C","F")]

        for k in self.lista_nodos:
            self.grafito.agregar_nodo(k)

        for a,b in self.lista_aristas:
            self.grafito.agregar_arista(a,b, no_dirigido=True)

    def test_aarmado(self):
        """Check aristas y nodos en grafo no dirigido"""
        nodos = self.grafito.lista_nodos()
        for nodo in nodos:
            self.assertTrue(nodo in self.lista_nodos, "Nodo "+nodo+" no encontrado")

        # Comparo cardinalidad
        self.assertEqual(len(nodos), len(self.lista_nodos), "Cantidad de nodos invalida")

        # Chequeo parentezco
        for a in self.lista_nodos:
            for b in self.lista_nodos:
                unidos = ((a,b) in self.lista_aristas) or ((b,a) in self.lista_aristas)
                self.assertEqual(self.grafito.son_adyacentes(a,b), unidos, "Error en parentezco ("+a+","+b+").")


if __name__ == '__main__':
    unittest.main(verbosity=2)
