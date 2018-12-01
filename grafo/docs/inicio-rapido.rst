Inicio Rápido
==============

En esta sección se describe velozmente cómo utilizar un TDA Grafo. Para detalles
sobre los métodos de la clase y sus particularidades ver la sección
Documentación.

Detalles importantes
--------------------

La clase Grafo representa un grafo no dirigido, con pesos en las aristas
no negativos. Posee métodos para insertar y eliminar nodos y aristas
fácilmente.

Utilizamos los nombres "padre" e "hijo" para designar las relaciones entre
nodos de una forma visual. Si el nodo A se enlaza al nodo B, decimos que A
es el padre de B. Si el nodo A se enlaza con el B y a su vez, también el
B enlaza con el A, ambos son padre e hijo del otro a la vez.

Árbol genealógico
-----------------

A continuación se utiliza un Grafo para armar un árbol genealógico::

  >> from Grafo import grafo

  >> grafito = Grafo()
  >> grafito.agregar_nodo("jjose")
  >> grafito.agregar_nodo("vero")
  >> grafito.agregar_nodo("naty")
  >> grafito.agregar_nodo("cone")
  >> grafito.agregar_arista("jjose","vero")
  >> grafito.agregar_arista("jjose","naty")
  >> grafito.agregar_arista("vero","cone")

  >> grafito.listar_hijos("jjose")
  ["vero","naty"]

  >> grafito.listar_hijos("vero")
  ["cone"]

  >> grafito.listar_hijos("naty")
  []

Perdiendo todo el sentido de árbol genealógico, se puede armar un loop::

  >> grafito.agregar_arista("cone", "jjose")
