#include <bits/stdc++.h>
using namespace std;

#include "min-cost-matching/MCM.cpp"
#include "digrafo.hpp"
#include "floyd-warshall.cpp"
#include "euler-grafo.cpp"
#include "problema-transporte.cpp"

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
        vector<int> F, S;
        vector<int> dF, dS;

        vector<vector<Aresta>> &adj = G.adj;
        vector<vector<Aresta>> inv = G.getAdjInverso();
        for(int u=0;u<G.n;u++){
            demanda[u] =  (int)adj[u].size() - inv[u].size();
            if(demanda[u] < 0){
                F.push_back(u);
                dF.push_back(demanda[u]);
            }
            else if(demanda[u] > 0){
                S.push_back(u);
                dS.push_back(demanda[u])
            }
        }

        ProblemaTransporte pt(G.n, F, dF, S, dS, mnDist); // dist ou mnDist?
        vector<tuple<int, int, int>> f = pt.solve();

        for(tuple<int, int, int> tp: f){
            int u, v, flow;
            tie(u, v, flow) = tp;
            while(flow--){
                expande(u, v, mnDist);
            }
        }
    }

    
};
