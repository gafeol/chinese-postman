#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/digrafo.hpp"
#include "../code/ssa.cpp"

TEST(SSA, Tree){
    Digrafo G(2, {{0, 1, 1.}, {1, 0, 2.}});
    auto ssa = ChuLiu(G);
    auto [cost, take] = ssa.solve(0);
    EXPECT_DOUBLE_EQ(cost, 1.);
    vector<int> expTake = {0};
    EXPECT_EQ(take, expTake);
}


TEST(SSA, Tree2){
    Digrafo G(2, {{0, 1, 2.}, {1, 0, 1.}});
    auto ssa = ChuLiu(G);
    auto [cost, take] = ssa.solve(0);
    EXPECT_DOUBLE_EQ(cost, 2.);
    vector<int> expTake = {0};
    EXPECT_EQ(take, expTake);
}

TEST(SSA, TreeOtherRoot){
    Digrafo G(2, {{0, 1, 2.}, {1, 0, 1.}});
    auto ssa = ChuLiu(G);
    auto [cost, take] = ssa.solve(1);
    EXPECT_DOUBLE_EQ(cost, 1.);
    vector<int> expTake = {1};
    EXPECT_EQ(take, expTake);
}

TEST(SSA, Cycle){
    Digrafo G(4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}}); 
    auto ssa  = ChuLiu(G);
    vector<int> expTake = {0, 1, 2};
    auto [cost, take] = ssa.solve(0);
    EXPECT_DOUBLE_EQ(cost, 3.);
    EXPECT_EQ(take, expTake);
}

/*
0 1
2 1
4 1
2 0
1 4
3 0
1 3
2 0
2 4
4 2
*/ 

TEST(SSA, Triangles){
    Digrafo G(5, {{0, 1}, {2, 1}, {4, 1}, {2, 0}, {1, 4}, {3, 0}, {1, 3}, {2, 0}, {2, 4}, {4, 2}} );
    auto ssa = ChuLiu(G);
    vector<int> expTake = {0, 4, 6, 9};
    auto [cost, take] = ssa.solve(0);
    EXPECT_DOUBLE_EQ(cost, 4);
    EXPECT_EQ(take, expTake);
}

/*
0 1
2 1
4 1
2 0
1 4
3 0
1 3
2 0
2 4
*/

TEST(SSA, NotStronglyConnected){
    Digrafo G(5, {{0, 1}, {2, 1}, {4, 1}, {2, 0}, {1, 4}, {3, 0}, {1, 3}, {2, 0}, {2, 4}} );
    auto ssa = ChuLiu(G);
    EXPECT_DEATH(ssa.solve(0), "");
}

