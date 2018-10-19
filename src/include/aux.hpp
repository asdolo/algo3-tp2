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
bool isConsistentEdge(vector<vector<double>> agm, int nodoA, int nodoB, int vecindad, int version = 1, double excesoNecesarioDesvioEstandar = 3, double ratioExceso = 2);

// Ejercicio 2
vector<vector<double>> currenciesToGraph(vector<vector<double>> currencies);

// General
void printMatriz(vector<vector<double>> matriz);


#endif