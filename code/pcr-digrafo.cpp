#include "bits/stdc++.h"
using namespace std;
#include "digrafo.hpp"
#include "euler-digrafo.cpp"
#include "problema-transporte.cpp"
#include "ssa.cpp"

struct PCR {

    vector<Aresta> expande(int ini, int fim, Digrafo &G, vector<vector<double>> &mnDist){
        if(ini == fim)
            return {};
        vector<vector<Aresta>> &adj = G.adj;
        vector<Aresta> ans;
        for(Aresta ar: adj[ini]){
            if(ar.cus + mnDist[ar.prox][fim] == mnDist[ini][fim]){
                ans.push_back(ar);
                vector<Aresta> aux = expande(ar.prox, fim, G, mnDist);
                ans.insert(ans.end(), aux.begin(), aux.end());
                return ans;
            }
        }
        assert(false);
    }

    /// Devolve uma solução do PCR: um circuito que percorre todo arco de R ao menos uma vez.
    /// Serão retornados o custo da solução encontrada pro PCR e um vetor dos arcos que formam a solução.
    pair<double, vector<int>> solve(Digrafo G, vector<int> R){
        auto [ssaCost, ssa] = findRuralSSA(G, R);

        // Derivar novo digrafo induzido apenas pelos arcos de ssa.
        auto origListaAdj = G.listaArcos();
        auto mnDist = floyd_warshall(G);

        // Lista de arcos selecionados pelo SSA
        vector<tuple<int, int, double>> nArcos;
        for(int id: ssa)
            nArcos.push_back(origListaAdj[id]);
        // Possivelmente nG é desconexo. (vértices que não são especiais podem ter grau zero)
        Digrafo nG(G.n, nArcos); 
        
        // Resolver problema de transporte para tornar o digrafo euleriano.
            // Condensar o grafo nG em um F,S-bipartido completo 
        vector<int> F, dF, S, dS; 
        for(int u=0;u<G.n;u++){
            int demanda = nG.grauSaida[u] - nG.grauEntrada[u];
            if(demanda < 0){ 
                F.push_back(u);
                dF.push_back(-demanda);
            }
            else if(demanda > 0){
                S.push_back(u);
                dS.push_back(demanda);
            }
        }
        double tCost;
        auto pt  = ProblemaTransporte(G.n, F, dF, S, dS, mnDist);
        auto M = pt.solve();
            // Montar grafo GM com os arcos escolhidos expandidos e duplicados.
            // O grafo GM sera montado a partir dos arcos de 'listaArcos', declarado a seguir.
        vector<tuple<int, int, double>> listaArcos;
        vector<int> realId;

        // TODO: Adicionar em listaArcos todos arcos do ssa com os ids reais do grafo original.

        for (auto [u, v, flow] : M) {
            while(flow--){
                vector<Aresta> arcos = expande(u, v, G, mnDist);
                for(Aresta arco: arcos){
                    realId.push_back(arco.id);
                    listaArcos.emplace_back(u, arco.prox, arco.cus);
                    u = arco.prox;
                }
            }
        }

        // GM também pode ser não conexo. Talvez precise determinar um nó inicial pro circuito euleriano que seja especial.
        Digrafo GM(G.n, listaArcos);
        // Encontrar circuito euleriano no digrafo estendido.
        auto euler = Euler(GM);
        assert(euler.euleriano());
        int no_especial;
        vector<int> circuito = euler.trilha_euleriana_id(no_especial);
        return {ssaCost + tCost, circuito};
    }
};
