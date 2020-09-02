#include "gtest/gtest.h"
#include <bits/stdc++.h>
using namespace std;

#include "../code/grafo.hpp"
#include "../code/pcc-grafo.cpp"

TEST(PCCGrafo, Simples){
    Grafo G(2, { {0, 1, 2.}});
    PCC pcc;
    pair<double, vector<int>> ans = pcc.solve(G);
    EXPECT_EQ(ans.first, 4);
}