bool mrk[E];
queue<int> final_path;
stack<int> temp_path;
int edge_id = 0;

struct edge{
	int to, id;
};

vector<edge> adj[N];

void add_edge(int u, int v){
	adj[a].push_back({b, edge_id});	
	adj[b].push_back({a, edge_id});
	edge_id = edge_id + 1;
}

void euler_dfs(int u){
	temp_path.push(u);
	for(edge e: adj[u]){
		if(mrk[e.id]) continue;
		mrk[e.id] = true;
		euler_dfs(e.to);
	}
	final_path.push(temp_path.top());
	temp_path.pop();
}
