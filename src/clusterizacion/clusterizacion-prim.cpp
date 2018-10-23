#include <iostream>
#include <vector>
#include <tuple>
#include <math.h>
#include <climits>
#include <fstream>
#include <sstream>
#include <chrono>
#include "../include/aux.hpp"

using namespace std;

// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(vector<double> key, vector<bool> mstSet)
{
    uint n = key.size();

    // Initialize min value
    int min = INT_MAX; // +inf
    int min_index;

    for (uint v = 0; v < n; v++)
    {
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    }

    return min_index;
}

vector<vector<double>> prim(vector<vector<double>> E)
{
    uint n = E.size();

    // Inicializo la matriz de adyacencia del AGM en +infinito (-1)
    vector<vector<double>> res(n);

    for (uint i = 0; i < n; i++)
    {
        res[i] = vector<double>(n);
        for (uint j = 0; j < n; j++)
        {
            res[i][j] = -1;
        }
    }

    // Array to store constructed MST
    vector<int> parent(n);
    // Key values used to pick minimum weight edge in cut
    vector<double> key(n);
    // To represent set of vertices not yet included in MST
    vector<bool> mstSet(n);

    // Initialize all keys as INFINITE
    for (uint i = 0; i < n; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (uint count = 0; count < n - 1; count++)
    {
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (uint v = 0; v < n; v++)
        {
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (E[u][v] && mstSet[v] == false && E[u][v] < key[v])
            {
                parent[v] = u, key[v] = E[u][v];
            }
        }
    }

    for (uint i = 0; i < parent.size(); i++)
    {
        int nodoPadre = parent[i];

        if (nodoPadre != -1)
        {
            res[i][nodoPadre] = E[i][nodoPadre];
            res[nodoPadre][i] = E[nodoPadre][i];
        }
    }

    return res;
}

/*
 Argumentos:
    1. Archivo .csv donde se va a guardar cada punto y a qué clúster pertenece.
    2. Archivo .csv donde se va a agregar una línea que indique la cantidad de puntos,
        los parámetros del test (vecindad, version, excesoNecesarioDesvioEstandar y ratioExceso),
        la cantidad de clústers resultantes y el tiempo de ejecución del algoritmo.
    3. Tamaño de la vencindad a tener en cuenta para definir si un eje es inconsistente.
    4. Versión de noción de eje inconsistente a utilizar (valor entre 1 y 2)
    5. Cantidad de veces que debe exceder el peso de un eje con respecto al desvió estándar
        de su vecindad para considerarse inconsistente (versión 1).
    6. Ratio que debe exceder un eje para considerarse inconsistente (versión 2).
*/
int main(int argc, char *argv[])
{
    int vecindad = argc >= 4 ? stoi(argv[3]) : 2;
    int version = argc >= 5 ? stoi(argv[4]) : 1;
    double excesoNecesarioDesvioEstandar = argc >= 6 ? stod(argv[5]) : 3;
    double ratioExceso = argc >= 7 ? stod(argv[6]) : 2;
    
    int cantPuntos = 0;
    cin >> cantPuntos;

    if (cantPuntos < 0)
    {
        cerr << "La cantidad de puntos debe ser no negativa." << endl;
        return -1;
    }

    ofstream archivoTablaClusters;
    ofstream archivoResultados;
    archivoTablaClusters.open(argc >= 2 ? argv[1] : "output/clusterizacion/clusters-prim.csv", ios_base::app);
    archivoResultados.open(argc >= 3 ? argv[2] : "output/clusterizacion/mediciones-prim.csv", ios_base::app);

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

    // Ejecutamos prim, que nos devuelve una matriz de adyacencia que representa un AGM
    // del árbol que le pasamos.
    vector<vector<double>> agm;
    auto startTime = chrono::steady_clock::now();
    agm = prim(E);
    auto endTime = chrono::steady_clock::now();
    
    tuple<vector<int>, int> res;
    
    auto startTime2 = chrono::steady_clock::now();
    res = obtenerClusters(agm, vecindad, version, excesoNecesarioDesvioEstandar, ratioExceso);
    auto endTime2 = chrono::steady_clock::now();

    for (uint i = 0; i < get<0>(res).size(); i++)
    {
        cout << get<0>(res)[i] << endl;
    }

    // Guardamos las salidas en los archivos .csv
    for (int i = 0; i < cantPuntos; i++)
    {
        archivoTablaClusters << i << "," << get<0>(coordenadas[i]) << "," << get<1>(coordenadas[i]) << "," << get<0>(res)[i] << endl;
    }
    archivoTablaClusters.close();

    archivoResultados << cantPuntos << "," << vecindad << "," << version << "," << excesoNecesarioDesvioEstandar << "," << ratioExceso << "," << get<1>(res) << "," << chrono::duration<double, milli>((endTime - startTime) + (endTime2 - startTime2)).count() << endl;
    archivoResultados.close();

    return 0;
}