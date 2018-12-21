#!/usr/bin/env python
"""TP 3"""

# Agrego carpeta raiz a path, asi los modulos se ven
import sys
sys.path.insert(1, '.')


from cmd import Cmd
from Grafo import Grafo
import Grafo.utils as utils
import FCombi

class MyPrompt(Cmd):
    prompt = ''
    intro = ""
    doc_header = ""
    undoc_header = ""
    misc_header = ""

    def do_exit(self, inp):
        # Cualquier metodo de esta clase que haga return True termina el loop del menu
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
        """Lista las operaciones disponibles"""
        # comandos que quiero evitar
        excluir = ['do_EOF', 'do_exit', 'do_salir', 'do_ayuda', 'do_help', 'do_listar_operaciones', ]
        ops = {x.split("do_")[1] for x in dir(self) if "do_" in x and x not in excluir}
        for x in ops:
            print(x)

    #### camino_mas
    def help_camino_mas(self):
        print('Use "camino_mas <rapido/barato>,<ciudad origen>,<ciudad destino>"')

    def do_camino_mas(self, inp=""):
        """Obtengo el camino mas rapido o barato entre dos ciudades."""

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
            costo, camino = FCombi.camino_minimo(origen,destino,grafo_precio,aeropuertos_por_ciudad)
        elif tipo == 'rapido':
            costo, camino = FCombi.camino_minimo(origen,destino,grafo_tiempo,aeropuertos_por_ciudad)
        else:
            print("Tipo de recorrido invalido. Use ayuda camino_mas")


        # Imprimo resultado
        utils.imprimir_camino(camino)

        # Guardo para exportar
        self.ultima_ruta = camino

    #### camino_escalas
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
            #print("Origen y/o destino inválidos") #no imprimir en error?
            return

        # Calculo
        costo,camino = FCombi.camino_minimo(origen,destino,grafo_vuelos,aeropuertos_por_ciudad,pesado=True)

        # Si no estan conectados
        if not camino:
            print("No existe ninguna ruta.")

        # Imprimo resultado
        utils.imprimir_camino(camino)

        # Guardo para exportar
        self.ultima_ruta = camino


    #### centralidad
    def help_centralidad(self):
        print('Use centralidad')

    def do_centralidad(self, inp=""):
        #     print(','.join(map(str,sorted(centralidad, key=centralidad.get, reverse=True)[0:cantidad_aeropuertos])))
        """Obtengo la centralidad de un grafo"""

        # Valido parametros y los parseo
        params = inp.split(' ')
        if not len(params)==1:
            print("Cantidad de parametros invalida. Use ayuda centralidad")
            return
        try:
            n= int(params[0])
        except:
            print("El parametro debe ser un número entero")

        centralidad = utils.centralidad(grafo_vuelos,n)

    # #### itinerario
    # def help_itinerario(self):
    #     print('No info here')
    #
    # def do_itinerario(self, inp=","):
    #     """Devuelvo un itinerario cultural"""
    #
    #     # Valido parametros y los parseo
    #     itinerario = inp.split(' ')
    #     if not len(lugares)==1:
    #         print("Cantidad de parametros invalida. Use ayuda centralidad")
    #         return
    #     lugares=utils.armar_itinerario_cultural(itinerario)
    #     utils.obtener_itinerario_cultural(grafo_vuelos,lugares,aeropuertos_por_ciudad)

    #### vacaciones
    def help_vacaciones(self):
        print('Use: vacaciones ciudad,<cantidad de escalas>')

    def do_vacaciones(self, inp=""):
        """Obtengo vacaciones"""

        # Valido parametros y los parseo
        params = inp.split(',')
        if not len(params)==2:
            print("Cantidad de parametros invalida. Use ayuda vacaciones")
            return
        origen=params[0]
        n= int(params[1])
        ruta = FCombi.viaje_n_lugares(grafo=grafo_tiempo,n=n,origen=origen,aeropuertos_por_ciudad=aeropuertos_por_ciudad)
        if not ruta:
            print('No existe ningún recorrido')
        else:
            print(utils.formatear_camino(ruta))
            self.ultima_ruta = ruta

    #### camino_mas
    def help_pagerank(self):
        print('Use pagerank <cantidad de nodos>')

    def do_pagerank(self, inp=""):
        """Obtengo el pagerank de un grafo"""

        # Valido parametros y los parseo
        try:
            params = inp.split(' ')
            n= int(params[0])
        except:
            print("Parámetros inválidos. Use ayuda pagerank")
            return

        # calculo
        PR = utils.pagerank(grafo_vuelos)

        # devuelvo
        print(','.join(map(str,PR[0:n])))


    ### exportar a KML
    def help_exportar_kml(self):
        print("Use exportar_kml <nombre_archivo.kml> para guardar el último camino obtenido en un kml.")

    def do_exportar_kml(self, inp=""):
        """Exporto un KML con la ultima ruta"""

        # Valido parametros y los parseo
        params = inp.split(' ')
        if not len(params)==1:
            print("Cantidad de parametros invalida. Use ayuda exportar_kml")
            return
        file = params[0]

        if not self.ultima_ruta:
            return

        FCombi.exportar_kml(self.ultima_ruta, coordenadas, ciudades_aerop, file=file)
        print("OK")

    def do_test_kml(self, inp=""):
        # Simulo un resultado
        caminito = ['JFK', 'ABY', 'BRD', 'DIK']
        print (utils.formatear_camino(caminito))

        # Seteo el resultado en la variable para exportar_kml
        self.ultima_ruta = caminito
        return

if __name__ == '__main__':
    # Leo los CSV
    import sys
    import csv
    from Grafo import Grafo
    import FCombi

    if not len(sys.argv) == 3:
        print(f"Se requieren tres parametros: {sys.argv[0]} aeropuertos.csv vuelos.csv")
        sys.exit(1)

    path_aeropuertos = sys.argv[1]
    path_vuelos = sys.argv[2]

    grafo_tiempo = Grafo()
    grafo_precio = Grafo()
    grafo_vuelos = Grafo()
    aeropuertos_por_ciudad={}
    ciudades_aerop = {}
    coordenadas = {}
    # Agrego los vertices
    with open(path_aeropuertos, newline='') as csvfile:
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

            # agrego coordenadas
            coordenadas[aeropuerto]=(float(longitud),float(latitud))
            # agrego cuidades
            ciudades_aerop[aeropuerto]=ciudad

    # Agrego las aristas
    with open(path_vuelos, newline='') as csvfile:
        vuelos = csv.reader(csvfile, delimiter=',')
        for origen,destino, tiempo,precio,cant_vuelos_entre_aeropuertos in vuelos:
            grafo_tiempo.agregar_arista(origen,destino,int(tiempo),True)
            grafo_precio.agregar_arista(origen,destino,int(precio),True)
            grafo_vuelos.agregar_arista(origen,destino,1/int(cant_vuelos_entre_aeropuertos),True)

    # Cargo el menu
    MyPrompt().cmdloop()

    # Termino
    sys.exit(0)
