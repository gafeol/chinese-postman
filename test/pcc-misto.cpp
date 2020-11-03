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

bool testTrilhaDe(int u, vector<int> trilha, Misto G){
    int ini = u;
    auto lista = G.listaAdj();
    for(int id: trilha){
        int w, v;
        tie(w, v, ignore) = lista[id];
        if(u == w)
            u = v;
        else if(u == v && G.aresta(id))
            u = w;
        else
            return false;
    }    
    return (ini == u);
}

void testTrilhaPCCM(Misto G, vector<int> trilha){
    vector<int> cnt(G.m, 0);
    for(int id: trilha)
        cnt[id]++;
    // Testa se toda aresta/arco foi percorrida ao menos uma vez
    EXPECT_GE(*min_element(cnt.begin(), cnt.end()), 1);
    auto lista = G.listaAdj();
    EXPECT_TRUE(testTrilhaDe(get<0>(lista[trilha[0]]), trilha, G) ||
                testTrilhaDe(get<1>(lista[trilha[0]]), trilha, G));
}

void printv(vector<tuple<int, int, double, int>> v){
    for(auto [u, v, c, id]: v){
        printf("u %d v %d c %.3f id %d\n", u, v, c, id);
    }
}

TEST(PCCMisto, GrauTotalParArestaArco){
    Misto G(2, {{1, 0}}, {{0, 1}});
    Misto GPar = pcc.grau_total_par(G);
    for(int u=0;u<G.n;u++){
        EXPECT_EQ(G.adj[u], GPar.adj[u]);
    }
    testGrauTotalPar(GPar);
}

TEST(PCCMisto, GrauTotalParAresta){
    Misto G(2, {{0, 1}}, {});
    for(int u=0;u<2;u++)
        EXPECT_NE(G.grauTotal(u)%2, 0);
    Misto GPar = pcc.grau_total_par(G);
    testGrauTotalPar(GPar);
}

TEST(PCCMisto, GrauTotalPar){
    Misto G(4, {}, {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 2}});
    G = pcc.grau_total_par(G);
    testGrauTotalPar(G);
    EXPECT_EQ(G.grauTotal(0), 4);
    EXPECT_EQ(G.grauTotal(2), 4);
    EXPECT_EQ(G.grauTotal(1), 2);
    EXPECT_EQ(G.grauTotal(3), 2);
}

TEST(PCCMisto, GrauTotalParComPesos){
    Misto G(4, {}, {{0, 1, 1.}, {1, 2, 1.}, {2, 3, 1.}, {3, 0, 1.}, {0, 2, 3.}});
    G = pcc.grau_total_par(G);
    testGrauTotalPar(G);
    EXPECT_EQ(G.grauTotal(0), 4);
    EXPECT_EQ(G.grauTotal(1), 4);
    EXPECT_EQ(G.grauTotal(2), 4);
    EXPECT_EQ(G.grauTotal(3), 2);
}

TEST(PCCMisto, GrauTotalParComPesos2){
    Misto G(4, {}, {{0, 1, 1.}, {1, 2, 5.}, {2, 3, 2.}, {3, 0, 10.}, {0, 2, 3.}});
    G = pcc.grau_total_par(G);
    testGrauTotalPar(G);
    EXPECT_EQ(G.grauTotal(0), 4);
    EXPECT_EQ(G.grauTotal(2), 4);
    EXPECT_EQ(G.grauTotal(1), 2);
    EXPECT_EQ(G.grauTotal(3), 2);
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
    auto [custo, trilha] = pcc.solveById(G);
    vector<int> expTrilha = {0, 0};
    EXPECT_EQ(trilha, expTrilha);
    EXPECT_DOUBLE_EQ(custo, 2.);
}

/*
0 4 5.000 
4 0 5.000

1 2 1.000 
2 1 1.000 

2 3 3.000
3 2 3.000

3 4 2.000
4 3 2.000

0 2 5.000

0 2 5.000

1 0 3.000

3 1 4.000

1 2 1.000
2 1 1.000

2 3 3.000
3 2 3.000
*/

TEST(PCCMisto, SolveExemplo){
    /// Exemplo usado na seção referente ao PCCM da monografia
    Misto G(5,
            {{0, 4, 5.},
             {1, 2, 1.},
             {2, 3, 3.},
             {3, 4, 2.}},
            {{0, 2, 5.},
             {0, 2, 5.},
             {1, 0, 3.},
             {3, 1, 4.}});
    auto [custo, trilha] = pcc.solveById(G);
    EXPECT_DOUBLE_EQ(custo, 32.);
    testTrilhaPCCM(G, trilha);
}

TEST(PCCMisto, SolveCiclos){
    /// Exemplo usado na seção referente ao PCCM da monografia
    Misto G(10,
            {{2, 3},
             {3, 0},
             {4, 5},
             {5, 6},
             {7, 8},
             {8, 9},
             {9, 3}},
            {{0, 1},
             {1, 2},
             {3, 4},
             {6, 3},
             {7, 3}});
    auto [custo, trilha] = pcc.solveById(G);
    EXPECT_DOUBLE_EQ(custo, 12.);
    testTrilhaPCCM(G, trilha);
}

TEST(PCCMisto, SolvePesos){
    Misto G(2, 
            {{0, 1, 2.}},
            {{0, 1, 2.}, 
             {1, 0, 1.}});
    auto [custo, trilha] = pcc.solveById(G);
    EXPECT_DOUBLE_EQ(custo, 6.);
    testTrilhaPCCM(G, trilha);
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