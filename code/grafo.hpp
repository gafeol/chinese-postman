#ifndef GRAFO_H
#define GRAFO_H

struct Aresta{
    int prox;
    int id;
};

struct Grafo{
    vector<vector<Aresta>> adj;

    Grafo () {}

    /// Constrói grafo não direcionado a partir do número de vértices e uma lista de arestas. Assume-se que os vértices vão de 0 a n-1.
    /// Recebe: 
    ///     'n' o número de vértices do grafo, 
    ///     'arestas' a lista de pares de vértices que possuem uma aresta entre si
    Grafo(int n, vector<pair<int, int>> arestas){
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
    Grafo(vector<vector<Aresta>> adjj) : adj(adjj) {} 

    void print(){
        printf("Grafo com %d nós\nArestas:\n", (int)adj.size());
        for(int a=0;a<(int)adj.size();a++){
            for(Aresta ar: adj[a]){
                if(a <= ar.prox)
                printf("%d %d\n", a, ar.prox);
            }
        }
    }
};

#endif