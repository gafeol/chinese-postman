#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/euler-grafo.cpp"

TEST(Euler, EulerChecker){
    Euler euler(3, { {0, 1}, {1, 2}, {2, 0} });
    vector<int> trilha = euler.trilha_euleriana();
    EXPECT_TRUE(euler.euleriano()) << "O grafo testado não é euleriano";
    EXPECT_TRUE(euler.checkEulerianTrail()) << "A trilha não é euleriana";
    vector<int> validTrail = {0, 2, 1, 0};
    EXPECT_TRUE(euler.checkEulerianTrail(validTrail));
    vector<int> fakeTrail = {0, 2, 1};
    EXPECT_FALSE(euler.checkEulerianTrail(fakeTrail));
}

TEST(Euler, EulerIdChecker){
    Euler euler(3, { {0, 1}, {1, 2}, {2, 0} });
    vector<int> trilha = euler.trilha_euleriana_id();
    EXPECT_TRUE(euler.euleriano()) << "O grafo testado não é euleriano";
    EXPECT_TRUE(euler.checkEulerianTrailById()) << "A trilha não é euleriana";
}

TEST(Euler, EulerCycle){
    Euler euler(3, { {0, 1}, {1, 2}, {2, 0} });
    EXPECT_TRUE(euler.euleriano()) << "O grafo é euleriano.";
    vector<int> trilha = euler.trilha_euleriana();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_EQ(trilha[0], trilha.back()) << "O início e fim da trilha são iguais";
    EXPECT_TRUE(euler.checkEulerianTrail(trilha)) << "A trilha não é euleriana";
}

TEST(Euler, EulerIdCycle){
    Euler euler(3, { {0, 1}, {1, 2}, {2, 0} });
    EXPECT_TRUE(euler.checkEulerianTrailById()) << "A trilha não é euleriana";
    EXPECT_TRUE(euler.checkEulerianTrailById({0, 1, 2}));
    EXPECT_TRUE(euler.checkEulerianTrailById({0, 2, 1}));
    EXPECT_TRUE(euler.checkEulerianTrailById({1, 0, 2}));
    EXPECT_TRUE(euler.checkEulerianTrailById({1, 2, 0}));
    EXPECT_TRUE(euler.checkEulerianTrailById({2, 0, 1}));
    EXPECT_TRUE(euler.checkEulerianTrailById({2, 1, 0}));

    EXPECT_DEATH(euler.checkEulerianTrailById({3, 0, 1, 2}), "");
    EXPECT_FALSE(euler.checkEulerianTrailById({0, 1, 0}));
}


TEST(Euler, EulerCycle2){
    Euler d(5, { {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1} });
    EXPECT_TRUE(d.euleriano()) << "O grafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_EQ(trilha[0], trilha.back()) << "O início e fim da trilha são iguais";
    EXPECT_TRUE(d.checkEulerianTrail(trilha)) << "A trilha não é euleriana";
}

TEST(Euler, Disconnected){
    Euler d(4, { {0, 1}, {1, 0}, {2, 3}, {3, 2} });
    EXPECT_FALSE(d.euleriano()) << "O grafo não é euleriano";
    EXPECT_FALSE(d.checkConexo()) << "O grafo não é conexo";
    EXPECT_TRUE(d.checkDeg()) << "Os graus de entrada e saída são iguais";
}

TEST(Euler, WrongDeg){
    Euler d(4, { {0, 1}, {1, 2}, {2, 3} });
    EXPECT_FALSE(d.euleriano()) << "O grafo é euleriano";
    EXPECT_FALSE(d.checkDeg()) << "Os graus são pares"; 
    EXPECT_TRUE(d.checkConexo()) << "O grafo não é conexo";
    EXPECT_DEATH(d.trilha_euleriana(), "") << "O algoritmo entra em exceção";
}

TEST(Euler, Loop){
    Euler d(1, { {0, 0} });
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(d.checkEulerianTrail());
}

TEST(Euler, Loop2){
    Euler d(1, { {0, 0}, {0, 0}, {0, 0} });
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(d.checkEulerianTrail());
}

TEST(Euler, MultipleArc){
    Euler d(2, { {0, 1}, {1, 0}, {0, 1}, {1, 0} });
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(d.checkEulerianTrail());
}

TEST(Euler, MultipleArc2){
    Euler d(3, { {0, 1}, {1, 2}, {2, 0}, {1, 0}, {2, 1}, {0, 2} });
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(d.checkEulerianTrail());
}

TEST(Euler, WrongTrailById){
    Euler d(4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}});
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(d.checkEulerianTrail());
    EXPECT_TRUE(d.checkEulerianTrailById());
    vector<int> fakeTrailById = {0, 2, 1, 3};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
}

TEST(Euler, InstanceReset){
    Euler d(4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}} );
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(d.checkEulerianTrail());
    EXPECT_TRUE(d.checkEulerianTrailById());
    EXPECT_TRUE(d.checkEulerianTrail());
    EXPECT_TRUE(d.checkEulerianTrailById());
    d = Euler(4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}} );
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(d.checkEulerianTrail());
    EXPECT_TRUE(d.checkEulerianTrailById());
    EXPECT_TRUE(d.checkEulerianTrail());
    EXPECT_TRUE(d.checkEulerianTrailById());
    d = Euler(3, { {0, 1}, {1, 2}, {2, 0} });
    EXPECT_TRUE(d.checkEulerianTrailById()) << "A trilha não é euleriana";
    EXPECT_TRUE(d.checkEulerianTrailById({0, 1, 2}));
    EXPECT_TRUE(d.checkEulerianTrailById({0, 2, 1}));
    EXPECT_TRUE(d.checkEulerianTrailById({1, 0, 2}));
    EXPECT_TRUE(d.checkEulerianTrailById({1, 2, 0}));
    EXPECT_TRUE(d.checkEulerianTrailById({2, 0, 1}));
    EXPECT_TRUE(d.checkEulerianTrailById({2, 1, 0}));

    EXPECT_DEATH(d.checkEulerianTrailById({3, 0, 1, 2}), "");
    EXPECT_FALSE(d.checkEulerianTrailById({0, 1, 0}));
}

TEST(Euler, NotCircuit){
    Euler d(4, {{0, 1}, {1, 2}, {2, 3}});
    vector<int> fakeTrailById = {0, 1, 2};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
}