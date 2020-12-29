// Problema do carteiro com ruas com vento (windy postman problem), ou problema do carteiro chinês em grafo íngreme.
// Resolve o caso particular em que todo circuito de um grafo possui o mesmo custo em ambos sentidos.

#include "bits/stdc++.h"
using namespace std;

#include "grafo-ingreme.hpp"
#include "grafo.hpp"
#include "aresta-ingreme.hpp"
#include "pcc-grafo.cpp"

struct PCV {
    private:
    // Função auxiliar que checa se os ciclos de G possuem o mesmo custo independente do sentido que são percorridos.
    bool dfs(int u, int lstId, vector<bool> &mrk, vector<double> &pc, vector<double> &pic, GrafoIngreme &G){
        bool ok = true;
        mrk[u] = true;
        for(auto [nxt, id, c, ic]: G.adj[u]){
            if(id == lstId) continue;
            double nxtc = pc[u] + c;
            double nxtic = pic[u] + ic;
            if(mrk[nxt]){
                ok &= (nxtc - pc[nxt] == nxtic - pic[nxt]);
            }
            else{
                pc[nxt] = nxtc;
                pic[nxt] = nxtic;
                ok &= dfs(nxt, id, mrk, pc, pic, G);
            }
        }
        return ok;
    }

    public:
    // Checa se todo ciclo do grafo G tem o mesmo custo independente do sentido que é percorrido.
    bool checkCyclesCost(GrafoIngreme G){
        vector<bool> mrk(G.n, 0);
        vector<double> pathCost(G.n, 0.), pathInvCost(G.n, 0.);
        return dfs(0, -1, mrk, pathCost, pathInvCost, G);
    }

    // Devolve o custo e os identificadores de uma solução para o Problema do Carteiro Íngreme
    pair<double, vector<int>> solve(GrafoIngreme G){
        assert(checkCyclesCost(G));
        auto listaArestas = G.listaArestas();
        vector<tuple<int, int, double>> arestas;
        for(auto [u, v, c1, c2]: listaArestas)
            arestas.emplace_back(u, v, (c1 + c2)/2.);
        Grafo nG(G.n, arestas);
        auto pcc = PCC(nG);
        return pcc.solveById();
    }
};