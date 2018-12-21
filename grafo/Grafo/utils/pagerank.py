from random import *

def pagerank (grafo, d=0.8):
    """Obtiene el pagerank de un grafo y devuelve los n vertices mas importantes.
    n es pasado por parametro. Parametro opcional: dumping factor, d=0.8 por defecto"""
    # armo un diccionario con el PR de cada nodo, seteado aleatorio ente 0 y 1
    PR={v: random() for v in grafo}
    dif=float("inf")

    k=(1-d)/len(grafo)

    while dif > 0.01**2:
        # actualizo PR de todos los nodos
        dif = 0 # norma² de la diferencia
        for v in grafo:
            old = PR[v]
            PR[v] = k
            for u in grafo.obtener_adyacentes(v):
                PR[v] += d*PR[u]/len(grafo.obtener_adyacentes(u))
            #endfor
            dif += (old-PR[v])**2
        #endfor
    #endwhile

    # devuelvo PR en orden
    return sorted(PR, key=PR.get, reverse=True)
