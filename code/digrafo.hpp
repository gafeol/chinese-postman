#ifndef DIGRAFO_H
#define DIGRAFO_H

#include <bits/stdc++.h>
using namespace std;

#include "aresta.hpp"

struct Digrafo{
    /// 'n' representa o número de vértices e 'm' o de arcos
    int n, m;
    /// 'adj' armazena a lista de adjacências do digrafo
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
            adj[ar.first].emplace_back(ar.second, i);
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
            adj[u].emplace_back(v, i, cus);
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
                adj[u].emplace_back(v, m++, cus);
            }
        }
    } 

    /// Constrói, a partir da lista de adjacências, um vetor com todos arcos do digrafo, indexados pelo seu id.
    /// Retorna:
    ///     Vetor de tupla de inteiro, inteiro e double
    ///     Exemplo: 
    ///         arcos[i] = (u, v, c) -> Representa o arco de id 'i', do nó 'u' a 'v' com custo real 'c'.
    vector<tuple<int, int, double>> listaArcos(){
        vector<tuple<int, int, double>> arcos(m);
        for(int u=0;u<n;u++){
            for(Aresta ar: adj[u]){
                arcos[ar.id] = make_tuple(u, ar.prox, ar.cus);
            }
        }
        return arcos;
    }

    /// Constrói, a partir da lista de adjacências, a lista de adjacências inversa.
    /// Se existe um arco de u a v no grafo, a lista de adjacências inversa representará uma aresta de mesmo id e custo de v a u
    /// Particularmente útil para conseguir calcular o grau de entrada de cada vértice.
    /// Retorna:
    ///     Vector de vector de Aresta, representando a lista de adjacências inversa do grafo
    vector<vector<Aresta>> getAdjInverso(){
        vector<vector<Aresta>> inv(n);
        for(int u=0;u<n;u++){
            for(Aresta ar: adj[u]){
                inv[ar.prox].emplace_back(u, ar.id, ar.cus);
            }
        }
        return inv;
    }

    /// Função de depuração que imprime o digrafo e todos seus arcos.
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