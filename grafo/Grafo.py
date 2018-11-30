import numpy as np
from scipy import sparse
import warnings

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

        Si el peso es 0, el vertice es eliminado."""

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
