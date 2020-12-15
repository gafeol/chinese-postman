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


/// Se o grafo induzido pelos arcos pi possuir circuitos, essa função retornará o vetor contendo os vértices de um circuito desse grafo.
vector<int> extractCycle(Digrafo &G, vector<int> &pi){
    auto lista = G.listaArcos();
    vector<vector<pair<int, double>>> adjPi(G.n);
    vector<int> indeg(G.n, 0);
    for(int u=0;u<G.n;u++){
        auto [i, j, c] = lista[pi[u]];
        adjPi[i].emplace_back(j, c);
        indeg[j]++;
    }
    queue<int> q;
    for(int u=0;u<G.n;u++){
        
    }
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


    vector<int> C = extractCycle(G, pi);

    auto comp = compress(G, C);

    auto cAns = findSSA(comp.getCompressed());




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


// Implementação do ChuLiu por elvasito (https://github.com/mhunicken/icpc-team-notebook-el-vasito)
double INF = DBL_MAX/2.;
struct edge {
    int u, v, id;
    double cus;
};
struct ChuLiu {
    int n;
    vector<edge> e;
    vector<int> inc, dec, take, pre, num, id, vis;
    vector<double> inw;
    void add_edge(int x, int y, double w) {
        inc.push_back(0);
        dec.push_back(0);
        take.push_back(0);
        e.push_back({x, y, (int)e.size(), w});
    }
    ChuLiu(int n) : n(n), pre(n), num(n), id(n), vis(n), inw(n) {}

    ChuLiu(Digrafo G) : ChuLiu(G.n) {
        auto lista = G.listaArcos();
        for (int id = 0; id < G.m; id++) {
            auto [u, v, c] = lista[id];
            add_edge(u, v, c);
        }
    }

    pair<double, vector<int>> solve(int root) {
        auto eCopy = e;
        double ans = 0;
        int eg = e.size() - 1, pos = e.size() - 1;
        while (1) {
            for (int i = 0; i < n; i++) {
                inw[i] = INF; 
                id[i] = vis[i] = -1;
            }
            // Define a função pi(v), representando o arco de menor custo que chega em v.
            // O arco pi(v) é representada pelos valores: num[v] - salvando o id do arco, pre[v] - salvando a origem do arco e inw[v] - salvando o custo do arco
            for (auto [u, v, id, cus] : eCopy)
                if (cus < inw[v]) {
                    inw[v] = cus;
                    pre[v] = u;
                    num[v] = id;
                }
            inw[root] = 0; // Remove-se o pi(root).
            assert(*max_element(inw.begin(), inw.end()) < INF);
            int tot = -1;
            for (int i = 0; i < n; i++) {
                ans += inw[i];
                if (i != root)
                    take[num[i]]++;
                int j = i;
                while (vis[j] != i && j != root && id[j] < 0)
                    vis[j] = i, j = pre[j];
                if (j != root && id[j] < 0) {
                    id[j] = ++tot;
                    for (int k = pre[j]; k != j; k = pre[k])
                        id[k] = tot;
                }
            }
            if (tot < 0)
                break;
            for (int i = 0; i < n; i++)
                if (id[i] < 0)
                    id[i] = ++tot;
            n = tot + 1;
            int j = 0;
            for (int i = 0; i < (int)eCopy.size(); i++) {
                int v = eCopy[i].v;
                eCopy[j].v = id[eCopy[i].v];
                eCopy[j].u = id[eCopy[i].u];
                if (eCopy[j].v != eCopy[j].u) {
                    eCopy[j].cus = eCopy[i].cus - inw[v];
                    inc.push_back(eCopy[i].id);
                    dec.push_back(num[v]);
                    take.push_back(0);
                    eCopy[j++].id = ++pos;
                }
            }
            eCopy.resize(j);
            root = id[root];
        }
        while (pos > eg) {
            if (take[pos] > 0)
                take[inc[pos]]++, take[dec[pos]]--;
            pos--;
        }
        vector<int> edges; 
        for(int id=0;id<(int)e.size();id++){
            if(take[id])
                edges.push_back(id);
        }
        return {ans, edges};
    }
};
