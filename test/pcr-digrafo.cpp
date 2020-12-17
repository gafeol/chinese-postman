#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/digrafo.hpp"
#include "../code/pcr-digrafo.cpp"

TEST(PCRDigrafo, FracamenteConexo){
    Digrafo G(2, { {0, 1, 2.}});
    PCR pcr;
    EXPECT_DEATH(pcr.solve(G, {0}), "");
}

TEST(PCRDigrafo, Simples){
    Digrafo G(2, { {0, 1, 2.}, {1, 0, 1.}});
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {0});
    EXPECT_DOUBLE_EQ(cost, 3.);
    vector<int> expArcs = {0, 1};
    EXPECT_EQ(arcs, expArcs);
}

TEST(PCRDigrafo, Simples2){
    Digrafo G(2, { {0, 1, 2.}, {1, 0, 1.}});
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {1});
    EXPECT_DOUBLE_EQ(cost, 3.);
    vector<int> expArcs = {0, 1};
    EXPECT_EQ(arcs, expArcs);
}

TEST(PCRDigrafo, Simples3){
    Digrafo G(2, { {0, 1, 2.}, {1, 0, 1.}});
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {0, 1});
    EXPECT_DOUBLE_EQ(cost, 3.);
    vector<int> expArcs = {0, 1};
    EXPECT_EQ(arcs, expArcs);
}

TEST(PCRDigrafo, ArvoreCircuito){
    Digrafo G(3, { {0, 1, 2.}, {1, 0, 1.}, {1, 2, 1.}});
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {1});
    EXPECT_DOUBLE_EQ(cost, 3.);
    vector<int> expArcs = {0, 1};
    EXPECT_EQ(arcs, expArcs);
}

/*
TEST(PCRDigrafo, Circuito) {
    Digrafo G(4, {{0, 1, 1.},
                {1, 2, 2.},
                {2, 3, 3.},
                {3, 0, 4.}});
    PCR pcr;
    auto ans = pcr.solveById(G, {1, 2, 3}); 
    vector<int> exp = {0, 1, 2, 3};
    EXPECT_EQ(ans, exp);
}

TEST(PCRDigrafo, Circuito2) {
    Digrafo G(4, {{0, 1, 10.},
                {1, 2, 2.},
                {2, 3, 3.},
                {3, 0, 4.}});
    PCR pcr;
    auto ans = pcr.solveById(G, {1, 2, 3}); 
    vector<int> exp = {3, 2, 1, 1, 2, 3};
    EXPECT_EQ(ans, exp);
}

TEST(PCRDigrafo, Circuito3) {
    Digrafo G(4, {{0, 1, 10.},
                {1, 2, 2.},
                {2, 3, 3.},
                {3, 0, 4.}});
    PCR pcr;
    auto ans = pcr.solveById(G, {1, 2}); 
    vector<int> exp = {1, 2, 2, 1};
    EXPECT_EQ(ans, exp);
}

0 1 
0 2 
0 3 
1 4
2 5
3 6

TEST(PCRDigrafo, Estrela){
    Digrafo G(7, {{0, 1},
                {0, 2},
                {0, 3},
                {1, 4},
                {2, 5},
                {3, 6}});
    PCR pcr;
    auto ans = pcr.solveById(G, {3, 4, 5});
    // trilha se inicia em 1
    auto exp = vector<int> { 3, 3, 0, 2, 5, 5, 2, 1, 4, 4, 1, 0 };
    EXPECT_EQ(ans, exp);
}

TEST(PCRDigrafo, EstrelaComAtalhos){
    Digrafo G(7, {{0, 1}, // 0
                {0, 2},// 1
                {0, 3},// 2
                {1, 4},// 3
                {2, 5},// 4
                {3, 6},// 5
                {4, 5},// 6
                {5, 6},// 7
                {6, 4}});// 8
    PCR pcr;
    auto ans = pcr.solveById(G, {3, 4, 5});
    // trilha se inicia em 1, solucao otima com custo 8
    auto exp = vector<int> {3, 8, 5, 2, 1, 4, 6, 3 };
    EXPECT_EQ(ans, exp);
}


/// Exemplo apresentado na seção do PCR da monografia.
/// Solução ótima encontrada, com custo 16
TEST(PCRDigrafo, Exemplo){
    const int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5;
    Digrafo G(6, {{a, b, 2.}, // 0
                {a, c, 4.}, // 1
                {b, c, 2.}, // 2
                {b, d, 1.}, // 3
                {c, d, 1.}, // 4
                {b, f, 3.}, // 5
                {d, f, 2.}, // 6
                {c, e, 5.}, // 7
                {e, f, 2.}}); // 8
    PCR pcr;
    auto ans = pcr.solveById(G, {0, 1, 2, 8});
    auto exp = vector<int>{1, 4, 6, 8, 8, 6, 4, 2, 0};
    EXPECT_EQ(ans, exp);
}

/*
1 2 3
0 3 1
3 2 1
1 3 2 
0 1 2

Custo: 11 (duplica 1 3 2)
TEST(PCCDigrafo, Ciclo){
    Digrafo G(4, { make_tuple(1, 2, 3),
                 make_tuple(0, 3, 1),
                 make_tuple(3, 2, 1),
                 make_tuple(1, 3, 2),
                 make_tuple(0, 1, 2)});
    
    PCC pcc(G);
    auto ans = pcc.solve();
    EXPECT_DOUBLE_EQ(ans.first, 11);
    EXPECT_TRUE(pcc.checkSolution(ans));
}

// Este teste força o algoritmo a usar arestas paralelas de custos diferentes
TEST(PCCDigrafo, ArestasParalelas){
    Digrafo G(2, {make_tuple(0, 1, 2.),
                make_tuple(0, 1, 3.)});
    PCC pcc(G);
    auto ans = pcc.solveById();
    EXPECT_DOUBLE_EQ(ans.first, 5);
    EXPECT_TRUE(pcc.checkSolutionById(ans));
}


0 3 2
3 2 7
0 1 4
3 4 10
1 5 1
1 6 3

Tem que duplicar todas arestas, custo otimo 2*27 = 54


TEST(PCCDigrafo, Arvore){
    Digrafo G(7, { make_tuple(0, 3, 2.),
                 make_tuple(3, 2, 7),
                 make_tuple(0, 1, 4),
                 make_tuple(3, 4, 10),
                 make_tuple(1, 5, 1),
                 make_tuple(1, 6, 3)});
    PCC pcc(G);
    auto ans = pcc.solveById();
    EXPECT_DOUBLE_EQ(ans.first, 54);
    EXPECT_TRUE(pcc.checkSolutionById(ans));
}

TEST(PCCDigrafo, CustoErradoId){
    Digrafo G(7, { make_tuple(0, 3, 2.),
                 make_tuple(3, 2, 7),
                 make_tuple(0, 1, 4),
                 make_tuple(3, 4, 10),
                 make_tuple(1, 5, 1),
                 make_tuple(1, 6, 3)});
    PCC pcc(G);
    auto ans = pcc.solveById();
    EXPECT_DOUBLE_EQ(ans.first, 54);
    ans.first = 53.9;
    EXPECT_FALSE(pcc.checkSolutionById(ans));
    ans.first = 54.1;
    EXPECT_FALSE(pcc.checkSolutionById(ans));
}

TEST(PCCDigrafo, CustoErrado){
    Digrafo G(7, { make_tuple(0, 3, 2.),
                 make_tuple(3, 2, 7),
                 make_tuple(0, 1, 4),
                 make_tuple(3, 4, 10),
                 make_tuple(1, 5, 1),
                 make_tuple(1, 6, 3)});
    PCC pcc(G);
    auto ans = pcc.solve();
    EXPECT_DOUBLE_EQ(ans.first, 54);
    ans.first = 53.9;
    EXPECT_FALSE(pcc.checkSolution(ans));
    ans.first = 54.1;
    EXPECT_FALSE(pcc.checkSolution(ans));
}

TEST(PCCDigrafo, CircuitoErradoId){
    Digrafo G(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}});
    PCC pcc(G);
    pair<double, vector<int>> ans;
    ans.first = 6;
    ans.second = {0, 1, 2, 3, 4, 1};
    EXPECT_FALSE(pcc.checkSolutionById(ans));
    ans.first = 7;
    ans.second = {0, 1, 2, 3, 4, 0, 1};
    EXPECT_FALSE(pcc.checkSolutionById(ans));
    ans.first = 6;
    ans.second = {1, 2, 3, 4, 0, 1};
    EXPECT_FALSE(pcc.checkSolutionById(ans));
}

TEST(PCCDigrafo, CheckSolucoesId){
    Digrafo G(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}});
    PCC pcc(G);
    auto ans = pcc.solveById();
    EXPECT_DOUBLE_EQ(5, ans.first);
    EXPECT_TRUE(pcc.checkSolutionById(ans));
    ans.first = 10;
    int sz = ans.second.size();
    for(int i=0;i<sz;i++)
        ans.second.push_back(ans.second[i]);
    EXPECT_TRUE(pcc.checkSolutionById(ans));
    ans.first = 5;
    ans.second = {1, 2, 3, 4, 0};
    EXPECT_TRUE(pcc.checkSolutionById(ans));
    ans.first = 7;
    ans.second = {1, 2, 3, 4, 0, 1, 1};
    EXPECT_TRUE(pcc.checkSolutionById(ans));
}

TEST(PCCDigrafo, CircuitoErrado){
    Digrafo G(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}});
    PCC pcc(G);
    auto ans = pcc.solve();
    EXPECT_DOUBLE_EQ(5, ans.first);
    EXPECT_TRUE(pcc.checkSolution(ans));
    ans.first = 6;
    ans.second = {0, 1, 2, 3, 4, 0, 1};
    EXPECT_FALSE(pcc.checkSolution(ans));
    ans.first = 7;
    ans.second = {0, 1, 2, 3, 4, 0, 1, 0};
    EXPECT_TRUE(pcc.checkSolution(ans));
    ans.first = 5;
    ans.second = {1, 2, 3, 4, 0, 1};
    EXPECT_TRUE(pcc.checkSolution(ans));
    ans.first = 4;
    ans.second = {1, 2, 3, 4, 0};
    EXPECT_FALSE(pcc.checkSolution(ans));
}


TEST(PCCDigrafo, CaminhoSimples){
    Digrafo G(3, {{0, 1}, {1, 2}});
    PCC pcc(G);
    auto ans = pcc.solveById();
    EXPECT_DOUBLE_EQ(4, ans.first);
    EXPECT_TRUE(pcc.checkSolutionById(ans));

    ans = pcc.solve();
    EXPECT_DOUBLE_EQ(4, ans.first);
    EXPECT_TRUE(pcc.checkSolution(ans));
}

TEST(PCCDigrafo, ArestaNaoPercorrida){
    Digrafo G(3, {{0, 1}, {1, 2}});
    PCC pcc(G);
    pair<double, vector<int>> ansId = {2., {0, 0}};
    EXPECT_FALSE(pcc.checkSolutionById(ansId));
    pair<double, vector<int>> ans = {2., {0, 1, 0}};
    EXPECT_FALSE(pcc.checkSolution(ans));
}

*/