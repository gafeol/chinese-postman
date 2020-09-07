#include "gtest/gtest.h"
#include <bits/stdc++.h>
using namespace std;

#include "../code/grafo.hpp"
#include "../code/pcc-grafo.cpp"

TEST(PCCGrafo, Simples){
    Grafo G(2, { make_tuple(0, 1, 2.)});
    PCC pcc(G);
    pair<double, vector<int>> ans = pcc.solve();
    EXPECT_EQ(ans.first, 4);
    EXPECT_TRUE(pcc.checkSolution(ans));
}


/*
1 2 3
0 3 1
3 2 1
1 3 2 
0 1 2

Custo: 11 (duplica 1 3 2)
*/
TEST(PCCGrafo, Ciclo){
    Grafo G(4, { make_tuple(1, 2, 3),
                 make_tuple(0, 3, 1),
                 make_tuple(3, 2, 1),
                 make_tuple(1, 3, 2),
                 make_tuple(0, 1, 2)});
    
    PCC pcc(G);
    auto ans = pcc.solve();
    EXPECT_EQ(ans.first, 11);
    EXPECT_TRUE(pcc.checkSolution(ans));
}

// Este teste força o algoritmo a usar arestas paralelas de custos diferentes
TEST(PCCGrafo, ArestasParalelas){
    Grafo G(2, {make_tuple(0, 1, 2.),
                make_tuple(0, 1, 3.)});
    PCC pcc(G);
    auto ans = pcc.solveById();
    EXPECT_EQ(ans.first, 5);
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

*/

TEST(PCCGrafo, Arvore){
    Grafo G(7, { make_tuple(0, 3, 2.),
                 make_tuple(3, 2, 7),
                 make_tuple(0, 1, 4),
                 make_tuple(3, 4, 10),
                 make_tuple(1, 5, 1),
                 make_tuple(1, 6, 3)});
    PCC pcc(G);
    auto ans = pcc.solveById();
    EXPECT_EQ(ans.first, 54);
    EXPECT_TRUE(pcc.checkSolutionById(ans));
}