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