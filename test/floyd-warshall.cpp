#include "gtest/gtest.h"
#include <bits/stdc++.h>
using namespace std;

#include "../code/grafo.hpp"
#include "../code/floyd-warshall.cpp"

TEST(FloydWarshall, GrafoSimples){
    int n = 4;
    Grafo G(n, { make_tuple(0, 1, 2.), 
                 make_tuple(1, 2, 5.), 
                 make_tuple(0, 2, 2.),
                 make_tuple(3, 2, 1.) });
    vector<vector<double>> d = floyd_warshall(G);
    EXPECT_EQ(d.size(), n);
    for(int i=0;i<(int)d.size();i++)
        EXPECT_EQ(d[i].size(), n);
    EXPECT_DOUBLE_EQ(d[0][0], 0);
    EXPECT_DOUBLE_EQ(d[0][1], 2);
    EXPECT_DOUBLE_EQ(d[0][2], 2);
    EXPECT_DOUBLE_EQ(d[0][3], 3);

    EXPECT_DOUBLE_EQ(d[1][0], 2);
    EXPECT_DOUBLE_EQ(d[1][1], 0);
    EXPECT_DOUBLE_EQ(d[1][2], 4);
    EXPECT_DOUBLE_EQ(d[1][3], 5);

    EXPECT_DOUBLE_EQ(d[2][0], 2);
    EXPECT_DOUBLE_EQ(d[2][1], 4);
    EXPECT_DOUBLE_EQ(d[2][2], 0);
    EXPECT_DOUBLE_EQ(d[2][3], 1);

    EXPECT_DOUBLE_EQ(d[3][0], 3);
    EXPECT_DOUBLE_EQ(d[3][1], 5);
    EXPECT_DOUBLE_EQ(d[3][2], 1);
    EXPECT_DOUBLE_EQ(d[3][3], 0);
}

TEST(FloydWarshall, Disconexo){
    int n = 3;
    Grafo G(n, { make_tuple(0, 1, 2.), 
                 make_tuple(1, 0, 5.)});
    vector<vector<double>> d = floyd_warshall(G);
    EXPECT_DOUBLE_EQ(d[0][0], 0.);
    EXPECT_DOUBLE_EQ(d[0][1], 2.);
    EXPECT_DOUBLE_EQ(d[0][2], INF);

    EXPECT_DOUBLE_EQ(d[1][0], 2.);
    EXPECT_DOUBLE_EQ(d[1][1], 0.);
    EXPECT_DOUBLE_EQ(d[1][2], INF);

    EXPECT_DOUBLE_EQ(d[2][0], INF);
    EXPECT_DOUBLE_EQ(d[2][1], INF);
    EXPECT_DOUBLE_EQ(d[2][2], 0);
}

/*
0 1 3.
1 2 3.
2 3 6.
3 0 2.
3 1 1.
0 3 1.
*/

TEST(FloydWarshall, Digrafo){
    int n = 4;
    Digrafo G(n, { make_tuple(0, 1, 3.),
                    make_tuple(1, 2, 3.),
                    make_tuple(2, 3, 6),
                    make_tuple(3, 0, 2),
                    make_tuple(3, 1, 1),
                    make_tuple(0, 3, 1)});
    
    vector<vector<double>> d = floyd_warshall(G);
    EXPECT_EQ(d.size(), n);
    for(int i=0;i<(int)d.size();i++)
        EXPECT_EQ(d[i].size(), n);
    EXPECT_DOUBLE_EQ(d[0][0], 0);
    EXPECT_DOUBLE_EQ(d[0][1], 2);
    EXPECT_DOUBLE_EQ(d[0][2], 5);
    EXPECT_DOUBLE_EQ(d[0][3], 1);

    EXPECT_DOUBLE_EQ(d[1][0], 11);
    EXPECT_DOUBLE_EQ(d[1][1], 0);
    EXPECT_DOUBLE_EQ(d[1][2], 3);
    EXPECT_DOUBLE_EQ(d[1][3], 9);

    EXPECT_DOUBLE_EQ(d[2][0], 8);
    EXPECT_DOUBLE_EQ(d[2][1], 7);
    EXPECT_DOUBLE_EQ(d[2][2], 0);
    EXPECT_DOUBLE_EQ(d[2][3], 6);

    EXPECT_DOUBLE_EQ(d[3][0], 2);
    EXPECT_DOUBLE_EQ(d[3][1], 1);
    EXPECT_DOUBLE_EQ(d[3][2], 4);
    EXPECT_DOUBLE_EQ(d[3][3], 0);
}