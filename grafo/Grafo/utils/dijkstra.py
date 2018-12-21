import Grafo.utils as utils
import heapq

def dijkstra(grafo,origen,dest=None):
    """Calcula el camino minimo desde un origen dado a un vértice o
    a todo el grafo.
    Devuelve un diccionario con la distancia desde el orignen
    hacia cada vertice, y otro diccionario con el predecesor
    en el recorrido minimo de cada vértice en cuestión."""

    distancia={}
    predecesores={}

    for vertice in grafo:
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

        for w in grafo.obtener_adyacentes(vertice):
            if distancia[vertice]+ grafo.obtener_arista(vertice,w)< distancia[w]:
                distancia[w]= distancia[vertice]+ grafo.obtener_arista(vertice,w)
                predecesores[w]=vertice
                heapq.heappush(heap,(distancia[w],w))

    return distancia,predecesores
