#include "gtest/gtest.h"
#include <bits/stdc++.h>
using namespace std;

#include "../code/digrafo.hpp"
#include "../code/pcc-digrafo.cpp"

TEST(PCCDigrafo, Simples){
    Digrafo G(2, { make_tuple(0, 1, 2.),
                    make_tuple(0, 1, 7.),
                    make_tuple(1, 0, 3.)});
    PCC pcc(G);
    pair<double, vector<int>> ans = pcc.solveById();
    EXPECT_DOUBLE_EQ(ans.first, 15);
    EXPECT_TRUE(pcc.checkSolutionById(ans));
}