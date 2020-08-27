#ifndef DIGRAFO_H
#define DIGRAFO_H

#include <bits/stdc++.h>
using namespace std;

struct Digrafo{
    int n;
    vector<vector<int>> adj;

    Digrafo () {}

    /// Constrói grafo direcionado a partir do número de vértices e uma lista de arcos. Assume-se que os vértices vão de 0 a n-1.
    /// Recebe: 
    ///     'nv' o número de vértices do grafo, 
    ///     'arcos' a lista de pares de vértices que possuem um arco entre si
    Digrafo(int nv, vector<pair<int, int>> arcos): n(nv) {
        adj.resize(n);
        for(int i=0;i<(int)arcos.size();i++){
            pair<int, int> ar = arcos[i];
            assert(ar.first >= 0 && ar.first < n);
            assert(ar.second >= 0 && ar.second < n);
            adj[ar.first].push_back(ar.second);
        }
    }

    /// Constrói grafo não direcionado a partir da lista de adjacências. Assume-se que os vértices vão de 0 a adjj.size()-1.
    /// Recebe: 
    ///     'adjj' a lista de adjacências do grafo
    Digrafo(vector<vector<int>> adjj) : n((int)adjj.size()), adj(adjj) {} 

    void print(){
        printf("Digrafo com %d nós\nArcos:\n", n);
        for(int a=0;a<n;a++){
            for(int nxt: adj[a]){
                if(a <= nxt)
                printf("%d %d\n", a, nxt);
            }
        }
    }
};

#endif