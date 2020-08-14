#include "gtest/gtest.h"
#include <bits/stdc++.h>
using namespace std;

#include "../code/euler.cpp"

bool chckCaminhoEuleriano(digrafo &d, vector<int> &trilha){
    map<int, map<int, int>> cnt;
    for(int u=0;u<(int)d.adj.size();u++){
        for(int v: d.adj[u]){
            cnt[u][v]++;
        }
    }
    
    for(int i=0;i+1<(int)trilha.size();i++){
         
    }
    return true;
}

TEST(Euler, Cycle){
    digrafo d(3, { {0, 1}, {1, 2}, {2, 0} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_EQ(trilha[0], trilha.back()) << "O início e fim da trilha são iguais";
}

TEST(Euler, NaoConexo){
    digrafo d(2, {});
    EXPECT_FALSE(d.euleriano()) << "O digrafo não é euleriano";
    EXPECT_FALSE(d.checkConexo());
}
