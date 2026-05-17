#include <gtest/gtest.h>
#include "Cell.h"

TEST(CellTest, DefaultWallsAreTrue) {
    Cell cell;
    EXPECT_TRUE(cell.walls[0]);
    EXPECT_TRUE(cell.walls[1]);
    EXPECT_TRUE(cell.walls[2]);
    EXPECT_TRUE(cell.walls[3]);
}

TEST(CellTest, ResetSearchClearsFlags) {
    Cell cell;
    cell.visitedDuringSearch = true;
    cell.inPath = true;
    
    cell.resetSearch();
    
    EXPECT_FALSE(cell.visitedDuringSearch);
    EXPECT_FALSE(cell.inPath);
}

TEST(CellTest, StartFlagWorks) {
    Cell cell;
    cell.isStart = true;
    EXPECT_TRUE(cell.isStart);
}

TEST(CellTest, FinishFlagWorks) {
    Cell cell;
    cell.isFinish = true;
    EXPECT_TRUE(cell.isFinish);
}

TEST(CellTest, MultipleFlagsCanBeSet) {
    Cell cell;
    cell.isStart = true;
    cell.isFinish = true;
    cell.visitedDuringSearch = true;
    
    EXPECT_TRUE(cell.isStart);
    EXPECT_TRUE(cell.isFinish);
    EXPECT_TRUE(cell.visitedDuringSearch);
}
