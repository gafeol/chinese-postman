#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/digrafo.hpp"
#include "../code/ssa.cpp"

TEST(SSA, Tree){
    Digrafo G(2, {{0, 1, 1.}, {1, 0, 2.}});
    auto ssa = findSSA(G);
    EXPECT_EQ(ssa, vector<int>{0});
}


