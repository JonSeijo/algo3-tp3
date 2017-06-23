import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

verde = '#55A868'
rojo = '#C44E52'
azul = '#4C72B0'

T_TIEMPO = 0
T_TAMCLIQUE = 1
T_FRONTERA = 2

data_exacta = pd.read_csv('experimentos/exacta/grafo_malo.csv')
tiempo_exacta = data_exacta.groupby('n')['tiempo'].mean() / 1000000000
tamclique_exacta = data_exacta.groupby('n')['tamClique'].median()
fronteramax_exacta = data_exacta.groupby('n')['fronteraMax'].mean()

data_greedy = pd.read_csv('experimentos/greedy/grafo_malo.csv')
tiempo_greedy = data_greedy.groupby('n')['tiempo'].mean() / 1000000000
tamclique_greedy = data_greedy.groupby('n')['tamClique'].median()
fronteramax_greedy = data_greedy.groupby('n')['fronteraMax'].mean()

# -----------------------------------------------------------------------

# tipo = T_TIEMPO
# tipo = T_TAMCLIQUE
tipo = T_FRONTERA

titulo = ""

plt.clf()

if tipo == T_TIEMPO:
    plot_50 = tiempo_exacta.plot(fontsize = 13, figsize=(11,8), color=verde)
    plot_50.set_title(titulo + 'Tiempo medio para diferentes tamaños de grafos', fontsize = 15)
    plot_50.set_ylabel("Segundos", size = 14)
    tiempo_greedy.plot(ax=plot_50, color=azul)
    plot_50.legend(['Exacta', 'Greedy'], fontsize = 14)
    plot_50.set_xlabel("Cantidad de nodos", size = 14)

elif tipo == T_TAMCLIQUE:
    plot_50 = tamclique_exacta.plot(fontsize = 13, figsize=(11,8), color=verde)
    plot_50.set_title(titulo + 'Clique solución para diferentes tamaños de grafos', fontsize = 15)
    plot_50.set_ylabel("Tamaño clique", size = 14)
    tamclique_greedy.plot(ax=plot_50, color=azul)
    plot_50.legend(['Exacta', 'Greedy'], fontsize = 14)
    plot_50.set_xlabel("Cantidad de nodos", size = 14)

elif tipo == T_FRONTERA:
    plot_50 = fronteramax_exacta.plot(fontsize = 13, figsize=(11,8), color=verde)
    plot_50.set_title(titulo + 'Frontera máxima para diferentes tamaños de grafos', fontsize = 15)
    plot_50.set_ylabel("Frontera máxima ", size = 14)
    fronteramax_greedy.plot(ax=plot_50, color=azul)
    plot_50.legend(['Exacta', 'Greedy'], fontsize = 14)
    plot_50.set_xlabel("Cantidad de nodos", size = 14)


plt.show()