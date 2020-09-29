#ifndef FLOYD_H
#define FLOYD_H

#include "grafo.hpp"
#include "digrafo.hpp"
#include "bits/stdc++.h"
using namespace std;

const double INF = DBL_MAX/3.;
vector<vector<double>> floyd_warshall(Grafo G){
    int n = G.n;
    vector<vector<double>> dist(n, vector<double>(n, INF));
    for(int i=0;i<n;i++){
        dist[i][i] = 0;
        for(Aresta ar: G.adj[i]){
            int nxt = ar.prox;
            double cus = ar.cus;
            dist[i][nxt] = min(dist[i][nxt], cus);
            dist[nxt][i] = min(dist[nxt][i], cus);
        }
    }
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}

vector<vector<double>> floyd_warshall(Digrafo G){
    int n = G.n;
    vector<vector<double>> dist(n, vector<double>(n, INF));
    for(int i=0;i<n;i++){
        dist[i][i] = 0;
        for(Aresta ar: G.adj[i]){
            int nxt = ar.prox;
            double cus = ar.cus;
            dist[i][nxt] = min(dist[i][nxt], cus);
        }
    }
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}

#endif