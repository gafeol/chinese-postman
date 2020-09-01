#include <bits/stdc++.h>
using namespace std;

#include "min-cost-matching/MCM.hpp"
#include "grafo.hpp"
#include "floyd-warshall.cpp"

struct PCC {
    vector<int> solve(Grafo G) {
        vector<vector<double>> mnDist = floyd_warshall(G);
        vector<int> imp;
        Grafo K;
    }
};