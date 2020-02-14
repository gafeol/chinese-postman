stack<int> path;
vector<int> adj[N];
int cur_ed[N];

void add_edge(int u, int v){
	adj[a].push_back(b);	
	adj[b].push_back(a);
}

void euler_dfs(int u){
	while(cur_ed[u] < adj[u].size()){
        int nxt = adj[u][cur_ed[u]];
        euler_dfs(nxt);
        cur_ed[u]++;
	}
	final_path.push(u);
}
