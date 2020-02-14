stack<int> path;
vector<int> adj[N];
int cur_ed[N];

void euler_dfs(int u){
	while(cur_ed[u] < adj[u].size()){
        int nxt = adj[u][cur_ed[u]];
        euler_dfs(nxt);
        cur_ed[u]++;
	}
	path.push(u);
}
