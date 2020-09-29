#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/euler-misto.cpp"

TEST(EulerMistoId, EulerChecker){
    Euler d(3, 0, { {0, 1}, {1, 2}, {2, 0} });
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha)) << "A trilha não é euleriana";
    vector<int> fakeTrailById = {0, 2, 1, 0};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
    fakeTrailById = {0, 2, 1};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
}

TEST(EulerMistoId, EulerCycle){
    Euler d(3, 0, { {0, 1}, {1, 2}, {2, 0} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_TRUE(d.checkEulerianTrailById(trilha)) << "A trilha não é euleriana por id";
}

TEST(EulerMistoId, EulerCycle2){
    Euler d(5, 0, { {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_TRUE(d.checkEulerianTrailById(trilha)) << "A trilha não é euleriana por id";
}

TEST(EulerMistoId, Disconnected){
    Euler d(4, 0, { {0, 1}, {1, 0}, {2, 3}, {3, 2} });
    EXPECT_FALSE(d.euleriano()) << "O digrafo não é euleriano";
    //EXPECT_FALSE(d.checkFortementeConexo()) << "O digrafo não é conexo";
    //EXPECT_TRUE(d.checkDeg()) << "Os graus de entrada e saída são iguais";
}

TEST(EulerMistoId, WrongDeg){
    Euler d(4, 0, { {0, 1}, {1, 2}, {2, 3} });
    EXPECT_FALSE(d.euleriano()) << "O digrafo não é euleriano";
    //EXPECT_FALSE(d.checkDeg()) << "Os graus de entrada e saída não são iguais"; 
    //EXPECT_FALSE(d.checkFortementeConexo()) << "O digrafo é fortemente conexo";
    EXPECT_DEATH(d.trilha_euleriana_id(), "") << "O algoritmo chega a uma exceção buscando trilha euleriana inexistente";
}

TEST(EulerMistoId, Loop){
    Euler d(1, 0, { {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
}

TEST(EulerMistoId, Loop2){
    Euler d(1, 0, { {0, 0}, {0, 0}, {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
}

TEST(EulerMistoId, MultipleArc){
    Euler d(2, 0, { {0, 1}, {1, 0}, {0, 1}, {1, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
}

TEST(EulerMistoId, MultipleArc2){
    Euler d(3, 0, { {0, 1}, {1, 2}, {2, 0}, {1, 0}, {2, 1}, {0, 2} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
} 