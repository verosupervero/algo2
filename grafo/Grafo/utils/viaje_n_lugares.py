import Grafo.utils as utils

def viaje_n_lugares(grafo,n,origen,aeropuertos_por_ciudad,imprimir=True):
    """Obtener algún recorrido que comience en origen y que termine en origen también, de largo n."""
    ruta=[]
    for aeropuerto_i in aeropuertos_por_ciudad[origen]:
            ruta=utils.nlugares.nlugares(grafo,n,aeropuerto_i,aeropuerto_i)
            if ruta:
                break
    if not ruta:
        print("No se encontro recorrido")
    else:
        if imprimir:
            utils.utils.imprimir_camino(ruta)
    return ruta
