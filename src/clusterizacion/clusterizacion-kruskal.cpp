#include <vector>
#include <math.h> 
#include <iostream>
#include <tuple>
#include <string>
using namespace std;

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