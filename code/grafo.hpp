#ifndef GRAFO_H
#define GRAFO_H

#include <bits/stdc++.h>
using namespace std;

struct Aresta{
    int prox;
    int id;
};

struct Grafo{
    int n;
    vector<vector<Aresta>> adj;

    Grafo () {}

    /// Constrói grafo não direcionado a partir do número de vértices e uma lista de arestas. Assume-se que os vértices vão de 0 a n-1.
    /// Recebe: 
    ///     'nn' o número de vértices do grafo, 
    ///     'arestas' a lista de pares de vértices que possuem uma aresta entre si
    Grafo(int nn, vector<pair<int, int>> arestas): n(nn) {
        adj.resize(n);
        for(int i=0;i<(int)arestas.size();i++){
            pair<int, int> ar = arestas[i];
            assert(ar.first >= 0 && ar.first < n);
            adj[ar.first].push_back({ar.second, i});
            assert(ar.second >= 0 && ar.second < n);
            adj[ar.second].push_back({ar.first, i});
        }
    }

    /// Constrói grafo não direcionado a partir da lista de adjacências. Assume-se que os vértices vão de 0 a adjj.size()-1.
    /// Recebe: 
    ///     'adjj' a lista de adjacências do grafo
    Grafo(vector<vector<Aresta>> adjj) : n((int)adjj.size()), adj(adjj) {} 

    void print(){
        printf("Grafo com %d nós\nArestas:\n", n);
        for(int a=0;a<n;a++){
            for(Aresta ar: adj[a]){
                if(a <= ar.prox)
                printf("%d %d\n", a, ar.prox);
            }
        }
    }
};

#endif