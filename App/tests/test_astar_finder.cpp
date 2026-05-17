#include <gtest/gtest.h>
#include "AStarFinder.h"
#include "BFSFinder.h"
#include "DFSGenerator.h"
#include "KruskalGenerator.h"

TEST(AStarFinderTest, FindsPathOnSimpleMaze) {
    Labyrinth lab(3, 3);
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (x < 2) lab.getCell(x, y).walls[2] = false;
            if (y < 2) lab.getCell(x, y).walls[1] = false;
        }
    }
    lab.setStart(0, 0);
    lab.setFinish(2, 2);
    
    AStarFinder finder;
    auto path = finder.findPath(lab);
    
    EXPECT_GT(path.size(), 0);
    EXPECT_EQ(path[0].first, 0);
    EXPECT_EQ(path[0].second, 0);
    EXPECT_EQ(path.back().first, 2);
    EXPECT_EQ(path.back().second, 2);
}

TEST(AStarFinderTest, AStarFindsPath) {
    Labyrinth lab(15, 15);
    DFSGenerator gen;
    gen.generate(lab);
    lab.setStart(0, 0);
    lab.setFinish(14, 14);
    
    AStarFinder astar;
    auto astarPath = astar.findPath(lab);
    
    EXPECT_GT(astarPath.size(), 0);
    EXPECT_EQ(astarPath.front().first, 0);
    EXPECT_EQ(astarPath.front().second, 0);
    EXPECT_EQ(astarPath.back().first, 14);
    EXPECT_EQ(astarPath.back().second, 14);
}

TEST(AStarFinderTest, ReturnsPathWithStartAndFinish) {
    Labyrinth lab(8, 8);
    KruskalGenerator gen;
    gen.generate(lab);
    
    AStarFinder finder;
    auto path = finder.findPath(lab);
    
    EXPECT_GE(path.size(), 1);
    EXPECT_EQ(path[0].first, 0);
    EXPECT_EQ(path[0].second, 0);
}

TEST(AStarFinderTest, PathLengthIsAtLeastManhattanDistance) {
    Labyrinth lab(10, 10);
    DFSGenerator gen;
    gen.generate(lab);
    
    AStarFinder finder;
    auto path = finder.findPath(lab);
    
    EXPECT_GE(path.size(), 18);
}

TEST(AStarFinderTest, PathIsValid) {
    Labyrinth lab(10, 10);
    DFSGenerator gen;
    gen.generate(lab);
    
    AStarFinder finder;
    auto path = finder.findPath(lab);
    
    ASSERT_GT(path.size(), 0);
    EXPECT_EQ(path[0].first, 0);
    EXPECT_EQ(path[0].second, 0);
    EXPECT_EQ(path.back().first, 9);
    EXPECT_EQ(path.back().second, 9);
}

TEST(AStarFinderTest, MarksVisitedCells) {
    Labyrinth lab(5, 5);
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (x < 4) lab.getCell(x, y).walls[2] = false;
            if (y < 4) lab.getCell(x, y).walls[1] = false;
        }
    }
    lab.setStart(0, 0);
    lab.setFinish(4, 4);
    
    AStarFinder finder;
    finder.findPath(lab);
    
    bool hasVisited = false;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (lab.getCell(x, y).visitedDuringSearch) {
                hasVisited = true;
            }
        }
    }
    EXPECT_TRUE(hasVisited);
}

TEST(AStarFinderTest, MultipleFindPathsOnSameMaze) {
    Labyrinth lab(8, 8);
    KruskalGenerator gen;
    gen.generate(lab);
    
    AStarFinder finder;
    auto path1 = finder.findPath(lab);
    lab.clearSearch();
    auto path2 = finder.findPath(lab);
    
    EXPECT_EQ(path1.size(), path2.size());
}
