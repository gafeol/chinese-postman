stack<int> trilha;

struct aresta{
    int prox;
    int id;
};

stack<aresta> adj[N];
map<int, bool> foiDeletada;

void euler_hierholzer(int u){
	while(!adj[u].empty()){
        aresta e = adj[u].top();
        int v = e.prox;
        int id = e.id;
        adj[u].pop();
        if(!foiDeletada[íd]){
            foiDeletada[id] = true;
            euler_dfs(v);
        }
	}
	trilha.push(u);
}
