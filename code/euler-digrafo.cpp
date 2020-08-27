#include <bits/stdc++.h>
using namespace std;
#include "digrafo.hpp"

struct Euler {
    private:
        stack<int> trilha;
        vector<vector<int>> _adj;
        void euler_hierholzer(int u){
            while(!_adj[u].empty()){
                int v = _adj[u].back();
                _adj[u].pop_back();
                euler_hierholzer(v);
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
            for(int nxt: digrafo.adj[u]){
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
                for(int v: digrafo.adj[u]){
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

        bool euleriano(){
            return checkDeg() && checkConexo();
        }

        Euler(Digrafo d) : digrafo(d) {
            reset();
        }

        Euler(int n, vector<pair<int, int>> arc) : Euler(Digrafo(n, arc)) {}


        bool checkEulerianTrail(vector<int> trilha){
            map<int, map<int, int>> cnt;
            for(int u=0;u<digrafo.n;u++){
                for(int v: digrafo.adj[u]){
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

        bool checkEulerianTrail() {
            return checkEulerianTrail(trilha_euleriana());
        }
};
