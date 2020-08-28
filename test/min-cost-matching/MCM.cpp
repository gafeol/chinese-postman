#include "gtest/gtest.h"
#include "../../code/min-cost-matching/MCM.cpp"
#include <bits/stdc++.h>
using namespace std;

void ord(vector<pair<int, int>> &v){
    for(pair<int, int> &p: v){
        if(p.first > p.second)
            swap(p.first, p.second);
    }
    sort(v.begin(), v.end());
}

TEST(MCPM, SimpleMatching){
    vector<tuple<int, int, double>> arestas = {
        make_tuple(0, 1, 1.),
        make_tuple(0, 2, 2.),
        make_tuple(1, 2, 0.),
        make_tuple(2, 3, 7.),
        make_tuple(1, 3, 3.)
    };
    pair<double, vector<pair<int, int>>> ans = MinimumCostPerfectMatching(4, arestas);
    double cost = ans.first;
    EXPECT_EQ(cost, 5);
    vector<pair<int, int>> matching = ans.second;
    vector<pair<int, int>> optMatching = {{2, 0}, {1, 3}};
    ord(matching); ord(optMatching);
    EXPECT_EQ(matching, optMatching);
}
