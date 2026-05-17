#include <gtest/gtest.h>
#include "Labyrinth.h"

TEST(LabyrinthTest, ConstructorCreatesCorrectSize) {
    Labyrinth lab(10, 15);
    EXPECT_EQ(lab.getWidth(), 10);
    EXPECT_EQ(lab.getHeight(), 15);
}

TEST(LabyrinthTest, GetCellReturnsValidCell) {
    Labyrinth lab(5, 5);
    Cell& cell = lab.getCell(2, 3);
    EXPECT_TRUE(cell.walls[0]);
}

TEST(LabyrinthTest, SetStartWorks) {
    Labyrinth lab(10, 10);
    lab.setStart(3, 4);
    auto [x, y] = lab.getStart();
    EXPECT_EQ(x, 3);
    EXPECT_EQ(y, 4);
    EXPECT_TRUE(lab.getCell(3, 4).isStart);
}

TEST(LabyrinthTest, SetFinishWorks) {
    Labyrinth lab(10, 10);
    lab.setFinish(7, 8);
    auto [x, y] = lab.getFinish();
    EXPECT_EQ(x, 7);
    EXPECT_EQ(y, 8);
    EXPECT_TRUE(lab.getCell(7, 8).isFinish);
}

TEST(LabyrinthTest, ResetClearsAllCells) {
    Labyrinth lab(5, 5);
    lab.setStart(1, 1);
    lab.setFinish(3, 3);
    lab.getCell(2, 2).walls[0] = false;
    
    lab.reset();
    
    EXPECT_TRUE(lab.getCell(2, 2).walls[0]);
    EXPECT_FALSE(lab.getCell(1, 1).isStart);
    EXPECT_FALSE(lab.getCell(3, 3).isFinish);
}

TEST(LabyrinthTest, ClearSearchResetsSearchFlags) {
    Labyrinth lab(5, 5);
    lab.getCell(1, 1).visitedDuringSearch = true;
    lab.getCell(2, 2).inPath = true;
    
    lab.clearSearch();
    
    EXPECT_FALSE(lab.getCell(1, 1).visitedDuringSearch);
    EXPECT_FALSE(lab.getCell(2, 2).inPath);
}

TEST(LabyrinthTest, DefaultStartIsTopLeftFinishIsBottomRight) {
    Labyrinth lab(8, 6);
    auto [sx, sy] = lab.getStart();
    auto [fx, fy] = lab.getFinish();
    
    EXPECT_EQ(sx, 0);
    EXPECT_EQ(sy, 0);
    EXPECT_EQ(fx, 7);
    EXPECT_EQ(fy, 5);
}
