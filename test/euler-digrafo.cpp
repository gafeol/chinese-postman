#include "gtest/gtest.h"
#include <bits/stdc++.h>
using namespace std;

#include "../code/euler-digrafo.cpp"

bool checkEulerianTrail(digrafo &d, vector<int> &trilha){
    map<int, map<int, int>> cnt;
    for(int u=0;u<(int)d.adj.size();u++){
        for(int v: d.adj[u]){
            cnt[u][v]++;
        }
    }
    
    for(int i=0;i+1<(int)trilha.size();i++){
        int u = trilha[i], v = trilha[i+1]; 
        cnt[u][v]--;
    }
    for(auto lin: cnt){
        for(auto col: lin.second){
            if(col.second != 0) return false;
        }
    }
    return true;
}

TEST(Euler, EulerChecker){
    digrafo d(3, { {0, 1}, {1, 2}, {2, 0} });
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(checkEulerianTrail(d, trilha)) << "A trilha não é euleriana";
    vector<int> fakeTrail = {0, 2, 1, 0};
    EXPECT_FALSE(checkEulerianTrail(d, fakeTrail));
    fakeTrail = {0, 2, 1};
    EXPECT_FALSE(checkEulerianTrail(d, fakeTrail));
}

TEST(Euler, EulerCycle){
    digrafo d(3, { {0, 1}, {1, 2}, {2, 0} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_EQ(trilha[0], trilha.back()) << "O início e fim da trilha são iguais";
    EXPECT_TRUE(checkEulerianTrail(d, trilha)) << "A trilha não é euleriana";
}

TEST(Euler, EulerCycle2){
    digrafo d(5, { {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_EQ(trilha[0], trilha.back()) << "O início e fim da trilha são iguais";
    EXPECT_TRUE(checkEulerianTrail(d, trilha)) << "A trilha não é euleriana";
}

TEST(Euler, Disconnected){
    digrafo d(4, { {0, 1}, {1, 0}, {2, 3}, {3, 2} });
    EXPECT_FALSE(d.euleriano()) << "O digrafo não é euleriano";
    EXPECT_FALSE(d.checkConexo()) << "O digrafo não é conexo";
    EXPECT_TRUE(d.checkDeg()) << "Os graus de entrada e saída são iguais";
}

TEST(Euler, WrongDeg){
    digrafo d(4, { {0, 1}, {1, 2}, {2, 3} });
    EXPECT_FALSE(d.euleriano()) << "O digrafo não é euleriano";
    EXPECT_FALSE(d.checkDeg()) << "Os graus de entrada e saída não são iguais"; 
    EXPECT_TRUE(d.checkConexo()) << "O digrafo é conexo";
}

TEST(Euler, Loop){
    digrafo d(1, { {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(checkEulerianTrail(d, trilha));
}

TEST(Euler, Loop2){
    digrafo d(1, { {0, 0}, {0, 0}, {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(checkEulerianTrail(d, trilha));
}

TEST(Euler, MultipleArc){
    digrafo d(2, { {0, 1}, {1, 0}, {0, 1}, {1, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(checkEulerianTrail(d, trilha));
}

TEST(Euler, MultipleArc2){
    digrafo d(3, { {0, 1}, {1, 2}, {2, 0}, {1, 0}, {2, 1}, {0, 2} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(checkEulerianTrail(d, trilha));
}
