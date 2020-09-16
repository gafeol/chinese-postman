#include <bits/stdc++.h>
using namespace std;
#include "digrafo.hpp"

struct Euler {
    private:
        stack<int> trilha;
        vector<vector<Aresta>> _adj;

        void euler_hierholzer(int u){
            while(!_adj[u].empty()){
                Aresta e = _adj[u].back();
                int v = e.prox;
                _adj[u].pop_back();
                euler_hierholzer(v);
            }
            trilha.push(u);
        }

        void euler_hierholzer_id(int u, int id=-1){
            while(!_adj[u].empty()){
                Aresta e = _adj[u].back();
                int v = e.prox;
                int id = e.id;
                _adj[u].pop_back();
                euler_hierholzer_id(v, id);
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
            for(Aresta ar: digrafo.adj[u]){
                int nxt = ar.prox;
                if(vis[nxt]) continue;
                cnt += dfs(nxt, vis);
            }
            return cnt;
        }

        void reset(){
            _adj = digrafo.adj;
            clear(trilha);
        }

    public: 
        Digrafo digrafo;

        bool checkDeg(){
            vector<int> inDeg(digrafo.n, 0);
            vector<int> outDeg(digrafo.n, 0);
            for(int u=0;u<digrafo.n;u++){
                for(auto ar: digrafo.adj[u]){
                    int v = ar.prox;
                    outDeg[u]++;
                    inDeg[v]++;
                }
            }
            for(int u=0;u<digrafo.n;u++)
                if(inDeg[u] != outDeg[u])
                    return false;
            return true;
        }

        bool checkConexo(){
            vector<bool> vis(digrafo.n, 0);
            return (dfs(0, vis) == digrafo.n);
        }

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

        /// Devolve uma trilha euleriana do digrafo `digrafo`, parâmetro desta classe
        /// Recebe:
        ///     'u' o vértice inicial da trilha.
        /// Devolve:
        ///     vector de inteiros, contendo os ids dos arcos percorridos na trilha euleriana
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

        bool euleriano(){
            return checkDeg() && checkConexo();
        }

        Euler(Digrafo d) : digrafo(d) {
            reset();
        }

        Euler(int n, vector<pair<int, int>> arc) 
            : Euler(Digrafo(n, arc)) {}

        Euler(int n, vector<tuple<int, int, double>> arc)
            : Euler(Digrafo(n, arc)) {}

        bool checkEulerianTrail(vector<int> trilha){
            map<int, map<int, int>> cnt;
            for(int u=0;u<digrafo.n;u++){
                for(Aresta ar: digrafo.adj[u]){
                    int v = ar.prox;
                    cnt[u][v]++;
                }
            }
            
            for(int i=0;i+1<(int)trilha.size();i++){
                int u = trilha[i], v = trilha[i+1]; 
                cnt[u][v]--;
            }
            for(auto lin: cnt){
                for(auto col: lin.second){
                    if(col.second != 0) return false;
                }
            }
            return true;
        }

        bool checkEulerianTrailById(vector<int> trilha){
            /*
            printf("check trilha por id:\n");
            for(int id: trilha){
                printf("%d ", id);
            }
            puts("");
            */
            for(int id: trilha)
                assert(id >= 0 && id < digrafo.m);
            vector<int> cnt(digrafo.m, 1);
            vector<pair<int, int>> arco(digrafo.m);
            for(int u=0;u<digrafo.n;u++){
                for(Aresta ar: digrafo.adj[u]){
                    int v = ar.prox;
                    arco[ar.id] = {u, v};
                    //printf("arco[%d] = %d %d\n", ar.id, u, v);
                }
            }
            
            int u = arco[trilha.back()].second; 
            for(int id: trilha){
                if(u != arco[id].first)
                    return false;
                cnt[id]--;
                u = arco[id].second;
            }

            if(*max_element(cnt.begin(), cnt.end()) != 0 ||
                *min_element(cnt.begin(), cnt.end()) != 0)
                return false;
            
            return true;
        }

        bool checkEulerianTrail() {
            return checkEulerianTrail(trilha_euleriana());
        }
};
