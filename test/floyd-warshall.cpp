#include "gtest/gtest.h"
#include <bits/stdc++.h>
using namespace std;

#include "../code/grafo.hpp"
#include "../code/floyd-warshall.cpp"

TEST(FloydWarshall, GrafoSimples){
    int n = 4;
    Grafo G(n, { {0, 1, 2.}, 
                 {1, 2, 5.}, 
                 {0, 2, 2.},
                 {3, 2, 1.}});
    vector<vector<double>> d = floyd_warshall(G);
    EXPECT_EQ(d.size(), n);
    for(int i=0;i<(int)d.size();i++)
        EXPECT_EQ(d[i].size(), n);
    EXPECT_EQ(d[0][0], 0);
    EXPECT_EQ(d[0][1], 2);
    EXPECT_EQ(d[0][2], 2);
    EXPECT_EQ(d[0][3], 3);

    EXPECT_EQ(d[1][0], 2);
    EXPECT_EQ(d[1][1], 0);
    EXPECT_EQ(d[1][2], 4);
    EXPECT_EQ(d[1][3], 5);

    EXPECT_EQ(d[2][0], 2);
    EXPECT_EQ(d[2][1], 4);
    EXPECT_EQ(d[2][2], 0);
    EXPECT_EQ(d[2][3], 1);

    EXPECT_EQ(d[3][0], 3);
    EXPECT_EQ(d[3][1], 5);
    EXPECT_EQ(d[3][2], 1);
    EXPECT_EQ(d[3][3], 0);
}

TEST(FloydWarshall, Disconexo){
    int n = 3;
    Grafo G(n, { {0, 1, 2.}, 
                 {1, 0, 5.}});
    vector<vector<double>> d = floyd_warshall(G);
    EXPECT_EQ(d[0][0], 0.);
    EXPECT_EQ(d[0][1], 2.);
    EXPECT_EQ(d[0][2], INF);

    EXPECT_EQ(d[1][0], 2.);
    EXPECT_EQ(d[1][1], 0.);
    EXPECT_EQ(d[1][2], INF);

    EXPECT_EQ(d[2][0], INF);
    EXPECT_EQ(d[2][1], INF);
    EXPECT_EQ(d[2][2], 0);
}