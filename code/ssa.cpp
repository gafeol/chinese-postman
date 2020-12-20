// Arborescência geradora mínima (Shortest Spanning Arborescence) - Algoritmo de Chu-Liu/Edmonds
#include "bits/stdc++.h"
using namespace std;
#include "digrafo.hpp"
#include "union-find.cpp"
#include "floyd-warshall.cpp"

// Implementação adaptada do algoritmo de Chu-Liu por el-vasito 
// (https://github.com/mhunicken/icpc-team-notebook-el-vasito)
struct edge {
    int u, v, id;
    double cus;
};
struct ChuLiu {
    const double INF = DBL_MAX / 2.;
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

vector<int> expande(int ini, int fim, Digrafo &G, vector<vector<double>> &mnDist){
    printf("expande ini %d fim %d dis %.4f\n", ini, fim, mnDist[ini][fim]);
    if(ini == fim)
        return {};
    vector<int> ans;
    for(Aresta ar: G.adj[ini]){
        if(ar.cus + mnDist[ar.prox][fim] == mnDist[ini][fim]){
            printf("    usa aresta %d %d %.4f\n", ini, ar.prox, ar.cus);
            ans.push_back(ar.id);
            auto aux = expande(ar.prox, fim, G, mnDist);
            ans.insert(ans.end(), aux.begin(), aux.end());
            return ans;
        }
    }
    puts("assert false aqui no expande");
    assert(false);
}

struct compress {
    private:
    Digrafo oriG, compG;
    vector<int> arcDict, newV; 
    vector<vector<int>> vDict;
    UnionFind uf;


    /// Preenche a lista de novos "id" para os arcos do grafo original.
    /// Exemplo: seja oriId o índice de um vértice do grafo original oriG, o valor de id[oriId] será o valor de índice do vértice condensado correspondente no grafo compG
    /// Essa função também preenche o valor de vDict, que tem a associação inversa, mapeando cada vértice de compG para os vértices originais que o compõe.
    void getNewV(){
        // Renomeando nós de G para nós de compG
        assert((int)newV.size() == oriG.n);
        int cnt = 0;
        for(int u=0;u<oriG.n;u++)
            if(uf.p[u] == u)
                newV[u] = cnt++;
        vDict.clear();
        vDict.resize(cnt);
        for(int u=0;u<oriG.n;u++){
            newV[u] = newV[uf.raiz(u)];
            vDict[newV[uf.raiz(u)]].push_back(u);
        }
    }


    public:
    // Recebe um digrafo G e um conjunto de arcos A que devem ser comprimidos.
    // O grafo G será salvo em oriG, e a compressão desse grafo será salva por compG.
    compress(Digrafo G, vector<int> A) : oriG(G), newV(vector<int>(G.n)), uf(UnionFind(G.n)) {
        auto listaArcos = G.listaArcos();
        for(int id: A){
            auto [u, v, c] = listaArcos[id];
            uf.join(u, v);
        }

        getNewV();

        // Criando a lista de adjacências do grafo comprimido
        vector<tuple<int, int, double>> nAdj;
        arcDict.clear();
        for(int u=0;u<G.n;u++){
            for(auto [v, id, c] : G.adj[u]){
                if(newV[u] == newV[v]) continue;
                arcDict.push_back(id);
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

    // Recebe o identificador de um vértice do grafo original e devolve seu identificador correspondente comprimido.
    // É o inverso da função vId
    int newVId(int v){
        return newV[v];
    }
};

/// Encontra a arborescência geradora mínima do grafo G enraizado em um vértice especial qualquer (pertencente a uma componente de R).
/// Serão retornados tanto a raiz escolhida para o grafo quanto um vetor dos arcos que formam a arborescência.
pair<double, vector<int>> findRuralSSA(Digrafo G, vector<int> R, int root=-1){
    // Condensar o grafo nas R-componentes
    auto comp = compress(G, R);
    auto cG = comp.getCompressed();

    root = (root >= 0 ? comp.newVId(root) : root);
    printf("root %d\n", root);

    puts("print cG");
    cG.print();

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
    for(int i=0;i<nComps;i++){
        for(int j=0;j<nComps;j++){
            compAdj[i][j] = mnDist[compId[i]][compId[j]];
        }
    }
    root = (root >= 0 ? compId[root] : 0);
    printf("root %d\n", root);
    auto Kcomp = Digrafo(compAdj);
    auto cl = ChuLiu(Kcomp);
    printf("ChuLiu com root %d\n\n\n\n", root);
    auto [ssaCost, ssaKcomp] = cl.solve(root);

    puts("Kcomp:");
    Kcomp.print();

    // Passa de Kcomp -> cG
    auto listaAdjKcomp = Kcomp.listaArcos();
    vector<int> ssaCG;
    printf("listaAdjKcomp sz %d\n", (int)listaAdjKcomp.size());
    for(int id: ssaKcomp){ 
        printf("id %d\n", id);
        auto [ku, kv, c] = listaAdjKcomp[id];
        int u = compId[ku];
        int v = compId[kv];

        printf("u %d v %d c %.4f\n", u, v, c);
        auto aux = expande(u, v, cG, mnDist);
        puts("expandiu");
        ssaCG.insert(ssaCG.end(), aux.begin(), aux.end());
    }
    // Passa de cG -> G
    vector<int> ssa;
    for(int id: ssaCG){
        printf("retrieve ArcId(%d): ", id);
        ssa.push_back(comp.arcId(id));
        printf("%d\n", comp.arcId(id));
    }
    puts("got ssa");
    return {ssaCost, ssa};
}
