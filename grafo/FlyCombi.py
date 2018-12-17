#!/usr/bin/env python
"""TP 3"""

from cmd import Cmd

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
        if not inp or not len(params)==3:
            print("Cantidad de parametros invalida. Use ayuda camino_mas")
            return
        tipo = params[0]
        origen = params[1]
        destino = params[2]

        if ciudades_codigo.has_key(origen)==False or ciudades_codigo.has_key(destino)==False:
            print("Origen y/o destino inválidos")
            return

        # Dependiendo del tipo, llamo a cada funcion o devuelvo error
        if tipo == 'barato':
            grafo_precio.camino_minimo(ciudades_codigo[origen],ciudades_codigo[destino])

        elif tipo == 'rapido':
            grafo_tiempo.camino_minimo(ciudades_codigo[origen],ciudades_codigo[destino])
        else:
            print("Tipo de recorrido invalido. Use ayuda camino_mas")

    #### camino_mas
    def help_camino_escalas(self):
        print('Use "camino con menos escalas"')

    def do_camino_escalas(self, inp=""):
        """Obtengo el camino con menos escalas entre dos aeropuertos."""

        # Valido parametros y los parseo
        params = inp.split(',')
        if not inp or not len(params)==3:
            print("Cantidad de parametros invalida. Use ayuda camino_escalas")
            return
        tipo = params[0]
        origen = params[1]
        destino = params[2]

        if ciudades_codigo.has_key(origen)==False or ciudades_codigo.has_key(destino)==False:
            print("Origen y/o destino inválidos")
            return

        # Dependiendo del tipo, llamo a cada funcion o devuelvo error
        if tipo == 'camino_escalas':
            grafo_escalas.camino_minimo(ciudades_codigo[origen],ciudades_codigo[destino])
        else:
            print("Tipo de recorrido invalido. Use ayuda camino_escalas")


if __name__ == '__main__':
    # Leo los CSV
    import csv
    from Grafo import Grafo
    grafo_tiempo = Grafo()
    grafo_precio = Grafo()
    grafo_vuelos = Grafo()
    grafo_escalas= Grafo()
    ciudades_codigo={}
    # Agrego los vertices
    with open('aeropuertos.csv', newline='') as csvfile:
        aeropuertos = csv.reader(csvfile, delimiter=',')
        for dato in aeropuertos:
            #Agrego la ciudad de nombre y valor el codigo
            diccionario_ciudades_codigo[dato[0]]=dato[1]

            #Agrego los vertices al grafo, son los codigos
            grafo_tiempo.agregar_vertice(dato[1])
            grafo_precio.agregar_vertice(dato[1])
            grafo_vuelos.agregar_vertice(dato[1])

    # Agrego las aristas
    with open('vuelos.csv', newline='') as csvfile:
        vuelos = csv.reader(csvfile, delimiter=',')
        for dato in vuelos:
            grafo_tiempo.agregar_arista(dato[0],dato[1],dato[2])
            grafo_precio.agregar_arista(dato[0],dato[1],dato[3])
            grafo_vuelos.agregar_arista(dato[0],dato[1],dato[4])
            grafo_escalas.agregar_arista(dato[0],dato[1])


    # Cargo el menu
    MyPrompt().cmdloop()
