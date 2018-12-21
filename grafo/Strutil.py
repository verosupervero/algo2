from Grafo import Grafo
import warnings
import unittest
from unittest import TestCase
from collections import deque
import heapq












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
