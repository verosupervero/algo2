#!/usr/bin/env python
"""TP 3"""

from cmd import Cmd
import Strutil as st

class MyPrompt(Cmd):
    prompt = 'FlyCombi> '
    intro = "Interfaz de comandos de FlyCombi. Escriba listar_operaciones para ver operaciones disponibles."
    doc_header = "Lista de operaciones disponibles. Para ayuda, escriba help nombre_del_comando"
    undoc_header = "Operaciones no documentadas"
    misc_header = "Comandos generales del programa"

    def do_exit(self, inp):
        # Cualquier metodo de esta clase que haga return True termina el loop del menu
        print("Al toke perro.")
        return True

    def help_exit(self):
        print('Sale de la aplicación. Otras invocaciones: x q Ctrl-D.')

    # Alias para la fucion exit al llegar al final del archivo de comandos
    do_EOF = do_exit
    help_EOF = help_exit

    # Alias de la funcion exit para que este en español
    do_salir = do_exit
    help_salir = help_exit

    # ayuda
    def do_ayuda(self, inp):
        self.onecmd(f"help {inp}")

    def help_ayuda(self):
        print('Muestra informacion sobre el uso de un comando, usando "ayuda nombre_del_comando".\n\
Utilizando "help" a secas, lista los comandos disponibles. Es equivalente al comando ayuda.')

    # Ayuda del comando help, es decir, "help help" o "ayuda help"
    def help_help(self):
        print('Muestra informacion sobre el uso de un comando, usando "help nombre_del_comando".\n\
Utilizando ayuda a secas, lista los comandos disponibles. Es equivalente al comando help.')

    # Comandos desconocidos o personalizados
    def default(self, inp):
        """Metodo para cualquier comando no reconocido"""
        if inp == 'x' or inp == 'q':
            return self.do_exit(inp)

        print(f"Comando no reconocido: {inp}. Use listar_operaciones para ver una lista de comandos validos.")


    ######## COMANDOS DEL TP #########

    #### listar_operaciones: simplemente llama al comando interno "help"
    def help_listar_operaciones(self):
        print("Muestra una lista con las operaciones validas y otros comandos.")

    def do_listar_operaciones(self, inp):
        self.onecmd("help")

    #### camino_mas
    def help_camino_mas(self):
        print('Use "camino_mas rapido/barato,origen,destino"')

    def do_camino_mas(self, inp=""):
        """Obtengo el camino mas rapido o barato entre dos aeropuertos."""

        # Valido parametros y los parseo
        params = inp.split(',')
        if not len(params)==3:
            print("Cantidad de parametros invalida. Use ayuda camino_mas")
            return
        tipo = params[0]
        origen = params[1]
        destino = params[2]

        if not origen in aeropuertos_por_ciudad or not destino in aeropuertos_por_ciudad:
            print("Origen y/o destino inválidos")
            return

        # Dependiendo del tipo, llamo a cada funcion o devuelvo error
        if tipo == 'barato':
            st.obtener_camino_minimo_origen_destino(origen,destino,grafo_precio,aeropuertos_por_ciudad)
        elif tipo == 'rapido':
            st.obtener_camino_minimo_origen_destino(origen,destino,grafo_tiempo,aeropuertos_por_ciudad)
        else:
            print("Tipo de recorrido invalido. Use ayuda camino_mas")

    #### camino_mas
    def help_camino_escalas(self):
        print('Use "camino con menos escalas"')

    def do_camino_escalas(self, inp=""):
        """Obtengo el camino con menos escalas entre dos aeropuertos."""

        # Valido parametros y los parseo
        params = inp.split(',')
        if not inp or not len(params)==2:
            print("Cantidad de parametros invalida. Use ayuda camino_escalas")
            return
        origen = params[0]
        destino = params[1]

        if not origen in aeropuertos_por_ciudad or not destino in aeropuertos_por_ciudad:
            print("Origen y/o destino inválidos")
            return
        st.obtener_camino_minimo_origen_destino(origen,destino,grafo_vuelos,aeropuertos_por_ciudad)

        #grafo_vuelos.bfs(aeropuertos_por_ciudad[origen],aeropuertos_por_ciudad[destino])

    #### camino_mas
    def help_centralidad(self):
        print('Use centralidad')

    def do_centralidad(self, inp=""):
        """Obtengo la centralidad de un grafo"""

        # Valido parametros y los parseo
        params = inp.split(' ')
        if not len(params)==1:
            print("Cantidad de parametros invalida. Use ayuda centralidad")
            return
        n= int(params[0])

        grafo_vuelos.centralidad(n)

    #### camino_mas
    def help_vacaciones(self):
        print('Use vacaciones')

    def do_vacaciones(self, inp=""):
        """Obtengo vacaciones"""

        # Valido parametros y los parseo
        params = inp.split(',')
        if not len(params)==2:
            print("Cantidad de parametros invalida. Use ayuda vacaciones")
            return
        origen=params[0]
        n= int(params[1])

        st.obtener_viaje_n_lugares(n,origen,grafo_vuelos,aeropuertos_por_ciudad,imprimir=True)

    #### camino_mas
    def help_pagerank(self):
        print('Use pagerank')

    def do_pagerank(self, inp=""):
        """Obtengo el pagerank de un grafo"""

        # Valido parametros y los parseo
        params = inp.split(' ')
        if not len(params)==1:
            print("Cantidad de parametros invalida. Use ayuda pagerank")
            return
        n= int(params[0])

        grafo_vuelos.pagerank(n,True)

if __name__ == '__main__':
    # Leo los CSV
    import csv
    from Grafo import Grafo
    grafo_tiempo = Grafo()
    grafo_precio = Grafo()
    grafo_vuelos = Grafo()
    aeropuertos_por_ciudad={}
    # Agrego los vertices
    with open('aeropuertos_inventados.csv', newline='') as csvfile:
        aeropuertos = csv.reader(csvfile, delimiter=',')
        for ciudad, aeropuerto,latitud,longitud in aeropuertos: #aca me devuelve dos cosas no entiendo la queja
            #Agrego la ciudad de nombre y valor el codigo
            if not ciudad in aeropuertos_por_ciudad:
                aeropuertos_por_ciudad[ciudad]=[]
            aeropuertos_por_ciudad[ciudad].append(aeropuerto)

            #Agrego los vertices al grafo, son los codigos
            grafo_tiempo.agregar_vertice(aeropuerto)
            grafo_precio.agregar_vertice(aeropuerto)
            grafo_vuelos.agregar_vertice(aeropuerto)

    # Agrego las aristas
    with open('vuelos_inventados.csv', newline='') as csvfile:
        vuelos = csv.reader(csvfile, delimiter=',')
        for origen,destino, tiempo,precio,cant_vuelos_entre_aeropuertos in vuelos:
            grafo_tiempo.agregar_arista(origen,destino,int(tiempo),True)
            grafo_precio.agregar_arista(origen,destino,int(precio),True)
            grafo_vuelos.agregar_arista(origen,destino,1/int(cant_vuelos_entre_aeropuertos),True)

    # Cargo el menu
    MyPrompt().cmdloop()
