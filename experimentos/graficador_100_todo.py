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

data_exacta_100 = pd.read_csv('experimentos/exacta/completo.csv')
tiempo_exacta_100 = data_exacta_100.groupby('n')['tiempo'].mean() / 1000000000
tamclique_exacta_100 = data_exacta_100.groupby('n')['tamClique'].mean()
fronteramax_exacta_100 = data_exacta_100.groupby('n')['fronteraMax'].mean()

data_greedy_100 = pd.read_csv('experimentos/greedy/completo.csv')
tiempo_greedy_100 = data_greedy_100.groupby('n')['tiempo'].mean() / 1000000000
tamclique_greedy_100 = data_greedy_100.groupby('n')['tamClique'].mean()
fronteramax_greedy_100 = data_greedy_100.groupby('n')['fronteraMax'].mean()

# -----------------------------------------------------------------------

tipo = T_TIEMPO

plt.clf()

if tipo == T_TIEMPO:
    plot_100 = tiempo_exacta_100.plot(fontsize = 13, figsize=(11,8), color=verde)
    plot_100.set_title('\n 100% aristas \n Tiempo medio para diferentes tamaños de grafos', fontsize = 15)
    plot_100.set_ylabel("Segundos", size = 14)
    tiempo_greedy_100.plot(ax=plot_100, color=azul)
    plot_100.legend(['Exacta', 'Greedy'], fontsize = 14)
    plot_100.set_xlabel("Cantidad de nodos", size = 14)

elif tipo == T_TAMCLIQUE:
    plot_100 = tamclique_exacta_100.plot(fontsize = 13, figsize=(11,8), color=verde)
    plot_100.set_title('\n 100% aristas \n Clique solucion para diferentes tamaños de grafos', fontsize = 15)
    plot_100.set_ylabel("Tamaño clique", size = 14)
    tamclique_greedy_100.plot(ax=plot_100, color=azul)
    plot_100.legend(['Exacta', 'Greedy'], fontsize = 14)
    plot_100.set_xlabel("Cantidad de nodos", size = 14)

elif tipo == T_FRONTERA:
    plot_100 = fronteramax_exacta_100.plot(fontsize = 13, figsize=(11,8), color=verde)
    plot_100.set_title('\n 100% aristas \n FronteraMax para diferentes tamaños de grafos', fontsize = 15)
    plot_100.set_ylabel("FronteraMax", size = 14)
    fronteramax_greedy_100.plot(ax=plot_100, color=azul)
    plot_100.legend(['Exacta', 'Greedy'], fontsize = 14)
    plot_100.set_xlabel("Cantidad de nodos", size = 14)


plt.show()