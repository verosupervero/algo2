def exportar_kml(ciudades, coordenadas, ciudades_aerop, file=None, kml=None):
    """Recibe una lista de cuidades y las agrega al kml pasado"""

    icon = 'http://maps.google.com/mapfiles/kml/shapes/placemark_circle.png'

    if not kml:
        kml = simplekml.Kml()

    # Trayectos
    for idx in range(0, len(ciudades)-1):
        orig = ciudades[idx]
        dest = ciudades[idx+1]
        ls = kml.newlinestring(name=f"{orig}->{dest}")
        ls.coords = [coordenadas[orig], coordenadas[dest]]
        ls.altitudemode = simplekml.AltitudeMode.relativetoground
        ls.extrude = 1

    # Marcadores
    for x in ciudades:
        pnt = kml.newpoint(name=x, coords=[coordenadas[x]])
        if ciudades_aerop:
            pnt.style.balloonstyle.text = f"{x} - {ciudades_aerop[x]}"
        else:
            pnt.style.balloonstyle.text = x
        pnt.style.balloonstyle.bgcolor = simplekml.Color.lightgreen
        pnt.style.balloonstyle.textcolor = simplekml.Color.rgb(0, 0, 255)

    if file:
      return kml.save(file)
    return
