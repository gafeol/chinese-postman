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