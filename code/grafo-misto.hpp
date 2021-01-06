#ifndef MISTO_H
#define MISTO_H

#include "bits/stdc++.h"
using namespace std;
#include "aresta.hpp"

struct Misto{
    /// 'n' representa o número de vértices e 'm' o total de arestas e arcos
    int n, m;
    // Quantidade de arestas (Não arcos) desse grafo
    int nArestas;
    /// 'adj' armazena a lista de adjacências do digrafo
    vector<vector<Aresta>> adj;
    /// 'idReal' armazena o 'id' base para as arestas e arcos copiados
    /// Ver método 'copia'
    map<int, int> idReal;
    /// 'idOriginal' armazena o 'id' da aresta original, sem orientação
    /// Ver construtor Misto(n, M, U)
    /// Utilizado para manter a identidade das arestas de um grafo 
    map<int, int> idOriginal;

    Misto () {}

    /// Constrói grafo misto a partir do número de vértices e da lista de arestas e de arcos. Assume-se que os vértices vão de 0 a n-1.
    /// Recebe: 
    ///     'n' o número de vértices do grafo, 
    ///     'arestas' a lista de pares de vértices que possuem uma aresta entre si
    ///     'arcos' a lista de arcos do grafo
    Misto(int n, vector<pair<int, int>> arestas, vector<pair<int, int>> arcos): n(n), m((int)arestas.size() + arcos.size()), nArestas((int)arestas.size()) {
        adj.resize(n);
        int id = 0;
        for(pair<int, int> ar: arestas){
            assert(ar.first >= 0 && ar.first < n);
            assert(ar.second >= 0 && ar.second < n);
            adj[ar.first].emplace_back(ar.second, id);
            adj[ar.second].emplace_back(ar.first, id);
            id++;
        }
        for(pair<int, int> ar: arcos){
            assert(ar.first >= 0 && ar.first < n);
            assert(ar.second >= 0 && ar.second < n);
            adj[ar.first].emplace_back(ar.second, id);
            id++;
        }
    }

    /// Constrói grafo misto a partir do número de vértices e da lista de arestas e de arcos. Assume-se que os vértices vão de 0 a n-1.
    /// Recebe: 
    ///     'n' o número de vértices do grafo, 
    ///     'arestas' a lista de pares de vértices que possuem uma aresta entre si
    ///     'arcos' a lista de arcos do grafo
    Misto(int n, vector<tuple<int, int, double>> arestas, vector<tuple<int, int, double>> arcos): n(n), m((int)arestas.size() + arcos.size()), nArestas((int)arestas.size()) {
        adj.resize(n);
        int id = 0;
        for(tuple<int, int, double> ar: arestas){
            auto [u, v, c] = ar;
            assert(u >= 0 && u < n);
            assert(v >= 0 && v < n);
            adj[u].emplace_back(v, id, c);
            adj[v].emplace_back(u, id, c);
            id++;
        }
        for(tuple<int, int, double> ar: arcos){
            auto [u, v, c] = ar;
            assert(u >= 0 && u < n);
            assert(v >= 0 && v < n);
            adj[u].emplace_back(v, id, c);
            id++;
        }
    }

    /// Constrói grafo misto a partir do número de vértices e uma lista de arestas. Assume-se que os vértices vão de 0 a n-1.
    /// Recebe: 
    ///     'n' o número de vértices do grafo, 
    ///     'nArestas' o número de arestas (não direcionados)
    ///     'arestas' a lista de pares de vértices que possuem uma aresta entre si
    Misto(int n, int nArestas, vector<pair<int, int>> arestas): n(n), m((int)arestas.size()), nArestas(nArestas) {
        adj.resize(n);
        for(int i=0;i<(int)arestas.size();i++){
            pair<int, int> ar = arestas[i];
            assert(ar.first >= 0 && ar.first < n);
            assert(ar.second >= 0 && ar.second < n);
            adj[ar.first].emplace_back(ar.second, i);
            if(i < nArestas)
                adj[ar.second].emplace_back(ar.first, i);
        }
    }

    Misto(int n, int nArestas, vector<tuple<int, int, double>> arestas): n(n), m((int)arestas.size()), nArestas(nArestas) {
        adj.resize(n);
        for(int i=0;i<(int)arestas.size();i++){
            auto [u, v, cus] = arestas[i];
            assert(u >= 0 && u < n);
            assert(v >= 0 && v < n);
            adj[u].emplace_back(v, i, cus);
            if(i < nArestas)
                adj[v].emplace_back(u, i, cus);
        }
    }

    /// Constrói grafo não direcionado a partir da lista de adjacências. Assume-se que os vértices vão de 0 a adjj.size()-1.
    /// Recebe: 
    ///     'adjj' a lista de adjacências do grafo
    Misto(vector<vector<Aresta>> adjj) : n((int)adjj.size()), adj(adjj) {
        map<int, int> cnt;
        for(int u=0;u<(int)adj.size();u++){
            for(Aresta ar: adj[u]){
                cnt[ar.id]++;
            }
        }
        nArestas = 0;
        while(cnt[nArestas++] == 2);
        m = cnt.size();
        for(int a=0;a<m;a++){
            if(a < nArestas)
                assert(cnt[a] == 2);
            else
                assert(cnt[a] == 1);
        }
        for(int u=0;u<(int)adj.size();u++){
            for(Aresta ar: adj[u]){
                assert(ar.id < m); // Garante que todas arestas tem id < m
            }
        }
    } 

    /// Constrói, a partir do multiconjunto de arcos e arestas direcionadas (M), e o multiconjunto de arestas (U) um grafo misto. 
    /// Essa construção faz parte da resolução do pcc-misto.
    /// Assume-se que existe um grafo misto base G que é estendido para uma versão euleriana.
    /// O grafo devolvido por esse construtor deve ser a extensão euleriana deste grafo original.
    Misto(int n, vector<tuple<int, int, double, int>> M, vector<tuple<int, int, double, int>> U) : n(n), m(M.size() + U.size()), nArestas(U.size()) {
        adj.resize(n);
        int newId = 0;
        for(auto [u, v, c, id]: U){
            adj[u].emplace_back(v, newId, c);
            adj[v].emplace_back(u, newId, c);
            idOriginal[newId++] = id;
        }
        assert(newId == nArestas);
        for(auto [u, v, c, id]: M){
            adj[u].emplace_back(v, newId, c);
            idOriginal[newId++] = id;
        }
        assert(newId == m);
    }

    /// Constrói, a partir do vetor de adjacências, um vetor com todas arestas e arcos do grafo, indexados pelo seu id.
    /// Retorna:
    ///     Vetor de tupla de inteiro, inteiro e double
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
    ///     Exemplo: 
    ///         arestas[i] = (u, v, c) -> Representa a aresta entre os vértices 'u' e 'v' com custo real 'c'.
    /// Cuidado: as arestas não são indexadas por seus 'id's na lista retornada
    vector<tuple<int, int, double>> listaArestas(){
        auto lista = listaAdj();
        vector<tuple<int, int, double>> arestas;
        for(int i=0;i<(int)lista.size();i++){
            if(aresta(i))
                arestas.push_back(lista[i]);
        }
        return arestas;
    }

    /// Constrói, a partir da lista de adjacências a lista de arcos do grafo, indexadas por seus ids subtraidos de 'nArestas'
    /// Retorna:
    ///     Vetor de tupla de inteiro, inteiro e double
    ///     Os primeiros 'nArestas' valores representam arestas, enquanto que os restantes arcos, por isso, apagam-se os arcos nesse método.
    ///     Exemplo: 
    ///         arestas[i] = (u, v, c) -> Representa a aresta de id 'i', entre os vértices 'u' e 'v' com custo real 'c'.
    /// Cuidado: os arcos não são indexados por seus 'id's na lista retornada
    vector<tuple<int, int, double>> listaArcos(){
        auto lista = listaAdj();
        vector<tuple<int, int, double>> arcos;
        for(int i=0;i<(int)lista.size();i++){
            if(arco(i))
                arcos.push_back(lista[i]);
        }
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
    
    int grauTotal(int u){
        return grauEntrada(u) + grauSaida(u) + grau(u);
    }

    int grau(int u){
        int deg = 0;
        for(Aresta ar: adj[u])
            deg += aresta(ar.id);
        return deg;
    }

    int grauSaida(int u){
        int deg = 0;
        for(Aresta ar: adj[u])
            deg += arco(ar.id);
        return deg;
    }

    int grauEntrada(int u){
        vector<vector<Aresta>> inv = adjInverso();
        int deg = 0;
        for(Aresta ar: inv[u]){
            deg += arco(ar.id);
        }
        return deg;
    }

    /// Testa se a aresta com identificador 'id' é uma aresta.
    bool aresta(int id){
        if(idReal.find(id) != idReal.end())
            id = idReal[id];
        return (id < nArestas);
    }

    /// Testa se a aresta com identificador 'id' é um arco ou uma aresta direcionada.
    bool arco(int id){
        if(idReal.find(id) != idReal.end())
            id = idReal[id];
        return (id >= nArestas);
    }

    /// Cria uma cópia da aresta/arco de identificador 'id'
    void copia(int id){
        // Provavelmente so adiciona no fim do adj e marca num map o id real da aresta, que entao pode ser classificada por nArestas
        auto [u, v, c] = listaAdj()[id];
        int novoId = m++;
        idReal[novoId] = id;
        adj[u].emplace_back(v, novoId, c);
        if(aresta(novoId))
            adj[v].emplace_back(u, novoId, c);
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
        for (int ini = 0; ini < n; ini++) {
            if (!vis[ini])
                tarjan(ini);
        }
        return nc;
    }

    /// Função que retorna o id da aresta ou arco base sobre o qual 'id' foi criado.
    int original(int id){
        assert(idReal.find(id) == idReal.end() || idOriginal.find(id) == idOriginal.end());
        if(idReal.find(id) != idReal.end())
            return idReal[id];
        if(idOriginal.find(id) != idOriginal.end())
            return idOriginal[id];
        return id;
    }

    /// Função de depuração que imprime o grafo e todas suas arestas.
    void print(){
        printf("Grafo misto com %d nós\nArestas:\n", n);
        for(int a=0;a<n;a++){
            for(Aresta ar: adj[a]){
                if(aresta(ar.id))
                    printf("%d %d %.3f (id %d)\n", a, ar.prox, ar.cus, ar.id);
            }
        }
        puts("Arcos");
        for(int a=0;a<n;a++){
            for(Aresta ar: adj[a]){
                if(arco(ar.id))
                    printf("%d %d %.3f (id %d)\n", a, ar.prox, ar.cus, ar.id);
            }
        }
    }
};

#endif
