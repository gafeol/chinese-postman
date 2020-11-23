#ifndef EULER_MISTO
#define EULER_MISTO

#include "bits/stdc++.h"
using namespace std;
#include "grafo-misto.hpp"

struct Euler {
    private: 
        stack<int> trilha;
        vector<vector<Aresta>> _adj;
        vector<bool> foiDeletada;

        void euler_hierholzer_id(int u, int id = -1) {
            while (!_adj[u].empty()) {
                Aresta e = _adj[u].back();
                int v = e.prox;
                int id = e.id;
                _adj[u].pop_back();
                assert(id >= 0 && id < G.m);
                if (!foiDeletada[id]) {
                    foiDeletada[id] = true;
                    euler_hierholzer_id(v, id);
                }
            }
            if (id != -1) trilha.push(id);
        }

        int dfs(int u, vector<bool>& vis){
            vis[u] = true;
            int cnt = 1;
            for(Aresta ar: G.adj[u]){
                if(vis[ar.prox]) continue;
                cnt += dfs(ar.prox, vis);
            }
            return cnt;
        }

        void reset(){
            assert(trilha.empty());
            _adj = G.adj;
            foiDeletada.clear();
            foiDeletada.resize(G.m, false);
        }

        /// Checa se uma trilha por id's é valida a partir de um vértice inicial 'ini'.
        bool checkTrailByIdFrom(int ini, vector<int> &trilha, vector<pair<int, int>> &p){
            int u = ini; 
            for(int i=0;i<(int)trilha.size();i++){
                int id = trilha[i];
                if (G.aresta(id)) {
                    if (u == p[id].first)
                        u = p[id].second;
                    else if (u == p[id].second)
                        u = p[id].first;
                    else
                        return false;
                }
                else { // arco
                    if(u == p[id].first)
                        u = p[id].second;
                    else
                        return false;
                }
            }
            if(u != ini) // fecha um circuito
                return false;
            return true;
        }


    public:
        Misto G;

        /// Checa se o grafo G misto é euleriano.
        /// Isto é, checa se todos vértices tem grau de entrada igual ao grau de saída e se tem grau (não direcionado) par.
        bool euleriano(){
            if(G.countSCC() > 1)
                return false;

            vector<vector<Aresta>> adj = G.adj;
            vector<vector<Aresta>> inv = G.adjInverso();

            for(int u=0;u<G.n;u++){
                int degIn, degOut, deg;
                degIn = degOut = deg = 0;
                for(Aresta nxt: adj[u]){
                    if(G.arco(nxt.id))
                        degOut++;
                    else
                        deg++;
                }
                for(Aresta prv: inv[u]){
                    if(G.arco(prv.id))
                        degIn++;
                }
                if(degIn != degOut || deg%2 != 0){
                    return false;
                }
            }
            return true;
        }

        /// Devolve um circuito euleriano dado um vértice inicial u.
        /// O circuito devolvido é a sequência de identificadores de arestas ou arcos percorridas no passeio euleriano.
        /// Retorna:
        ///     vetor de inteiros com os id's de aresta percorridas no circuito euleriano
        vector<int> trilha_euleriana_id(int u=0){
            reset();
            assert(euleriano());
            euler_hierholzer_id(u); 
            vector<int> vTrilha;
            while(!trilha.empty()){
                vTrilha.push_back(trilha.top());
                trilha.pop();
            }
            return vTrilha; 
        }

        bool checkEulerianTrailById() {
            vector<int> trilha = trilha_euleriana_id();
            return checkEulerianTrailById(trilha);
        }

        /// Checa se uma trilha euleriana por id, passada por parâmetro, é válida.
        bool checkEulerianTrailById(vector<int> trilha){
            for(int id: trilha)
                assert(id >= 0 && id < G.m);
            vector<int> cnt(G.m, 1);
            vector<pair<int, int>> p(G.m);
            for(int u=0;u<(int)G.adj.size();u++){
                for(Aresta ar: G.adj[u]){
                    assert(ar.id >= 0 && ar.id < G.m);
                    p[ar.id] = {u, ar.prox};
                }
            }
            for(int id: trilha){
                //printf("percorre id %d cnt = %d - 1\n", id, cnt[id]);
                cnt[id]--;
            }
            for (int id = 0; id < G.m; id++) {
                if(cnt[id] != 0){
                    //printf("falhou no id %d cnt %d != 0\n",id, cnt[id]);
                    return false;
                }
            }
            if(!checkTrailByIdFrom(p[trilha[0]].first, trilha, p) &&
                !checkTrailByIdFrom(p[trilha[0]].second, trilha, p))
                return false;
            return true;
        }

        Euler () {}
        Euler(Misto G): G(G) {}
        Euler(int n, vector<pair<int, int>> arestas, vector<pair<int, int>> arcos) : G(Misto(n, arestas, arcos)) {}
        Euler(int n, vector<tuple<int, int, double>> arestas, vector<tuple<int, int, double>> arcos) : G(Misto(n, arestas, arcos)) {}
        Euler(int n, int nArestas, vector<pair<int, int>> ar) : G(Misto(n, nArestas, ar)) {}
        Euler(int n, int nArestas, vector<tuple<int, int, double>> ar) : G(Misto(n, nArestas, ar)) {}
};

#endif