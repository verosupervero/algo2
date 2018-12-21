# para usar estas funciones desde otro lado, hacer from itinerario_cultural import *

def armar_itinerario_cultural(archivo):
    """Arma un itinerario cultural desde un archivo dado"""
    grafo_orden_topo = Grafo()
    with open(archivo, newline='') as csvfile:
        lugares = csv.reader(csvfile, delimiter=',')
        for lugar in lugares:
            if not vertice in grafo_orden_topo:
                grafo_orden_topo.agregar_vertice(lugar)

        for i in range(0,len(lugares)):
            grafo_orden_topo.agregar_arista(lugar[i],lugar[i+1])

    grafo_orden_topo.ver_diccionario()

def obtener_itinerario_cultural(grafo,lugares,aeropuertos_por_ciudad):
    """Obtiene el itinerario cultural en pantalla luego de armarlo del archivo"""
    print(",".join(map(str,lugares)))
    for i in range (0,len(lugares)):
        obtener_camino_minimo_origen_destino(lugares[i],lugares[i+1],grafo,aeropuertos_por_ciudad,True,False)
