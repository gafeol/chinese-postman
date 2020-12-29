#ifndef GRAFO_ING_H
#define GRAFO_ING_H

#include "bits/stdc++.h"
using namespace std;
#include "aresta-ingreme.hpp"

struct GrafoIngreme{
    /// 'n' representa o número de vértices e 'm' o de arestas
    int n, m;
    /// 'adj' armazena a lista de adjacências do grafo
    vector<vector<ArestaIngreme>> adj;

    GrafoIngreme () {}

    GrafoIngreme(int n, vector<tuple<int, int, double, double>> arestas): n(n), m((int)arestas.size()) {
        adj.resize(n);
        for(int i=0;i<(int)arestas.size();i++){
            auto [u, v, dirCus, invCus] = arestas[i];
            assert(u >= 0 && u < n);
            adj[u].emplace_back(v, i, dirCus, invCus);
            assert(v >= 0 && v < n);
            adj[v].emplace_back(u, i, invCus, dirCus);
        }
    }

    /// Constrói, a partir da lista de adjacências, um vetor com todos arcos do grafo, indexados pelo seu id.
    /// Retorna:
    ///     Vetor de tupla de inteiro, inteiro, double e double
    ///     Exemplo: 
    ///         arcos[i] = (u, v, c1, c2) -> Representa a aresta de id 'i', entre os vértices 'u' e 'v' com custo real 'c1' para percorrer u -> v e 'c2' para v -> u.
    vector<tuple<int, int, double, double>> listaArestas(){
        vector<tuple<int, int, double, double>> arestas(m);
        for(int u=0;u<n;u++){
            for(ArestaIngreme ar: adj[u]){
                arestas[ar.id] = make_tuple(u, ar.prox, ar.dirCus, ar.invCus);
            }
        }
        return arestas;
    }

    /// Função de depuração que imprime o grafo e todas suas arestas.
    void print(){
        printf("GrafoIngreme com %d nós\nArestas:\n", n);
        for(int a=0;a<n;a++){
            for(ArestaIngreme ar: adj[a]){
                if(a <= ar.prox)
                    printf("%d %d %.3f %.3f (id %d)\n", a, ar.prox, ar.dirCus, ar.invCus, ar.id);
            }
        }
    }
};

#endif