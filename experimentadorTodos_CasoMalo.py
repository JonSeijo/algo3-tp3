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

# InputFile donde se van a guardar cada instancia que se ejecute
input_path_tmp = "./experimentos/input.tmp"

repeticiones = 1

csv_exacta = "./experimentos/exacta/grafo_malo.csv"
csv_greedy = "./experimentos/greedy/grafo_malo.csv"
csv_local = "./experimentos/local/grafo_malo.csv"
csv_grasp = "./experimentos/grasp/grafo_malo.csv"

n_exacta = 31
n_greedy = 61
n_local = 61
n_grasp = 61

nodos = [x for x in range(15)]
grafo_malo_incial = [
    (0, 1), (1, 2), (2, 3),
    (0, 4), (0, 5), (0, 6), (0, 7), (0, 8),
    (2, 9), (2, 10), (2, 11),
    (3, 12), (3, 13), (3, 14)
]
grafo_malo = list(grafo_malo_incial)

# Para valores existe Random y costo Random
def save_input(f, n):
    f.write(str(n) + ' ')
    f.write(str(len(grafo_malo)) + '\n')
    for arista in grafo_malo:
        v1 = nodos[arista[0]] + 1
        v2 = nodos[arista[1]] + 1
        f.write(str(v1) + " " + str(v2) + '\n')


# Genera un input del tipo en input_tmp de tamaño n
def generate_input(n):
    # aca guardo un input random en input_tmp de tamaño n
    with open(input_path_tmp, 'w') as f:
        save_input(f, n)

# Experimentacion generica, el input es lo que varia dependiendo de los parametros que se le pasen
# CSV_FILENAMES = [EXACTA, GREEDY]

def experimentar(csv_filenames, ejecutables, n_max):
    global nodos
    global grafo_malo
    # Guardar encabezado de csv
    for csv_filename in csv_filenames:
        with open(csv_filename, 'w') as csv:
            csv.write("n,fronteraMax,tamClique,tiempo" + '\n')

    # Para cada tamaño de n
    for k in range(((n_max - 15) // 3) + 1):
        n = 3*k + 15
        print("- n actual: " + str(n))

        # Para cada repes_random de cada tamaño
        for repe in range(repeticiones):
            print("pasame la repe: " + str(repe))

            # Generar el input falopa en un input_tmp
            random.shuffle(nodos)
            generate_input(n)

            for i in range(len(csv_filenames)):
                # Correr ejecutable con el input falopa
                # Guarda tiempo en output, ignora stderr (Python3!)
                # for i in range(len(csv_filenames)):
                with open(input_path_tmp) as input_file:
                    tiempo_y_output = subprocess.check_output(
                                [ejecutables[i]], stdin=input_file, stderr=subprocess.DEVNULL
                            ).decode(sys.stdout.encoding)

                # Guardar en un csv
                # Cada linea: n,tiempo_y_output = n,fronteraMax,tamClique,tiempo
                # csv_filenames = [EXACTA, GREEDY]
                with open(csv_filenames[i], 'a') as csv :
                    csv.write(str(n) + "," + tiempo_y_output + '\n')



        nodos += [n, n+1, n+2]
        grafo_malo += [(0, n), (2, n+1), (3, n+2)]


if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument("-exacto", help="Exacto", action='store_true')
    parser.add_argument("-greedy", help="Greedy", action='store_true')
    parser.add_argument("-local", help="Local", action='store_true')
    parser.add_argument("-grasp", help="Grasp", action='store_true')
    parser.add_argument("-todos", help="TODOS LOS EXPERIMENTOS", action='store_true')

    args = parser.parse_args()

    if not len(sys.argv) > 1:
        sys.exit("No arguments passed! Use -h flag for help")

    if args.todos:
        # @DEBUG
        # AGREGAR LOS DEMAS TIPOS CUANDO ESTEN LISTOS
        experimentar([csv_exacta, csv_greedy], [ejecutable_tiempos_exacta, ejecutable_tiempos_greedy], n_exacta)

    else:
        if args.exacto:
            experimentar([csv_exacta], [ejecutable_tiempos_exacta], n_exacta)
        if args.greedy:
            experimentar([csv_greedy], [ejecutable_tiempos_greedy], n_greedy)
        # if args.local:
            # experimentar([csv_local], n_local)
        # if args.grasp:
            # experimentar([csv_grasp], n_grasp)

