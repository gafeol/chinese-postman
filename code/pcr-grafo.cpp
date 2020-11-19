#include "bits/stdc++.h"
using namespace std;
#include "grafo.hpp"
#include "floyd-warshall.cpp"
#include "euler-grafo.cpp"
#include "union-find.cpp"
#include "min-cost-matching/MCM.cpp"

struct PCR {

    /// Função auxiliar que expande uma aresta condensada entre 'ini' e 'fim' para um conjunto de arestas presente no grafo 'G'.
    /// Retorna:
    ///     Vetor de identificadores que representam as arestas condensadas. 
    vector<int> expande(Grafo &G, int ini, int fim, vector<vector<double>> &mnDist) {
        if (ini == fim)
            return {};
        vector<vector<Aresta>> &adj = G.adj;
        vector<int> ans;
        for (Aresta ar : adj[ini]) {
            if (ar.cus + mnDist[ar.prox][fim] == mnDist[ini][fim]) {
                ans.push_back(ar.id);
                vector<int> aux = expande(G, ar.prox, fim, mnDist);
                ans.insert(ans.end(), aux.begin(), aux.end());
                return ans;
            }
        }
        assert(false);
    }

    /// Função auxiliar que expande uma aresta condensada entre 'ini' e 'fim' para um conjunto de arestas presente no grafo 'G'.
    /// Retorna: 
    ///     Vetor de identificadores das arestas que compõem a aresta condensada entre ini e fim.
    vector<int> expande(int ini, int fim, vector<vector<double>> &mnDist, Grafo& G){
        if(ini == fim)
            return {};
        vector<vector<Aresta>> &adj = G.adj;
        vector<int> ans;
        for(Aresta ar: adj[ini]){
            if(ar.cus + mnDist[ar.prox][fim] == mnDist[ini][fim]){
                ans.push_back(ar.id);
                auto aux = expande(ar.prox, fim, mnDist, G);
                ans.insert(ans.end(), aux.begin(), aux.end());
                return ans;
            }
        }
        assert(false);
    }


    /// Devolve a árvore geradora mínima que conecta as componentes condensadas induzidas de R.
    /// Usa uma adaptação do algoritmo de Kruskal, tratando vértices ligados por arestas de R como uma componente única.
    vector<int> getMST(Grafo &G, vector<vector<double>> &mnDist, UnionFind &uf){
        vector<tuple<int, int, double>> condensedEdges;
        for(int u=0;u<G.n;u++){
            for(int v=0;v<G.n;v++){
                condensedEdges.emplace_back(u, v, mnDist[u][v]);
            }
        }
        sort(condensedEdges.begin(),
                condensedEdges.end(),
                [&](tuple<int, int, double> a,
                    tuple<int, int, double> b){
                        return get<double>(a) < get<double>(b);
                    });
        vector<tuple<int, int, double>> condensedT;
        UnionFind mstUf = UnionFind(G.n);
        for(auto [u, v, c]: condensedEdges){
            int ru = uf.raiz(u);
            int rv = uf.raiz(v);
            if(uf.sz[ru] == 1 || uf.sz[rv] == 1) continue; // não é componente especial
            if(mstUf.join(ru, rv)){
                condensedT.emplace_back(u, v, c);
            }
        }
        vector<int> T;
        for(auto [u, v, cus]: condensedT){
            assert(mnDist[u][v] == cus);
            auto origPath = expande(u, v, mnDist, G);
            T.insert(T.end(), origPath.begin(), origPath.end());
        }
        return T;
    }

    /// Devolve um supergrafo euleriano a partir de G, usando um emparelhamento perfeito de custo mínimo entre vértices de grau ímpar.
    /// Devolve também um vetor com o id real. Isso é importante para conseguir mapear as arestas duplicadas pelo matching em arestas reais do grafo original G.
    pair<Grafo, vector<int>> makeEulerian(Grafo &G){
        auto mnDist = floyd_warshall(G);
        vector<int> imp;
        for(int u=0;u<G.n;u++)
            if(G.adj[u].size()&1)
                imp.push_back(u);
        vector<tuple<int, int, double>> arestasImp;
        for(int i=0;i<(int)imp.size();i++){
            for(int j=i+1;j<(int)imp.size();j++){
                arestasImp.emplace_back(i, j, mnDist[imp[i]][imp[j]]);
            }
        }
        auto [ignore, M] = MinimumCostPerfectMatching(imp.size(), arestasImp); 
        auto novoAdj = G.adj;
        vector<int> idReal;
        for(int a=0;a<G.m;a++)
            idReal.push_back(a);

        auto listaAdj = G.listaArestas();
        
        for(auto [ini, fim]: M){
            vector<int> path = expande(imp[ini], imp[fim], mnDist, G);
            int u = imp[ini], v;
            for(int id: path){ 
                int fakeId = idReal.size();
                idReal.push_back(id);
                auto [w1, w2, c] = listaAdj[id];
                assert(u == w1 || u == w2);
                if(u == w1)
                    v = w2;
                else 
                    v = w1;
                novoAdj[u].emplace_back(v, fakeId, c);
                novoAdj[v].emplace_back(u, fakeId, c);
                u = v;
            }
            assert(u == imp[fim]);
        }
        Grafo nG(novoAdj);
        return {nG, idReal};
    }

    /// Devolve o custo e os identificadores de uma rota que resolve o problema do carteiro rural.
    /// O conjunto R define as arestas que devem ser percorridas no trajeto final.
    /// Implementa a 1.5 aproximação polinomial sugerida por Christofides.
    vector<int> solveById(Grafo G, vector<int> R){
        if(R.empty())
            return vector<int>();
        vector<bool> isSpecial(G.m, false);
        for(int id: R)
            isSpecial[id] = true;
        
        UnionFind uf(G.n); 
        for(int u=0;u<G.n;u++){
            for(auto [prox, id, cus]: G.adj[u]){
                if(isSpecial[id]){
                    uf.join(u, prox);
                }
            }
        }

        auto mnDist = floyd_warshall(G);
        auto T = getMST(G, mnDist, uf);
        auto listaAdj = G.listaArestas();
        vector<tuple<int, int, double>> edgesRT;
        vector<int> realIds;
        // Quebra nocao de ids aqui
        for(int id: R){
            edgesRT.push_back(listaAdj[id]);
            realIds.push_back(id);
        }
        for(int id: T){
            edgesRT.push_back(listaAdj[id]);
            realIds.push_back(id);
        }
        Grafo GRT(G.n, edgesRT);
        auto [Ge, edgesDict] = makeEulerian(GRT);
        auto euler = Euler(Ge);

        // Não necessariamente o grafo Ge é conexo, por isso é importante escolher um vértice de início que esteja na componente conexa de Ge
        int ini;
        for(int u=0;u<G.n;u++){
            if(uf.sz[u] > 1){
                ini = u;
                break;
            }
        }
        auto trilha = euler.trilha_euleriana_id(ini);
        for(auto &id: trilha){
            id = edgesDict[id]; // transforma arestas de M -> arestas de GRT
            id = realIds[id]; // transforma arestas de GRT -> arestas de G
        }
        return trilha;
    }
};
