// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1237
// 10296 - Jogging Trails

#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
#ifndef ONLINE_JUDGE
#define debug(args...) fprintf(stderr,args)
#else
#define debug(args...)
#endif //ONLINE_JUDGE
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int MAXN = 212345;

const ll INF = LLONG_MAX/3ll;

int n, m, k;
int s[MAXN];

void floyd_warshall(vector<vector<ll>> &mnDist){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j =0;j<n;j++){
                mnDist[i][j] = min(mnDist[i][k] + mnDist[k][j], mnDist[i][j]);
            }
        }
    }
}


void prepare_flow(vector<vector<pair<int, ll>>> &adj, vector<vector<ll> &mnDist){
    for(int a=0;a<n;a++){

    }
}

void add_edge(int u, int v, ll cost){
    /// creates an undirected edge between u and v with defined cost


}

vector<pair<int, int>> perfect_min_cost_match(vector<pair<int, ll>> &adj, vector<vector<ll>> &mnDist){
    vector<int> oddVertex;
    for(int a=0;a<n;a++)
        if(adj[a].size()&1)
            oddVertex.pb(a);
    for(int i=0;i<oddVertex;i++)
        for(int j=i+1;j<oddVertex;j++)
            add_edge(oddVertex[i], oddVertex[j], mnDist[i][j]);

}

int main (){
    while(scanf("%d", &n) != EOF && n){
        scanf("%d", &m);
        vector<vector<pair<int, ll>>> adj(n);
        vector<vector<ll>> minDist(n, vector<ll>(n, INF));
        for(int a=0;a<m;a++){
            int i, j;
            ll c;
            scanf("%d%d%lld", &i, &j, &c);
            i--;j--;
            adj[i].pb({j, c});
            adj[j].pb({i, c});
            mnDist[i][j] = min(mnDist[i][j], c);
            mnDist[j][i] = min(mnDist[j][i], c);
        }
        floyd_warshall(mnDist);
        vector<pair<int, int>> M = perfect_min_cost_match(adj, mnDist);  
    }
}

