#include "bits/stdc++.h"
using namespace std;

#include "grafo-misto.hpp"
#include "aresta.hpp"
#include "floyd-warshall.cpp"
#include "euler-misto.cpp"
#include "min-cost-matching/MCM.hpp"


struct PCC {

    /// Adiciona arestas ou arcos de forma ótima para tornar o grau total (delta_t) par para todo vértice.
    /// Retorna:
    ///     Grafo misto com alguns arestas e arcos duplicados 
    Misto grau_total_par(Misto G){
        vector<int> vImp;

        for(int u=0;u<G.n;u++)
            if(G.grauTotal(u)&1)
                vImp.push_back(u);

        Grafo undGraph(G.adj);
        auto mnDist = floyd_warshall(undGraph);

        vector<tuple<int, int, double>> kEdges;
        for(int i=0;i<(int)vImp.size();i++){
            int u = vImp[i];
            for(int j=i+1;j<(int)vImp.size();j++){
                int v = vImp[j];
                kEdges.emplace_back(i, j, mnDist[u][v]);
            }
        }

        auto M = MinimumCostPerfectMatching((int)vImp.size(), kEdges);
        vector<pair<int, int>> mEdges = M.second;

        // expandir mEdges em arcos e arestas de G
        // criar metodo que adiciona aresta extra para grados mistos
    }

    /// Encontra multiconjuntos M, U, de arcos, arestas direcionadas e arestas não direcionadas que formam um supergrafo com grau de entrada igual ao grau de saída.
    /// Assume-se que o grafo misto M que é propriedade da classe já possui grau total par em todos seus vértices.
    /// Retorna:
    ///     Multiconjuntos M, composto por arcos e algumas arestas de G direcionadas, e U, composto por arestas de G não direcionadas.
    ///     O grafo misto induzido pelos multiconjuntos (M, U) deve possuir grau de entrada e saída iguais 
    pair<vector<Aresta>, vector<Aresta>> iguala_grau_dir(Misto G){

    }

    /// Retorna multiconjuntos M', U' que mantem a propriedade de M, U, que o grau de entrada e saída de todos vértices são iguais. 
    /// Porém M', U' devem garatir ainda que o grau (não direcionado) de todo vértice seja par. Tornando assim o grafo induzido por M', U' euleriano.
    pair<vector<Aresta>, vector<Aresta>> grau_par(vector<Aresta> M, vector<Aresta> U){

    }

    /// Implementa o algoritmo de 2-aproximação sugerido por Frederickson em paper de '79.
    /// Retorna um circuito euleriano cujo custo é no máximo o dobro do custo ótimo.
    /// O circuito euleriano é dado por um vector de 'id's das arestas e arcos percorridos no circuito.
    vector<int> solveById(Misto G){
        G = grau_total_par(G);
        vector<Aresta> M, U;
        auto [M, U] = iguala_grau_dir(G);
        auto [M, U] =  grau_par(M, U);
        Misto Ge = Misto(M, U);
        Euler E = Euler(Ge);
        return E.trilha_euleriana_id();
    }

    PCC() {}
};