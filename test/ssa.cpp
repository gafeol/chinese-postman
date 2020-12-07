#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/digrafo.hpp"
#include "../code/ssa.cpp"

TEST(SSA, Tree){
    Digrafo G(2, {{0, 1, 1.}, {1, 0, 2.}});
    auto ssa = ChuLiu(G);
    double cost = ssa.doit(0);
    EXPECT_DOUBLE_EQ(cost, 1.);
    EXPECT_EQ(ssa.take[0], 1);
    EXPECT_EQ(ssa.take[1], 0);
}


TEST(SSA, Tree2){
    Digrafo G(2, {{0, 1, 2.}, {1, 0, 1.}});
    auto ssa = ChuLiu(G);
    double cost = ssa.doit(0);
    EXPECT_DOUBLE_EQ(cost, 2.);
    EXPECT_EQ(ssa.take[0], 1);
    EXPECT_EQ(ssa.take[1], 0);
}

TEST(SSA, TreeOtherRoot){
    Digrafo G(2, {{0, 1, 2.}, {1, 0, 1.}});
    auto ssa = ChuLiu(G);
    double cost = ssa.doit(1);
    EXPECT_DOUBLE_EQ(cost, 1.);
    EXPECT_EQ(ssa.take[0], 0);
    EXPECT_EQ(ssa.take[1], 1);
}

