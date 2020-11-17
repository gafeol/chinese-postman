#ifndef UNION_H
#define UNION_H

#include "bits/stdc++.h"
using namespace std;

/// Implementação de Union Find com operações "união" (join) e "raiz" em amortizado O(log*).
struct UnionFind {
    /// Número de vértices no grafo.
    int n;
    /// Array que guarda o ancestral direto de cada vértice.
    vector<int> p;
    /// Array que armazena o tamanho da subárvore de cada vértice.
    vector<int> sz;

    UnionFind(int n) : n(n) {
        p.resize(n);
        sz.resize(n);
        for(int u=0;u<n;u++){
            p[u] = u;
            sz[u] = 1;
        }
    }

    int raiz(int u){
        return (p[u] == u ? u : p[u] = raiz(p[u]));
    }

    bool join(int u, int v){
        u = raiz(u); v = raiz(v);
        if(u == v)
            return false;
        if(sz[u] < sz[v])
            swap(u, v);
        p[v] = u;
        sz[u] += sz[v];
        return true;
    }
};

#endif 