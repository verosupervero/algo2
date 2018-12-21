def nlugares(grafo,largo,origen, destino= None):
    """Encuentra una ruta desde origen a destino de largo n en el grafo"""

    if(destino==None):
        destino=origen

    # Declaraciones
    ruta = []
    mem = {} # acá guardo lo que voy calculando

    # declaro funcion wrappeada
    def _nlugares(grafo,origen, destino, largo, ruta=[]):
        #print(largo)
        if origen in ruta:
            return False

        ruta.append(origen)
        if largo==1:
            if destino in grafo.obtener_adyacentes(origen):
                ruta.append(destino)
                return True
            else:
                ruta.pop()
                return False

        for v in grafo.obtener_adyacentes(origen):
            if _nlugares_mem(grafo=grafo, origen=v, destino=destino, largo=largo-1, ruta=ruta):
                return True

        ruta.pop()
        return False

    # funcion que memoriza lo que calcula
    def _nlugares_mem(grafo,origen, destino, largo, ruta=[]):
        op = f"{origen} {largo}"
        if op in mem:
            if mem[op]==None:
                return False
            else:
                ruta.append(op[mem])
                return True
        else:
            return _nlugares(grafo=grafo, origen=origen, destino=destino, largo=largo, ruta=ruta)

     # inicio recursion
    _nlugares_mem(grafo=grafo, origen=origen, destino=destino, largo=largo, ruta=ruta)
    return ruta
