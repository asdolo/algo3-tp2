#include <vector>
#include <tuple>
#include <math.h>
#include <iostream>
using namespace std;

// Ejercicio 1

vector<vector<double>> pointsToGraph(vector<tuple<int, int>> points)
{
    // Obtengo la cantidad de nodos
    int n = points.size();

    // Inicializo la matriz de adyacencia en 0
    vector<vector<double>> res(n);

    for (int i = 0; i < n; i++)
    {
        res[i] = vector<double>(n);
        for (int j = 0; j < n; j++)
        {
            res[i][j] = 0;
        }
    }

    // Para cada nodo, calculo su distancia al resto de los nodos (es un grafo completo)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
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

void obtenerVecinosN(vector<vector<double>> agm, int nodoA, int nodoB, int n, vector<double> &res, double &sumatoria)
{
    if (n == 0)
    {
        return;
    }
    for (int i = 0; i < agm[0].size(); i++)
    {
        if (agm[nodoA][i] != -1 && i != nodoB && nodoA != i)
        {
            res.push_back(agm[nodoA][i]);
            sumatoria += agm[nodoA][i];
            obtenerVecinosN(agm, i, nodoA, n - 1, res, sumatoria);
        }
    }
}

bool isConsistentEdge(vector<vector<double>> agm, int nodoA, int nodoB, int vecindad, int version = 1, double excesoNecesarioDesvioEstandar = 3, double ratioExceso = 2)
{
    vector<double> distanciasVecinosNodoA;
    double sumatoriaNodoA = 0;
    obtenerVecinosN(agm, nodoA, nodoB, vecindad, distanciasVecinosNodoA, sumatoriaNodoA);
    vector<double> distanciasVecinosNodoB;
    double sumatoriaNodoB = 0;
    obtenerVecinosN(agm, nodoB, nodoA, vecindad, distanciasVecinosNodoB, sumatoriaNodoB);
    double promedioA = sumatoriaNodoA / distanciasVecinosNodoA.size();
    double promedioB = sumatoriaNodoB / distanciasVecinosNodoB.size();
    double desvioEstandarA = standardDeviation(distanciasVecinosNodoA, distanciasVecinosNodoA.size());
    double desvioEstandarB = standardDeviation(distanciasVecinosNodoB, distanciasVecinosNodoB.size());
    double distanciaEntreAyB = agm[nodoA][nodoB];
    double excesoDeInconsistenciaA = distanciaEntreAyB / desvioEstandarA;
    double excesoDeInconsistenciaB = distanciaEntreAyB / desvioEstandarB;
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
    int n = currencies.size();

    vector<vector<double>> weights(n);

    for (int i = 0; i < n; i++)
    {
        weights[i] = vector<double>(n);
        for (int j = 0; j < n; j++)
        {
            weights[i][j] = -1 * log10(currencies[i][j]);
        }
    }

    return weights;
}

// General

void printMatriz(vector<vector<double>> matriz)
{
    for (int i = 0; i < matriz.size(); i++)
    {
        for (int j = 0; j < matriz.size(); j++)
        {
            cout << matriz[i][j] << "\t\t";
        }
        cout << endl;
    }
}