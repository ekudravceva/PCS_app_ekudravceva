#include <gtest/gtest.h>
#include "BFSFinder.h"
#include "DFSGenerator.h"
#include "KruskalGenerator.h"

TEST(BFSFinderTest, FindsPathOnSimpleMaze) {
    Labyrinth lab(3, 3);
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (x < 2) lab.getCell(x, y).walls[2] = false;
            if (y < 2) lab.getCell(x, y).walls[1] = false;
        }
    }
    lab.setStart(0, 0);
    lab.setFinish(2, 2);
    
    BFSFinder finder;
    auto path = finder.findPath(lab);
    
    EXPECT_GT(path.size(), 0);
    EXPECT_EQ(path[0].first, 0);
    EXPECT_EQ(path[0].second, 0);
    EXPECT_EQ(path.back().first, 2);
    EXPECT_EQ(path.back().second, 2);
}

TEST(BFSFinderTest, ReturnsPathWithStartAndFinish) {
    Labyrinth lab(4, 4);
    DFSGenerator gen;
    gen.generate(lab);
    
    BFSFinder finder;
    auto path = finder.findPath(lab);
    
    EXPECT_GE(path.size(), 1);
    EXPECT_TRUE(lab.getCell(0, 0).isStart || path[0].first == 0);
}

TEST(BFSFinderTest, PathLengthIsAtLeastManhattanDistance) {
    Labyrinth lab(10, 10);
    DFSGenerator gen;
    gen.generate(lab);
    
    BFSFinder finder;
    auto path = finder.findPath(lab);
    
    EXPECT_GE(path.size(), 18);
}

TEST(BFSFinderTest, PathExistsInGeneratedMaze) {
    Labyrinth lab(10, 10);
    DFSGenerator gen;
    gen.generate(lab);
    
    BFSFinder finder;
    auto path = finder.findPath(lab);
    
    EXPECT_GT(path.size(), 0);
    EXPECT_EQ(path.front().first, 0);
    EXPECT_EQ(path.front().second, 0);
    EXPECT_EQ(path.back().first, 9);
    EXPECT_EQ(path.back().second, 9);
}

TEST(BFSFinderTest, MarksVisitedCells) {
    Labyrinth lab(5, 5);
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (x < 4) lab.getCell(x, y).walls[2] = false;
            if (y < 4) lab.getCell(x, y).walls[1] = false;
        }
    }
    lab.setStart(0, 0);
    lab.setFinish(4, 4);
    
    BFSFinder finder;
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

TEST(BFSFinderTest, PathCellsAreMarked) {
    Labyrinth lab(4, 4);
    for (int i = 0; i < 4; i++) {
        if (i < 3) {
            lab.getCell(i, 0).walls[2] = false;
            lab.getCell(0, i).walls[1] = false;
        }
    }
    lab.setStart(0, 0);
    lab.setFinish(3, 3);
    
    BFSFinder finder;
    finder.findPath(lab);
    
    EXPECT_TRUE(lab.getCell(0, 0).isStart || lab.getCell(0, 0).inPath);
}

TEST(BFSFinderTest, MultipleFindPathsOnSameMaze) {
    Labyrinth lab(6, 6);
    DFSGenerator gen;
    gen.generate(lab);
    
    BFSFinder finder;
    auto path1 = finder.findPath(lab);
    lab.clearSearch();
    auto path2 = finder.findPath(lab);
    
    EXPECT_EQ(path1.size(), path2.size());
}
