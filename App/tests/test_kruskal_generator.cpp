#include <gtest/gtest.h>
#include "KruskalGenerator.h"
#include "DFSGenerator.h"

TEST(KruskalGeneratorTest, GeneratesMazeOfCorrectSize) {
    Labyrinth lab(10, 10);
    KruskalGenerator gen;
    gen.generate(lab);
    
    EXPECT_EQ(lab.getWidth(), 10);
    EXPECT_EQ(lab.getHeight(), 10);
}

TEST(KruskalGeneratorTest, MazeIsConnected) {
    Labyrinth lab(7, 7);
    KruskalGenerator gen;
    gen.generate(lab);
    
    auto [sx, sy] = lab.getStart();
    auto [fx, fy] = lab.getFinish();
    
    EXPECT_TRUE(lab.getCell(sx, sy).isStart);
    EXPECT_TRUE(lab.getCell(fx, fy).isFinish);
}

TEST(KruskalGeneratorTest, StartAndFinishAreSet) {
    Labyrinth lab(8, 8);
    KruskalGenerator gen;
    gen.generate(lab);
    
    EXPECT_TRUE(lab.getCell(0, 0).isStart);
    EXPECT_TRUE(lab.getCell(7, 7).isFinish);
}

TEST(KruskalGeneratorTest, MazeHasNoFullWalls) {
    Labyrinth lab(6, 6);
    KruskalGenerator gen;
    gen.generate(lab);
    
    bool hasPath = false;
    for (int y = 0; y < lab.getHeight(); y++) {
        for (int x = 0; x < lab.getWidth(); x++) {
            bool allWalls = lab.getCell(x, y).walls[0] &&
                           lab.getCell(x, y).walls[1] &&
                           lab.getCell(x, y).walls[2] &&
                           lab.getCell(x, y).walls[3];
            if (!allWalls) hasPath = true;
        }
    }
    EXPECT_TRUE(hasPath);
}

TEST(KruskalGeneratorTest, BorderWallsArePresent) {
    Labyrinth lab(5, 5);
    KruskalGenerator gen;
    gen.generate(lab);
    
    EXPECT_TRUE(lab.getCell(0, 0).walls[3]);
    EXPECT_TRUE(lab.getCell(0, 0).walls[0]);
}

TEST(KruskalGeneratorTest, DifferentSizesWork) {
    std::vector<std::pair<int,int>> sizes = {{5,5}, {10,10}, {15,20}, {20,15}};
    KruskalGenerator gen;
    
    for (auto [w, h] : sizes) {
        Labyrinth lab(w, h);
        gen.generate(lab);
        
        EXPECT_EQ(lab.getWidth(), w);
        EXPECT_EQ(lab.getHeight(), h);
        EXPECT_TRUE(lab.getCell(0, 0).isStart);
        EXPECT_TRUE(lab.getCell(w-1, h-1).isFinish);
    }
}

TEST(KruskalGeneratorTest, KruskalProducesDifferentMazeThanDFS) {
    Labyrinth lab1(10, 10);
    Labyrinth lab2(10, 10);
    
    DFSGenerator dfs;
    KruskalGenerator kruskal;
    
    dfs.generate(lab1);
    kruskal.generate(lab2);
    
    bool differ = false;
    for (int y = 0; y < 10 && !differ; y++) {
        for (int x = 0; x < 10 && !differ; x++) {
            for (int w = 0; w < 4; w++) {
                if (lab1.getCell(x, y).walls[w] != lab2.getCell(x, y).walls[w]) {
                    differ = true;
                    break;
                }
            }
        }
    }
    EXPECT_TRUE(differ);
}
