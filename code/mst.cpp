#ifndef MST_H
#define MST_H

#include "bits/stdc++.h"
using namespace std;
#include "union-find.cpp"

/// Implements Kruskal algorithm to find MST in graph
struct MST{
    vector<tuple<int, int, double>> solve(Grafo G){
        vector<tuple<int, int, double>> ans;
        auto uf = UnionFind(G.n);
        auto listaAdj = G.listaArestas();

        sort(listaAdj.begin(), listaAdj.end(), [](tuple<int, int, double> a, tuple<int, int, double> b) { return get<double>(a) < get<double>(b);  });

        for(auto [i, j, c]: listaAdj){
            if(uf.join(i, j)){
                ans.emplace_back(i, j, c);
            }
        }
        return ans;
    }
};

#endif