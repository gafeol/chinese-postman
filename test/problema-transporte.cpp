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


