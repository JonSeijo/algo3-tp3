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
def crear_lista_dataframes(datos):
    return [
        datos.groupby('n')['tiempo'].mean() / 1000000000,
        datos.groupby('n')['tamClique'].median(),
        datos.groupby('n')['fronteraMax'].mean()
    ]


def obtener_dataframe(t_algoritmo, t_data):
    return data[t_algoritmo[0]][t_data[0]]


verde = '#55A868'
rojo = '#C44E52'
azul = '#4C72B0'

colores = [azul, verde, rojo]

T_TIEMPO = (0, "Tiempo medio para diferentes tamaños de grafos", "Segundos")
T_TAMCLIQUE = (1, "Tamaño de la clique solución para diferentes tamaños de grafos", "Tamaño clique")
T_FRONTERA = (2, "Frontera máxima para diferentes tamaños de grafos", "Frontera máxima")

T_EXACTA = (0, "Exacta")
T_GREEDY = (1, "Golosa")
T_LOCAL = (2, "Búsqueda local")
T_GRASP = (3, "GRASP")

T_GRAFO_MALO = ("grafo_malo.csv", "")
T_GRAFO_50 = ("random_aristas_50.csv", "50% Aristas random\n")
T_GRAFO_COMPLETO = ("completo.csv", "Grafo completo\n")


# Elegir al menos uno de cada uno!

tipo = T_TAMCLIQUE
algos = [T_LOCAL, T_GREEDY]
grafo = T_GRAFO_50
titulo = grafo[1]


data_exacta = pd.read_csv('experimentos/exacta/' + grafo[0])
data_greedy = pd.read_csv('experimentos/greedy/' + grafo[0])
data_local = pd.read_csv('experimentos/local/' + grafo[0])
data_grasp = pd.read_csv('experimentos/grasp/' + grafo[0])

data = [
    crear_lista_dataframes(data_exacta),
    crear_lista_dataframes(data_greedy),
    crear_lista_dataframes(data_local),
    crear_lista_dataframes(data_grasp)
]

plt.clf()

plot_grafo = obtener_dataframe(algos[0], tipo).plot(fontsize = 13, figsize=(11,8), color=colores[0])
plot_grafo.set_title(titulo + tipo[1], fontsize = 15)
plot_grafo.set_ylabel(tipo[2], size = 14)

for i in range(1, len(algos)):
    obtener_dataframe(algos[i], tipo).plot(ax=plot_grafo, color=colores[i])

plot_grafo.legend([algo[1] for algo in algos], fontsize = 14)
plot_grafo.set_xlabel("Cantidad de nodos", size = 14)

plt.show()