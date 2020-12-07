// Arborescência geradora mínima (Shortest Spanning Arborescence) - Algoritmo de Chu-Liu/Edmonds
#include "bits/stdc++.h"
using namespace std;
#include "digrafo.hpp"
#include "union-find.cpp"
#include "floyd-warshall.cpp"

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

    /// Realiza a compressão do algoritmo de Chu-Liu.
    compress(Digrafo G, vector<int> C, vector<Aresta> pi): oriG(G), uf(UnionFind(G.n)) {
        auto listaArcos = G.listaArcos();
        for(int i=0;i+1<(int)C.size();i++)
            uf.join(C[i], C[i+1]);
        int cycleRoot = uf.raiz(C[0]);
        auto newV = getNewV();
        // Criando a lista de adjacências do grafo comprimido
        vector<tuple<int, int, double>> nAdj;
        arcDict.clear();
        arcDict.resize(G.m);
        for(int u=0;u<G.n;u++){
            for(auto [v, id, c] : G.adj[u]){
                if(newV[u] == newV[v]) continue;
                arcDict[id] = nAdj.size();
                if(uf.raiz(v) == cycleRoot) // an edge coming into the cycle
                    nAdj.emplace_back(newV[u], newV[v], c - pi[v].cus);
                else // an edge going away from the cycle or unrelated to the cycle
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

/// Encontra a arborescência geradora mínima do grafo G enraizado em 'root'.
vector<int> findSSA(Digrafo G, int root=0){
    // Checar se G é fortemente conexo
    assert(G.countSCC() == 1);
    // Remover arcos do grafo que apontem para a raiz
    for(int u=0;u<G.n;u++){
        for(int i=G.adj[u].size()-1;i>=0;i--){
            auto [v, id, c] = G.adj[u][i];
            if(v == root){
                swap(G.adj[u][i], G.adj[u].back());
                G.adj[u].pop_back();
            }
        }
    }

    // CUIDADO: Alguns id nao existem mais, foram removidos os que apontam para root
    // Gerar grafo induzido por pi(v)
    auto lista = G.listaArcos();
    auto inv  = G.getAdjInverso();
    vector<int> pi(G.n);
    for(int u=0;u<G.n;u++){
        double minCost = DBL_MAX;
        for(auto [v, id, c] : inv[u]){
            if(c < minCost){
                minCost = c;
                pi[u] = id;
            }
        }
    }

    // TODO: continuar daqui!

    // Checar se o grafo induzido possui ao menos um circuito.
    // - Se não, só retorna pi.
    // - Se sim, então pega as arestas do circuito, condensa o grafo nelas e chama findSSA nele. Depois precisa descondensar o grafo pra remontar o pi.
    /*
       Otherwise, P {\displaystyle P} P contains at least one cycle. Arbitrarily choose one of these cycles and call it C {\displaystyle C} C. We now define a new weighted directed graph D ′ = ⟨ V ′ , E ′ ⟩ {\displaystyle D^{\prime }=\langle V^{\prime },E^{\prime }\rangle } D^\prime = \langle V^\prime, E^\prime \rangle in which the cycle C {\displaystyle C} C is "contracted" into one node as follows:

       The nodes of V ′ {\displaystyle V^{\prime }} V^\prime are the nodes of V {\displaystyle V} V not in C {\displaystyle C} C plus a new node denoted v C {\displaystyle v_{C}} v_C.
       If ( u , v ) {\displaystyle (u,v)} (u,v) is an edge in E {\displaystyle E} E with u ∉ C {\displaystyle u\notin C} u\notin C and v ∈ C {\displaystyle v\in C} v\in C (an edge coming into the cycle), then include in E ′ {\displaystyle E^{\prime }} E^\prime a new edge e = ( u , v C ) {\displaystyle e=(u,v_{C})} e = (u, v_C), and define w ′ ( e ) = w ( u , v ) − w ( π ( v ) , v ) {\displaystyle w^{\prime }(e)=w(u,v)-w(\pi (v),v)} w^\prime(e) = w(u,v) - w(\pi(v),v).
       If ( u , v ) {\displaystyle (u,v)} (u,v) is an edge in E {\displaystyle E} E with u ∈ C {\displaystyle u\in C} u\in C and v ∉ C {\displaystyle v\notin C} v\notin C (an edge going away from the cycle), then include in E ′ {\displaystyle E^{\prime }} E^\prime a new edge e = ( v C , v ) {\displaystyle e=(v_{C},v)} e = (v_C, v), and define w ′ ( e ) = w ( u , v ) {\displaystyle w^{\prime }(e)=w(u,v)} w^\prime(e) = w(u,v) .
       If ( u , v ) {\displaystyle (u,v)} (u,v) is an edge in E {\displaystyle E} E with u ∉ C {\displaystyle u\notin C} u\notin C and v ∉ C {\displaystyle v\notin C} v\notin C (an edge unrelated to the cycle), then include in E ′ {\displaystyle E^{\prime }} E^\prime a new edge e = ( u , v ) {\displaystyle e=(u,v)} e=(u,v), and define w ′ ( e ) = w ( u , v ) {\displaystyle w^{\prime }(e)=w(u,v)} w^\prime(e) = w(u,v) .

       For each edge in E ′ {\displaystyle E^{\prime }} E^\prime, we remember which edge in E {\displaystyle E} E it corresponds to. 
    */
}



/// Encontra a arborescência geradora mínima do grafo G enraizado em um vértice especial qualquer (pertencente a uma componente de R).
/// Serão retornados tanto a raiz escolhida para o grafo quanto um vetor dos arcos que formam a arborescência.
vector<int> findRuralSSA(Digrafo G, vector<int> R){
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
    auto kAns = findSSA(Kcomp);

    // Passa de Kcomp -> cG
    auto listaAdjKcomp = Kcomp.listaArcos();
    vector<int> cGAns;
    for(int id: kAns){ 
        auto [u, v, c] = listaAdjKcomp[id];
        auto aux = expande(u, v, compAdj, cG);
        cGAns.insert(cGAns.end(), aux.begin(), aux.end());
    }
    // Passa de cG -> G
    vector<int> ans;
    for(int id: cGAns){
        ans.push_back(comp.arcId(id));
    }
    return ans;
}
