#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/digrafo.hpp"
#include "../code/pcr-digrafo.cpp"

TEST(PCRDigrafo, FracamenteConexo){
    Digrafo G(2, { {0, 1, 2.}});
    PCR pcr;
    EXPECT_DEATH(pcr.solve(G, {0}), "");
}

TEST(PCRDigrafo, Simples){
    Digrafo G(2, { {0, 1, 2.}, {1, 0, 1.}});
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {0});
    EXPECT_DOUBLE_EQ(cost, 3.);
    vector<int> expArcs = {0, 1};
    EXPECT_EQ(arcs, expArcs);
}

TEST(PCRDigrafo, Simples2){
    Digrafo G(2, { {0, 1, 2.}, {1, 0, 1.}});
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {1});
    EXPECT_DOUBLE_EQ(cost, 3.);
    vector<int> expArcs = {1, 0};
    EXPECT_EQ(arcs, expArcs);
}

TEST(PCRDigrafo, Simples3){
    Digrafo G(2, { {0, 1, 2.}, {1, 0, 1.}});
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {0, 1});
    EXPECT_DOUBLE_EQ(cost, 3.);
    vector<int> expArcs = {0, 1};
    EXPECT_EQ(arcs, expArcs);
}

TEST(PCRDigrafo, ArvoreCircuito){
    Digrafo G(3, { {0, 1, 2.}, {1, 0, 1.}, {1, 2, 1.}});
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {1});
    EXPECT_DOUBLE_EQ(cost, 3.);
    vector<int> expArcs = {1, 0};
    EXPECT_EQ(arcs, expArcs);
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

TEST(PCRDigrafo, Triangles){
    Digrafo G(5, {{0, 1}, {2, 1}, {4, 1}, {2, 0}, {1, 4}, {3, 0}, {1, 3}, {2, 0}, {2, 4}, {4, 2}} );
    
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {0, 3, 5});
    vector<int> expArcs = {0, 6, 5, 0, 4, 9, 3};
    EXPECT_DOUBLE_EQ(cost, 7);
    EXPECT_EQ(arcs, expArcs);
}

TEST(PCRDigrafo, Triangles2){
    Digrafo G(5, {{0, 1}, {2, 1}, {4, 1}, {2, 0}, {1, 4}, {3, 0}, {1, 3}, {2, 0}, {2, 4}, {4, 2}} );
    
    PCR pcr;
    auto [cost, arcs] = pcr.solve(G, {5, 9});
    vector<int> expArcs = {5, 0, 4, 9, 1, 6};
    EXPECT_DOUBLE_EQ(cost, 6);
    EXPECT_EQ(arcs, expArcs);
}

