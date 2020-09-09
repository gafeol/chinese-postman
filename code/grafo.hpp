#ifndef GRAFO_H
#define GRAFO_H

#include <bits/stdc++.h>
using namespace std;
#include "aresta.hpp"

struct Grafo{
    int n, m;
    vector<vector<Aresta>> adj;

    Grafo () {}

    /// Constrói grafo não direcionado a partir do número de vértices e uma lista de arestas. Assume-se que os vértices vão de 0 a n-1.
    /// Recebe: 
    ///     'nn' o número de vértices do grafo, 
    ///     'arestas' a lista de pares de vértices que possuem uma aresta entre si
    Grafo(int n, vector<pair<int, int>> arestas): n(n), m((int)arestas.size()) {
        adj.resize(n);
        for(int i=0;i<(int)arestas.size();i++){
            pair<int, int> ar = arestas[i];
            assert(ar.first >= 0 && ar.first < n);
            adj[ar.first].emplace_back(ar.second, i);
            assert(ar.second >= 0 && ar.second < n);
            adj[ar.second].emplace_back(ar.first, i);
        }
    }

    Grafo(int n, vector<tuple<int, int, double>> arestas): n(n), m((int)arestas.size()) {
        adj.resize(n);
        for(int i=0;i<(int)arestas.size();i++){
            int u, v; double cus;
            tie(u, v, cus) = arestas[i];
            assert(u >= 0 && u < n);
            adj[u].emplace_back(v, i, cus);
            assert(v >= 0 && v < n);
            adj[v].emplace_back(u, i, cus);
        }
    }

    /// Constrói grafo não direcionado a partir da lista de adjacências. Assume-se que os vértices vão de 0 a adjj.size()-1.
    /// Recebe: 
    ///     'adjj' a lista de adjacências do grafo
    Grafo(vector<vector<Aresta>> adjj) : n((int)adjj.size()), adj(adjj) {
        m = 0;
        for(int u=0;u<(int)adj.size();u++){
            m += adj[u].size();
        }
        m /= 2;
        for(int u=0;u<(int)adj.size();u++){
            for(Aresta ar: adj[u]){
                assert(ar.id < m); // Garante que todas arestas tem id < m
            }
        }
    } 

    void print(){
        printf("Grafo com %d nós\nArestas:\n", n);
        for(int a=0;a<n;a++){
            for(Aresta ar: adj[a]){
                if(a <= ar.prox)
                    printf("%d %d %.3f (id %d)\n", a, ar.prox, ar.cus, ar.id);
            }
        }
    }

    vector<tuple<int, int, double>> listaArestas(){
        vector<tuple<int, int, double>> arestas(m);
        for(int u=0;u<n;u++){
            for(Aresta ar: adj[u]){
                arestas[ar.id] = make_tuple(u, ar.prox, ar.cus);
            }
        }
        return arestas;
    }
};

#endif