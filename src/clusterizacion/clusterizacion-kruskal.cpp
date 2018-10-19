#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <tuple>
#include <string>
#include "../include/aux.hpp"

using namespace std;

bool noPertenece(vector<tuple<int, int, int>> res, int x, int y)
{
    for (uint i = 0; i < res.size(); i++)
    {
        if ((get<0>(res[i]) == x && get<1>(res[i]) == y) || (get<0>(res[i]) == y && get<1>(res[i]) == x))
            return false;
    }
    return true;
}
vector<tuple<int, int, int>> obtenerListaDeAristas(vector<vector<double>> E)
{
    vector<tuple<int, int, int>> res;
    for (uint i = 0; i < E[0].size(); i++)
    {
        for (uint j = 0; j < E[0].size(); j++)
        {
            if (E[i][j] != -1 && noPertenece(res, i, j) && i != j)
            {
                tuple<int, int, int> t{i, j, E[i][j]};
                res.push_back(t);
            }
        }
    }
    return res;
}
bool sortbyth(const tuple<int, int, int> &a,
              const tuple<int, int, int> &b)
{
    return (get<2>(a) < get<2>(b));
}

int FIND(int u, vector<int> &representantes)
{
    return representantes[u];
}
void UNION(int u, int v, vector<int> &representantes)
{
    int x = representantes[v];
    for (uint i = 0; i < representantes.size(); i++)
    {
        if (representantes[i] == x)
            representantes[i] = representantes[u];
    }
}
vector<vector<double>> kruskal(vector<vector<double>> E)
{
    vector<int> representantes;
    //Creo el vector de representantes
    for (uint i = 0; i < E[0].size(); i++)
    {
        representantes.push_back(i);
    }

    vector<tuple<int, int, int>> agm;
    vector<tuple<int, int, int>> listaDeAristas = obtenerListaDeAristas(E);
    sort(listaDeAristas.begin(), listaDeAristas.end(), sortbyth);

    for (uint i = 0; i < listaDeAristas.size(); i++)
    {
        tuple<int, int, int> arista = listaDeAristas[i];
        if (FIND(get<0>(arista), representantes) != FIND(get<1>(arista), representantes))
        {
            agm.push_back(arista);
            UNION(get<0>(arista), get<1>(arista), representantes);
        }
    }
    //Ya tengo el AGM en res. Lo paso a matriz de adyacencia
    vector<vector<double>> res(E[0].size(), vector<double>(E[0].size(), -1));
    for (uint i = 0; i < agm.size(); i++)
    {
        tuple<int, int, int> arista = agm[i];
        res[get<0>(arista)][get<1>(arista)] = get<2>(arista);
        res[get<1>(arista)][get<0>(arista)] = get<2>(arista);
    }
    return res;
}

int main()
{
    int cantPuntos = 0;
    cin >> cantPuntos;

    if (cantPuntos < 0)
    {
        cerr << "La cantidad de puntos debe ser no negativa." << endl;
        return -1;
    }

    vector<tuple<int, int>> coordenadas(cantPuntos);

    // Leemos las coordenadas de cada punto por stdin
    for (uint i = 0; i < cantPuntos; i++)
    {
        int x, y;
        cin >> x;
        cin >> y;

        coordenadas[i] = make_tuple(x, y);
    }

    // Modelaremos un grafo completo donde cada nodo será un punto del plano,
    // y el peso de cada arista entre cada par de nodos será la distancia en el plano
    // de los puntos que son representados por dichos nodos
    // Representamos en grafo con una matriz de adyacencia
    vector<vector<double>> E = pointsToGraph(coordenadas);

    // Ejecutamos kruskal, que nos devuelve una matriz de adyacencia que representa un AGM
    // del árbol que le pasamos.
    vector<vector<double>> agm = kruskal(E);

    return 0;
}