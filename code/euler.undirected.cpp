typedef pair<int, int> pii;

struct aresta{
    int prox;
    int id;
};

struct grafo {
    private:
        map<int, bool> foiDeletada;
        stack<int> trilha;
        vector<vector<aresta>> _adj;
        void euler_hierholzer(int u){
            while(!_adj[u].empty()){
                aresta e = _adj[u].back();
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
            for(aresta ar: adj[u]){
                if(vis[ar.prox]) continue;
                cnt += dfs(ar.prox, vis);
            }
            return cnt;
        }
    public: 
        vector<vector<aresta>> adj;
        bool checkDeg(){
            for(int u=0;u<(int)adj.size();u++)
                if(adj[u].size()&1)
                    return false;
            return true;
        }
        bool checkConexo(){
            vector<bool> vis(adj.size(), 0);
            return (dfs(0, vis) == (int)adj.size());
        }

        vector<int> trilha_euleriana(int u=0){
            clear(trilha);
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

        grafo(int n, vector<pii> arest){
            foiDeletada.clear();
            adj.resize(n);
            _adj.resize(n);
            for(int a=0;a<n;a++){
                adj[a].clear();
                _adj[a].clear();
            }
            clear(trilha);
            for(int id=0;id<(int)arest.size();id++){
                pii ar = arest[id];
                assert(ar.first >= 0 && ar.first < n);
                assert(ar.second >= 0 && ar.second < n);
                adj[ar.first].push_back({ar.second, id});
                _adj[ar.first].push_back({ar.second, id});
                adj[ar.second].push_back({ar.first, id});
                _adj[ar.second].push_back({ar.first, id});
            }
        }

        void print(){
            printf("Grafo com %d nós\nArestas:\n", (int)adj.size());
            for(int a=0;a<(int)adj.size();a++){
                for(aresta ar: adj[a]){
                    if(a <= ar.prox)
                    printf("%d %d\n", a, ar.prox);
                }
            }
        }
};