#include "bits/stdc++.h"
using namespace std;
#include "grafo.hpp"

struct Euler {
    private:
        stack<int> trilha;
        vector<vector<Aresta>> _adj;
        vector<bool> foiDeletada;

        /// Adiciona à 'trilha' um circuito euleriano.
        /// O circuito é construido nesse método a partir dos vértices percorridas, o que pode ser ambíguo em relação às arestas realmente percorridas.
        /// Em uma situação que o grafo possui arestas paralelas, vale a pena usar 'euler_hierholzer_id', que devolve o mesmo circuito, porém identificado pelos 'id' das arestas percorridas.
        void euler_hierholzer(int u){
            while(!_adj[u].empty()){
                Aresta e = _adj[u].back();
                int v = e.prox;
                int id = e.id;
                _adj[u].pop_back();
                assert(id >= 0 && id < grafo.m);
                if(!foiDeletada[id]){
                    foiDeletada[id] = true;
                    euler_hierholzer(v);
                }
            }
            trilha.push(u);
        }

        /// Adiciona à 'trilha' um circuito euleriano.
        /// O circuito é construido nesse método a partir da identificação 'id' das arestas que são percorridas.
        void euler_hierholzer_id(int u, int id=-1){
            while(!_adj[u].empty()){
                Aresta e = _adj[u].back();
                int v = e.prox;
                int id = e.id;
                _adj[u].pop_back();
                assert(id >= 0 && id < grafo.m);
                if(!foiDeletada[id]){
                    foiDeletada[id] = true;
                    euler_hierholzer_id(v, id);
                }
            }
            if(id != -1)
                trilha.push(id);
        }


        void clear(stack<int> &st){
            while(!st.empty())
                st.pop();
        }

        int dfs(int u, vector<bool>& vis){
            vis[u] = true;
            int cnt = 1;
            for(Aresta ar: grafo.adj[u]){
                if(vis[ar.prox]) continue;
                cnt += dfs(ar.prox, vis);
            }
            return cnt;
        }

        void reset(){
            clear(trilha);
            _adj = grafo.adj;
            foiDeletada.clear();
            foiDeletada.resize(grafo.m, false);
        }

        /// Checa se uma trilha por id's é valida a partir de um vértice inicial 'ini'.
        bool checkTrailByIdFrom(int ini, vector<int> &trilha, vector<pair<int, int>> &p){
            int u = ini; 
            for(int i=0;i<(int)trilha.size();i++){
                int id = trilha[i]; 
                if(u == p[id].first)
                    u = p[id].second;
                else if(u == p[id].second)
                    u = p[id].first;
                else
                    return false;
            }
            if(u != ini) // fecha um circuito
                return false;
            return true;
        }

    public: 
        Grafo grafo;
        /// Devolve um circuito euleriano dado um vértice inicial u.
        /// O circuito devolvido é a sequência de vértices percorridos no passeio euleriano.
        /// Retorna:
        ///     vetor de inteiros com os vértices percorridos no circuito euleriano
        vector<int> trilha_euleriana(int u=0){
            reset();
            euler_hierholzer(u); 
            vector<int> vTrilha;
            while(!trilha.empty()){
                vTrilha.push_back(trilha.top());
                trilha.pop();
            }
            return vTrilha; 
        }

        /// Devolve um circuito euleriano dado um vértice inicial u.
        /// O circuito devolvido é a sequência de identificadores de arestas percorridas no passeio euleriano.
        /// Retorna:
        ///     vetor de inteiros com os id's de aresta percorridas no circuito euleriano
        vector<int> trilha_euleriana_id(int u=0){
            reset();
            euler_hierholzer_id(u); 
            vector<int> vTrilha;
            while(!trilha.empty()){
                vTrilha.push_back(trilha.top());
                trilha.pop();
            }
            return vTrilha; 
        }

        Euler(Grafo g) : grafo(g) {
            reset();
        }

        Euler(int n, vector<pair<int, int>> arest) : Euler(Grafo(n, arest)) {}

        /// Verifica se o grau de todos vértices do grafo são par.
        bool checkDeg(){
            for(int u=0;u<(int)grafo.adj.size();u++)
                if(grafo.adj[u].size()&1)
                    return false;
            return true;
        }

        /// Verifica se o grafo é conexo.
        bool checkConexo(){
            vector<bool> vis(grafo.adj.size(), 0);
            return (dfs(0, vis) == (int)grafo.adj.size());
        }

        /// Checa se um grafo é euleriano.
        bool euleriano(){
            return checkDeg() && checkConexo();
        }

        /// Constrói e checa se a trilha euleriana por vértices é válida.
        bool checkEulerianTrail() {
            vector<int> trilha = trilha_euleriana();
            return checkEulerianTrail(trilha);
        }

        /// Checa se uma trilha euleriana por vértices, passada por parâmetro, é válida.
        bool checkEulerianTrail(vector<int> trilha){
            map<int, map<int, int>> cnt;
            for(int u=0;u<(int)grafo.adj.size();u++){
                for(Aresta ar: grafo.adj[u]){
                    int v = ar.prox;
                    cnt[u][v]++;
                }
            }
            
            for(int i=0;i+1<(int)trilha.size();i++){
                int u = trilha[i], v = trilha[i+1]; 
                cnt[u][v]--;
                cnt[v][u]--;
            }
            for(auto lin: cnt){
                for(auto col: lin.second){
                    if(col.second != 0) return false;
                }
            }
            return true;
        }

        bool checkEulerianTrailById() {
            vector<int> trilha = trilha_euleriana_id();
            return checkEulerianTrailById(trilha);
        }

        /// Checa se uma trilha euleriana por id, passada por parâmetro, é válida.
        bool checkEulerianTrailById(vector<int> trilha){
            for(int id: trilha)
                assert(id >= 0 && id < grafo.m);
            vector<int> cnt(grafo.m, 1);
            vector<pair<int, int>> p(grafo.m);
            for(int u=0;u<(int)grafo.adj.size();u++){
                for(Aresta ar: grafo.adj[u]){
                    assert(ar.id >= 0 && ar.id < grafo.m);
                    p[ar.id] = {ar.prox, u};
                    //printf("id %d (%d %d)\n", ar.id, ar.prox, u);
                }
            }
            for(int id: trilha)
                cnt[id]--;
            for(int id=0;id<grafo.m;id++)
                if(cnt[id] != 0)
                    return false;
            if(!checkTrailByIdFrom(p[trilha[0]].first, trilha, p) &&
                !checkTrailByIdFrom(p[trilha[0]].second, trilha, p))
                return false;
            return true;
        }
};