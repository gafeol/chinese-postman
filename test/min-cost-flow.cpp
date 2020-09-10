#include "gtest/gtest.h"
#include <bits/stdc++.h>
using namespace std;

#include "../code/min-cost-flow.cpp"


TEST(MinCostFlow, Aresta){
    MinCostFlow mcf(2);

    mcf.add_edge(0, 1, 1, 2);

    double cost = mcf.solve(0, 1);
    int flow = mcf.flow;

    EXPECT_EQ(flow, 1);
    EXPECT_DOUBLE_EQ(cost, 2);
}

TEST(MinCostFlow, RedeBipartida){
    MinCostFlow mcf(6);
    mcf.add_edge(0, 1, INT_MAX, 0);
    mcf.add_edge(0, 2, INT_MAX, 0);
    mcf.add_edge(3, 5, INT_MAX, 0);
    mcf.add_edge(4, 5, INT_MAX, 0);

    mcf.add_edge(1, 3, 1, 2);
    mcf.add_edge(1, 4, 1, 1);
    mcf.add_edge(2, 4, 1, 3);
    mcf.add_edge(2, 3, 1, 1);

    double cost = mcf.solve(0, 5);
    int flow = mcf.flow;
    EXPECT_EQ(flow, 4);
    EXPECT_DOUBLE_EQ(cost, 7);
}

TEST(MinCostFlow, RedeBipartida2){
    MinCostFlow mcf(6);
    mcf.add_edge(0, 1, 1, 0);
    mcf.add_edge(0, 2, 1, 0);
    mcf.add_edge(3, 5, 1, 0);
    mcf.add_edge(4, 5, 1, 0);

    mcf.add_edge(1, 3, 1, 2);
    mcf.add_edge(1, 4, 1, 1);
    mcf.add_edge(2, 4, 1, 3);
    mcf.add_edge(2, 3, 1, 1);

    double cost = mcf.solve(0, 5);
    int flow = mcf.flow;
    EXPECT_EQ(flow, 2);
    EXPECT_DOUBLE_EQ(cost, 2);
}

TEST(MinCostFlow, RedeBipartida3){
    MinCostFlow mcf(6);
    mcf.add_edge(0, 1, 1, 0);
    mcf.add_edge(0, 2, 1, 0);
    mcf.add_edge(3, 5, 1, 0);
    mcf.add_edge(4, 5, 2, 10);

    mcf.add_edge(1, 3, 1, 2);
    mcf.add_edge(1, 4, 1, 1);
    mcf.add_edge(2, 3, 1, 1);
    mcf.add_edge(2, 4, 1, 3);

    double cost = mcf.solve(0, 5);
    int flow = mcf.flow;
    EXPECT_EQ(flow, 2);
    EXPECT_DOUBLE_EQ(cost, 12);
}