#include <vector>
#include <math.h>
#include <iostream>
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

const double cantExcedeDesvioEstandar = 3;
const double ratioExceso = 2;
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
  
double standardDeviation(vector<double> arr,  
                         int n) 
{ 
    return sqrt(variance(arr, n)); 
} 

void obtenerVecinosN(vector< vector<double> > agm,int nodoA,int nodoB,int n,vector<double>& res,double& sumatoria){
    if(n == 0){
        return;
    }
    for (int i = 0; i < agm[0].size(); i++)
    {
        if(agm[nodoA][i] != -1 && i != nodoB && nodoA!=i){
            res.push_back(agm[nodoA][i]);
            sumatoria+=agm[nodoA][i];
            obtenerVecinosN(agm,i,nodoA,n-1,res,sumatoria);
        }
    }
}

bool isConsistentEdge(vector< vector<double> > agm,int nodoA,int nodoB,int vecindad,int version){
    vector<double> distanciasVecinosNodoA;
    double sumatoriaNodoA=0;
    obtenerVecinosN(agm,nodoA,nodoB,vecindad,distanciasVecinosNodoA,sumatoriaNodoA);
    vector<double> distanciasVecinosNodoB;
    double sumatoriaNodoB=0;
    obtenerVecinosN(agm,nodoB,nodoA,vecindad,distanciasVecinosNodoB,sumatoriaNodoB);
    double promedioA = sumatoriaNodoA / distanciasVecinosNodoA.size();
    double promedioB = sumatoriaNodoB / distanciasVecinosNodoB.size();
    double desvioEstandarA = standardDeviation(distanciasVecinosNodoA,distanciasVecinosNodoA.size());
    double desvioEstandarB = standardDeviation(distanciasVecinosNodoB,distanciasVecinosNodoB.size());
    double distanciaEntreAyB = agm[nodoA][nodoB];
    double excesoDeInconsistenciaA = distanciaEntreAyB/desvioEstandarA;
    double excesoDeInconsistenciaB = distanciaEntreAyB/desvioEstandarB;
    double ratioA=distanciaEntreAyB/promedioA;
    double ratioB=distanciaEntreAyB/promedioB;
    if(version==1){
        return (excesoDeInconsistenciaA>cantExcedeDesvioEstandar && excesoDeInconsistenciaB>cantExcedeDesvioEstandar);
    }else{
        return (ratioA>ratioExceso && ratioB>ratioExceso);
    }
    
    return false;
}
