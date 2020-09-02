#include <bits/stdc++.h>
using namespace std;

#include "min-cost-matching/MCM.cpp"
#include "grafo.hpp"
#include "floyd-warshall.cpp"
#include "euler-grafo.cpp"

struct PCC {
    private:
    vector<pair<int, int>> expande(int ini, int fim, vector<vector<Aresta>> &adj, vector<vector<double>> &mnDist){
        if(ini == fim)
            return {};
        vector<pair<int, int>> ans;
        for(Aresta ar: adj[ini]){
            if(ar.cus + mnDist[ar.prox][fim] == mnDist[ini][fim]){
                ans.push_back({ini, ar.prox});
                vector<pair<int, int>> aux = expande(ar.prox, fim, adj, mnDist);
                ans.insert(ans.end(), aux.begin(), aux.end());
                return ans;
            }
        }
        assert(false);
    }

    public:
    pair<double, vector<int>> solve(Grafo G) {
        vector<vector<double>> mnDist = floyd_warshall(G);
        vector<int> imp;
        for(int a=0;a<G.n;a++)
            if(G.adj[a].size()&1)
                imp.push_back(a);
        vector<tuple<int, int, double>> arestasImp;
        for(int i=0;i<(int)imp.size();i++){
            for(int j=i+1;j<(int)imp.size();j++){
                arestasImp.emplace_back(i, j, mnDist[imp[i]][imp[j]]);
            }
        }
        pair<double, vector<pair<int, int>>> mcpm = MinimumCostPerfectMatching(imp.size(), arestasImp); // TODO: modificar para aceitar K
        vector<vector<Aresta>> nAdj = G.adj;
        for(pair<int, int> ar: mcpm.second){
            vector<pair<int, int>> path = expande(ar.first, ar.second, G.adj, mnDist);
            for(auto ar: path){ // duplica aresta
                int u = ar.first, v = ar.second;
                nAdj[u].push_back({v, mnDist[u][v]});
                nAdj[v].push_back({u, mnDist[v][u]});
            }
        }
        Grafo nG(nAdj);
        Euler euler(nG);
        double cus = 0;
        for(int u=0;u<(int)nAdj.size();u++){
            for(Aresta ar: nAdj[u]){
                cus += ar.cus;
            }
        }
        cus /= 2.;
        return {cus, euler.trilha_euleriana()};
    }
};