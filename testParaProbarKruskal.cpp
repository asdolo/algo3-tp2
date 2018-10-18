//g++ -std=c++11 testParaProbarKruskal.cpp 
#include <vector>
#include <math.h> 
#include <iostream>
#include <tuple>
#include <string>
using namespace std;


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

bool noPertenece(vector< tuple<int, int, int> > res,int x,int y){
    for(int i=0;i<res.size();i++){
        if( (get<0>(res[i]) == x && get<1>(res[i]) == y) || (get<0>(res[i]) == y && get<1>(res[i]) == x) ) return false;
    }
    return true;
}
vector< tuple<int, int, int> > obtenerListaDeAristas(vector< vector<double> > E){
    vector< tuple<int, int, int> > res;
    for(int i=0;i<E[0].size();i++){
        for(int j=0;j<E[0].size();j++){
            if(E[i][j]!=-1 && noPertenece(res,i,j) && i!=j){
                tuple<int, int,int> t{ i, j , E[i][j]};
                res.push_back(t);
            }
        }
    }
    return res;
}
bool sortbyth(const tuple<int, int, int>& a,  
              const tuple<int, int, int>& b) 
{ 
    return (get<2>(a) < get<2>(b)); 
} 

int FIND(int u, vector<int>& representantes){
    return representantes[u];
}
void UNION(int u,int v,vector<int>& representantes){
    int x = representantes[v];
    for(int i = 0; i < representantes.size(); i++)
    {
        if(representantes[i]==x) representantes[i]=representantes[u];
    }
    
}
vector< tuple<int, int, int> > kruskal(vector< vector<double> > E,vector<int>& representantes){
    vector< tuple<int, int, int> > res;
    vector< tuple<int, int, int> > listaDeAristas = obtenerListaDeAristas(E);
    sort(listaDeAristas.begin(), listaDeAristas.end(), sortbyth); 

    for(int i =0;i<listaDeAristas.size();i++){
        tuple<int, int, int> arista = listaDeAristas[i];
        if(FIND(get<0>(arista),representantes) != FIND(get<1>(arista),representantes)){
            res.push_back(arista);
            UNION(get<0>(arista),get<1>(arista),representantes);
        }
    }
    return res;
}

int main() 
{ 
    vector<double> a(4,-1);
    a[0]=21;
    a[1]=22;
    a[2]=19;
    a[3]=15;
    vector< vector<double> > agm(17,vector<double>(17,-1));
    for(int i=0;i<17;i++) agm[i][i]=0;
    agm[0][1]=18;
    agm[1][0]=18;
    agm[1][2]=22;
    agm[2][1]=22;
    agm[2][3]=19;
    agm[3][2]=19;
    agm[2][4]=15;
    agm[4][2]=15;
    agm[4][5]=21;
    agm[5][4]=21;
    agm[2][6]=21;
    agm[6][2]=21;
    agm[6][7]=78;
    agm[7][6]=78;
    agm[7][8]=14;
    agm[8][7]=14;
    agm[8][9]=22;
    agm[9][8]=22;
    agm[8][10]=17;
    agm[10][8]=17;
    agm[10][11]=22;
    agm[11][10]=22;
    agm[11][12]=17;
    agm[12][11]=17;
    agm[8][13]=12;
    agm[13][8]=12;
    agm[13][14]=18;
    agm[14][13]=18;
    agm[13][15]=19;
    agm[15][13]=19;
    agm[15][16]=11;
    agm[16][15]=11;
    bool b =isConsistentEdge(agm,6,7,2,1);
    vector<int> representantes(17,-1);
    for(int i = 0; i < representantes.size(); i++)
    {
        representantes[i]=i;
    }
    agm[0][12]=4;
    agm[12][0]=4;
    vector< tuple<int, int, int> > res = kruskal(agm,representantes);
    return 0; 
} 