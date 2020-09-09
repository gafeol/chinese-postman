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

    
};
