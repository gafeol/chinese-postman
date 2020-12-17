#include "bits/stdc++.h"
using namespace std;
#include "digrafo.hpp"
#include "euler-digrafo.cpp"
#include "problema-transporte.cpp"
#include "ssa.cpp"

struct PCR {
    /// Devolve uma solução do PCR: um circuito que percorre todo arco de R ao menos uma vez.
    /// Serão retornados o custo da solução encontrada pro PCR e um vetor dos arcos que formam a solução.
    pair<double, vector<int>> solve(Digrafo G, vector<int> R){
        auto [ssaCost, ssa] = findRuralSSA(G, R);

        // Derivar novo digrafo induzido apenas pelos arcos de ssa.
        Digrafo nG; 
        
        // Resolver problema de transporte para tornar o digrafo euleriano.
            // Condensar o grafo nG em um F,S-bipartido completo 
        double tCost;
        auto pt  = ProblemaTransporte(G.n, F, dF, S, dS, mnDist);
        auto M = pt.solve();
            // Montar grafo GM com os arcos escolhidos expandidos e duplicados.
        Digrafo GM;
        // Encontrar circuito euleriano no digrafo estendido.
        auto euler = Euler(GM);
        assert(euler.euleriano());
        vector<int> circuito = euler.trilha_euleriana_id();
        return {ssaCost + tCost, circuito};
    }
};
