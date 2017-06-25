#encoding: utf-8

# Importe a mansalva, revisar
import os #listdir, path.joi
import subprocess # Popen, communicate
import filecmp # cmp
import argparse
import random
import subprocess
import time
import sys
import random
import math


ejecutable_tiempos_exacta = "./tiempoExacta"
ejecutable_tiempos_greedy = "./tiempoGreedy"
ejecutable_tiempos_local = "./tiempoLocal"
ejecutable_tiempos_grasp = "./tiempoGrasp"

# InputFile donde se van a guardar cada instancia que se ejecute
input_path_tmp = "./experimentos/input.tmp"

repeticiones = 1
n_max = 26 # Aumentar

ejecutables = [
    ejecutable_tiempos_exacta,
    ejecutable_tiempos_greedy,
    ejecutable_tiempos_local,
    ejecutable_tiempos_grasp
]

def generar_lista_outs(ejecutables, porc):
    a = []
    csv = ""

    if (porc == 25):
        csv = "random_aristas_25.csv"
    elif (porc == 50):
        csv = "random_aristas_50.csv"
    elif (porc == 75):
        csv = "random_aristas_75.csv"
    elif (porc == 100):
        csv = "completo.csv"
    else:
        print("ERROR")

    if (ejecutable_tiempos_exacta in ejecutables):
        a.append("./experimentos/exacta/" + csv)
    if (ejecutable_tiempos_greedy in ejecutables):
        a.append("./experimentos/greedy/" + csv)
    if (ejecutable_tiempos_local in ejecutables):
        a.append("./experimentos/local/" + csv)
    if (ejecutable_tiempos_grasp in ejecutables):
        a.append("./experimentos/grasp/" + csv)

    return a


# random25
csv_random25 = generar_lista_outs(ejecutables, 25)
n_max_random25 = n_max
tipo_random25 = "RANDOM_ARISTAS_25"

# random50
csv_random50 = generar_lista_outs(ejecutables, 50)
n_max_random50 = n_max
tipo_random50 = "RANDOM_ARISTAS_50"

# random75
csv_random75 = generar_lista_outs(ejecutables, 75)
n_max_random75 = n_max
tipo_random75 = "RANDOM_ARISTAS_75"

# completo
csv_completo = generar_lista_outs(ejecutables, 100)
n_max_completo = n_max
tipo_completo = "GRAFO_COMPLETO"


# Para valores existe Random y costo Random
def save_input(f, n, todas_las_aristas, porcentaje_aristas):
    f.write(str(n) + ' ')

    # Todas las aristas
    if (porcentaje_aristas == 100):
        f.write(str(int(n*(n-1)/2)) + '\n')
        for i in range(1, n+1):
            for j in range(i+1, n+1):
                f.write(str(i) + " " + str(j) + '\n')

        return

    else:
        # De todas las aristas posibles, tomo porcentaje_aristas%
        # Escribo el tamaño de esto, y luego todos los elementos
        cantidad_a_tomar = math.ceil((porcentaje_aristas*(n*(n-1))/2)/100)
        aristas = random.sample(todas_las_aristas, cantidad_a_tomar)

        f.write(str(len(aristas)) + '\n')
        for e in aristas:
            f.write(str(e[0]) + " " + str(e[1]) + '\n')


# Genera un input del tipo en input_tmp de tamaño n
def generate_input(tipo, n, todas_las_aristas):
    # aca guardo un input random en input_tmp de tamaño n
    with open(input_path_tmp, 'w') as f:
        if tipo == tipo_completo:
            save_input(f, n, todas_las_aristas, 100)
        elif tipo == tipo_random75:
            save_input(f, n, todas_las_aristas, 75)
        elif tipo == tipo_random50:
            save_input(f, n, todas_las_aristas, 50)
        elif tipo == tipo_random25:
            save_input(f, n, todas_las_aristas, 25)
        else:
            sys.exit("Tipo invalido en generacion de input")


# Experimentacion generica, el input es lo que varia dependiendo de los parametros que se le pasen
# CSV_FILENAMES = [EXACTA, GREEDY]

def experimentar(csv_filenames, n_max, tipo):
    global ejecutables

    # Guardar encabezado de csv
    for csv_filename in csv_filenames:
        with open(csv_filename, 'w') as csv :
            csv.write("n,fronteraMax,tamClique,tiempo" + '\n')

    # Para cada tamaño de n
    for n in range(3, n_max):

        # TODO:
        # Posible optimizacion: en vez de generar toda la lista para cada n, solo agrgar los nuevos
        todas_las_aristas = [(i, j) for i in range(1, n+1) for j in range(i+1, n+1)]

        print(tipo + " - n actual: " + str(n))

        # Para cada repes_random de cada tamaño
        for repe in range(repeticiones):

            # Generar el input falopa en un input_tmp
            generate_input(tipo, n, todas_las_aristas)

            # Correr ejecutable con el input falopa
            # Guarda tiempo en output, ignora stderr (Python3!)

            for i in range(len(csv_filenames)):
                with open(input_path_tmp) as input_file:
                    leyo = True
                    try:
                        tiempo_y_output = subprocess.check_output(
                                    [ejecutables[i]], stdin=input_file, stderr=subprocess.DEVNULL
                                ).decode(sys.stdout.encoding)
                    except:
                        print("ups")
                        leyo = False
                if (leyo):
                    # Guardar en un csv
                    # Cada linea: n,tiempo_y_output = n,fronteraMax,tamClique,tiempo
                    # csv_filenames = [EXACTA, GREEDY]
                    with open(csv_filenames[i], 'a') as csv :
                        csv.write(str(n) + "," + tiempo_y_output + '\n')



if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument("-todos", help="TODOS LOS EXPERIMENTOS", action='store_true')
    parser.add_argument("-random_25", help="Aristas random 25perc", action='store_true')
    parser.add_argument("-random_50", help="Aristas random 50perc", action='store_true')
    parser.add_argument("-random_75", help="Aristas random 75perc", action='store_true')
    parser.add_argument("-completo", help="Grafo completo, todas las aristas", action='store_true')

    args = parser.parse_args()

    if not len(sys.argv) > 1:
        sys.exit("No arguments passed! Use -h flag for help")

    if args.todos:
        experimentar(csv_random25, n_max_random25, tipo_random25)
        experimentar(csv_random50, n_max_random50, tipo_random50)
        experimentar(csv_random75, n_max_random75, tipo_random75)
        experimentar(csv_completo, n_max_completo, tipo_completo)

    else:
        if args.random_25:
            experimentar(csv_random25, n_max_random25, tipo_random25)
        if args.random_50:
            experimentar(csv_random50, n_max_random50, tipo_random50)
        if args.random_75:
            experimentar(csv_random75, n_max_random75, tipo_random75)
        if args.completo:
            experimentar(csv_completo, n_max_completo, tipo_completo)
