from Grafo import Grafo
import warnings
from random import *
import unittest
from unittest import TestCase
from collections import deque
import heapq

def imprimir_camino(pila):
    print("->".join(map(str,pila)))

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
    armar_camino(distancia,predecesores,pila, origen, predecesores[dest])

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

def obtener_camino_minimo_origen_destino(origen,dest,grafo,aeropuertos_por_ciudad,imprimir=True,pesado=True):
    """Obtiene el camino minimo de un vertice a otro del grafo"""
    camino=[]
    costo=float("inf")
    for aeropuerto_i in aeropuertos_por_ciudad[origen]:
        for aeropuerto_j in aeropuertos_por_ciudad[dest]:
            if pesado:
                distancia, predecesores= dijkstra(grafo,aeropuerto_i,aeropuerto_j)
            else:
                predecesores, distancia= bfs(grafo,aeropuerto_i,aeropuerto_j)

            if distancia[aeropuerto_j]< costo:
                costo=distancia[aeropuerto_j]
                camino.clear()
                armar_camino(distancia,predecesores,camino,aeropuerto_i,aeropuerto_j)

            distancia.clear()
            predecesores.clear()

    if imprimir:
        imprimir_camino(camino)
    return costo,camino

def obtener_viaje_n_lugares(grafo,n,origen,aeropuertos_por_ciudad,imprimir=True):
    """Obtener algún recorrido que comience en origen y que termine en origen también, de largo n."""
    ruta=[]
    for aeropuerto_i in aeropuertos_por_ciudad[origen]:
            ruta=nlugares(grafo,n,aeropuerto_i,aeropuerto_i)
            if ruta:
                break
    if not ruta:
        print("No se encontro recorrido")
    else:
        if imprimir:
            imprimir_camino(ruta)
    return ruta

def bfs(grafo,origen=None,dest=None):
    """Recorrido en anchura del grafo"""
    visitados=[]
    predecesores={}
    distancia_al_origen={}

    for vertice in grafo.obtener_vertices():
        distancia_al_origen[vertice]= float("inf")
        predecesores[vertice]=None

    distancia_al_origen[origen]=0

    cola=deque([])
    cola.append(origen)
    while cola:
        if dest is not None and dest in visitados:
            break

        # Desencolo un nodo y lo agrego a visitados
        origen=cola.popleft()
        visitados.append(origen)
        #print(visitados)
        #print("-----levanto: ", origen)

        # Encolo todos sus hijos que no hayan sido visitados previamente
        adyacentes=grafo.obtener_adyacentes(origen)
        for w in adyacentes:
            #print (w, "visitado:", w in visitados)
            if not w in visitados and not w in cola:
                cola.append(w)
                predecesores[w]=origen
                distancia_al_origen[w]=distancia_al_origen[origen]+1
                #print("encolo: ", w)
    if dest!=None:
        return predecesores, distancia_al_origen
    return visitados,predecesores, distancia_al_origen

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


def dijkstra(grafo,origen,dest=None):
    """Calcula el camino minimo desde un origen dado a un vértice o
    a todo el grafo.
    Devuelve un diccionario con la distancia desde el orignen
    hacia cada vertice, y otro diccionario con el predecesor
    en el recorrido minimo de cada vértice en cuestión."""

    distancia={}
    predecesores={}

    for vertice in grafo:
        distancia[vertice]=float("inf")

    distancia[origen]=0
    predecesores[origen]=None

    heap=[]
    heapq.heapify(heap)
    heapq.heappush(heap,(distancia[origen],origen))

    while heap:
        [distancia_al_origen, vertice]= heapq.heappop(heap)
        if vertice==dest:
            break

        for w in grafo.obtener_adyacentes(vertice):
            if distancia[vertice]+ grafo.obtener_arista(vertice,w)< distancia[w]:
                distancia[w]= distancia[vertice]+ grafo.obtener_arista(vertice,w)
                predecesores[w]=vertice
                heapq.heappush(heap,(distancia[w],w))

    return distancia,predecesores

def centralidad(grafo,cantidad_aeropuertos):
    """Mediante Betweeness Centrality genera un vector con los vertices ordenados
    por importancia"""

    centralidad={}
    for vertice in grafo:
        centralidad[vertice]=0

    for vertice in grafo:
        centralidad_auxiliar= {}
        distancia,predecesor= dijkstra(grafo,vertice)

        for w in grafo:
            centralidad_auxiliar[w]=0

        distancias_filtradas= {k: v for k, v in distancia.items() if v<float("inf")}

        for w in sorted(distancias_filtradas, key=distancias_filtradas.__getitem__,reverse=True):
            if w==vertice: continue
            centralidad_auxiliar[predecesor[w]]+=1
            centralidad_auxiliar[predecesor[w]]+=centralidad_auxiliar[w]

        for w in grafo:
            if w==vertice: continue
            centralidad[w]+=centralidad_auxiliar[w]

    print(','.join(map(str,sorted(centralidad, key=centralidad.get, reverse=True)[0:cantidad_aeropuertos])))
    return centralidad

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

# def nlugares(grafo,largo,origen, destino= None):
#     lista={}
#     for i in range (0,largo+1):
#         lista[i]=[]
#
#     inicio=0
#     fin=largo
#     armar_lugares(grafo,lista,largo+1,origen,destino,inicio,fin)
#     visitar_lugares(grafo,lista,origen,0)
#
# def visitar_lugares(grafo,lista,origen,inicio,visitados=[]):
#     visitados.append(origen)
#
#     for adyacente in grafo.obtener_adyacentes(lista[inicio]):
#         if adyacente in lista[inicio+1] and not adyacente in visitados:
#             if visitar_lugares(grafo,lista,inicio+1):
#                 return lista
#
#     visitados.pop()
#
# def armar_lugares(grafo,lista, largo,origen,inicio,fin):
#
#     if largo%2 == 0:
#         if inicio== largo/2-1 and fin==largo/2:
#             if lista[inicio]==lista[fin]:
#                 return lista
#
#     else:
#         if inicio==fin and inicio==largo/2:
#             if lista[inicio]==lista[inicio-1]:
#                 return lista
#
#     #enlisto el origen al ppio y al fin
#     lista[inicio].append(origen)
#     lista[fin].append(origen)
#
#     for adyacente in grafo.obtener_adyacentes(origen):
#         if adyacente not in lista[inicio+1]:
#             armar_lugares(grafo,largo,adyacente,inicio+1,fin-1)
#
#     return []


# def nlugares(grafo,largo,origen, destino= None):
#     ruta = {}
#     if(destino==None):
#         destino=origen
#     for i in range 0:largo+1:
#         ruta[i]=[]
#     ruta[0].append(origen)
#     ruta[largo].append(origen)
#
#     # declaro funcion wrappeada
#     def _nlugares(origen, destino, largo, ruta=[]):
#         if ruta[largo]:
#             for adyacente in grafo.obtener_adyacentes(origen):
#                 if not adyacente in ruta[largo]
#                     ruta[largo].append(adyacente)
#         else:
#             if origen in ruta[largo]=grafo.obtener_adyacentes(origen):
#                 return True
#             return False
#
#         if largo==0:
#             if origen==destino:
#                 return True
#             else:
#                 ruta.pop()
#                 return False
#
#         for v in grafo.obtener_adyacentes(origen):
#             if not v in ruta:
#                 if _nlugares(v, destino, largo-1, ruta):
#                     return True
#
#         ruta.pop()
#         return False
#
#     # inicio recursion
#     _nlugares(origen, destino, largo-1, ruta)
#     return ruta

def pagerank (grafo,n=10,imprimir=False):
    """Obtiene el pagerank de un grafo y devuelve los n vertices mas importantes.
    n es pasado por parametro"""
    # armo un diccionario con el PR de cada nodo, seteado aleatorio ente 0 y 1
    PR={v: random() for v in grafo}
    dif=float("inf")

    d=0.8
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
    #Imprimo el pagerank y lo devuelvo
    if imprimir:
        print(','.join(map(str,sorted(PR, key=PR.get, reverse=True)[0:n])))
    return sorted(PR, key=PR.get, reverse=True)

class TestArmarCamino(TestCase):

    def setUp(self):
        """Test armar camino"""

    def test_distintos_origenes_no_dirigido(self):
        """Armar Dijstra en no dirigido"""

        grafito = Grafo()
        lista_vertices = ["A","B","C","D","F","H","I"]
        lista_aristas = [("A","B",5), ("B","F",1), ("C","A",7), ("D","F",6), ("A","F",8), ("C","D",8), ("H","I",1)]

        for k in lista_vertices:
            grafito.agregar_vertice(k)

        for a,b,peso in lista_aristas:
            grafito.agregar_arista(a,b,peso=peso, no_dirigido=True)

        pila_1=[]
        pila_2=[]
        pila_3=[]

        pila_A_destD=["A","B","F","D"]
        distancia_D, predecesores_D = dijkstra(grafito,origen="A",dest="D")
        armar_camino(distancia_D,predecesores_D,pila_1, "A", "D")

        pila_A_destF=["A","B","F"]
        distancia_F, predecesores_F = dijkstra(grafito,origen="A",dest="F")
        armar_camino(distancia_F,predecesores_F,pila_2, "A", "F")

        pila_D_destA=["D","F","B","A"]
        distancia_A, predecesores_A = dijkstra(grafito,origen="D",dest="A")
        armar_camino(distancia_A,predecesores_A,pila_3, "D", "A")

        self.assertEqual(pila_A_destD, pila_1, "Los caminos minimos A a D no coinciden")
        self.assertEqual(pila_A_destF, pila_2, "Los caminos A a F no coinciden")
        self.assertEqual(pila_D_destA, pila_3, "Los caminos minimos D a A no coinciden")

    def test_distintos_origenes_dirigido(self):
        """Armar Dijstra en dirigido"""

        grafito = Grafo()

        lista_vertices = ["A","B","C","D","F","H","I"]
        # aristas no dirigidas
        lista_aristas = [("A","B",5), ("C","A",7), ("A","F",8), ("D","F",6), ("C","D",8), ("H","I",1)]

        for k in lista_vertices:
            grafito.agregar_vertice(k)

        for a,b,peso in lista_aristas:
            grafito.agregar_arista(a,b,peso=peso, no_dirigido=True)

        # arista dirigida
        grafito.agregar_arista("B", "F", peso=1)

        pila_1=[]
        pila_2=[]
        pila_3=[]
        pila_4=[]
        pila_5=[]

        pila_A_destD=["A","B","F","D"]
        distancia_D, predecesores_D = dijkstra(grafito,origen="A",dest="D")
        armar_camino(distancia_D,predecesores_D,pila_1, "A", "D")

        pila_A_destF=["A","B","F"]
        distancia_F, predecesores_F = dijkstra(grafito,origen="A",dest="F")
        armar_camino(distancia_F,predecesores_F,pila_2, "A", "F")

        pila_D_destA=["D","F","A"]
        distancia_A, predecesores_A = dijkstra(grafito,origen="D",dest="A")
        armar_camino(distancia_A,predecesores_A,pila_3, "D", "A")

        pila_F_destC=["F","D","C"]
        distancia_C, predecesores_C = dijkstra(grafito,origen="F",dest="C")
        armar_camino(distancia_C,predecesores_C,pila_4, "F", "C")

        pila_F_destB=["F","A","B"]
        distancia_B, predecesores_B = dijkstra(grafito,origen="F",dest="B")
        armar_camino(distancia_B,predecesores_B,pila_5, "F", "B")

        self.assertEqual(pila_A_destD, pila_1, "Los caminos minimos A a D no coinciden")
        self.assertEqual(pila_A_destF, pila_2, "Los caminos A a F no coinciden")
        self.assertEqual(pila_D_destA, pila_3, "Los caminos minimos D a A no coinciden")
        self.assertEqual(pila_F_destC, pila_4, "Los caminos F a C no coinciden")
        self.assertEqual(pila_F_destB, pila_5, "Los caminos minimos F a B no coinciden")

    def test_distintos_origenes_no_dirigido2(self):
        """Armar Dijstra en no dirigido"""

        grafito = Grafo()
        lista_vertices = ["A","B","C","D","E","F"]
        lista_aristas = [("A","C",1), ("B","C",1), ("C","E",2), ("C","D",3), ("E","D",1), ("E","F",1), ("A","F",30)]

        for k in lista_vertices:
            grafito.agregar_vertice(k)

        for a,b,peso in lista_aristas:
            grafito.agregar_arista(a,b,peso=peso, no_dirigido=True)

        pila_1=[]
        pila_2=[]
        pila_3=[]
        pila_4=[]
        pila_5=[]
        pila_6=[]

        pila_A_destD=["A","C","D"]
        distancia_D, predecesores_D = dijkstra(grafito,origen="A",dest="D")
        armar_camino(distancia_D,predecesores_D,pila_1, "A", "D")

        pila_A_destF=["A","C","E","F"]
        distancia_F, predecesores_F = dijkstra(grafito,origen="A",dest="F")
        armar_camino(distancia_F,predecesores_F,pila_2, "A", "F")

        pila_D_destA=["D","C","A"]
        distancia_A, predecesores_A = dijkstra(grafito,origen="D",dest="A")
        armar_camino(distancia_A,predecesores_A,pila_3, "D", "A")

        pila_F_destC=["F","E","C"]
        distancia_C, predecesores_C = dijkstra(grafito,origen="F",dest="C")
        armar_camino(distancia_C,predecesores_C,pila_4, "F", "C")

        pila_F_destB=["F","E","C","B"]
        distancia_B, predecesores_B = dijkstra(grafito,origen="F",dest="B")
        armar_camino(distancia_B,predecesores_B,pila_5, "F", "B")

        pilaBA=["B","C","A"]
        distancia_BA, predecesores_BA = dijkstra(grafito,origen="B",dest="A")
        armar_camino(distancia_BA,predecesores_BA,pila_6, "B", "A")

        self.assertEqual(pila_A_destD, pila_1, "Los caminos minimos A a D no coinciden")
        self.assertEqual(pila_A_destF, pila_2, "Los caminos A a F no coinciden")
        self.assertEqual(pila_D_destA, pila_3, "Los caminos minimos D a A no coinciden")
        self.assertEqual(pila_F_destC, pila_4, "Los caminos F a C no coinciden")
        self.assertEqual(pila_F_destB, pila_5, "Los caminos minimos F a B no coinciden")

    def test_distintos_origenes_no_dirigido_competencia(self):
        """Armar Dijstra en no dirigido"""

        grafito = Grafo()
        lista_vertices = ["A","B","C","D","E"]
        lista_aristas = [("A","D",2), ("D","E",3), ("B","C",2), ("C","E",1)]

        for k in lista_vertices:
            grafito.agregar_vertice(k)

        for a,b,peso in lista_aristas:
            grafito.agregar_arista(a,b,peso=peso, no_dirigido=True)

        pila_1=[]
        pila_2=[]
        pila_3=[]
        pila_4=[]
        pila_5=[]
        pila_6=[]

        pila_A_destD=["A","D"]
        distancia_D, predecesores_D = dijkstra(grafito,origen="A",dest="D")
        armar_camino(distancia_D,predecesores_D,pila_1, "A", "D")

        pila_A_destE=["A","D","E"]
        distancia_E, predecesores_E = dijkstra(grafito,origen="A",dest="E")
        armar_camino(distancia_E,predecesores_E,pila_2, "A", "E")

        pila_D_destA=["D","A"]
        distancia_A, predecesores_A = dijkstra(grafito,origen="D",dest="A")
        armar_camino(distancia_A,predecesores_A,pila_3, "D", "A")

        pila_E_destC=["E","C"]
        distancia_C, predecesores_C = dijkstra(grafito,origen="E",dest="C")
        armar_camino(distancia_C,predecesores_C,pila_4, "E", "C")

        pila_E_destB=["E","C","B"]
        distancia_B, predecesores_B = dijkstra(grafito,origen="E",dest="B")
        armar_camino(distancia_B,predecesores_B,pila_5, "E", "B")

        pilaBA=[]
        distancia_BA, predecesores_BA = dijkstra(grafito,origen="B",dest="A")
        armar_camino(distancia_BA,predecesores_BA,pila_6, "B", "A")

        self.assertEqual(pila_A_destD, pila_1, "Los caminos minimos A a D no coinciden")
        self.assertEqual(pila_A_destE, pila_2, "Los caminos A a E no coinciden")
        self.assertEqual(pila_D_destA, pila_3, "Los caminos minimos D a A no coinciden")
        self.assertEqual(pila_E_destC, pila_4, "Los caminos E a C no coinciden")
        self.assertEqual(pila_E_destB, pila_5, "Los caminos minimos E a B no coinciden")

class TestPagerankNoDirigido(TestCase):
    """Creación del grafo no dirigido"""

    def setUp(self):
        self.grafito = Grafo()

        self.lista_vertices = ["A","B","C","D","BA","BB"]
        # aristas no dirigidas
        self.lista_aristas = [("A","B",1), ("A","C",1), ("A","D",1), ("B","BA",1), ("B","BB",1),("BB","C",0.1)]

        for k in self.lista_vertices:
            self.grafito.agregar_vertice(k)

        for a,b,peso in self.lista_aristas:
            self.grafito.agregar_arista(a,b,peso=peso, no_dirigido=True)

    def test_pagerank_grafo_no_dirigido(self):
        pg=pagerank(self.grafito)
        pagerank_ok= ['A', 'B', 'C', 'BB', 'D', 'BA']
        self.assertEqual(pg, pagerank_ok, f"Los pagerank coinciden")


class TestRecorridosNoDirigidos(TestCase):
    """ Prueba recorridos sobre el siguiente grafo no dirigido:
             A
             |
        -----------
       /     |      \
      B      C       E
    /  \     |       |
   D    F    G       |
        |____________|
    """
    def setUp(self):
        """Creación del grafo a utilizar en cada prueba de esta clase"""
        self.grafito = Grafo()
        self.lista_vertices = ["A","B","C","D","E","F","G"]
        self.lista_aristas = [("A","B"), ("B","D"), ("B","F"), ("F","E"), #
        ("A","C"),("C","G"), #
        ("A","E")]

        for k in self.lista_vertices:
            self.grafito.agregar_vertice(k)

        for a,b in self.lista_aristas:
            self.grafito.agregar_arista(a,b,no_dirigido=True)

    def test_recorridos_dfs(self):
        for padre in self.lista_vertices:
            # Corro el algoritmo arrancando por el vertice padre
            recorrido = dfs(self.grafito,padre)
            # Verifico que haya recorrido todos los vertices
            faltantes = [n for n in self.lista_vertices if not n in recorrido]
            error_help = f"{self.__doc__}\n Raiz: {padre}\n Aclanzables: {self.lista_vertices}\n Recorrido: {recorrido}\n"
            self.assertEqual(len(faltantes), 0, f"Falta recorrer vertices por DFS\n {error_help}")

            # Verifico cardinalidad por duplicados
            self.assertEqual(len(recorrido), len(self.lista_vertices), f"Sobran vertices al recorrer por DFS\n {error_help}")


    def test_recorridos_bfs(self):
        for padre in self.lista_vertices:
            # Corro el algoritmo arrancando por el vertice padre
            recorrido, p, d = bfs(self.grafito,padre)
            # Verifico que haya recorrido todos los vertices
            faltantes = [n for n in self.lista_vertices if not n in recorrido]
            error_help = f"{self.__doc__}\n Raiz: {padre}\n Aclanzables: {self.lista_vertices}\n Recorrido: {recorrido}\n"
            self.assertEqual(len(faltantes), 0, f"Falta recorrer vertices por BFS\n {error_help}")

            # Verifico cardinalidad por duplicados
            self.assertEqual(len(recorrido), len(self.lista_vertices), f"Sobran vertices al recorrer por BFS\n {error_help}")

class TestRecorridosDirigidos(TestCase):
    """ Prueba recorridos sobre el siguiente grafo dirigido:
             A
             v
        -----------
       v     v      v
      B      C       E
    v  v     v       ^
   D    F    G       |
        v____________|
    """
    def setUp(self):
        """Creación del grafo a utilizar en cada prueba de esta clase"""
        self.grafito = Grafo()
        self.lista_vertices = ["A","B","C","D","E","F","G"]
        self.lista_aristas = [("A","B"), ("B","D"), ("B","F"), ("F","E"), #
        ("A","C"),("C","G"), #
        ("A","E")]

        for k in self.lista_vertices:
            self.grafito.agregar_vertice(k)

        for a,b in self.lista_aristas:
            self.grafito.agregar_arista(a,b)

    def test_recorridos_dfs(self):
        tests = [ #(padre, lista de vertices alcanzables)
            ("A", {"A","B","C","D","E","F","G"}),
            ("B", {"B","D","F","E"}),
            ("D", {"D"}),
            ("F", {"F","E"}),
            ("C", {"C","G"}),
            ("G", {"G"}),
            ("E", {"E"})
        ]

        for padre, alcanzables in tests:
            # Corro el algoritmo arrancando por el vertice padre
            recorrido = dfs(self.grafito,padre)
            # Verifico que haya recorrido todos los vertices alcanzables
            faltantes = [n for n in alcanzables if not n in recorrido]
            error_help = f"{self.__doc__}\n Raiz: {padre}\n Aclanzables: {self.lista_vertices}\n Recorrido: {recorrido}\n"
            self.assertEqual(len(faltantes), 0, f"Falta recorrer vertices por DFS\n {error_help}")

            # Verifico cardinalidad por duplicados
            self.assertEqual(len(recorrido), len(alcanzables), f"Sobran vertices al recorrer por DFS\n {error_help}")

    def test_recorridos_bfs(self):
        tests = [ #(padre, lista de vertices alcanzables)
            ("A", {"A","B","C","D","E","F","G"}),
            ("B", {"B","D","F","E"}),
            ("D", {"D"}),
            ("F", {"F","E"}),
            ("C", {"C","G"}),
            ("G", {"G"}),
            ("E", {"E"})
        ]

        for padre, alcanzables in tests:
            # Corro el algoritmo arrancando por el vertice padre
            recorrido, p, d  = bfs(self.grafito,padre)
            # Verifico que haya recorrido todos los vertices alcanzables
            faltantes = [n for n in alcanzables if not n in recorrido]
            error_help = f"{self.__doc__}\n Raiz: {padre}\n Aclanzables: {self.lista_vertices}\n Recorrido: {recorrido}\n"
            self.assertEqual(len(faltantes), 0, f"Falta recorrer vertices por BFS\n {error_help}")

            # Verifico cardinalidad por duplicados
            self.assertEqual(len(recorrido), len(alcanzables), f"Sobran vertices al recorrer por BFS\n {error_help}")

class TestCaminoMinimo(TestCase):
    # WIP -- hacer
    def setUp(self):
        """Creación del grafo a utilizar en cada prueba de esta clase"""

    def test_nodirigido(self):
        """Dijstra en no dirigido"""

        grafito = Grafo()
        obtener_vertices = ["A","B","C","D","F","H","I"]
        lista_aristas = [("A","B",5), ("B","F",1), ("C","A",7), ("D","F",6), ("A","F",8), ("C","D",8), ("H","I",1)]

        for k in obtener_vertices:
            grafito.agregar_vertice(k)

        for a,b,peso in lista_aristas:
            grafito.agregar_arista(a,b,peso=peso, no_dirigido=True)


        pesos, padres = dijkstra(grafito,origen="A")

        pesos_ok = {'A': 0, 'B': 5.0, 'C': 7.0, 'D': 12.0, 'F': 6.0, 'H': float("inf"), 'I': float("inf")}
        padres_ok = {'A': None, 'B': 'A', 'C': 'A', 'F': 'B', 'D': 'F'}

        self.assertEqual(pesos, pesos_ok, "Los caminos minimos no coinciden")
        self.assertEqual(padres, padres_ok, "Los predecesores no coinciden")

    def test_dirigido(self):

        grafito = Grafo()

        obtener_vertices = ["A","B","C","D","F","H","I"]
        # aristas no dirigidas
        lista_aristas = [("A","B",5), ("C","A",7), ("A","F",8), ("D","F",6), ("C","D",8), ("H","I",1)]

        for k in obtener_vertices:
            grafito.agregar_vertice(k)

        for a,b,peso in lista_aristas:
            grafito.agregar_arista(a,b,peso=peso, no_dirigido=True)

        # arista dirigida
        grafito.agregar_arista("F", "B", peso=1)

        pesos,padres= dijkstra(grafito,origen="A")

        pesos_ok = {'A': 0, 'B': 5.0, 'C': 7.0, 'D': 14.0, 'F': 8.0, 'H': float("inf"), 'I': float("inf")}
        padres_ok = {'A': None, 'B': 'A', 'C': 'A', 'F': 'A', 'D': 'F'}

        self.assertEqual(pesos, pesos_ok, "Los caminos minimos no coinciden")
        self.assertEqual(padres, padres_ok, "Los predecesores no coinciden")

class TestObtenerCaminoMinimoOrigenDestino(TestCase):
    # WIP -- hacer
    def setUp(self):
        """Creación del grafo a utilizar en cada prueba de esta clase"""

    def test_distintos_origenes_no_dirigido_caminos_paralelos(self):

        """Armar Dijstra en no dirigido"""
        aeropuertos_por_ciudad={}
        aeropuertos_por_ciudad["Bs As"]=[]
        aeropuertos_por_ciudad["Bs As"].append("A")
        aeropuertos_por_ciudad["Bs As"].append("B")
        aeropuertos_por_ciudad["Cordoba"]=[]
        aeropuertos_por_ciudad["Cordoba"].append("E")

        grafito = Grafo()
        lista_vertices = ["A","B","C","D","E"]
        lista_aristas = [("A","D",2), ("D","E",3), ("B","C",2), ("C","E",1)]

        for k in lista_vertices:
            grafito.agregar_vertice(k)

        for a,b,peso in lista_aristas:
            grafito.agregar_arista(a,b,peso=peso, no_dirigido=True)

        costo_ok=3
        camino_ok=["B","C","E"]
        costo,camino=obtener_camino_minimo_origen_destino("Bs As","Cordoba",grafito,aeropuertos_por_ciudad,False)
        self.assertEqual(camino_ok, camino, "Los caminos no coinciden")
        self.assertEqual(costo_ok, costo, "Los costos no coinciden")

if __name__ == '__main__':
    unittest.main(verbosity=2)
