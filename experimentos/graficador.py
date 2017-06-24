#@JonSeijo

"""
Graficador

IMPORTANTE:
Para hacerlo funcionar es NECESARIO que existan los archivos que se cargan.
No hace falta que tengan contenido, pero la pirmera linea DEBE ser: n,fronteraMax,tamClique,tiempo
(con algunos valores en la 2da linea)
Esto es porque con Pandas tomo las columnas y tira error si no existen.

TODO: Solucionar el problema anterior capturando errores con try/except


USO:
Modificar las variables: "algos", "tipo", "grafo" a la que se quiera
"""


import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

# El orden debe ser preciso: tiempo, tamClique, frontera
def crear_lista_dataframes(datos, tope=None):
    return [
        (datos.groupby('n')['tiempo'].mean() / 1000000000)[:tope],
        (datos.groupby('n')['tamClique'].median())[:tope],
        (datos.groupby('n')['fronteraMax'].mean())[:tope]
    ]


def obtener_dataframe(t_algoritmo, t_data):
    return data[t_algoritmo[0]][t_data[0]]


verde = '#55A868'
rojo = '#C44E52'
azul = '#4C72B0'
amarillo = '#EAEA25'
violeta = '#8c108c'

colores = [azul, verde, rojo, amarillo, violeta]

T_TIEMPO = (0, "Tiempo medio para diferentes tamaños de grafos", "Segundos")
T_TAMCLIQUE = (1, "Tamaño de la clique solución para diferentes tamaños de grafos", "Tamaño clique")
T_FRONTERA = (2, "Frontera máxima para diferentes tamaños de grafos", "Frontera máxima")

T_EXACTA = (0, "Exacta")
T_GREEDY = (1, "Golosa")
T_LOCAL = (2, "Búsqueda local")
T_GRASP_0 = (3, "GRASP: alpha=0")
T_GRASP_25 = (4, "GRASP: alpha=0.25")
T_GRASP_50 = (5, "GRASP: alpha=0.50")
T_GRASP_1 = (6, "GRASP: alpha=1")

T_GRAFO_MALO = ("grafo_malo", "")
T_GRAFO_50 = ("random_aristas_50", "50% Aristas random\n")
T_GRAFO_COMPLETO = ("completo", "Grafo completo\n")


# Elegir al menos uno de cada uno!

tipo = T_FRONTERA
algos = [T_LOCAL, T_GRASP_0, T_GRASP_25, T_GRASP_50, T_GRASP_1]
grafo = T_GRAFO_MALO
titulo = grafo[1]

logy = False

data_exacta = pd.read_csv('experimentos/exacta/' + grafo[0] + '.csv')
data_greedy = pd.read_csv('experimentos/greedy/' + grafo[0] + '.csv')
data_local = pd.read_csv('experimentos/local/' + grafo[0] + '.csv')
data_grasp_0 = pd.read_csv('experimentos/grasp/' + grafo[0] + '_0.csv')
data_grasp_25 = pd.read_csv('experimentos/grasp/' + grafo[0] + '_25.csv')
data_grasp_50 = pd.read_csv('experimentos/grasp/' + grafo[0] + '_50.csv')
data_grasp_1 = pd.read_csv('experimentos/grasp/' + grafo[0] + '_1.csv')

data = [
    crear_lista_dataframes(data_exacta),
    crear_lista_dataframes(data_greedy),
    crear_lista_dataframes(data_local),
    crear_lista_dataframes(data_grasp_0),
    crear_lista_dataframes(data_grasp_25),
    crear_lista_dataframes(data_grasp_50),
    crear_lista_dataframes(data_grasp_1)
]

plt.clf()

plot_grafo = obtener_dataframe(algos[0], tipo).plot(fontsize = 13, figsize=(11,8), logy=logy, color=colores[0])
plot_grafo.set_title(titulo + tipo[1], fontsize = 15)
plot_grafo.set_ylabel(tipo[2], size = 14)

for i in range(1, len(algos)):
    obtener_dataframe(algos[i], tipo).plot(ax=plot_grafo, color=colores[i])

plot_grafo.legend([algo[1] for algo in algos], fontsize = 14)
plot_grafo.set_xlabel("Cantidad de nodos", size = 14)

plt.show()