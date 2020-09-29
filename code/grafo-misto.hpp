#ifndef MISTO_H
#define MISTO_H

#include <bits/stdc++.h>
using namespace std;
#include "aresta.hpp"

struct Misto{
    /// 'n' representa o número de vértices e 'm' o total de arestas e arcos
    int n, m;
    // Quantidade de arestas (Não arcos) desse grafo
    int nArestas;
    /// 'adj' armazena a lista de adjacências do digrafo
    vector<vector<Aresta>> adj;

    Misto () {}

    /// Constrói grafo a partir do número de vértices e uma lista de arestas. Assume-se que os vértices vão de 0 a n-1.
    /// Recebe: 
    ///     'nn' o número de vértices do grafo, 
    ///     'arestas' a lista de pares de vértices que possuem uma aresta entre si
    Misto(int n, vector<pair<int, int>> arestas): n(n), m((int)arestas.size()) {
        adj.resize(n);
        for(int i=0;i<(int)arestas.size();i++){
            pair<int, int> ar = arestas[i];
            assert(ar.first >= 0 && ar.first < n);
            adj[ar.first].emplace_back(ar.second, i);
            assert(ar.second >= 0 && ar.second < n);
            adj[ar.second].emplace_back(ar.first, i);
        }
    }

    Misto(int n, vector<tuple<int, int, double>> arestas): n(n), m((int)arestas.size()) {
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
    Misto(vector<vector<Aresta>> adjj) : n((int)adjj.size()), adj(adjj) {
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

    /// Constrói, a partir do vetor de adjacências, um vetor com todas arestas e arcos do grafo, indexados pelo seu id.
    /// Retorna:
    ///     Vetor de tupla de inteiro, inteiro e double
    ///     Os primeiros 'nArestas' valores representam arestas, enquanto que os restantes arcos.
    ///     Exemplo: 
    ///         lista[i] = (u, v, c) -> Representa a aresta de id 'i', entre os vértices 'u' e 'v' com custo real 'c'.
    vector<tuple<int, int, double>> listaAdj(){
        vector<tuple<int, int, double>> lista(m);
        for(int u=0;u<n;u++){
            for(Aresta ar: adj[u]){
                lista[ar.id] = make_tuple(u, ar.prox, ar.cus);
            }
        }
        return lista;
    }

    /// Constrói, a partir da lista de adjacências a lista de arestas do grafo, indexadas por seus ids
    /// Retorna:
    ///     Vetor de tupla de inteiro, inteiro e double
    ///     Os primeiros 'nArestas' valores representam arestas, enquanto que os restantes arcos, por isso, apagam-se os arcos nesse método.
    ///     Exemplo: 
    ///         arestas[i] = (u, v, c) -> Representa a aresta de id 'i', entre os vértices 'u' e 'v' com custo real 'c'.
    vector<tuple<int, int, double>> listaArestas(){
        auto arestas = listaAdj();
        arestas.resize(nArestas);
        return arestas;
    }

    /// Constrói, a partir da lista de adjacências a lista de arcos do grafo, indexadas por seus ids subtraidos de 'nArestas'
    /// Retorna:
    ///     Vetor de tupla de inteiro, inteiro e double
    ///     Os primeiros 'nArestas' valores representam arestas, enquanto que os restantes arcos, por isso, apagam-se os arcos nesse método.
    ///     Exemplo: 
    ///         arestas[i] = (u, v, c) -> Representa a aresta de id 'i', entre os vértices 'u' e 'v' com custo real 'c'.
    /// Cuidado: os arcos não são indexados por seus 'id's, seus 'id's na verdade são i + nArestas
    vector<tuple<int, int, double>> listaArcos(){
        auto arcos = listaAdj();
        arcos.erase(arcos.begin(), arcos.begin() + nArestas); 
        return arcos;
    }

    /// Testa se aresta com identificador 'id' é aresta.
    bool aresta(int id){
        assert(id >= 0);
        return (id < nArestas);
    }

    /// Testa se aresta com identificador 'id' é arco.
    bool arco(int id){
        assert(id >= 0);
        return (id >= nArestas);
    }

    /// Função de depuração que imprime o grafo e todas suas arestas.
    void print(){
        printf("Grafo misto com %d nós\nArestas:\n", n);
        for(int a=0;a<n;a++){
            for(Aresta ar: adj[a]){
                if(a <= ar.prox)
                    printf("%d %d %.3f (id %d)\n", a, ar.prox, ar.cus, ar.id);
            }
        }
    }
};

#endif