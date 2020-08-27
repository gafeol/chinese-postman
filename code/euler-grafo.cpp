#include <bits/stdc++.h>
using namespace std;
#include "grafo.hpp"

struct Euler {
    private:
        map<int, bool> foiDeletada;
        stack<int> trilha;
        vector<vector<Aresta>> _adj;
        void euler_hierholzer(int u){
            while(!_adj[u].empty()){
                Aresta e = _adj[u].back();
                int v = e.prox;
                int id = e.id;
                _adj[u].pop_back();
                if(!foiDeletada[id]){
                    foiDeletada[id] = true;
                    euler_hierholzer(v);
                }
            }
            trilha.push(u);
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
        }

    public: 
        Grafo grafo;
        vector<int> trilha_euleriana(int u=0){
            reset();
            assert(euleriano());
            euler_hierholzer(u); 
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

        bool checkDeg(){
            for(int u=0;u<(int)grafo.adj.size();u++)
                if(grafo.adj[u].size()&1)
                    return false;
            return true;
        }

        bool checkConexo(){
            vector<bool> vis(grafo.adj.size(), 0);
            return (dfs(0, vis) == (int)grafo.adj.size());
        }

        bool euleriano(){
            return checkDeg() && checkConexo();
        }

        bool checkEulerianTrail() {
            vector<int> trilha = trilha_euleriana();
            return checkEulerianTrail(trilha);
        }

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
};