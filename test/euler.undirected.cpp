#include "gtest/gtest.h"
#include <bits/stdc++.h>
using namespace std;

#include "../code/euler.undirected.cpp"

bool checkEulerianTrail(grafo &d, vector<int> &trilha){
    map<int, map<int, int>> cnt;
    for(int u=0;u<(int)d.adj.size();u++){
        for(aresta ar: d.adj[u]){
            int v = ar.prox;
            cnt[u][v]++;
        }
    }
    
    for(int i=0;i+1<(int)trilha.size();i++){
        int u = trilha[i], v = trilha[i+1]; 
        cnt[u][v]--;
        cnt[v][u]--;
    }
    for(auto lin: cnt){
        for(auto col: lin.second){
            if(col.second != 0) return false;
        }
    }
    return true;
}

TEST(Euler, EulerChecker){
    grafo d(3, { {0, 1}, {1, 2}, {2, 0} });
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(checkEulerianTrail(d, trilha)) << "A trilha não é euleriana";
    vector<int> validTrail = {0, 2, 1, 0};
    EXPECT_TRUE(checkEulerianTrail(d, validTrail));
    vector<int> fakeTrail = {0, 2, 1};
    EXPECT_FALSE(checkEulerianTrail(d, fakeTrail));
}

TEST(Euler, EulerCycle){
    grafo d(3, { {0, 1}, {1, 2}, {2, 0} });
    EXPECT_TRUE(d.euleriano()) << "O grafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_EQ(trilha[0], trilha.back()) << "O início e fim da trilha são iguais";
    EXPECT_TRUE(checkEulerianTrail(d, trilha)) << "A trilha não é euleriana";
}

TEST(Euler, EulerCycle2){
    grafo d(5, { {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1} });
    EXPECT_TRUE(d.euleriano()) << "O grafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_EQ(trilha[0], trilha.back()) << "O início e fim da trilha são iguais";
    EXPECT_TRUE(checkEulerianTrail(d, trilha)) << "A trilha não é euleriana";
}

TEST(Euler, Disconnected){
    grafo d(4, { {0, 1}, {1, 0}, {2, 3}, {3, 2} });
    EXPECT_FALSE(d.euleriano()) << "O grafo não é euleriano";
    EXPECT_FALSE(d.checkConexo()) << "O grafo não é conexo";
    EXPECT_TRUE(d.checkDeg()) << "Os graus de entrada e saída são iguais";
}

TEST(Euler, WrongDeg){
    grafo d(4, { {0, 1}, {1, 2}, {2, 3} });
    EXPECT_FALSE(d.euleriano()) << "O grafo não é euleriano";
    EXPECT_FALSE(d.checkDeg()) << "Os graus não são pares"; 
    EXPECT_TRUE(d.checkConexo()) << "O grafo é conexo";
}

TEST(Euler, Loop){
    grafo d(1, { {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(checkEulerianTrail(d, trilha));
}

TEST(Euler, Loop2){
    grafo d(1, { {0, 0}, {0, 0}, {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(checkEulerianTrail(d, trilha));
}

TEST(Euler, MultipleArc){
    grafo d(2, { {0, 1}, {1, 0}, {0, 1}, {1, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(checkEulerianTrail(d, trilha));
}

TEST(Euler, MultipleArc2){
    grafo d(3, { {0, 1}, {1, 2}, {2, 0}, {1, 0}, {2, 1}, {0, 2} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(checkEulerianTrail(d, trilha));
}