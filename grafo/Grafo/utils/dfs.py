def dfs (grafo,origen=None):
    """Recorrido en profundidad del grafo"""
    visitados=[]
    pila=[]
    pila.append(origen)

    while pila:
        # Saco un nodo de la pila
        origen = pila.pop(0)
        #print("levanto: "+origen)
        visitados.append(origen)

        # Apilo todos sus hijos que no hayan sido visitados
        adyacentes=grafo.obtener_adyacentes(origen)
        for nodo in adyacentes:
             if not (nodo in visitados or nodo in pila): #FIXME
                 pila.insert(0,nodo)
                 #print("inserto: "+nodo)
    return visitados
