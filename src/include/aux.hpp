#include <vector>
#include <tuple>

#ifndef AUX_HPP
#define AUX_HPP

using namespace std;

// Ejercicio 1
vector<vector<double>> pointsToGraph(vector<tuple<int, int>> points);
double variance(vector<double> a, int n);
double standardDeviation(vector<double> arr, int n);
void obtenerVecinosN(vector<vector<double>> agm, int nodoA, int nodoB, int n, vector<double> &res, double &sumatoria);
bool isConsistentEdge(vector<vector<double>> agm, int nodoA, int nodoB, int vecindad, int version, double excesoNecesarioDesvioEstandar, double ratioExceso);
tuple<vector<int>, int> obtenerClusters(vector<vector<double>> agm, int vecindad, int version, double excesoNecesarioDesvioEstandar, double ratioExceso);
void definirCluster(vector<vector<double>> grafo, vector<int> &result, vector<bool> &visitados, int i, int nroCluster);
// Ejercicio 2
vector<vector<double>> currenciesToGraph(vector<vector<double>> currencies);

// General
void printMatriz(vector<vector<double>> matriz);
vector<tuple<int, int, int>> obtenerListaDeAristas(vector<vector<double>> E);
#endif