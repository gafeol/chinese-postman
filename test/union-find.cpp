#include "gtest/gtest.h"
#include "bits/stdc++.h"
using namespace std;

#include "../code/union-find.cpp"

TEST(UnionFind, ThreeNodes){
    UnionFind uf(3);

    EXPECT_TRUE(uf.join(1, 2));
    EXPECT_TRUE(uf.sz[1] == 2);
    EXPECT_TRUE(uf.sz[2] == 1);
    EXPECT_TRUE(uf.p[1] == 1);
    EXPECT_TRUE(uf.p[2] == 1);
    EXPECT_TRUE(uf.join(0, 1));
    EXPECT_TRUE(uf.p[0] == 1);
    EXPECT_TRUE(uf.sz[1] == 3);
}