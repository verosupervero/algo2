import Grafo.utils as utils
from collections import deque

def bfs(grafo,origen=None,dest=None):
    """Recorrido en anchura del grafo"""
    visitados=[]
    predecesores={}
    distancia_al_origen={}

    for vertice in grafo.obtener_vertices():
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
        #print(visitados)
        #print("-----levanto: ", origen)

        # Encolo todos sus hijos que no hayan sido visitados previamente
        adyacentes=grafo.obtener_adyacentes(origen)
        for w in adyacentes:
            #print (w, "visitado:", w in visitados)
            if not w in visitados and not w in cola:
                cola.append(w)
                predecesores[w]=origen
                distancia_al_origen[w]=distancia_al_origen[origen]+1
                #print("encolo: ", w)
    if dest!=None:
        return predecesores, distancia_al_origen
    return visitados,predecesores, distancia_al_origen
