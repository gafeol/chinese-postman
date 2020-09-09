#include <bits/stdc++.h>
using namespace std;

#include "min-cost-matching/MCM.cpp"
#include "digrafo.hpp"
#include "floyd-warshall.cpp"
#include "euler-grafo.cpp"

struct PCC {
    private:
    Digrafo G;

    vector<pair<int, int>> expande(int ini, int fim, vector<vector<double>> &mnDist){
        if(ini == fim)
            return {};
        vector<vector<Aresta>> &adj = G.adj;
        vector<pair<int, int>> ans;
        for(Aresta ar: adj[ini]){
            if(ar.cus + mnDist[ar.prox][fim] == mnDist[ini][fim]){
                ans.push_back({ini, ar.prox});
                vector<pair<int, int>> aux = expande(ar.prox, fim, mnDist);
                ans.insert(ans.end(), aux.begin(), aux.end());
                return ans;
            }
        }
        assert(false);
    }

    vector<int> solveById(){
        vector<vector<double>> mnDist = floyd_warshall(G);
        vector<int> demanda(G.n);
        vector<pair<int, int>> F, S;

        vector<vector<Aresta>> &adj = G.adj;
        vector<vector<Aresta>> inv = G.getAdjInverso();
        for(int u=0;u<G.n;u++){
            demanda[u] =  (int)adj[u].size() - inv[u].size();
            if(demanda[u] < 0)
                F.emplace_back(u, demanda[u]);
            else if(demanda[u] > 0)
                S.emplace_back(u, demanda[u]);
        }

        ProblemaTransporte pt = ProblemaTransporte(F, S, dist);
        vector<int> f = pt.solve();

        assert(f.size() == G.m);
        for(int e=0;e<G.m;e++){
            
        }
    }

    
};
