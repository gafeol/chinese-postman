#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/euler-misto.cpp"

TEST(EulerMisto, DirecionadoEulerChecker){
    Euler d(3, 0, { {0, 1}, {1, 2}, {2, 0} });
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha)) << "A trilha não é euleriana";
    vector<int> fakeTrailById = {0, 2, 1, 0};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
    fakeTrailById = {0, 2, 1};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
}

TEST(EulerMisto, DirecionadoEulerCycle){
    Euler d(3, 0, { {0, 1}, {1, 2}, {2, 0} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_TRUE(d.checkEulerianTrailById(trilha)) << "A trilha não é euleriana por id";
}

TEST(EulerMisto, DirecionadoEulerCycle2){
    Euler d(5, 0, { {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1} });
    EXPECT_TRUE(d.euleriano()) << "O digrafo é euleriano.";
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_FALSE(trilha.empty()) << "A trilha não é vazia"; 
    EXPECT_TRUE(d.checkEulerianTrailById(trilha)) << "A trilha não é euleriana por id";
}

TEST(EulerMisto, DirecionadoLoop){
    Euler d(1, 0, { {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
}

TEST(EulerMisto, DirecionadoLoop2){
    Euler d(1, 0, { {0, 0}, {0, 0}, {0, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
}

TEST(EulerMisto, DirecionadoMultipleArc){
    Euler d(2, 0, { {0, 1}, {1, 0}, {0, 1}, {1, 0} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
}

TEST(EulerMisto, DirecionadoMultipleArc2){
    Euler d(3, 0, { {0, 1}, {1, 2}, {2, 0}, {1, 0}, {2, 1}, {0, 2} });
    EXPECT_TRUE(d.euleriano());
    vector<int> trilha = d.trilha_euleriana_id();
    EXPECT_TRUE(d.checkEulerianTrailById(trilha));
} 

TEST(EulerMisto, EulerIdChecker){
    Euler euler(3, 3, { {0, 1}, {1, 2}, {2, 0} });
    vector<int> trilha = euler.trilha_euleriana_id();
    EXPECT_TRUE(euler.euleriano()) << "O grafo testado não é euleriano";
    EXPECT_TRUE(euler.checkEulerianTrailById()) << "A trilha não é euleriana";
}

TEST(EulerMisto, EulerIdCycle){
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

TEST(EulerMisto, WrongTrailById){
    Euler d(4, 4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}});
    EXPECT_TRUE(d.euleriano());
    EXPECT_TRUE(d.checkEulerianTrailById());
    vector<int> fakeTrailById = {0, 2, 1, 3};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
}

TEST(EulerMisto, InstanceReset){
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

TEST(EulerMisto, NotCircuit){
    Euler d(4, 3, {{0, 1}, {1, 2}, {2, 3}});
    vector<int> fakeTrailById = {0, 1, 2};
    EXPECT_FALSE(d.checkEulerianTrailById(fakeTrailById));
}

TEST(EulerMisto, MixedTwoNodes){
    Euler d(2, 1, {{1, 0}, {0, 1}});
    EXPECT_FALSE(d.euleriano());
}

TEST(EulerMisto, MixedTwoNodesMultipleArcs){
    Euler d(2, {{1, 0}}, {{0, 1}, {0, 1}});
    EXPECT_FALSE(d.euleriano());
}

TEST(EulerMisto, MixedThreeNodes){
    Euler d(3, {{2, 0}}, {{0, 1}, {1, 2}});
    EXPECT_FALSE(d.euleriano());
}

TEST(EulerMisto, TwoSCC){
    Misto G(2, {}, {{0, 1}});
    Euler d(G);
    EXPECT_FALSE(d.euleriano());
}
