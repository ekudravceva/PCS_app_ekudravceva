#include "StepByStepFinder.h"
#include "Visualizer.h"
#include <algorithm>

StepByStepFinder::StepByStepFinder(Labyrinth& lab, int algoType)
    : lab(&lab), algorithm(algoType), finished(false), found(false) {
    reset();
}

StepByStepFinder::~StepByStepFinder() {}

void StepByStepFinder::reset() {
    lab->clearSearch();
    finished = false;
    found = false;
    path.clear();
    prev.clear();
    
    start = lab->getStart();
    finish = lab->getFinish();
    
    // Очищаем очереди
    while (!bfsQueue.empty()) bfsQueue.pop();
    while (!aStarPq.empty()) aStarPq.pop();
    gScore.clear();
    
    if (algorithm == 1) { // BFS
        bfsQueue.push(start);
        lab->getCell(start.first, start.second).visitedDuringSearch = true;
    } else { // A*
        int h = heuristic(start.first, start.second, finish.first, finish.second);
        aStarPq.push({start.first, start.second, 0, h});
        gScore[{start.first, start.second}] = 0;
    }
}

int StepByStepFinder::heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

bool StepByStepFinder::isWallBlocked(int x, int y, int nx, int ny) {
    const Cell& cell = lab->getCell(x, y);
    if (nx == x + 1) return cell.walls[2];  // восток
    if (nx == x - 1) return cell.walls[3];  // запад
    if (ny == y + 1) return cell.walls[1];  // юг
    if (ny == y - 1) return cell.walls[0];  // север
    return true;
}

void StepByStepFinder::reconstructPath() {
    path.clear();
    if (!found) return;
    
    std::pair<int,int> cur = finish;
    while (!(cur.first == start.first && cur.second == start.second)) {
        path.push_back(cur);
        if (prev.find(cur) == prev.end()) break;
        cur = prev[cur];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    
    for (auto& p : path) {
        lab->getCell(p.first, p.second).inPath = true;
    }
}

bool StepByStepFinder::hasNext() {
    return !finished;
}

void StepByStepFinder::nextStep(Visualizer& vis) {
    if (finished) return;
    
    int w = lab->getWidth();
    int h = lab->getHeight();
    
    if (algorithm == 1) { // BFS
        if (bfsQueue.empty()) {
            finished = true;
            reconstructPath();
            return;
        }
        
        auto [x, y] = bfsQueue.front();
        bfsQueue.pop();
        
        if (x == finish.first && y == finish.second) {
            found = true;
            finished = true;
            reconstructPath();
            return;
        }
        
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (auto& d : dirs) {
            int nx = x + d[0], ny = y + d[1];
            if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
            if (isWallBlocked(x, y, nx, ny)) continue;
            
            if (!lab->getCell(nx, ny).visitedDuringSearch) {
                lab->getCell(nx, ny).visitedDuringSearch = true;
                prev[{nx, ny}] = {x, y};
                bfsQueue.push({nx, ny});
            }
        }
        
    } else { // A*
        if (aStarPq.empty()) {
            finished = true;
            reconstructPath();
            return;
        }
        
        AStarNode cur = aStarPq.top();
        aStarPq.pop();
        int x = cur.x, y = cur.y;
        
        if (x == finish.first && y == finish.second) {
            found = true;
            finished = true;
            reconstructPath();
            return;
        }
        
        lab->getCell(x, y).visitedDuringSearch = true;
        
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (auto& d : dirs) {
            int nx = x + d[0], ny = y + d[1];
            if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
            if (isWallBlocked(x, y, nx, ny)) continue;
            
            int tentative_g = gScore[{x, y}] + 1;
            if (gScore.find({nx, ny}) == gScore.end() || tentative_g < gScore[{nx, ny}]) {
                prev[{nx, ny}] = {x, y};
                gScore[{nx, ny}] = tentative_g;
                int f = tentative_g + heuristic(nx, ny, finish.first, finish.second);
                aStarPq.push({nx, ny, tentative_g, f});
            }
        }
    }
    
    // Отображаем текущее состояние после шага
    vis.draw(*lab);
}
