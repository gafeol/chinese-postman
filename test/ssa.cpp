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

TEST(SSA, CompressedCycle){
    Digrafo G(4, {{0, 1, 2.},
                  {1, 0, 2.},
                  {1, 2, 1.},
                  {2, 3, 1.},
                  {3, 1, 1.}});
    auto ssa = ChuLiu(G);
    auto [cost, take] = ssa.solve(0);
    EXPECT_DOUBLE_EQ(cost, 4);
    vector<int> expTake = {0, 2, 3};
    EXPECT_EQ(take, expTake);
}

TEST(SSA, CompressedCycle2){
    Digrafo G(6, {{0, 1, 2.},
                  {1, 0, 2.},
                  {1, 2, 1.},
                  {2, 3, 1.},
                  {3, 1, 1.},
                  {3, 4, 3.}, 
                  {4, 2, 2.},
                  {4, 5, 1.},
                  {5, 4, 1.}});
    auto ssa = ChuLiu(G);
    auto [cost, take] = ssa.solve(0);
    EXPECT_DOUBLE_EQ(cost, 8);
    vector<int> expTake = {0, 2, 3, 5, 7};
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
2 4
4 2
*/ 

TEST(SSA, Triangles){
    Digrafo G(5, {{0, 1}, {2, 1}, {4, 1}, {2, 0}, {1, 4}, {3, 0}, {1, 3}, {2, 4}, {4, 2}} );
    auto ssa = ChuLiu(G);
    vector<int> expTake = {0, 4, 6, 8};
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
2 4
*/

TEST(SSA, NotStronglyConnected){
    Digrafo G(5, {{0, 1}, {2, 1}, {4, 1}, {2, 0}, {1, 4}, {3, 0}, {1, 3}, {2, 4}} );
    auto ssa = ChuLiu(G);
    EXPECT_DEATH(ssa.solve(0), "");
}

void print(vector<int> v){
    printf("vector with %d elements:\n", (int)v.size());
    for(int x: v)
        printf("%d ", x);
    puts("");
}

TEST(SSARural, Arco){
    Digrafo G(2, { {0, 1, 2.}});
    auto [c, ssa] = findRuralSSA(G, {0});
    EXPECT_DOUBLE_EQ(c, 0.);
    EXPECT_TRUE(ssa.empty());
}

TEST(SSARural, Simples){
    Digrafo G(2, { {0, 1, 2.}, {1, 0, 1.}});
    auto [cost, ssa] = findRuralSSA(G, {0, 1});
    EXPECT_DOUBLE_EQ(cost, 0);
    EXPECT_TRUE(ssa.empty());
}

TEST(SSARural, DoisArcosR){
    Digrafo G(4, { {0, 1}, {1, 2}, {2, 3}, {3, 0}});
    auto [cost, ssa] = findRuralSSA(G, {0, 2});
    EXPECT_DOUBLE_EQ(cost, 1.);
    EXPECT_EQ(ssa, vector<int> {1});
}

TEST(SSARural, Triangles){
    Digrafo G(5, {{0, 1}, {2, 1}, {4, 1}, {2, 0}, {1, 4}, {3, 0}, {1, 3}, {2, 4}, {4, 2}} );
    auto [cost, ssa] = findRuralSSA(G, {5, 8});
    vector<int> expArcs = {0, 4};
    EXPECT_DOUBLE_EQ(cost, 2.);
    EXPECT_EQ(ssa, expArcs);
}

TEST(SSARural, Triangles2){
    Digrafo G(5, {{0, 1}, {2, 1}, {4, 1}, {2, 0}, {1, 4}, {3, 0}, {1, 3}, {2, 4}, {4, 2}} );
    auto [cost, ssa] = findRuralSSA(G, {5, 8}, 2);
    vector<int> expArcs = {3};
    EXPECT_DOUBLE_EQ(cost, 1.);
    EXPECT_EQ(ssa, expArcs);
}

TEST(SSARural, Triangles3){
    Digrafo G(5, {{0, 1}, {2, 1}, {4, 1}, {2, 0}, {1, 4}, {3, 0}, {1, 3}, {2, 4}, {4, 2}} );
    auto [cost, ssa] = findRuralSSA(G, {5, 8}, 0);
    vector<int> expArcs = {0, 4};
    EXPECT_DOUBLE_EQ(cost, 2.);
    EXPECT_EQ(ssa, expArcs);
}

TEST(SSARural, InvalidRoot){
    Digrafo G(3, {{0, 1}, {1, 2}});
    EXPECT_DEATH(findRuralSSA(G, {0}, 2), "");
}

/*
TEST(SSARural, Simples2){
    Digrafo G(2, { {0, 1, 2.}, {1, 0, 1.}});
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {1});
    EXPECT_DOUBLE_EQ(cost, 3.);
    vector<int> expArcs = {0, 1};
    EXPECT_EQ(arcs, expArcs);
}

TEST(SSARural, Simples3){
    Digrafo G(2, { {0, 1, 2.}, {1, 0, 1.}});
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {0, 1});
    EXPECT_DOUBLE_EQ(cost, 3.);
    vector<int> expArcs = {0, 1};
    EXPECT_EQ(arcs, expArcs);
}

TEST(SSARural, ArvoreCircuito){
    Digrafo G(3, { {0, 1, 2.}, {1, 0, 1.}, {1, 2, 1.}});
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {1});
    EXPECT_DOUBLE_EQ(cost, 3.);
    vector<int> expArcs = {0, 1};
    EXPECT_EQ(arcs, expArcs);
}
*/
