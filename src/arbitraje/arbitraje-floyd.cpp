#include <iostream>
#include <vector>

#define infinito -1 

using namespace std;

bool arbitrajeFloyd (vector<vector<double>> cambiosDivisas, vector<int> *ciclosDivisas) 
{ 
	int n = cambiosDivisas.size();

	vector<vector<double>> distancias(n);
	vector<vector<int>> next(n);
	int i, j, k; 

	for (i = 0; i < n; i++) 
    {
        distancias[i] = vector<double>(n);
        next[i] = vector<int>(n);
        for (j = 0; j < n; j++)
        {
            distancias[i][j] = cambiosDivisas[i][j]; 
            next[i][j] = j;
        }
    }
		
	for (k = 0; k < n; k++) 
	{ 
		for (i = 0; i < n; i++) 
		{ 
			for (j = 0; j < n; j++) 
			{ 
				if (distancias[i][k] * distancias[k][j] > distancias[i][j])
				{
				    distancias[i][j] = distancias[i][k] * distancias[k][j];
				    next[i][j] = next[i][k];
				}
					
			} 
		} 
	} 

    bool hayArbitraje = false;
    int nodoArbitraje = -1;
    for (int i = 0; i < n; i++)
    {
        if (distancias[i][i] > 1.0)
        {
            hayArbitraje = true;
            nodoArbitraje = i;
            break;
        }
    }

    if (hayArbitraje)
    {
        int i = nodoArbitraje;

        do
        {
            (*ciclosDivisas).push_back(i);

            i = next[i][nodoArbitraje];
        } while(i != nodoArbitraje);

        (*ciclosDivisas).push_back(nodoArbitraje);
    }

    return hayArbitraje;
} 

int main() 
{ 

    int cantDivisas = 0;
    cin >> cantDivisas;

    if (cantDivisas < 0)
	{
		cerr << "La cantidad de divisas debe ser no negativa." << endl;
		return -1;
	}

    vector<vector<double>> cambiosDivisas(cantDivisas);

	for (int i = 0; i < cantDivisas; i++)
	{
        cambiosDivisas[i] = vector<double>(cantDivisas);

        for (int j = 0; j < cantDivisas; j++)
        {
            cin >> cambiosDivisas[i][j];
        }
    }

    /*
	double graph[V][V] = { {1, 1.15, 42.93},    // EURO A...
						{0.2, 1, 37.36},       // DOLAR A...
						{0.023, 0.027, 1},   // ARS A...
					}; 
    */

    vector<int> cicloDivisas(0); 
    bool hayArbitraje = arbitrajeFloyd(cambiosDivisas, &cicloDivisas);

    if (hayArbitraje)
    {
        cout << "SI";

        for (int i = 0; i < cicloDivisas.size(); i++)
        {
            cout << " " << cicloDivisas[i];
        }
    }
    else
    {
        cout << "NO";
    }

    cout << endl;

	return 0; 
} 