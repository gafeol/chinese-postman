#include <bits/stdc++.h>
using namespace std;

#include "min-cost-flow.cpp"

struct ProblemaTransporte {

    MinCostFlow mcf;
    int flow = 0;
    double cost = 0;
    int s, t;

    vector<pair<int, int>> arestas;

    ProblemaTransporte(int N, vector<int> F, vector<int> dF, vector<int> S, vector<int> dS, vector<vector<double>> mnDist)
        : mcf(MinCostFlow(N+2, (int)F.size()*S.size())), s(N), t(N+1) {

        for(int i=0;i<(int)F.size();i++){
            int u = F[i], d = dF[i];
            mcf.add_edge(s, u, d, 0);
        }
        for(int i=0;i<(int)S.size();i++){
            int u = S[i], d = dS[i];
            mcf.add_edge(u, t, d, 0);
        }
        
        arestas.clear();
        for(int i=0;i<(int)F.size();i++){
            int u = F[i];
            for(int j=0;j<(int)S.size();j++){
                int v = S[j];
                mcf.add_edge(u, v, INT_MAX, mnDist[u][v], (int)arestas.size());
                arestas.emplace_back(u, v);
            }
        }
    }

    vector<tuple<int, int, int>> solve(){
        cost = mcf.solve(s, t);
        vector<int> f = mcf.flowOnEdge;
        flow = mcf.flow;
        //printf("cost %.3f flow %d\n", cost, flow);
        vector<tuple<int, int, int>> ans;
        for(int i=0;i<(int)arestas.size();i++){
            if(f[i]){
                ans.emplace_back(arestas[i].first, arestas[i].second, f[i]);
            }
        }

        return ans;
    }
};