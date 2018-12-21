import Grafo.utils as utils

def nlugares(grafo,largo,origen, destino= None):
    ruta = []
    if(destino==None):
        destino=origen

    # declaro funcion wrappeada
    def _nlugares(grafo,origen, destino, largo, ruta=[]):
        ruta.append(origen)
        if largo==1:
            if origen==destino:
                return True
            else:
                ruta.pop()
                return False

        for v in grafo.obtener_adyacentes(origen):
            if not v in ruta:
                if _nlugares(v, destino, largo-1, ruta):
                    return True

        ruta.pop()
        return False

     # inicio recursion
    _nlugares(grafo,origen, destino, largo, ruta)
    return ruta
