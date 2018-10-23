#include <vector>
#include <tuple>
#include <math.h>
#include <iostream>
using namespace std;

// Ejercicio 1

vector<vector<double>> pointsToGraph(vector<tuple<int, int>> points)
{
    // Obtengo la cantidad de nodos
    uint n = points.size();

    // Inicializo la matriz de adyacencia en 0
    vector<vector<double>> res(n);

    for (uint i = 0; i < n; i++)
    {
        res[i] = vector<double>(n);
        for (uint j = 0; j < n; j++)
        {
            res[i][j] = 0;
        }
    }

    // Para cada nodo, calculo su distancia al resto de los nodos (es un grafo completo)
    for (uint i = 0; i < n; i++)
    {
        for (uint j = 0; j < n; j++)
        {
            int x1, y1, x2, y2;

            x1 = get<0>(points[i]);
            y1 = get<1>(points[i]);
            x2 = get<0>(points[j]);
            y2 = get<1>(points[j]);

            // Calculo la norma/distancia entre los dos puntos
            double distance = sqrt((pow(x2 - x1, 2)) + pow(y2 - y1, 2));

            res[i][j] = distance;
        }
    }

    return res;
}

double variance(vector<double> a, int n)
{
    // Compute mean (average of elements)
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    double mean = (double)sum /
                  (double)n;

    // Compute sum squared
    // differences with mean.
    double sqDiff = 0;
    for (int i = 0; i < n; i++)
        sqDiff += (a[i] - mean) *
                  (a[i] - mean);
    return sqDiff / n;
}

double standardDeviation(vector<double> arr, int n)
{
    return sqrt(variance(arr, n));
}

void obtenerVecinosN(vector<vector<double>> agm, uint nodoA, uint nodoB, uint n, vector<double> &res, double &sumatoria)
{
    if (n == 0)
    {
        return;
    }
    for (uint i = 0; i < agm[0].size(); i++)
    {
        if (agm[nodoA][i] != -1 && i != nodoB && nodoA != i)
        {
            res.push_back(agm[nodoA][i]);
            sumatoria += agm[nodoA][i];
            obtenerVecinosN(agm, i, nodoA, n - 1, res, sumatoria);
        }
    }
}

bool isConsistentEdge(vector<vector<double>> agm, int nodoA, int nodoB, int vecindad, int version, double excesoNecesarioDesvioEstandar, double ratioExceso)
{
    vector<double> distanciasVecinosNodoA(0);
    double sumatoriaNodoA = 0;
    obtenerVecinosN(agm, nodoA, nodoB, vecindad, distanciasVecinosNodoA, sumatoriaNodoA);
    vector<double> distanciasVecinosNodoB(0);
    double sumatoriaNodoB = 0;
    obtenerVecinosN(agm, nodoB, nodoA, vecindad, distanciasVecinosNodoB, sumatoriaNodoB);
    double promedioA = (distanciasVecinosNodoA.size() > 0 ? sumatoriaNodoA / distanciasVecinosNodoA.size() : 0);
    double promedioB = (distanciasVecinosNodoB.size() > 0 ? sumatoriaNodoB / distanciasVecinosNodoB.size() : 0);
    double desvioEstandarA = standardDeviation(distanciasVecinosNodoA, distanciasVecinosNodoA.size());
    double desvioEstandarB = standardDeviation(distanciasVecinosNodoB, distanciasVecinosNodoB.size());
    double distanciaEntreAyB = agm[nodoA][nodoB];
    double excesoDeInconsistenciaA = (desvioEstandarA != 0 ? distanciaEntreAyB / desvioEstandarA : 0);
    double excesoDeInconsistenciaB = (desvioEstandarB != 0 ? distanciaEntreAyB / desvioEstandarB : 0);
    double ratioA = distanciaEntreAyB / promedioA;
    double ratioB = distanciaEntreAyB / promedioB;
    if (version == 1)
        return (excesoDeInconsistenciaA > excesoNecesarioDesvioEstandar && excesoDeInconsistenciaB > excesoNecesarioDesvioEstandar);
    else if (version == 2)
        return (ratioA > ratioExceso && ratioB > ratioExceso);

    return false;
}

// Ejercicio 2

// Convierte la matriz de divisas a una matriz de sucesores donde cada posición (i,j) es el peso de la arista
// entre los nodos i y j del grafo dirigido que modela el problema de arbitraje
vector<vector<double>> currenciesToGraph(vector<vector<double>> currencies)
{
    uint n = currencies.size();

    vector<vector<double>> weights(n);

    for (uint i = 0; i < n; i++)
    {
        weights[i] = vector<double>(n);
        for (uint j = 0; j < n; j++)
        {
            weights[i][j] = -1 * log10(currencies[i][j]);
        }
    }

    return weights;
}

// General

void printMatriz(vector<vector<double>> matriz)
{
    for (uint i = 0; i < matriz.size(); i++)
    {
        for (uint j = 0; j < matriz.size(); j++)
        {
            cout << matriz[i][j] << "\t\t";
        }
        cout << endl;
    }
}

void definirCluster(vector<vector<double>> grafo, vector<int> &result, vector<bool> &visitados, uint i, int nroCluster)
{
    for (uint j = 0; j < grafo.size(); j++)
    {
        if (i != j && grafo[i][j] != -1 && visitados[j] == false)
        {
            visitados[j] = true;
            result[j] = nroCluster;
            definirCluster(grafo, result, visitados, j, nroCluster);
        }
    }
}
vector<int> obtenerClusters(vector<vector<double>> agm, int vecindad, int version, double excesoNecesarioDesvioEstandar, double ratioExceso)
{
    vector<tuple<int, int>> ejesInconsistentes;
    for (uint i = 0; i < agm[0].size(); i++)
    {
        for (uint j = 0; j < agm[0].size(); j++)
        {
            if (i != j && agm[i][j] != -1 && isConsistentEdge(agm, i, j, vecindad, version, excesoNecesarioDesvioEstandar, ratioExceso))
            {
                tuple<int, int> inconsistente;
                get<0>(inconsistente) = i;
                get<1>(inconsistente) = j;
                ejesInconsistentes.push_back(inconsistente);
            }
        }
    }

    //Ya tengo los ejes inconsistentes(Algunos repetidos pero no hay problema)
    //Saco los ejes inconsistentes del agm. Quedan n componentes conexas
    for (uint i = 0; i < ejesInconsistentes.size(); i++)
    {
        agm[get<0>(ejesInconsistentes[i])][get<1>(ejesInconsistentes[i])] = -1;
        agm[get<1>(ejesInconsistentes[i])][get<0>(ejesInconsistentes[i])] = -1;
    }

    //agm solamente tiene n componentes conexas, donde cada componente conexa es un cluster
    //Para obtener que punto pertenece a cada cluster veo los vecinos
    vector<int> puntosPertencienteACluster(agm.size(), -1);
    vector<bool> visitados(agm.size(), false);
    int nroCluster = 0;
    for (uint i = 0; i < visitados.size(); i++)
    {
        if (visitados[i] == false)
        {
            visitados[i] = true;
            puntosPertencienteACluster[i] = nroCluster;
            definirCluster(agm, puntosPertencienteACluster, visitados, i, nroCluster);
            nroCluster++;
        }
    }
    return puntosPertencienteACluster;
}