import Grafo.utils as utils
from Grafo import Grafo

def nlugares(grafo,largo,origen, destino= None):
    ruta = []
    visitados=set()
    if(destino==None):
        destino=origen
    print(largo)
    # declaro funcion wrappeada
    def _nlugares(grafo,origen, destino, largo, ruta=[],visitados=set()):
        #print(largo)
        visitados.add(origen)
        ruta.append(origen)
        if largo==1:
            if origen==destino:
                # print(visitados)
                # for visitado in sorted(visitados, key=visitados.get):
                #     ruta.append(visitado)
                print(ruta)
                return True
            else:
                #del visitados[origen]
                ruta.pop()
                visitados.discard (origen)
                return False

        for v in grafo.obtener_adyacentes(origen):
            if not v in visitados:
                if _nlugares(grafo=grafo, origen=v, destino=destino, largo=largo-1, ruta=ruta,visitados=visitados):
                    return True

        visitados.discard (origen)
        ruta.pop()
        return False

     # inicio recursion
    _nlugares(grafo=grafo, origen=origen, destino=destino, largo=largo, ruta=ruta,visitados=visitados)
    return ruta
