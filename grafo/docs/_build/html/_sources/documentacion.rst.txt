Documentación
==============


``Grafo(object)`` Crea un grafo vacio.

``agregar_nodo(nombre_nodo=None)`` Agrego un nodo al grafo, no lo enlazo

``__repr__()`` Devuelve una representación del grafo

``lista_nodos()`` Devuelve una lista de los nodos, ordenados según su aparición en la matriz de adyacencias

``mat_adyacencias()`` Devuelve la matriz de adyacencias de forma densa, la lista
de nodos se obtiene con lista_nodos()

``agregar_arista(padre=None, hijo=None, peso=1, no_dirigido=False)``
Agrega una arista desde el nodo padre hacia el nodo hijo, con un peso dado.
Si el vértice ya existía, lo reemplaza.
Si no se especifica el hijo, se crean dos vértices, uno en cada sentido, de peso dado.
Si el peso no se especifica, se asigna el valor 1.
El peso no puede ser negativo.
Si el peso es 0, el vertice es eliminado.

``peso_vertice(padre=None, hijo=None)`` Devuelve el peso del vertice desde el nodo
padre hacia el nodo hijo

``son_adyacentes(padre=None, hijo=None, no_dirigido=False)``
Devuelve True si el nodo padre posee una arista hacia el nodo hijo.
Si se usa no_dirigido=True, se verifica la existencia de la arista entre nodos, no así su sentido

``eliminar_arista(padre=None, hijo=None, no_dirigido=False)``
Elimina la arista desde el nodo padre al nodo hijo.
Si se usa no_dirigido=True, se eliminan ambas aristas

``eliminar_nodo(nodo=None)`` Elimina el nodo del grafo

``listar_hijos(padre=None)``
Devuelvo una lista con todos los hijos del nodo padre

``bfs(origen=None)`` Recorre el grafo en profundidad.

``dfs (self,origen=None)`` Recorre el grafo en anchura.
