    def nlugares(self,largo,origen, destino= None):
        ruta = []
        calculado = {}
        if(destino==None):
            destino=origen

        # declaro funcion wrappeada
        def _nlugares(largo, origen, destino, ruta=[]):
            if destino in calculado:
                # previamente calculado
                if largo in calculado[destino]:
                    res = calculado[destino][largo]
                    if res == False:
                        return False
                    else:
                        for i in res:
                            ruta.append(i)
                            return True
            else:
                # realizo el calculo
                ruta.append(origen)
                if largo==0: # caso base
                    if origen==destino:
                        return True
                    else:
                        ruta.pop()
                        return False

                for v in self.obtener_adyacentes(origen):
                    if not v in ruta:
                        haycamino = _nlugares(origen=v, destino=destino, largo=largo-1, ruta=ruta)
                        # guardo en memoria el resultado
                        if not destino in calculado:
                            calculado[destino] = {} # creo posicion

                        if haycamino:
                            calculado[destino][largo] = ruta
                            return True
                        else:
                            calculado[destino][largo] = False

                ruta.pop()
                return False

        # inicio recursion
        _nlugares(origen=origen, destino=destino, largo=largo, ruta=ruta)
        return ruta
