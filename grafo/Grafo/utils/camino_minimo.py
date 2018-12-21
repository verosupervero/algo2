import Grafo.utils as utils

def camino_minimo(origen,dest,grafo,aeropuertos_por_ciudad,imprimir=True,pesado=True):
    """Obtiene el camino minimo de un vertice a otro del grafo"""
    camino=[]
    costo=float("inf")
    for aeropuerto_i in aeropuertos_por_ciudad[origen]:
        for aeropuerto_j in aeropuertos_por_ciudad[dest]:
            if pesado:
                distancia, predecesores= utils.dijkstra.dijkstra(grafo,aeropuerto_i,aeropuerto_j)
            else:
                predecesores, distancia= utils.bfs.bfs(grafo,aeropuerto_i,aeropuerto_j)

            if distancia[aeropuerto_j]< costo:
                costo=distancia[aeropuerto_j]
                camino.clear()
                utils.utils.armar_camino(distancia,predecesores,camino,aeropuerto_i,aeropuerto_j)

            distancia.clear()
            predecesores.clear()

    if imprimir:
        utils.utils.imprimir_camino(camino)
    return costo,camino
