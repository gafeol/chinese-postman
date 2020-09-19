#include "gtest/gtest.h"
#include <bits/stdc++.h>
using namespace std;

#include "../code/digrafo.hpp"
#include "../code/pcc-digrafo.cpp"


/*
0 1 2
1 0 3

Resposta: 5 
*/

TEST(PCCDigrafo, Simples){
    Digrafo G(2, { make_tuple(0, 1, 2.),
                    make_tuple(1, 0, 3.)});
    PCC pcc(G);
    pair<double, vector<int>> ans = pcc.solveById();
    EXPECT_DOUBLE_EQ(ans.first, 5);
    EXPECT_TRUE(pcc.checkSolutionById(ans));
}


/*

0 1 2
0 1 7
1 0 3

Resposta: 15 (Duplica arco 1 0 3)
*/

TEST(PCCDigrafo, ArcosParalelos){
    Digrafo G(2, { make_tuple(0, 1, 2.),
                    make_tuple(0, 1, 7.),
                    make_tuple(1, 0, 3.)});
    PCC pcc(G);
    pair<double, vector<int>> ans = pcc.solveById();
    EXPECT_DOUBLE_EQ(ans.first, 15);
    EXPECT_TRUE(pcc.checkSolutionById(ans));
}


/*
1 2 3
0 3 1
3 2 1
1 3 2 
0 1 2
2 0 1

Custo: 15 

Duplica os arcos:
3 2 1
2 0 1
2 0 1
0 1 2
*/
TEST(PCCDigrafo, Ciclo){
    Digrafo G(4, { make_tuple(1, 2, 3),
                 make_tuple(0, 3, 1),
                 make_tuple(3, 2, 1),
                 make_tuple(1, 3, 2),
                 make_tuple(0, 1, 2),
                 make_tuple(2, 0, 1)});
    PCC pcc(G);
    auto ans = pcc.solveById();
    EXPECT_DOUBLE_EQ(ans.first, 15);
    EXPECT_TRUE(pcc.checkSolutionById(ans));
}

/*
0 1 4

Nao tem solucao valida possivel, por isso o codigo espera um assert
*/
TEST(PCCDigrafo, Arco){
    Digrafo G(2, { make_tuple(0, 1, 4) });
    PCC pcc(G);
    EXPECT_DEATH(pcc.solveById(), "");
}
