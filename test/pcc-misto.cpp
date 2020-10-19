#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/euler-misto.cpp"
#include "../code/pcc-misto.cpp"

PCC pcc;
void testGrauTotalPar(Misto G) { 
    for(int u=0;u<G.n;u++){
        EXPECT_EQ(G.grauTotal(u)%2, 0);
    }
}

void testGrauDir(Misto G){
    for(int u=0;u<G.n;u++){
        EXPECT_EQ(G.grauEntrada(u), G.grauSaida(u));
    }
}

void testGrauPar(Misto G){
    for(int u=0;u<G.n;u++){
        EXPECT_EQ(G.grauEntrada(u), G.grauSaida(u));
        EXPECT_EQ(G.grau(u)%2, 0);
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
    testGrauTotalPar(GPar);
}

TEST(PCCMisto, GrauTotalPar2){
    Misto G(2, {{0, 1}}, {});
    for(int u=0;u<2;u++)
        EXPECT_NE(G.grauTotal(u)%2, 0);
    Misto GPar = pcc.grau_total_par(G);
    testGrauTotalPar(GPar);
}

TEST(PCCMisto, GrauDirIgual){
    Misto G(2, {{1, 0}}, {{0, 1}});
    auto [M, U, MAdd] = pcc.iguala_grau_dir(G);
    Misto GDir(G.n, M, U);
    testGrauDir(GDir);
    // Orienta aresta 1 - 0 para 1 -> 0
    EXPECT_EQ(MAdd.size(), 1);
    EXPECT_EQ(GDir.grau(0), 0);
    EXPECT_EQ(GDir.grauEntrada(0), 1);
    EXPECT_EQ(GDir.grauSaida(0), 1);
    EXPECT_EQ(GDir.grau(1), 0);
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

TEST(PCCMisto, GrauPar){
    Misto G(2, {{1, 0}}, {{0, 1}});
    G = pcc.grau_total_par(G);
    auto [M, U, MAdd] = pcc.iguala_grau_dir(G);
    tie(M, U) = pcc.grau_par(G.n, M, U, MAdd);
    EXPECT_EQ(M.size(), 1);
    EXPECT_EQ(M[0], make_tuple(1, 0, 1., 0));
    EXPECT_EQ(U.size(), 0);
    for (int u = 0; u < G.n; u++) {
        for (Aresta ar : G.adj[u]) {
            if (G.arco(ar.id)) {
                M.emplace_back(u, ar.prox, ar.cus, ar.id);
            }
        }
    }
    testGrauPar(Misto(G.n, M, U));
}

TEST(PCCMisto, GrauPar2){
    Misto G(2, {{0, 1}}, {});
    G = pcc.grau_total_par(G);
    auto [M, U, MAdd] = pcc.iguala_grau_dir(G);
    tie(M, U) = pcc.grau_par(G.n, M, U, MAdd);
    for (int u = 0; u < G.n; u++) {
        for (Aresta ar : G.adj[u]) {
            if (G.arco(ar.id)) {
                M.emplace_back(u, ar.prox, ar.cus, ar.id);
            }
        }
    }
    EXPECT_EQ(M.size(), 0);
    EXPECT_EQ(U.size(), 2);
    vector<tiidi> expU = {make_tuple(1, 0, 1., 0), make_tuple(1, 0, 1., 1)};
    EXPECT_EQ(U, expU);
    testGrauPar(Misto(G.n, M, U));
}

TEST(PCCMisto, Solve){
    Misto G(2, {{0, 1}}, {});
    auto trilha = pcc.solveById(G);
    vector<int> expTrilha = {0, 0};
    EXPECT_EQ(trilha, expTrilha);
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