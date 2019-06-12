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

const int MAXN = 212;

const ll INF = LLONG_MAX/3ll;

int n, m, k;
int s[MAXN];


const int BITMASK = (1<<16);
ll dp[BITMASK];
vector<int> oddVertex; 
vector<vector<ll>> mnDist;

ll go(int bm){
    if(bm == 0) return 0;
    if(dp[bm] != -1) 
        return dp[bm];
    dp[bm] = LLONG_MAX;
    for(int i=0;i<oddVertex.size();i++){
        if(!(bm&(1<<i))) continue;
        for(int j=i+1;j<oddVertex.size();j++){
            if(!(bm&(1<<j))) continue;
            dp[bm] = min(dp[bm], mnDist[oddVertex[i]][oddVertex[j]] + go(bm ^ (1<<i) ^ (1<<j)));
        }
    }
    return dp[bm];
}

ll minCostPerfectMatch(int n) {
    for(int a=0;a<(1<<n);a++){
        dp[a] = -1;
    }
    return go((1<<n)-1);
}

ll cost_of_duplication(vector<vector<pair<int, ll>>> &adj){
    oddVertex.clear();
    for(int a=0;a<n;a++)
        if(((int)adj[a].size())&1)
            oddVertex.pb(a);


    ll cost = minCostPerfectMatch(oddVertex.size());
    return cost;
}

void floyd_warshall(){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j =0;j<n;j++){
                mnDist[i][j] = min(mnDist[i][k] + mnDist[k][j], mnDist[i][j]);
            }
        }
    }
}



int main (){
    while(scanf("%d", &n) != EOF && n){
        scanf("%d", &m);
        vector<vector<pair<int, ll>>> adj(n);
        mnDist.clear();
        mnDist.resize(n);
        for(int a=0;a<n;a++){
            mnDist[a].resize(n);
            for(int b=0;b<n;b++){
                mnDist[a][b] = INF;
            }
        }
        ll sum = 0;
        for(int a=0;a<n;a++)
            mnDist[a][a] = 0;
        for(int a=0;a<m;a++){
            int i, j;
            ll c;
            scanf("%d%d%lld", &i, &j, &c);
            i--;j--;
            adj[i].pb({j, c});
            adj[j].pb({i, c});
            mnDist[i][j] = min(mnDist[i][j], c);
            mnDist[j][i] = min(mnDist[j][i], c);
            sum += c;
        }
        floyd_warshall();
        //vector<pair<int, int>> M = perfect_min_cost_match(adj, mnDist);  
        printf("%lld\n", sum + cost_of_duplication(adj));
    }
}

