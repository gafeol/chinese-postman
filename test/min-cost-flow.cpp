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

TEST(MinCostFlow, EdgesFlow){
    MinCostFlow mcf(6, 8);
    mcf.add_edge(0, 1, 1, 0, 0);
    mcf.add_edge(0, 2, 1, 0, 1);
    mcf.add_edge(3, 5, 1, 0, 2);
    mcf.add_edge(4, 5, 2, 10, 3);

    mcf.add_edge(1, 3, 1, 2, 4);
    mcf.add_edge(1, 4, 1, 1, 5);
    mcf.add_edge(2, 3, 1, 1, 6);
    mcf.add_edge(2, 4, 1, 3, 7);

    double cost = mcf.solve(0, 5);
    int flow = mcf.flow;
    EXPECT_EQ(flow, 2);
    EXPECT_DOUBLE_EQ(cost, 12);

    vector<int> flowOnEdge = mcf.flowOnEdge;
    EXPECT_EQ(flowOnEdge[0], 1);
    EXPECT_EQ(flowOnEdge[1], 1);
    EXPECT_EQ(flowOnEdge[2], 1);
    EXPECT_EQ(flowOnEdge[3], 1);

    EXPECT_EQ(flowOnEdge[5], 1);
    EXPECT_EQ(flowOnEdge[6], 1);

    EXPECT_EQ(flowOnEdge[4], 0);
    EXPECT_EQ(flowOnEdge[7], 0);
}