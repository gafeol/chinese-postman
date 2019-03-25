// adjacency list
vector<pii> adj[MAXN];

int mrk[MAXE];

int temp_path[MAXE], final_path[MAXE], tsz, fsz;

int edge_id = 0;
void add_edge(int a, int b){
	// undirected edge
	adj[a].pb(pii(b, edge_id));	
	adj[b].pb(pii(a, edge_id));
	edge_id = edge_id + 1;
}

void euler_dfs(int u){
	temp_path[tsz++] = u;
	for(pii ar: adj[u]){
		int id = ar.snd;
		if(mrk[id]) continue;
		mrk[id] = 1;
		int v = ar.fst; euler_dfs(v);
	}
	final_path[fsz++] = temp_path[--tsz];
}
// Cycle stored in final_path[0...fsz-1]
