#include "bits/stdc++.h"
using namespace std;

typedef int val;   // unidades de fluxo
typedef double num; // custos 

struct MinCostFlow {
    int N, M, en;
    vector<int> es, to, nx, pai, seen, qu;
    vector<val> fl, cp;
    vector<val> flowOnEdge;
    vector<int> edgeId;
    vector<num> cs, d;
    const num eps = 1e-8;
    int tempo;
    num tot;

    MinCostFlow() {}

    MinCostFlow(int n): N(n), M(0) {
        en = 2;
        tempo = 0;
        fl.clear(); cp.clear(); nx.clear(); cs.clear(); to.clear();
        fl.resize(2); cp.resize(2); nx.resize(2); cs.resize(2); to.resize(2);
        es.clear();
        es.resize(N, 0);
        pai.resize(N);
        d.resize(N);
        seen.resize(N);
        qu.resize(N);
    }

    MinCostFlow(int n, int m): N(n), M(m) {
        en = 2;
        tempo = 0;
        fl.clear(); cp.clear(); nx.clear(); cs.clear(); to.clear();
        fl.resize(2); cp.resize(2); nx.resize(2); cs.resize(2); to.resize(2);
        es.clear();
        es.resize(N, 0);
        pai.resize(N);
        d.resize(N);
        seen.resize(N);
        qu.resize(N);
        flowOnEdge.clear();
        edgeId.clear();
        flowOnEdge.resize(M);
        edgeId.resize(M);
    }

	val spfa(int s, int t) {
		tempo++; int a = 0, b = 0;
		for(int i = 0; i < N; i++) d[i] = numeric_limits<num>::max();
		d[s] = 0; qu[b++] = s; seen[s] = tempo;
		while(a != b) {
			int u = qu[a++]; if(a == N) a = 0; seen[u] = 0;
			for(int e = es[u]; e; e = nx[e]) if(cp[e] - fl[e] > val(0) && d[u] + cs[e] < d[to[e]] - eps) {
				d[to[e]] = d[u] + cs[e]; pai[to[e]] = e ^ 1;
				if(seen[to[e]] < tempo) { seen[to[e]] = tempo; qu[b++] = to[e]; if(b == N) b = 0; }
			}
		}
		if(d[t] == numeric_limits<num>::max()) return false;
		val mx = numeric_limits<val>::max();
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
        /*printf("FLOW de %d a %d deu %d\n", s, t, flow);
        for(int a=0;a<en;a++){
            printf("    flow on en %d (to %d cp %d fl %d cs %.3f\n", a, to[a], cp[a], fl[a], cs[a]);
        }*/
        for(int i=0;i<M;i++)
            flowOnEdge[i] = fl[edgeId[i]];
        return tot;
    }

    void add_edge(int u, int v, val c, num s, int id=-1) {
        assert(u >= 0 && u < N);
        assert(v >= 0 && v < N);
        if(id != -1)
            edgeId[id] = en;
        //printf("add edge %d %d %d %.3f %d\n", u, v, c, s, id);
        fl.resize(en+2); cp.resize(en+2); to.resize(en+2); nx.resize(en+2); cs.resize(en+2); 
        fl[en] = 0; cp[en] = c; to[en] = v; nx[en] = es[u]; cs[en] =  s; es[u] = en++;
        fl[en] = 0; cp[en] = 0; to[en] = u; nx[en] = es[v]; cs[en] = -s; es[v] = en++;
    }

    void reset_flow(){
        for(int a=0;a<(int)fl.size();a++)
            fl[a] = 0;
    }
};