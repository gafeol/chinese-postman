stack<int> trilha;
stack<int> adj[N];

void euler_hierholzer(int u){
	while(!adj[u].empty()){
        int v = adj[u].top();
        adj[u].pop();
        euler_dfs(v);
	}
	trilha.push(u);
}
