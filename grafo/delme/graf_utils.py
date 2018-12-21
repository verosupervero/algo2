
from Grafo import Grafo
import numpy as np
from scipy import sparse
import warnings

import unittest
from unittest import TestCase

from collections import deque

import heapq

def obtener_camino_minimo_origen_destino2(origenes,destinos,grafo,imprimir=True):
    camino=[]
    mejor_costo=float("inf")
    mejor_origen = None
    mejor_destino = None
    mejor_predecesores = None
    for origen in origenes:
        for destino in destinos:
            distancia, predecesores = grafo.camino_minimo(aeropuerto_i,aeropuerto_j)
            if distancia < mejor_costo:
                mejor_origen = origen
                mejor_destino = destino
                mejor_costo = distancia
                mejor_predecesores = predecesores

    return mejor_costo, armar_camino_de_predecesores(mejor_predecesores)

def armar_camino_de_predecesores(dest, predecesores):
    pila = []
    pila.append(dest)
    while predecesores[pila[0]]:
        pila.insert(0, predecesores[pila[0]])

    return pila
