#include <bits/stdc++.h>
using namespace std;

#include "min-cost-matching/MCM.cpp"
#include "grafo.hpp"
#include "floyd-warshall.cpp"
#include "euler-grafo.cpp"

struct PCC {
    private:
    Grafo G;

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

    public:
    pair<double, vector<int>> solve() {  // TODO: fazer checagem de trilha por id
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
        int id = G.m;
        for(pair<int, int> ar: mcpm.second){
            vector<pair<int, int>> path = expande(imp[ar.first], imp[ar.second], mnDist);
            for(auto ar: path){ // duplica aresta
                int u = ar.first, v = ar.second;
                nAdj[u].push_back(Aresta(v, id, mnDist[u][v]));
                nAdj[v].push_back(Aresta(u, id, mnDist[v][u]));
                id++;
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

    bool checkSolution(pair<double, vector<int>> sol){ 
        double solutionCost = sol.first;
        vector<int> cycle = sol.second;
        if(cycle[0] != cycle.back()) return false;
        map<int, map<int, int>> mrk;
        map<int, map<int, double>> c;
        for(int u=0;u<G.n;u++){
            for(Aresta ar: G.adj[u]){
                mrk[u][ar.prox]++;
                c[u][ar.prox] = ar.cus;
            }
        }
        // TODO: Problema se houverem arestas paralelas
        double realCost = 0;
        for(int i=0;i+1<(int)cycle.size();i++){
            mrk[cycle[i]][cycle[i+1]]--;
            mrk[cycle[i+1]][cycle[i]]--;
            realCost += c[cycle[i]][cycle[i+1]];
        }
        if(realCost != solutionCost)
            return false;
        for(auto lin: mrk){
            for(auto cnt: lin.second){
                if(cnt.second > 0) // aresta nao percorrida
                    return false;
            }
        }
        return true;
    }

    PCC(Grafo G): G(G) {}
    PCC() {}
};