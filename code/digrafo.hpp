#ifndef DIGRAFO_H
#define DIGRAFO_H

#include <bits/stdc++.h>
using namespace std;

#include "aresta.hpp"

struct Digrafo{
    int n, m;
    vector<vector<Aresta>> adj;

    Digrafo () {}

    /// Constrói grafo direcionado a partir do número de vértices e uma lista de arcos. Assume-se que os vértices vão de 0 a n-1.
    /// Recebe: 
    ///     'nv' o número de vértices do grafo, 
    ///     'arcos' a lista de pares de vértices que possuem um arco entre si
    Digrafo(int nv, vector<pair<int, int>> arcos): n(nv), m((int)arcos.size()) {
        adj.resize(n);
        for(int i=0;i<m;i++){
            pair<int, int> ar = arcos[i];
            assert(ar.first >= 0 && ar.first < n);
            assert(ar.second >= 0 && ar.second < n);
            adj[ar.first].push_back(Aresta(ar.second, i));
        }
    }

    /// Constrói grafo direcionado a partir do número de vértices e uma lista de arcos com pesos. Assume-se que os vértices vão de 0 a n-1.
    /// Recebe: 
    ///     'nv' o número de vértices do grafo, 
    ///     'arcos' a lista de vértices que possuem um arco entre si e o custo de tal arco
    Digrafo(int nv, vector<tuple<int, int, double>> arcos): n(nv), m((int)arcos.size()) {
        adj.resize(n);
        for(int i=0;i<m;i++){
            int u, v; double cus;
            tie(u, v, cus) = arcos[i];
            assert(u >= 0 && u < n);
            assert(v >= 0 && v < n);
            adj[u].push_back(Aresta(v, i, cus));
        }
    }

    /// Constrói grafo direcionado a partir da lista de adjacências. Assume-se que os vértices vão de 0 a adjj.size()-1.
    /// Recebe: 
    ///     'adjj' a lista de adjacências do grafo, cada par (v, c) na linha u indica um arco de custo c de u a v
    Digrafo(vector<vector<pair<int, double>>> adjj) : n((int)adjj.size()) {
        adj.clear();
        m = 0;
        for(int u=0;u<n;u++){
            for(auto ar: adjj[u]){
                int v = ar.first;
                double cus = ar.second;
                adj[u].push_back(Aresta(v, m++, cus));
            }
        }
    } 

    vector<tuple<int, int, double>> listaArcos(){
        vector<tuple<int, int, double>> arcos(m);
        for(int u=0;u<n;u++){
            for(Aresta ar: adj[u]){
                arcos[ar.id] = make_tuple(u, ar.prox, ar.cus);
            }
        }
        return arcos;
    }

    vector<vector<Aresta>> getAdjInverso(){
        vector<vector<Aresta>> inv(n);
        for(int u=0;u<n;u++){
            for(Aresta ar: adj[u]){
                inv[ar.prox].pb(Aresta(u, ar.id, ar.cus));
            }
        }
        return inv;
    }

    void print(){
        printf("Digrafo com %d nós e %d arcos:\n", n, m);
        for(int a=0;a<n;a++){
            for(Aresta ar: adj[a]){
                printf("%d %d %.3f (id %d)\n", a, ar.prox, ar.cus, ar.id);
            }
        }
    }
};

#endif