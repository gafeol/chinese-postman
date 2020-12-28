
#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/pci-guan.cpp"
#include "../code/grafo-ingrime.hpp"

TEST(PCI, Simples){
    GrafoIngrime G(2, { {0, 1, 2., 3.}});
    PCI pci;
    auto [c, p] = pci.solve(G);
    EXPECT_DOUBLE_EQ(c, 5);
    EXPECT_EQ(p, vector<int>(2,0));
}


/*
1 2 3
0 3 1
3 2 1
1 3 2 
0 1 2

Custo: 11 (duplica 1 3 2)
TEST(PCCGrafo, Ciclo){
    Grafo G(4, { make_tuple(1, 2, 3),
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
TEST(PCCGrafo, ArestasParalelas){
    Grafo G(2, {make_tuple(0, 1, 2.),
                make_tuple(0, 1, 3.)});
    PCC pcc(G);
    auto ans = pcc.solveById();
    EXPECT_DOUBLE_EQ(ans.first, 5);
    EXPECT_TRUE(pcc.checkSolutionById(ans));
}

/*

0 3 2
3 2 7
0 1 4
3 4 10
1 5 1
1 6 3

Tem que duplicar todas arestas, custo otimo 2*27 = 54


TEST(PCCGrafo, Arvore){
    Grafo G(7, { make_tuple(0, 3, 2.),
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

TEST(PCCGrafo, CustoErradoId){
    Grafo G(7, { make_tuple(0, 3, 2.),
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

TEST(PCCGrafo, CustoErrado){
    Grafo G(7, { make_tuple(0, 3, 2.),
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

TEST(PCCGrafo, CircuitoErradoId){
    Grafo G(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}});
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

TEST(PCCGrafo, CheckSolucoesId){
    Grafo G(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}});
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

TEST(PCCGrafo, CircuitoErrado){
    Grafo G(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}});
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


TEST(PCCGrafo, CaminhoSimples){
    Grafo G(3, {{0, 1}, {1, 2}});
    PCC pcc(G);
    auto ans = pcc.solveById();
    EXPECT_DOUBLE_EQ(4, ans.first);
    EXPECT_TRUE(pcc.checkSolutionById(ans));

    ans = pcc.solve();
    EXPECT_DOUBLE_EQ(4, ans.first);
    EXPECT_TRUE(pcc.checkSolution(ans));
}

TEST(PCCGrafo, ArestaNaoPercorrida){
    Grafo G(3, {{0, 1}, {1, 2}});
    PCC pcc(G);
    pair<double, vector<int>> ansId = {2., {0, 0}};
    EXPECT_FALSE(pcc.checkSolutionById(ansId));
    pair<double, vector<int>> ans = {2., {0, 1, 0}};
    EXPECT_FALSE(pcc.checkSolution(ans));
}
*/