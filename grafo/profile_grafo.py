from Grafo import Grafo
import time
import math
import numpy as np

def profile_agregar_vertice(largo_lote=100, cant_lotes=100):
    grafito = Grafo()

    tiempos = []
    for nlote in range(0, cant_lotes):
        tic = time.perf_counter()
        for n in range(0,largo_lote):
            grafito.agregar_vertice(f"V_{nlote}_{n}")

        toc = time.perf_counter()-tic
        tiempos.append(toc)

    return tiempos

def profile_agregar_arista(cant_nodos_grafo=300, cant_aristas=800):
    grafito = Grafo()

    for n in range(0,cant_nodos_grafo):
        grafito.agregar_vertice(f"V_{n}")

    # obtengo cant_aristas coordenadas aleatorias del grafo
    x = (np.random.permutation(cant_nodos_grafo))[0:cant_aristas]

    tiempos = []
    cant_lotes = 20
    for nlote in range(0, cant_lotes):
        tic = time.perf_counter()
        for n in (np.random.permutation(cant_nodos_grafo))[0:30]:
            for j in (np.random.permutation(cant_nodos_grafo))[0:30]:
                grafito.agregar_arista(f"V_{x[n]}", f"V_{j}", n)

        toc = time.perf_counter()-tic
        tiempos.append(toc)

    return tiempos
