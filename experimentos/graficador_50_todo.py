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

data_exacta_50 = pd.read_csv('experimentos/exacta/random_aristas_50.csv')
tiempo_exacta_50 = data_exacta_50.groupby('n')['tiempo'].mean() / 1000000000
# tamclique_exacta_50 = data_exacta_50.groupby('n')['tamClique'].mean()
tamclique_exacta_50 = data_exacta_50.groupby('n')['tamClique'].median()
fronteramax_exacta_50 = data_exacta_50.groupby('n')['fronteraMax'].mean()
# fronteramax_exacta_50 = data_exacta_50.groupby('n')['fronteraMax'].median()

data_greedy_50 = pd.read_csv('experimentos/greedy/random_aristas_50.csv')
tiempo_greedy_50 = data_greedy_50.groupby('n')['tiempo'].mean() / 1000000000
# tamclique_greedy_50 = data_greedy_50.groupby('n')['tamClique'].mean()
tamclique_greedy_50 = data_greedy_50.groupby('n')['tamClique'].median()
fronteramax_greedy_50 = data_greedy_50.groupby('n')['fronteraMax'].mean()
# fronteramax_greedy_50 = data_greedy_50.groupby('n')['fronteraMax'].median()

# -----------------------------------------------------------------------

# tipo = T_TIEMPO
tipo = T_TAMCLIQUE
# tipo = T_FRONTERA

plt.clf()

if tipo == T_TIEMPO:
    plot_50 = tiempo_exacta_50.plot(fontsize = 13, figsize=(11,8), color=verde)
    plot_50.set_title('\n 50% aristas \n Tiempo medio para diferentes tamaños de grafos', fontsize = 15)
    plot_50.set_ylabel("Segundos", size = 14)
    tiempo_greedy_50.plot(ax=plot_50, color=azul)
    plot_50.legend(['Exacta', 'Greedy'], fontsize = 14)
    plot_50.set_xlabel("Cantidad de nodos", size = 14)

elif tipo == T_TAMCLIQUE:
    plot_50 = tamclique_exacta_50.plot(fontsize = 13, figsize=(11,8), color=verde)
    plot_50.set_title('\n 50% aristas \n Clique solucion para diferentes tamaños de grafos', fontsize = 15)
    plot_50.set_ylabel("Tamaño clique", size = 14)
    tamclique_greedy_50.plot(ax=plot_50, color=azul)
    plot_50.legend(['Exacta', 'Greedy'], fontsize = 14)
    plot_50.set_xlabel("Cantidad de nodos", size = 14)

elif tipo == T_FRONTERA:
    plot_50 = fronteramax_exacta_50.plot(fontsize = 13, figsize=(11,8), color=verde)
    plot_50.set_title('\n 50% aristas \n FronteraMax para diferentes tamaños de grafos', fontsize = 15)
    plot_50.set_ylabel("FronteraMax", size = 14)
    fronteramax_greedy_50.plot(ax=plot_50, color=azul)
    plot_50.legend(['Exacta', 'Greedy'], fontsize = 14)
    plot_50.set_xlabel("Cantidad de nodos", size = 14)


plt.show()