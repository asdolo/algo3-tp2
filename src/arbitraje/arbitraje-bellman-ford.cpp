#include <iostream>
#include <vector>
#include "../include/aux.hpp"

using namespace std;

// Devuelve:
// true si hay arbitraje. Además, devuelve un ciclo donde hay arbitraje en cicloDivisas
// false si no
bool arbitrajeBellmanFord(vector<vector<double>> E, vector<int> *cicloDivisas, int nodoInicial)
{
	int n = E.size();

	vector<double> distanciasMinimas(n); // Vector de distancias mínimas entre nodoInicial y el resto
	vector<int> ant(n);

	// Inicializamos el vector de distancias mínimas
	for (int i = 0; i < n; i++)
	{
		distanciasMinimas[i] = E[nodoInicial][i];
		ant[i] = nodoInicial;
	}

	int iteraciones = 0;
	bool hayCambios = true;
	while (hayCambios && iteraciones < n)
	{
		hayCambios = false;
		for (int u = 0; u < n; u++)
		{
			for (int v = 0; v < n; v++)
			{
				double peso = E[u][v];

				if (distanciasMinimas[u] + peso < distanciasMinimas[v])
				{
					distanciasMinimas[v] = distanciasMinimas[u] + peso;
					ant[v] = u;
					hayCambios = true;
				}
			}
		}

		iteraciones++;
	}

	// Ya ejecutamos Bellman-Ford y nos devolvió un vector de distancias mínimas a nodoInicial
	// Ahora buscamos nos fijamos si hay ciclos negativos.
	// Por cómo está modelado el problema en el grafo, esto equivale a detectar si hay arbitraje

	bool hayArbitraje = false;

	if (iteraciones == n)
	{
		// Hay ciclos negativos. Entonces hay arbitraje.

		hayArbitraje = true;

		// Buscamos el ciclo negativo (que ya sabemos que existe) y, en particular, vamos a decir
		// que cualquier nodo de ese ciclo va a ser el primer nodo del ciclo del arbitraje

		vector<bool> yaPase(n);
		for (int i = 0; i < n; i++)
			yaPase[i] = false;
		int actual = nodoInicial;
		do
		{
			yaPase[actual] = true;
			actual = ant[actual];
		} while (!yaPase[actual]);

		int nodoArbitraje = actual;

		// Una vez definido el primer nodo del ciclo del arbitraje, reconstruimos el ciclo
		// del arbitraje

		int i = nodoArbitraje;

		do
		{
			(*cicloDivisas).push_back(i);
			i = ant[i];
		} while (i != nodoArbitraje);

		(*cicloDivisas).push_back(nodoArbitraje);
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

	// Convertimos la matriz de cambios de divisas a una matriz de sucesores para
	// adaptarnos al modelo de grafo que usamos
	vector<vector<double>> E = currenciesToGraph(cambiosDivisas);

	vector<int> cicloDivisas(0);
	bool hayArbitraje = arbitrajeBellmanFord(E, &cicloDivisas, 0);

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