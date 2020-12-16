#include "bits/stdc++.h"
using namespace std;
#include "digrafo.hpp"
#include "union-find.cpp"
#include "floyd-warshall.cpp"
#include "ssa.cpp"


struct compress {
    private:
    Digrafo oriG, compG;
    vector<int> arcDict; 
    vector<vector<int>> vDict;
    UnionFind uf;


    /// Retorna a lista de novos "id" para os arcos do grafo original.
    /// Exemplo: seja oriId o índice de um vértice do grafo original oriG, o valor de id[oriId] será o valor de índice do vértice condensado correspondente no grafo compG
    /// Essa função também preenche o valor de vDict, que tem a associação inversa, mapeando cada vértice de compG para os vértices originais que o compõe.
    vector<int> getNewV(){
        // Renomeando nós de G para nós de compG
        vector<int> newV(oriG.n);
        int cnt = 0;
        for(int u=0;u<oriG.n;u++)
            if(uf.p[u] == u)
                newV[u] = cnt++;
        vDict.clear();
        vDict.resize(cnt);
        for(int u=0;u<oriG.n;u++){
            newV[u] = newV[uf.raiz(u)];
            vDict[uf.raiz(u)].push_back(u);
        }
        return newV;
    }


    public:
    // Recebe um digrafo G e um conjunto de arcos A que devem ser comprimidos.
    // O grafo G será salvo em oriG, e a compressão desse grafo será salva por compG.
    compress(Digrafo G, vector<int> A) : oriG(G), uf(UnionFind(G.n)) {
        auto listaArcos = G.listaArcos();
        for(int id: A){
            auto [u, v, c] = listaArcos[id];
            uf.join(u, v);
        }

        auto newV = getNewV();

        // Criando a lista de adjacências do grafo comprimido
        vector<tuple<int, int, double>> nAdj;
        arcDict.clear();
        arcDict.resize(G.m);
        for(int u=0;u<G.n;u++){
            for(auto [v, id, c] : G.adj[u]){
                if(newV[u] == newV[v]) continue;
                arcDict[id] = nAdj.size();
                nAdj.emplace_back(newV[u], newV[v], c);
            }
        }
        compG = Digrafo(uf.nComp, nAdj);
    }

    // Devolve o grafo comprimido gerado.   
    Digrafo getCompressed(){
        return compG;
    }

    // Recebe o identificador de um arco do grafo comprimido e devolve o identificador da aresta correspondente no grafo original.
    int arcId(int id){
        return arcDict[id];
    }

    // Recebe o identificador de um vértice do grafo comprimido e devolve o identificador dos vértices correspondente no grafo original.
    vector<int> vId(int v){
        return vDict[v];
    }
};

vector<int> expande(int ini, int fim, vector<vector<double>> &mnDist, Digrafo &G){
    if(ini == fim)
        return {};
    auto &adj = G.adj;
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

struct PCR {
    /// Devolve uma solução do PCR: um circuito que percorre todo arco de R ao menos uma vez.
    /// Serão retornados o custo da solução encontrada pro PCR e um vetor dos arcos que formam a solução.
    pair<double, vector<int>> solve(Digrafo G, vector<int> R){
        // Condensar o grafo nas R-componentes
        auto comp = compress(G, R);
        auto cG = comp.getCompressed();

        // Condensa o grafo cG em um Kcomp, grafo completo contendo apenas as componentes condensadas.
        auto mnDist = floyd_warshall(cG);

        vector<int> compId;
        for(int u=0;u<cG.n;u++){
            if(comp.vId(u).size() > 1){ // Vertice adjacente a arco de R
                compId.push_back(u);
            }
        }
        int nComps = compId.size();

        vector<vector<double>> compAdj(nComps, vector<double>(nComps));
        for(int u=0;u<nComps;u++){
            for(int v=0;v<nComps;v++){
                compAdj[u][v] = mnDist[compId[u]][compId[v]];
            }
        }
        auto Kcomp = Digrafo(compAdj);
        auto cl = ChuLiu(Kcomp);
        auto ssaKcomp = cl.solve()

        // Passa de Kcomp -> cG
        auto listaAdjKcomp = Kcomp.listaArcos();
        vector<int> ssacG;
        for(int id: ssaKcomp){ 
            auto [u, v, c] = listaAdjKcomp[id];
            auto aux = expande(u, v, compAdj, cG);
            ssacG.insert(ssacG.end(), aux.begin(), aux.end());
        }


        // Passa de cG -> G
        vector<int> ans;
        for(int id: cGAns){
            ans.push_back(comp.arcId(id));
        }
        return ans;
    }
}
