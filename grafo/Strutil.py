from Grafo import Grafo

"""Clase para representar y procesar grafos"""
import numpy as np
from scipy import sparse
import warnings

import unittest
from unittest import TestCase

from collections import deque

import heapq

def imprimir_camino(pila):
    print("->".join(map(str,pila)))

def armar_camino(distancia,predecesores,pila, origen, dest=None):
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

def obtener_camino_minimo_origen_destino(origen,dest,grafo,aeropuertos_por_ciudad,imprimir=True,pesado=True):
    camino=[]
    costo=float("inf")
    for aeropuerto_i in aeropuertos_por_ciudad[origen]:
        for aeropuerto_j in aeropuertos_por_ciudad[dest]:
            if pesado:
                distancia, predecesores= grafo.camino_minimo(aeropuerto_i,aeropuerto_j)
            else:
                distancia, predecesores= grafo.bfs(aeropuerto_i,aeropuerto_j)

            if distancia[aeropuerto_j]< costo:
                costo=distancia[aeropuerto_j]
                camino.clear()
                armar_camino(distancia,predecesores,camino,aeropuerto_i,aeropuerto_j)

    if imprimir:
        imprimir_camino(camino)
    return costo,camino

def obtener_viaje_n_lugares(n,origen,grafo,aeropuertos_por_ciudad,imprimir=True):
    ruta=[]
    for aeropuerto_i in aeropuertos_por_ciudad[origen]:
        for aeropuerto_j in aeropuertos_por_ciudad[origen]:
            ruta=grafo.nlugares(n,aeropuerto_i,aeropuerto_j)
            if ruta:
                break
    if not ruta:
        print("No se encontro recorrido")
    else:
        if imprimir:
            imprimir_camino(ruta)
    return ruta


class TestArmarCamino(TestCase):
    # WIP -- hacer
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
        distancia_D, predecesores_D = grafito.camino_minimo(origen="A",dest="D")
        armar_camino(distancia_D,predecesores_D,pila_1, "A", "D")

        pila_A_destF=["A","B","F"]
        distancia_F, predecesores_F = grafito.camino_minimo(origen="A",dest="F")
        armar_camino(distancia_F,predecesores_F,pila_2, "A", "F")

        pila_D_destA=["D","F","B","A"]
        distancia_A, predecesores_A = grafito.camino_minimo(origen="D",dest="A")
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
        distancia_D, predecesores_D = grafito.camino_minimo(origen="A",dest="D")
        armar_camino(distancia_D,predecesores_D,pila_1, "A", "D")

        pila_A_destF=["A","B","F"]
        distancia_F, predecesores_F = grafito.camino_minimo(origen="A",dest="F")
        armar_camino(distancia_F,predecesores_F,pila_2, "A", "F")

        pila_D_destA=["D","F","A"]
        distancia_A, predecesores_A = grafito.camino_minimo(origen="D",dest="A")
        armar_camino(distancia_A,predecesores_A,pila_3, "D", "A")

        pila_F_destC=["F","D","C"]
        distancia_C, predecesores_C = grafito.camino_minimo(origen="F",dest="C")
        armar_camino(distancia_C,predecesores_C,pila_4, "F", "C")

        pila_F_destB=["F","A","B"]
        distancia_B, predecesores_B = grafito.camino_minimo(origen="F",dest="B")
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
        distancia_D, predecesores_D = grafito.camino_minimo(origen="A",dest="D")
        armar_camino(distancia_D,predecesores_D,pila_1, "A", "D")

        pila_A_destF=["A","C","E","F"]
        distancia_F, predecesores_F = grafito.camino_minimo(origen="A",dest="F")
        armar_camino(distancia_F,predecesores_F,pila_2, "A", "F")

        pila_D_destA=["D","C","A"]
        distancia_A, predecesores_A = grafito.camino_minimo(origen="D",dest="A")
        armar_camino(distancia_A,predecesores_A,pila_3, "D", "A")

        pila_F_destC=["F","E","C"]
        distancia_C, predecesores_C = grafito.camino_minimo(origen="F",dest="C")
        armar_camino(distancia_C,predecesores_C,pila_4, "F", "C")

        pila_F_destB=["F","E","C","B"]
        distancia_B, predecesores_B = grafito.camino_minimo(origen="F",dest="B")
        armar_camino(distancia_B,predecesores_B,pila_5, "F", "B")

        pilaBA=["B","C","A"]
        distancia_BA, predecesores_BA = grafito.camino_minimo(origen="B",dest="A")
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
        distancia_D, predecesores_D = grafito.camino_minimo(origen="A",dest="D")
        armar_camino(distancia_D,predecesores_D,pila_1, "A", "D")

        pila_A_destE=["A","D","E"]
        distancia_E, predecesores_E = grafito.camino_minimo(origen="A",dest="E")
        armar_camino(distancia_E,predecesores_E,pila_2, "A", "E")

        pila_D_destA=["D","A"]
        distancia_A, predecesores_A = grafito.camino_minimo(origen="D",dest="A")
        armar_camino(distancia_A,predecesores_A,pila_3, "D", "A")

        pila_E_destC=["E","C"]
        distancia_C, predecesores_C = grafito.camino_minimo(origen="E",dest="C")
        armar_camino(distancia_C,predecesores_C,pila_4, "E", "C")

        pila_E_destB=["E","C","B"]
        distancia_B, predecesores_B = grafito.camino_minimo(origen="E",dest="B")
        armar_camino(distancia_B,predecesores_B,pila_5, "E", "B")

        pilaBA=[]
        distancia_BA, predecesores_BA = grafito.camino_minimo(origen="B",dest="A")
        armar_camino(distancia_BA,predecesores_BA,pila_6, "B", "A")

        self.assertEqual(pila_A_destD, pila_1, "Los caminos minimos A a D no coinciden")
        self.assertEqual(pila_A_destE, pila_2, "Los caminos A a E no coinciden")
        self.assertEqual(pila_D_destA, pila_3, "Los caminos minimos D a A no coinciden")
        self.assertEqual(pila_E_destC, pila_4, "Los caminos E a C no coinciden")
        self.assertEqual(pila_E_destB, pila_5, "Los caminos minimos E a B no coinciden")

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
