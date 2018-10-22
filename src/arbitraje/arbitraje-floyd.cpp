#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include "../include/aux.hpp"

using namespace std;

// Devuelve:
// true si hay arbitraje. Además, devuelve un ciclo donde hay arbitraje en cicloDivisas
// false si no
bool arbitrajeFloyd(vector<vector<double>> E, vector<int> *cicloDivisas)
{
    int n = E.size();

    vector<vector<double>> distanciasMinimas(n); // Matriz de distancias minimos entre cada par de nodos i,j
    vector<vector<int>> next(n);
    int i, j, k;

    // Inicializamos la matriz de distancias mínimas
    for (i = 0; i < n; i++)
    {
        distanciasMinimas[i] = vector<double>(n);
        next[i] = vector<int>(n);
        for (j = 0; j < n; j++)
        {
            distanciasMinimas[i][j] = E[i][j];
            next[i][j] = j;
        }
    }

    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (distanciasMinimas[i][k] + distanciasMinimas[k][j] < distanciasMinimas[i][j])
                {
                    distanciasMinimas[i][j] = distanciasMinimas[i][k] + distanciasMinimas[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Ya ejecutamos Floyd y nos devolvió una matriz de distancias mínimas
    // Ahora buscamos, en las diagonales, si hay ciclos negativos
    // Por cómo está modelado el problema en el grafo, esto equivale a detectar si hay arbitraje

    bool hayArbitraje = false;
    int nodoArbitraje = -1;
    for (int i = 0; i < n; i++)
    {
        if (distanciasMinimas[i][i] < 0)
        {
            // Hay ciclos negativos. Entonces hay arbitraje.
            hayArbitraje = true;
            nodoArbitraje = i;
            break;
        }
    }

    // Si detectamos que hay arbitraje, devolvemos true y reconstruimos un ciclo que sea solución
    // Si, no devolvemos false

    if (hayArbitraje)
    {
        int i = nodoArbitraje;

        do
        {
            (*cicloDivisas).push_back(i);

            i = next[i][nodoArbitraje];
        } while (i != nodoArbitraje);

        (*cicloDivisas).push_back(nodoArbitraje);
    }

    return hayArbitraje;
}

int main(int argc, char *argv[])
{

    int cantDivisas = 0;
    cin >> cantDivisas;

    if (cantDivisas < 0)
    {
        cerr << "La cantidad de divisas debe ser no negativa." << endl;
        return -1;
    }

    ofstream myFile;
    stringstream fileName;
    fileName << "output/arbitraje" << (argc >= 2 ? argv[1] : "floyd.csv");
    myFile.open(fileName.str(), ios_base::app);

    vector<vector<double>> cambiosDivisas(cantDivisas);

    for (int i = 0; i < cantDivisas; i++)
    {
        cambiosDivisas[i] = vector<double>(cantDivisas);

        for (int j = 0; j < cantDivisas; j++)
        {
            cin >> cambiosDivisas[i][j];
        }
    }

    // Convertimos la matriz de cambios de divisas a una matriz de sucesores para
    // adaptarnos al modelo de grafo que usamos
    vector<vector<double>> E = currenciesToGraph(cambiosDivisas);

    vector<int> cicloDivisas(0);

    bool hayArbitraje;
    auto startTime = chrono::steady_clock::now();
    hayArbitraje = arbitrajeFloyd(E, &cicloDivisas);
    auto endTime = chrono::steady_clock::now();

    if (hayArbitraje)
    {
        cout << "SI";

        for (uint i = 0; i < cicloDivisas.size(); i++)
        {
            cout << " " << cicloDivisas[i];
        }
    }
    else
    {
        cout << "NO";
    }

    cout << endl;

    // Guardamos la salida en un archivo csv para graficar
    myFile << cantDivisas << "," << (hayArbitraje ? "SI" : "NO") << ",";

    cout << cicloDivisas[0];
    for (uint i = 1; i < cicloDivisas.size(); i++)
    {
        cout << "-" << cicloDivisas[i];
    }

    myFile << "," << chrono::duration<double, milli>(endTime - startTime).count() << endl;
    myFile.close();

    return 0;
}