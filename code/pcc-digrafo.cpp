#include "bits/stdc++.h"
using namespace std;

#include "min-cost-matching/MCM.cpp"
#include "digrafo.hpp"
#include "floyd-warshall.cpp"
#include "euler-digrafo.cpp"
#include "problema-transporte.cpp"

struct PCC {
    private:
    Digrafo G;

    vector<Aresta> expande(int ini, int fim, vector<vector<double>> &mnDist){
        if(ini == fim)
            return {};
        vector<vector<Aresta>> &adj = G.adj;
        vector<Aresta> ans;
        for(Aresta ar: adj[ini]){
            if(ar.cus + mnDist[ar.prox][fim] == mnDist[ini][fim]){
                ans.push_back(ar);
                vector<Aresta> aux = expande(ar.prox, fim, mnDist);
                ans.insert(ans.end(), aux.begin(), aux.end());
                return ans;
            }
        }
        assert(false);
    }

    public:

    bool checkSolutionById(pair<double, vector<int>> sol) {
        double cost = sol.first;
        vector<int> pathId = sol.second;
        double realCost = 0;
        vector<tuple<int, int, double>> listaArcos = G.listaArcos();

        int u = get<1>(listaArcos[pathId.back()]);
        for(int id: pathId){
            int from, to;
            double c;
            tie(from, to, c) = listaArcos[id];
            if(u != from)
                return false;
            u = to;
            realCost += c;
        }

        return (realCost == cost);
    }

    /// Função que resolve o PCC para digrafos.
    /// Retorna um par cujo primeiro elemento é o custo da solução, enquanto que o segundo é a lista de ids dos arcos escolhidos
    pair<double, vector<int>> solveById(){
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
                dF.push_back(-demanda[u]);
            }
            else if(demanda[u] > 0){
                S.push_back(u);
                dS.push_back(demanda[u]);
            }
        }

        /*
        puts("F:");
        for(int i=0;i<F.size();i++){
            printf("%d  demanda %d\n", F[i], dF[i]);
        }
        puts("S:");
        for(int i=0;i<S.size();i++){
            printf("%d  demanda %d\n", S[i], dS[i]);
        }
        */

        ProblemaTransporte pt(G.n, F, dF, S, dS, mnDist); // dist ou mnDist?
        vector<tuple<int, int, int>> f = pt.solve();

        vector<tuple<int, int, double>> listaArcos = G.listaArcos();
        vector<int> realId;
        for(int i=0;i<(int)listaArcos.size();i++)
            realId.push_back(i);

        for(tuple<int, int, int> tp: f){
            int u, v, flow;
            tie(u, v, flow) = tp;
            while(flow--){
                //printf("expande de u %d a v %d\n", u, v);
                vector<Aresta> arcos = expande(u, v, mnDist);
                for(Aresta arco: arcos){
                    realId.push_back(arco.id);
                    listaArcos.emplace_back(u, arco.prox, arco.cus);
                    u = arco.prox;
                }

            }
        }

        for(int a=0;a<(int)listaArcos.size();a++){
            int i, j;
            double c;
            tie(i, j, c) = listaArcos[a];
            //printf("arcos %d %d %.4f\n", i, j, c);
        }
        Euler e = Euler(G.n, listaArcos);

        vector<int> trilha = e.trilha_euleriana_id();
        for(int i=0;i<(int)trilha.size();i++){
            trilha[i] = realId[trilha[i]];
        }
        double custo = 0.0;
        for(int id: trilha)
            custo += get<2>(listaArcos[id]);
        return make_pair(custo, trilha);
    }

    PCC(Digrafo G): G(G) {}
    PCC() {}
};
