Implementación de la clase Grafo
================================

Existen diversas formas de modelar un grafo, tal vez la más común sea con
una lista de nodos, donde cada nodo posea una lista de todos aquellos hijos
que posea.

Las ventajas de una lista es que agregar nodos y aristas resulta trivial, aunque
no tanto encontrar los padres de un nodo. Por esta razón al eliminar se debería
recorrer todos los nodos buscando las referencias al nodo eliminado para sacarlas.

Una forma matemáticamente elegante de representar un grafo es a través de
su matriz de adyacencias. En estas, el elemento (i,j) representa la conexión
desde el nodo i hacia el nodo j. Generalmente 0 si no están conectados y 1 si
lo están, o cualquier otro número positivo que represente algún peso.

Por lo general, a menos que un grafo esté extraordinariamente poblado
de aristas, es de esperarse una gran cantidad de elementos nulos y unas
pocas conexiones, por lo cual la mayor parte del espacio se gastaría en
almacenar ceros que no guardan información.

Eliminar el nodo i-ésimo implicaría eliminar la fila y la columna i-ésima, y
agregar un nodo implicaría agregar una nueva fila y columna a la matriz.
Las matrices suelen almacenarse como un gran vector donde cada columna
(o fila) está concatenada a la siguiente, por lo cual relizar estas operaciones
requeriría realizar una copia de todos los elementos a una nueva posición
en memoria.

Por estas cuestiones y otras más, no suele ser una buena idea almacenar un
grafo como una matriz (pensando en un array en memoria), a menos que se utilice
una matriz dispersa (o "sparse").

Matriz dispersa
---------------

Las matrices con grandes cantidades de cero aparecen mucho al trabajar con
sistemas y datos de la vida real, por lo cual, biblioteca algebráica que
se respete debe implementar alguna clase de matriz dispersa que permita manejar
tales situaciones.

La idea básica de una matriz dispersa es almacenar solamente los elementos
no nulos de la matriz. `SciPy <https://www.scipy.org/>`_ posee
`varias implementaciones <https://docs.scipy.org/doc/scipy/reference/sparse.html>`_
de matrices dispersas, cada una con sus ventajas y desventajas.

A grandes razgos, la compresión CSC y CSR consiste en concatenar las columnas
o filas (respectivamente) de la matriz, y eliminar los bloques de ceros. Esto
permite tener en regiones contiguas de memoria toda la información relevante.
Sin embargo, *redimensionar la matriz es igual de contraproducente que con
matrices normales*. DIA es similar, pero tomando las diagonales de la matriz.

Por otro lado, COO y DOK almacenan el dato y sus coordenadas, la primera
usando una lista y la segunda un diccionario. La diferencia es que COO permite
entradas repetidas (que se suman), y DOK perminte acceder en tiempo O(1) a los
datos. *En estas redimensionar una matriz puede hacerse de forma muy eficiente.*

Implementación
---------------

Por lo dicho anteriormente, la clase Grafo se implementó sobre una matriz
dispersa de la clase DOK de SciPy.
Para almacenar los nombres de los nodos, se utilizó un diccionario donde
las claves corresponden a los nombres de los nodos y su valor, a su índice
(es decir, el número de fila y columna respectiva en la matriz).

Al eliminar un nodo, para eliminar una fila y una columna sería necesario
readecuar el resto de los índices en el diccionario interno de la matriz, por
lo cual sería una operación O(catidad de vertices). **Nota:** Si bien puede que no
se realice in-place, duplicar la matriz también es una operacion O(vertices)
y no O(nodos^2).

Por este motivo, al eliminar un nodo se borran la fila y columna correspondientes
--asignandoles el valor 0, lo cual es O(nodos)--, y se retira el nombre
del diccionario, lo cual es O(1).
Dado que los ceros no ocupan espacio, no se está almacenando información trivial
en la matriz y de esta forma se puede realizar una eliminación más económica
en la mayoría de los casos.

De todas formas, se implementa el método ``_compactar()`` que hace lo anteriormente
dicho, a fin de poder obtener la matriz de adyacencia "real" si el usuario
la requiere.
