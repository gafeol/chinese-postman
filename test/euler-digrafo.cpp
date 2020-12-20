#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/euler-digrafo.cpp"

TEST(Euler, EulerChecker){
    Euler d(3, { {0, 1}, {1, 2}, {2, 0} });
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(d.checkEulerianTrail(trilha)) << "A trilha não é euleriana";
    vector<int> fakeTrail = {0, 2, 1, 0};
    EXPECT_FALSE(d.checkEulerianTrail(fakeTrail));
    fakeTrail = {0, 2, 1};
    EXPECT_FALSE(d.checkEulerianTrail(fakeTrail));
}

TEST(Euler, EulerCycle){
    Euler d(3, { {0, 1}, {1, 2}, {2, 0} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_EQ(trilha[0], trilha.back()) << "O início e fim da trilha são iguais";
    EXPECT_TRUE(d.checkEulerianTrail(trilha)) << "A trilha não é euleriana";
}

TEST(Euler, EulerCycle2){
    Euler d(5, { {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_EQ(trilha[0], trilha.back()) << "O início e fim da trilha são iguais";
    EXPECT_TRUE(d.checkEulerianTrail(trilha)) << "A trilha não é euleriana";
}

TEST(Euler, Disconnected){
    Euler d(4, { {0, 1}, {1, 0}, {2, 3}, {3, 2} });
    EXPECT_FALSE(d.euleriano()) << "O digrafo não é euleriano";
    EXPECT_FALSE(d.checkFortementeConexo()) << "O digrafo não é conexo";
    EXPECT_TRUE(d.checkDeg()) << "Os graus de entrada e saída são iguais";
}

TEST(Euler, WrongDeg){
    Euler d(4, { {0, 1}, {1, 2}, {2, 3} });
    EXPECT_FALSE(d.euleriano()) << "O digrafo não é euleriano";
    EXPECT_FALSE(d.checkDeg()) << "Os graus de entrada e saída não são iguais"; 
    EXPECT_FALSE(d.checkFortementeConexo()) << "O digrafo é fortemente conexo";
    EXPECT_DEATH(d.trilha_euleriana(), "") << "O algoritmo chega a uma exceção buscando trilha euleriana inexistente";
}

TEST(Euler, Loop){
    Euler d(1, { {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(d.checkEulerianTrail(trilha));
}

TEST(Euler, Loop2){
    Euler d(1, { {0, 0}, {0, 0}, {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(d.checkEulerianTrail(trilha));
}

TEST(Euler, MultipleArc){
    Euler d(2, { {0, 1}, {1, 0}, {0, 1}, {1, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(d.checkEulerianTrail(trilha));
}

TEST(Euler, MultipleArc2){
    Euler d(3, { {0, 1}, {1, 2}, {2, 0}, {1, 0}, {2, 1}, {0, 2} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana();
    EXPECT_TRUE(d.checkEulerianTrail(trilha));
}

TEST(EulerId, EulerChecker){
    Euler d(3, { {0, 1}, {1, 2}, {2, 0} });
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha)) << "A trilha não é euleriana";
    vector<int> fakeTrailById = {0, 2, 1, 0};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
    fakeTrailById = {0, 2, 1};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
}

TEST(EulerId, EulerCycle){
    Euler d(3, { {0, 1}, {1, 2}, {2, 0} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_TRUE(d.checkEulerianTrailById(trilha)) << "A trilha não é euleriana por id";
}

TEST(EulerId, EulerCycle2){
    Euler d(5, { {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_TRUE(d.checkEulerianTrailById(trilha)) << "A trilha não é euleriana por id";
}

TEST(EulerId, Disconnected){
    Euler d(4, { {0, 1}, {1, 0}, {2, 3}, {3, 2} });
    EXPECT_FALSE(d.euleriano()) << "O digrafo não é euleriano";
    EXPECT_FALSE(d.checkFortementeConexo()) << "O digrafo não é conexo";
    EXPECT_TRUE(d.checkDeg()) << "Os graus de entrada e saída são iguais";
}

TEST(EulerId, WrongDeg){
    Euler d(4, { {0, 1}, {1, 2}, {2, 3} });
    EXPECT_FALSE(d.euleriano()) << "O digrafo não é euleriano";
    EXPECT_FALSE(d.checkDeg()) << "Os graus de entrada e saída não são iguais"; 
    EXPECT_FALSE(d.checkFortementeConexo()) << "O digrafo é fortemente conexo";
    //EXPECT_DEATH(d.trilha_euleriana_id(), "") << "O algoritmo chega a uma exceção buscando trilha euleriana inexistente";
}

TEST(EulerId, Loop){
    Euler d(1, { {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
}

TEST(EulerId, Loop2){
    Euler d(1, { {0, 0}, {0, 0}, {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
}

TEST(EulerId, MultipleArc){
    Euler d(2, { {0, 1}, {1, 0}, {0, 1}, {1, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
}

TEST(EulerId, MultipleArc2){
    Euler d(3, { {0, 1}, {1, 2}, {2, 0}, {1, 0}, {2, 1}, {0, 2} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
} 

TEST(EulerChecker, CheckFail){
    Euler d(3, { {0, 1}, {1, 2}, {2, 0}, {0, 0} });
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(d.checkEulerianTrailById({0, 1, 2, 3}));
    EXPECT_FALSE(d.checkEulerianTrailById({0, 1, 2, 3, 3}));
    EXPECT_FALSE(d.checkEulerianTrailById({0, 1, 2}));
}