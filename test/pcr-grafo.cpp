#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/grafo.hpp"
#include "../code/pcr-grafo.cpp"


void print(vector<int> v){
    printf("vector with %d elements:\n", (int)v.size());
    for(int x: v)
        printf("%d ", x);
    puts("");
}

TEST(PCRGrafo, Simples){
    Grafo G(2, { {0, 1, 2.}});
    PCR pcr;
    auto ans = pcr.solveById(G, {0});
    EXPECT_EQ(ans, vector<int>(2, 0));
}

TEST(PCRGrafo, SimplesSemR){
    Grafo G(2, { {0, 1, 2.}});
    PCR pcr;
    auto ans = pcr.solveById(G, {});
    EXPECT_EQ(ans, vector<int>());
}

TEST(PCRGrafo, Arvore){
    Grafo G(3, { {0, 1, 2.}, {1, 2, 1.}});
    PCR pcr;
    auto ans = pcr.solveById(G, {1});
    EXPECT_EQ(ans, vector<int>(2, 1));
}

TEST(PCRGrafo, Circuito) {
    Grafo G(4, {{0, 1, 1.},
                {1, 2, 2.},
                {2, 3, 3.},
                {3, 0, 4.}});
    PCR pcr;
    auto ans = pcr.solveById(G, {1, 2, 3}); 
    vector<int> exp = {0, 1, 2, 3};
    EXPECT_EQ(ans, exp);
}

TEST(PCRGrafo, Circuito2) {
    Grafo G(4, {{0, 1, 10.},
                {1, 2, 2.},
                {2, 3, 3.},
                {3, 0, 4.}});
    PCR pcr;
    auto ans = pcr.solveById(G, {1, 2, 3}); 
    vector<int> exp = {3, 2, 1, 1, 2, 3};
    EXPECT_EQ(ans, exp);
}

TEST(PCRGrafo, Circuito3) {
    Grafo G(4, {{0, 1, 10.},
                {1, 2, 2.},
                {2, 3, 3.},
                {3, 0, 4.}});
    PCR pcr;
    auto ans = pcr.solveById(G, {1, 2}); 
    vector<int> exp = {1, 2, 2, 1};
    EXPECT_EQ(ans, exp);
}

/*
0 1 
0 2 
0 3 
1 4
2 5
3 6
*/

TEST(PCRGrafo, Estrela){
    Grafo G(7, {{0, 1},
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

TEST(PCRGrafo, EstrelaComAtalhos){
    Grafo G(7, {{0, 1}, // 0
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
TEST(PCRGrafo, Exemplo){
    const int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5;
    Grafo G(6, {{a, b, 2.}, // 0
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
