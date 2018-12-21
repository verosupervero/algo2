import Grafo.utils as utils
from Grafo import Grafo

def nlugares(grafo,largo,origen, destino= None):
    ruta = []
    visitados={}
    if(destino==None):
        destino=origen

    # declaro funcion wrappeada
    def _nlugares(grafo,origen, destino, largo, ruta=[],visitados={}):
        visitados[origen]=largo
        if largo==1:
            if origen==destino:
                for visitado in sorted(visitados, key=visitados.get):
                    ruta.append(visitado)
                return True
            else:
                del visitados[origen]
                return False

        for v in grafo.obtener_adyacentes(origen):
            if not v in ruta:
                if _nlugares(grafo=grafo, origen=v, destino=destino, largo=largo-1, ruta=ruta):
                    return True

        del visitados[origen]
        return False

     # inicio recursion
    _nlugares(grafo=grafo, origen=origen, destino=destino, largo=largo, ruta=ruta, visitados=visitados)
    return ruta
