from Grafo import Grafo

grafito = Grafo()
grafito.agregar_nodo("A")
grafito.agregar_nodo("B")
grafito.agregar_nodo("C")
grafito.agregar_nodo("D")
grafito.agregar_arista("jjose","vero")
grafito.agregar_arista("jjose","naty")
grafito.agregar_arista("vero","cone")

print("====== BFS ======")
grafito.bfs("jjose")

print("====== DFS ======")
grafito.bfs("jjose")
