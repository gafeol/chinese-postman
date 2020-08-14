typedef pair<int, int> pii;

struct digrafo {
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
            for(int nxt: adj[u]){
                if(vis[nxt]) continue;
                cnt += dfs(nxt, vis);
            }
            return cnt;
        }
    public: 
        vector<vector<int>> adj;
        bool checkDeg(){
            vector<int> inDeg(adj.size(), 0);
            vector<int> outDeg(adj.size(), 0);
            for(int u=0;u<(int)adj.size();u++){
                for(int v: adj[u]){
                    outDeg[u]++;
                    inDeg[v]++;
                }
            }
            for(int u=0;u<(int)adj.size();u++)
                if(inDeg[u] != outDeg[u])
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

        digrafo(int n, vector<pii> arest){
            adj.resize(n);
            _adj.resize(n);
            for(int a=0;a<n;a++){
                adj[a].clear();
                _adj[a].clear();
            }
            clear(trilha);
            for(pii ar: arest){
                assert(ar.first >= 0 && ar.first < n);
                assert(ar.second >= 0 && ar.second < n);
                adj[ar.first].push_back(ar.second);
                _adj[ar.first].push_back(ar.second);
            }
        }
};
