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

void testGrauDir(Misto G){
    for(int u=0;u<G.n;u++){
        EXPECT_EQ(G.grauEntrada(u), G.grauSaida(u));
    }
}

void printv(vector<tuple<int, int, double, int>> v){
    for(auto [u, v, c, id]: v){
        printf("u %d v %d c %.3f id %d\n", u, v, c, id);
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

TEST(PCCMisto, GrauDirIgual){
    Misto G(2, {{1, 0}}, {{0, 1}});
    auto [M, U, MAdd] = pcc.iguala_grau_dir(G);
    Misto GDir(G.n, M, U);
    testGrauDir(GDir);
    EXPECT_EQ(MAdd.size(), 1);
    EXPECT_EQ(GDir.grauEntrada(0), 1);
    EXPECT_EQ(GDir.grauSaida(0), 1);
    EXPECT_EQ(GDir.grauEntrada(1), 1);
    EXPECT_EQ(GDir.grauSaida(1), 1);
}

TEST(PCCMisto, GrauDirIgual2){
    Misto G(3, {{0, 1}}, {{0, 1}, {1, 2}, {2, 0}});
    auto [M, U, MAdd] = pcc.iguala_grau_dir(G);
    Misto GDir(G.n, M, U);
    testGrauDir(GDir);
    EXPECT_EQ(MAdd.size(), 0);
    EXPECT_EQ(GDir.grauEntrada(0), 1);
    EXPECT_EQ(GDir.grauSaida(0), 1);
    EXPECT_EQ(GDir.grauEntrada(1), 1);
    EXPECT_EQ(GDir.grauSaida(1), 1);
    EXPECT_EQ(GDir.grauEntrada(2), 1);
    EXPECT_EQ(GDir.grauSaida(2), 1);
}

TEST(PCCMisto, GrauDirIgual3){
    Misto G(3, {{0, 2}}, {{0, 1}, {1, 2}});
    auto [M, U, MAdd] = pcc.iguala_grau_dir(G);
    Misto GDir(G.n, M, U);
    EXPECT_EQ(MAdd.size(), 1);
    EXPECT_TRUE(U.empty());
    EXPECT_EQ(GDir.grauEntrada(0), 1);
    EXPECT_EQ(GDir.grauEntrada(1), 1);
    EXPECT_EQ(GDir.grauEntrada(2), 1);
    EXPECT_EQ(GDir.grau(0), 0);
    EXPECT_EQ(GDir.grau(1), 0);
    EXPECT_EQ(GDir.grau(2), 0);
    testGrauDir(GDir);
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