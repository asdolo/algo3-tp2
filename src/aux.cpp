#include <vector>
#include <math.h>

using namespace std;

// Convierte la matriz de divisas a una matriz de sucesores donde cada posición (i,j) es el peso de la arista
// entre los nodos i y j del grafo dirigido que modela el problema de arbitraje
vector<vector<double>> preProcesarDivisas(vector<vector<double>> cambiosDivisas)
{
    int n = cambiosDivisas.size();

    vector<vector<double>> weights(n);

    for (int i = 0; i < n; i++)
    {
        weights[i] = vector<double>(n);
        for (int j = 0; j < n; j++)
        {
            weights[i][j] = -1 * log10(cambiosDivisas[i][j]);
        }
    }

    return weights;
}