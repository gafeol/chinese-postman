#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/euler-misto.cpp"
#include "../code/pcc-misto.cpp"

PCC pcc;
void testGrauPar(Misto G) { 
    for(int u=0;u<G.n;u++){
        EXPECT_EQ(G.grauTotal(u)%2, 0);
    }
}

TEST(PCCMisto, GrauTotalPar){
    Misto G(2, {{1, 0}}, {{0, 1}});
    Misto GPar = pcc.grau_total_par(G);
    for(int u=0;u<G.n;u++){
        EXPECT_EQ(G.adj[u], GPar.adj[u]);
    }
    testGrauPar(GPar);
}

TEST(PCCMisto, GrauTotalPar2){
    Misto G(2, {{0, 1}}, {});
    for(int u=0;u<2;u++)
        EXPECT_NE(G.grauTotal(u)%2, 0);
    Misto GPar = pcc.grau_total_par(G);
    testGrauPar(GPar);
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