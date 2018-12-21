import Grafo.utils as utils

def imprimir_camino(pila):
    print(" -> ".join(map(str,pila)))

def formatear_camino(pila):
    """Convierte una lista de ciudades en un string separado por ->"""
    return " -> ".join(map(str,pila))

def armar_camino(distancia,predecesores,pila, origen, dest=None):
    """Reconstruye un camino desde un vertice teniendo sus predecesores"""
    if dest==origen:
        pila.insert(0,dest)
        return

    if dest==None:
        distancia_max=0
        for vertice,distancia in distancia.items():
            if distancia>distancia_max:
                distancia_max=distancia
                dest=vertice

    pila.insert(0,dest)
    utils.utils.armar_camino(distancia,predecesores,pila, origen, predecesores[dest])
