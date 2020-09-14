#include "gtest/gtest.h"
#include <bits/stdc++.h>
using namespace std;

#include "../code/problema-transporte.cpp"

TEST(ProblemaTransporte, RedeSimples){
    ProblemaTransporte pt(2, {0}, {2}, 
                             {1}, {2},
                             { { 0, 1 },
                                { 2, 0 }});
    vector<tuple<int, int, int>> ans = pt.solve();
    EXPECT_EQ(ans.size(), 1);
    int u, v, f;
    tie(u, v, f) = ans[0];
    EXPECT_EQ(u, 0);
    EXPECT_EQ(v, 1);
    EXPECT_EQ(f, 2);

    EXPECT_EQ(pt.cost, 2);
    EXPECT_EQ(pt.flow, 2);
}

TEST(ProblemaTransporte, RedeSimples2){
    ProblemaTransporte pt(2, {0}, {2}, 
                             {1}, {1},
                             { { 0., 0.4},
                                { 2., 0. }});
    
    vector<tuple<int, int, int>> ans = pt.solve();
    EXPECT_EQ(ans.size(), 1);
    int u, v, f;
    tie(u, v, f) = ans[0];
    EXPECT_EQ(u, 0);
    EXPECT_EQ(v, 1);
    EXPECT_EQ(f, 1);

    EXPECT_DOUBLE_EQ(pt.cost, 0.4);
    EXPECT_EQ(pt.flow, 1);
}

TEST(ProblemaTransporte, Rede){
    ProblemaTransporte pt(4, {0, 2}, {2, 3}, 
                             {1, 3}, {4, 1},
                             { { 0, 2, INT_MAX, 1},
                               { INT_MAX, INT_MAX, INT_MAX, INT_MAX},
                               { INT_MAX, 3, INT_MAX, 7 },
                               { INT_MAX, INT_MAX, INT_MAX, INT_MAX }
                             });
    vector<tuple<int, int, int>> ans = pt.solve();
    sort(ans.begin(), ans.end());
    vector<tuple<int, int, int>> exp = {make_tuple(0, 1, 1), make_tuple(0, 3, 1), make_tuple(2, 1, 3)};
    EXPECT_EQ(ans, exp);
}