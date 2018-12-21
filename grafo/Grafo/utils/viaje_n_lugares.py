import Grafo.utils as utils

def viaje_n_lugares(grafo,n,origen,aeropuertos_por_ciudad):
    """Obtener algún recorrido que comience en origen y que termine en origen también, de largo n."""
    ruta=[]
    for aeropuerto_i in aeropuertos_por_ciudad[origen]:
            ruta=utils.nlugares.nlugares(grafo=grafo,largo=n,origen=aeropuerto_i, destino=aeropuerto_i)
            if ruta:
                break

    return ruta
