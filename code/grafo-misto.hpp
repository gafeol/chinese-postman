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
    
    /// Constrói, a partir da lista de adjacências, a lista de adjacências inversa.
    /// Se existe um arco de u a v no grafo, a lista de adjacências inversa representará uma aresta de mesmo id e custo de v a u
    /// No caso de existir uma aresta entre u e v, a mesma aresta continuará se encontrando nas adjacencias de u e v.
    /// Particularmente útil para conseguir calcular o grau de entrada + grau não direcionado de cada vértice.
    /// Retorna:
    ///     Vector de vector de Aresta, representando a lista de adjacências inversa do grafo
    vector<vector<Aresta>> adjInverso(){
        vector<vector<Aresta>> inv(n);
        for(int u=0;u<n;u++){
            for(Aresta ar: adj[u]){
                inv[ar.prox].emplace_back(u, ar.id, ar.cus);
            }
        }
        return inv;
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


    vector<bool> vis;
    vector<int> cy, id, mn;
    stack<int> q;
    int nc, idd;

    int tarjan(int u) {
        q.push(u);
        vis[u] = true;
        id[u] = idd++;
        mn[u] = id[u];
        for (Aresta ar : adj[u]) {
            int nxt = ar.prox;
            if (!vis[nxt])
                mn[u] = min(mn[u], tarjan(nxt));
            else if(cy[nxt] == cy[u])
                mn[u] = min(mn[u], id[nxt]);
        }
        if(mn[u] == id[u]){
            cy[u] = nc++;
            while(q.top() != u){
                cy[q.top()] = cy[u];
                q.pop();
            }
            q.pop();
        }
        return mn[u];
    }

    /// Conta o número de componentes fortemente conexas em 'digrafo'
    /// Implementação do algoritmo de Tarjan
    int countSCC() {
        vis.clear();
        vis.resize(n, false);
        cy.clear();
        cy.resize(n, -1);
        id.resize(n);
        mn.resize(n);
        nc = 0;
        idd = 0;
        while(!q.empty())
            q.pop();
        for (int ini = 0; ini < n; ini++) {
            if (!vis[ini])
                tarjan(ini);
        }
        return nc;
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