#include <gtest/gtest.h>
#include "Labyrinth.h"
#include "DFSGenerator.h"
#include "KruskalGenerator.h"
#include "BFSFinder.h"
#include "AStarFinder.h"

// Сценарий 1: Полный цикл работы
TEST(ScenarioTest, FullWorkflow) {
    Labyrinth lab(10, 10);
    DFSGenerator gen;
    BFSFinder finder;
    
    gen.generate(lab);
    auto path = finder.findPath(lab);
    
    EXPECT_GT(path.size(), 0);
    EXPECT_EQ(path.front().first, 0);
    EXPECT_EQ(path.front().second, 0);
    EXPECT_EQ(path.back().first, 9);
    EXPECT_EQ(path.back().second, 9);
}

// Сценарий 2: Сравнение BFS и A* на одном лабиринте
TEST(ScenarioTest, CompareBFSandAStar) {
    Labyrinth lab(15, 15);
    KruskalGenerator gen;
    gen.generate(lab);
    
    Labyrinth labCopy = lab;
    
    BFSFinder bfs;
    AStarFinder astar;
    
    auto bfsPath = bfs.findPath(lab);
    auto astarPath = astar.findPath(labCopy);
    
    // Оба должны найти путь
    EXPECT_GT(bfsPath.size(), 0);
    EXPECT_GT(astarPath.size(), 0);
}

// Сценарий 3: Генерация нового лабиринта
TEST(ScenarioTest, RegenerateMaze) {
    Labyrinth lab(8, 8);
    DFSGenerator gen;
    
    gen.generate(lab);
    bool firstWall1 = lab.getCell(0, 0).walls[0];
    
    gen.generate(lab);
    bool firstWall2 = lab.getCell(0, 0).walls[0];
    
    EXPECT_TRUE(lab.getCell(0, 0).isStart);
}

// Сценарий 4: Разные размеры лабиринта
TEST(ScenarioTest, DifferentMazeSizes) {
    std::vector<std::pair<int,int>> sizes = {{5,5}, {10,10}, {15,20}, {20,15}, {30,30}};
    DFSGenerator gen;
    BFSFinder finder;
    
    for (auto [w, h] : sizes) {
        Labyrinth lab(w, h);
        gen.generate(lab);
        auto path = finder.findPath(lab);
        
        EXPECT_GT(path.size(), 0);
        EXPECT_EQ(path.back().first, w - 1);
        EXPECT_EQ(path.back().second, h - 1);
    }
}

// Сценарий 5: Поиск пути после сброса
TEST(ScenarioTest, FindPathAfterReset) {
    Labyrinth lab(10, 10);
    DFSGenerator gen;
    BFSFinder finder;
    
    gen.generate(lab);
    auto path1 = finder.findPath(lab);
    
    lab.clearSearch();
    auto path2 = finder.findPath(lab);
    
    EXPECT_EQ(path1.size(), path2.size());
}

// Сценарий 6: Все комбинации алгоритмов
TEST(ScenarioTest, AllAlgorithmCombinations) {
    Labyrinth lab(12, 12);
    DFSGenerator dfsGen;
    KruskalGenerator kruskalGen;
    BFSFinder bfs;
    AStarFinder astar;
    
    // DFS + BFS
    dfsGen.generate(lab);
    auto path1 = bfs.findPath(lab);
    
    // Kruskal + A*
    lab.reset();
    kruskalGen.generate(lab);
    auto path2 = astar.findPath(lab);
    
    EXPECT_GT(path1.size(), 0);
    EXPECT_GT(path2.size(), 0);
}

// Сценарий 7: Проверка связности лабиринта
TEST(ScenarioTest, MazeConnectivity) {
    Labyrinth lab(7, 7);
    DFSGenerator gen;
    gen.generate(lab);
    
    BFSFinder finder;
    auto path = finder.findPath(lab);
    
    EXPECT_TRUE(path.size() > 0);
}
