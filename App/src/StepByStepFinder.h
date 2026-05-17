#ifndef STEP_BY_STEP_FINDER_H
#define STEP_BY_STEP_FINDER_H

#include "Labyrinth.h"
#include "Visualizer.h"
#include <queue>
#include <map>
#include <vector>
#include <stack>
#include <functional>
#include <cmath>

class StepByStepFinder {
public:
    StepByStepFinder(Labyrinth& lab, int algoType); // 1=BFS, 2=A*
    ~StepByStepFinder();
    
    bool hasNext();
    void nextStep(Visualizer& vis);  // ← сигнатура должна совпадать с .cpp
    void reset();
    bool isFinished() const { return finished; }
    std::vector<std::pair<int,int>> getPath() const { return path; }
    
private:
    Labyrinth* lab;
    int algorithm;
    bool finished;
    bool found;
    std::vector<std::pair<int,int>> path;
    std::pair<int,int> start, finish;
    
    // Общие для BFS и A*
    std::map<std::pair<int,int>, std::pair<int,int>> prev;
    
    // Для BFS
    std::queue<std::pair<int,int>> bfsQueue;
    
    // Для A*
    struct AStarNode {
        int x, y, g, f;
        bool operator>(const AStarNode& other) const { return f > other.f; }
    };
    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> aStarPq;
    std::map<std::pair<int,int>, int> gScore;
    
    int heuristic(int x1, int y1, int x2, int y2);
    void reconstructPath();
    bool isWallBlocked(int x, int y, int nx, int ny);
};

#endif
