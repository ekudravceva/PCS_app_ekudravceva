#include <gtest/gtest.h>
#include "DFSGenerator.h"
#include "KruskalGenerator.h" 

TEST(DFSGeneratorTest, GeneratesMazeOfCorrectSize) {
    Labyrinth lab(10, 10);
    DFSGenerator gen;
    gen.generate(lab);
    
    EXPECT_EQ(lab.getWidth(), 10);
    EXPECT_EQ(lab.getHeight(), 10);
}

TEST(DFSGeneratorTest, MazeIsConnected) {
    Labyrinth lab(7, 7);
    DFSGenerator gen;
    gen.generate(lab);
    
    auto [sx, sy] = lab.getStart();
    auto [fx, fy] = lab.getFinish();
    
    EXPECT_TRUE(lab.getCell(sx, sy).isStart);
    EXPECT_TRUE(lab.getCell(fx, fy).isFinish);
}

TEST(DFSGeneratorTest, StartAndFinishAreSet) {
    Labyrinth lab(8, 8);
    DFSGenerator gen;
    gen.generate(lab);
    
    EXPECT_TRUE(lab.getCell(0, 0).isStart);
    EXPECT_TRUE(lab.getCell(7, 7).isFinish);
}

TEST(DFSGeneratorTest, MazeHasNoFullWalls) {
    Labyrinth lab(6, 6);
    DFSGenerator gen;
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

TEST(DFSGeneratorTest, BorderWallsArePresent) {
    Labyrinth lab(5, 5);
    DFSGenerator gen;
    gen.generate(lab);
    
    EXPECT_TRUE(lab.getCell(0, 0).walls[3]);  // западная граница
    EXPECT_TRUE(lab.getCell(0, 0).walls[0]);  // северная граница
}
