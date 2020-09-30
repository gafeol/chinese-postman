#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/euler-misto.cpp"

TEST(EulerMistoId, DirecionadoEulerChecker){
    Euler d(3, 0, { {0, 1}, {1, 2}, {2, 0} });
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha)) << "A trilha não é euleriana";
    vector<int> fakeTrailById = {0, 2, 1, 0};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
    fakeTrailById = {0, 2, 1};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
}

TEST(EulerMistoId, DirecionadoEulerCycle){
    Euler d(3, 0, { {0, 1}, {1, 2}, {2, 0} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_TRUE(d.checkEulerianTrailById(trilha)) << "A trilha não é euleriana por id";
}

TEST(EulerMistoId, DirecionadoEulerCycle2){
    Euler d(5, 0, { {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_TRUE(d.checkEulerianTrailById(trilha)) << "A trilha não é euleriana por id";
}

TEST(EulerMistoId, DirecionadoDisconnected){
    Euler d(4, 0, { {0, 1}, {1, 0}, {2, 3}, {3, 2} });
    EXPECT_FALSE(d.euleriano()) << "O digrafo não é euleriano";
    //EXPECT_FALSE(d.checkFortementeConexo()) << "O digrafo não é conexo";
    //EXPECT_TRUE(d.checkDeg()) << "Os graus de entrada e saída são iguais";
}

TEST(EulerMistoId, DirecionadoWrongDeg){
    Euler d(4, 0, { {0, 1}, {1, 2}, {2, 3} });
    EXPECT_FALSE(d.euleriano()) << "O digrafo não é euleriano";
    //EXPECT_FALSE(d.checkDeg()) << "Os graus de entrada e saída não são iguais"; 
    //EXPECT_FALSE(d.checkFortementeConexo()) << "O digrafo é fortemente conexo";
    EXPECT_DEATH(d.trilha_euleriana_id(), "") << "O algoritmo chega a uma exceção buscando trilha euleriana inexistente";
}

TEST(EulerMistoId, DirecionadoLoop){
    Euler d(1, 0, { {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
}

TEST(EulerMistoId, DirecionadoLoop2){
    Euler d(1, 0, { {0, 0}, {0, 0}, {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
}

TEST(EulerMistoId, DirecionadoMultipleArc){
    Euler d(2, 0, { {0, 1}, {1, 0}, {0, 1}, {1, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
}

TEST(EulerMistoId, DirecionadoMultipleArc2){
    Euler d(3, 0, { {0, 1}, {1, 2}, {2, 0}, {1, 0}, {2, 1}, {0, 2} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
} 

TEST(Euler, EulerIdChecker){
    Euler euler(3, 3, { {0, 1}, {1, 2}, {2, 0} });
    vector<int> trilha = euler.trilha_euleriana_id();
    EXPECT_TRUE(euler.euleriano()) << "O grafo testado não é euleriano";
    EXPECT_TRUE(euler.checkEulerianTrailById()) << "A trilha não é euleriana";
}

TEST(Euler, EulerIdCycle){
    Euler euler(3, 3, { {0, 1}, {1, 2}, {2, 0} });
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

TEST(Euler, WrongTrailById){
    Euler d(4, 4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}});
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(d.checkEulerianTrailById());
    vector<int> fakeTrailById = {0, 2, 1, 3};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
}

TEST(Euler, InstanceReset){
    Euler d(4, 4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}} );
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(d.checkEulerianTrailById());
    EXPECT_TRUE(d.checkEulerianTrailById());
    d = Euler(4, 4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}} );
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(d.checkEulerianTrailById());
    EXPECT_TRUE(d.checkEulerianTrailById());
    d = Euler(3, 3, { {0, 1}, {1, 2}, {2, 0} });
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
    Euler d(4, 3, {{0, 1}, {1, 2}, {2, 3}});
    vector<int> fakeTrailById = {0, 1, 2};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
}