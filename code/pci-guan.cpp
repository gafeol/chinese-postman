// Problema do carteiro com ruas íngrimes (windy postman problem).
// Resolve o caso particular em que todo circuito de um grafo possui o mesmo custo em ambos sentidos.

#include "bits/stdc++.h"
using namespace std;

#include "grafo-ingrime.hpp"
#include "grafo.hpp"
#include "aresta-ingrime.hpp"
#include "pcc-grafo.cpp"

struct PCI {
    bool dfs(int u, int lstId, vector<bool> &mrk, vector<double> &pc, vector<double> &pic, GrafoIngrime &G){
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

    // Checa se todo ciclo do grafo G tem o mesmo custo independente do sentido que é percorrido.
    bool checkCyclesCost(GrafoIngrime G){
        vector<bool> mrk(G.n, 0);
        vector<double> pathCost(G.n, 0.), pathInvCost(G.n, 0.);
        return dfs(0, -1, mrk, pathCost, pathInvCost, G);
    }

    // Devolve o custo e os identificadores da 
    pair<double, vector<int>> solve(GrafoIngrime G){
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