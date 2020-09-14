#include <bits/stdc++.h>
using namespace std;

typedef int val;   // unidades de fluxo
typedef double num; // custos 

struct MinCostFlow {
    int N, M, en;
    vector<int> es, to, nx, pai;
    vector<val> fl, cp;
    vector<val> flowOnEdge;
    vector<int> edgeId;
    vector<num> cs, d;
    const num inf = 1e8, eps = 1e-8;
    const val infv = INT_MAX;
    vector<int> seen, qu;
    int tempo;
    num tot;

    MinCostFlow() {}

    MinCostFlow(int n): N(n) {
        en = 0;
        tempo = 0;
        es.clear();
        es.resize(N, -1);
        pai.resize(N);
        d.resize(N);
        seen.resize(N);
        qu.resize(N);
        flowOnEdge.clear();
        edgeId.clear();
        flowOnEdge.resize(M);
        edgeId.resize(M);
    }

    MinCostFlow(int n, int m): N(n), M(m) {
        en = 0;
        tempo = 0;
        es.clear();
        es.resize(N, -1);
        pai.resize(N);
        d.resize(N);
        seen.resize(N);
        qu.resize(N);
        flowOnEdge.clear();
        edgeId.clear();
        flowOnEdge.resize(M);
        edgeId.resize(M);
        flowOnEdge.resize(M);
        edgeId.resize(M);
    }

    bool spfa(int s, int t) {
        tempo++;
        int a = 0, b = 0;
        for(int i = 0; i < N; i++) d[i] = inf;
        d[s] = 0;
        qu[b++] = s;
        seen[s] = tempo;
        while(a != b) {
            int u = qu[a++]; if(a == N) a = 0;
            seen[u] = 0;
            for(int e = es[u]; e != -1; e = nx[e])
                if(cp[e] - fl[e] > val(0) && d[u] + cs[e] < d[to[e]] - eps) {
                    d[to[e]] = d[u] + cs[e]; pai[to[e]] = e ^ 1;
                    if(seen[to[e]] < tempo) { seen[to[e]] = tempo; qu[b++] = to[e]; if(b == N) b = 0; }
                }
        }
        if(d[t] == inf) return false;
        val mx = infv;
        for(int u = t; u != s; u = to[pai[u]])
            mx = min(mx, cp[pai[u] ^ 1] - fl[pai[u] ^ 1]);
        tot += d[t] * val(mx);
        for(int u = t; u != s; u = to[pai[u]])
            fl[pai[u]] -= mx, fl[pai[u] ^ 1] += mx;
        return mx;
    }
    
    val flow;
    num solve(int s, int t) {
        tot = 0; flow = 0;
        while(val a = spfa(s, t)) flow += a;
        for(int i=0;i<M;i++)
            flowOnEdge[i] = fl[edgeId[i]];
        return tot;
    }

    void add_edge(int u, int v, val c, num s, int id=-1) {
        assert(u >= 0 && u < N);
        assert(v >= 0 && v < N);
        if(id != -1)
            edgeId[id] = en;
        fl.resize(en+2); cp.resize(en+2); to.resize(en+2); nx.resize(en+2); cs.resize(en+2); 
        fl[en] = 0; cp[en] = c; to[en] = v; nx[en] = es[u]; cs[en] =  s; es[u] = en++;
        fl[en] = 0; cp[en] = 0; to[en] = u; nx[en] = es[v]; cs[en] = -s; es[v] = en++;
    }
};