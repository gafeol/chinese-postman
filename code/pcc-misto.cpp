#include "bits/stdc++.h"
using namespace std;

#include "grafo-misto.hpp"
#include "aresta.hpp"
#include "floyd-warshall.cpp"
#include "euler-misto.cpp"
#include "min-cost-matching/MCM.hpp"
#include "problema-transporte.cpp"

typedef tuple<int, int, double, int> tiidi;

struct PCC {

    /// Expande o caminho minimo de u a v, considerando os arcos de G como arestas nao direcionadas.
    void expande(int u, int v, vector<vector<double>> &mnDist, Misto &G){
        if(u == v)
            return ;
        int cus = mnDist[u][v];
        for(Aresta ar: G.adj[u]){
            if(ar.cus + mnDist[ar.prox][v] == mnDist[u][v]){
                G.copia(ar.id);
                return expande(ar.prox, v, mnDist, G);
            }
        }

        vector<vector<Aresta>> inv = G.adjInverso();
        for(Aresta ar: inv[u]){
            if(ar.cus + mnDist[ar.prox][v] == mnDist[u][v]){
                G.copia(ar.id);
                return expande(ar.prox, v, mnDist, G);
            }
        }
    }

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

        for(pair<int, int> p : mEdges){
            expande(p.first, p.second, mnDist, G);
        }
        return G;
    }

    void insere(vector<tuple<int, int, double, int>> &v, tuple<int, int, double, int> ar, int copias=1){
        while(copias--)
            v.push_back(ar);
    }

    /// Encontra multiconjuntos M, U, de arcos, arestas direcionadas e arestas não direcionadas que formam um supergrafo com grau de entrada igual ao grau de saída.
    /// Assume-se que o grafo misto M que é propriedade da classe já possui grau total par em todos seus vértices.
    /// Retorna:
    ///     Multiconjuntos M, composto por arcos e algumas arestas de G direcionadas, e U, composto por arestas de G não direcionadas.
    ///     O grafo misto induzido pelos multiconjuntos (M, U) deve possuir grau de entrada e saída iguais 
    ///     Os multiconjuntos devolvidos contem elementos (u, v, c, id), representando uma aresta uv, de custo c e identificador id
    pair<vector<tuple<int, int, double, int>>, vector<tuple<int, int, double, int>>> iguala_grau_dir(Misto G){
        auto mnDist = floyd_warshall(G);

        vector<int> F, S, dF, dS;
        for(int u=0;u<G.n;u++){
            int d = G.grauSaida(u) - G.grauEntrada(u);
            if(d < 0){
                F.push_back(u);
                dF.push_back(-d);
            }
            else if(d > 0){
                S.push_back(u);
                dS.push_back(d);
            }
        }
        auto pt = ProblemaTransporte(G.n, F, dF, S, dS, mnDist);
        auto edgeFlow = pt.solve();

        vector<tuple<int, int, double, int>> M, U;
        // expande edgeFlow em flow de arestas e arcos de G

        // Guarda a quantidade de fluxo total passada por cada par ('id' de aresta, 'orientacao')
        map<int, map<bool, int>> f;
        vector<tuple<int, int, double>> listaArestas = G.listaAdj();

        // Retorna verdadeiro se a aresta 'id' for do formato '(u, v)', falso se for '(v, u)'
        auto orientacao = [&](int id, int u, int v) {
            return (u == get<0>(listaArestas[id]));
        };

        auto expande = [&](tuple<int, int, int> aresta){
            vector<Aresta> caminhoReal;
            auto [u, v, flow] = aresta;
            while(u != v){
                for(auto [prox, id, cus]: G.adj[u]){
                    if(cus + mnDist[prox][v] == mnDist[u][v]){
                        f[id][orientacao(id, u, prox)] += flow;
                        u = prox;
                        break; 
                    }
                    assert(false);
                }
            }
        };

        for(auto aresta : edgeFlow)
            expande(aresta);

        for(int id=0;id<listaArestas.size();id++){
            auto [u, v, c] = listaArestas[id];
            if(G.arco(id)){
                insere(M, make_tuple(u, v, c, id), f[id][1]+1);
            }
            else{
                if(f[id][false] >= 1 || f[id][true] >= 1){
                    assert(f[id][0] * f[id][1] == 0); // se custo > 0 impossivel ter ambas orientacoes com fluxo
                    insere(M, make_tuple(v, u, c, id), f[id][false]); 
                    insere(M, make_tuple(u, v, c, id), f[id][true]);
                }
                else
                    insere(U, make_tuple(u, v, c, id));
            }
        }

        return {M, U};
    }

    /// Retorna multiconjuntos M', U' que mantem a propriedade de M, U, que o grau de entrada e saída de todos vértices são iguais. 
    /// Porém M', U' devem garatir ainda que o grau (não direcionado) de todo vértice seja par. Tornando assim o grafo induzido por M', U' euleriano.
    pair<vector<tiidi>, vector<tiidi>> grau_par(vector<tiidi> M, vector<tiidi> U){

    }

    /// Implementa o algoritmo de 2-aproximação sugerido por Frederickson em paper de '79.
    /// Retorna um circuito euleriano cujo custo é no máximo o dobro do custo ótimo.
    /// O circuito euleriano é dado por um vector de 'id's das arestas e arcos percorridos no circuito.
    vector<int> solveById(Misto G){
        G = grau_total_par(G);
        auto [M, U] = iguala_grau_dir(G);
        tie(M, U) =  grau_par(M, U);
        Misto Ge = Misto(G.n, M, U);
        Euler E = Euler(Ge);
        return E.trilha_euleriana_id();
    }

    PCC() {}
};