#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/euler-misto.cpp"
#include "../code/pcc-misto.cpp"


TEST(PCCMisto, GrauTotalPar){
    Misto G(2, {{1, 0}}, {{0, 1}});
    EXPECT_EQ(G.grauEntrada(0), 0);
    EXPECT_EQ(G.grauSaida(0), 1);
    EXPECT_EQ(G.grau(0), 1);
    PCC pcc;
    Misto GPar = pcc.grau_total_par(G);
    for(int u=0;u<G.n;u++){
        EXPECT_EQ(G.adj[u], GPar.adj[u]);
    }
}

/*
TEST(PCCMisto, MixedTwoNodes){
    Misto G(2, {{1, 0}}, {{0, 1}});
    PCC pcc;
    auto sol = pcc.solveById(G);
    for(int u: sol){
        printf("%d ", u);
    }
    puts("");
}

TEST(PCCMisto, MixedTwoNodesMultipleArcs){
    Euler d(2, {{1, 0}}, {{0, 1}, {0, 1}});
    EXPECT_FALSE(d.euleriano());
}

TEST(PCCMisto, MixedThreeNodes){
    Euler d(3, {{2, 0}}, {{0, 1}, {1, 2}});
    EXPECT_FALSE(d.euleriano());
}
*/