#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <tuple>
#include <string>
#include "../include/aux.hpp"

using namespace std;

struct subset
{
    int parent;
    int rank;
};
bool noPertenece(vector<tuple<int, int, int>> res, int x, int y)
{
    for (int i = 0; i < res.size(); i++)
    {
        if ((get<0>(res[i]) == x && get<1>(res[i]) == y) || (get<0>(res[i]) == y && get<1>(res[i]) == x))
            return false;
    }
    return true;
}
vector<tuple<int, int, int>> obtenerListaDeAristas(vector<vector<double>> E)
{
    vector<tuple<int, int, int>> res;
    for (int i = 0; i < E[0].size(); i++)
    {
        for (int j = 0; j < E[0].size(); j++)
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

int FIND(int u, vector<subset> &subsets)
{
    if (subsets[u].parent != u)
        subsets[u].parent = FIND(subsets[u].parent, subsets);

    return subsets[u].parent;
}
void UNION(int u, int v, vector<subset> &subsets)
{
    int xroot = FIND(u, subsets);
    int yroot = FIND(v, subsets);

    if (subsets[xroot].rank < subsets[yroot].rank)
    {
        subsets[xroot].parent = yroot;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank)
    {
        subsets[yroot].parent = xroot;
    }
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
vector<vector<double>> kruskalPathCompression(vector<vector<double>> E)
{
    // Creo los structs subset para union-find con path compression
    vector<subset> subsets;
    // Inicializo los subsets
    for (int i = 0; i < E[0].size(); i++)
    {
        struct subset s;
        s.parent = i;
        s.rank = 0;
        subsets.push_back(s);
    }

    vector<tuple<int, int, int>> agm;
    vector<tuple<int, int, int>> listaDeAristas = obtenerListaDeAristas(E);
    sort(listaDeAristas.begin(), listaDeAristas.end(), sortbyth);

    for (int i = 0; i < listaDeAristas.size(); i++)
    {
        tuple<int, int, int> arista = listaDeAristas[i];
        if (FIND(get<0>(arista), subsets) != FIND(get<1>(arista), subsets))
        {
            agm.push_back(arista);
            UNION(get<0>(arista), get<1>(arista), subsets);
        }
    }
    //Ya tengo el AGM en res. Lo paso a matriz de adyacencia
    vector<vector<double>> res(E[0].size(), vector<double>(E[0].size(), -1));
    for (int i = 0; i < agm.size(); i++)
    {
        tuple<int, int, int> arista = agm[i];
        res[get<0>(arista)][get<1>(arista)] = get<2>(arista);
        res[get<1>(arista)][get<0>(arista)] = get<2>(arista);
    }
    return res;
}

int main(int argc, const char* argv[])
{
    int vecindad=2; 
    int version=1; 
    double excesoNecesarioDesvioEstandar=3;
    double ratioExceso=2;
    if(argc>4){
		vecindad=stoi(argv[1]); 
        version= stoi(argv[2]); 
        excesoNecesarioDesvioEstandar = stod(argv[3]);
        ratioExceso = stod(argv[4]);
	}
    int cantPuntos = 0;
    cin >> cantPuntos;

    if (cantPuntos < 0)
    {
        cerr << "La cantidad de puntos debe ser no negativa." << endl;
        return -1;
    }

    vector<tuple<int, int>> coordenadas(cantPuntos);

    // Leemos las coordenadas de cada punto por stdin
    for (int i = 0; i < cantPuntos; i++)
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

    // Ejecutamos kruskal con path compression, que nos devuelve una matriz de adyacencia que representa un AGM
    // del árbol que le pasamos.
    vector<vector<double>> agm = kruskalPathCompression(E);

    vector<int> res = obtenerClusters(agm, vecindad, version, excesoNecesarioDesvioEstandar, ratioExceso);
    for(int i=0;i<res.size();i++){
        cout << res[i] << endl;
    }
    return 0;
}