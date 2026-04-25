#include "AStarFinder.h"
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>

struct Node {
    int x, y;
    int g, f;
    bool operator>(const Node& other) const { return f > other.f; }
};

static int heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

std::vector<std::pair<int,int>> AStarFinder::findPath(Labyrinth& lab) {
    lab.clearSearch();
    int w = lab.getWidth(), h = lab.getHeight();
    auto [sx, sy] = lab.getStart();
    auto [fx, fy] = lab.getFinish();
    
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    std::map<std::pair<int,int>, int> gScore;
    std::map<std::pair<int,int>, std::pair<int,int>> prev;
    
    pq.push({sx, sy, 0, heuristic(sx, sy, fx, fy)});
    gScore[{sx, sy}] = 0;
    
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        int x = cur.x, y = cur.y;
        
        if (x == fx && y == fy) break;
        
        lab.getCell(x, y).visitedDuringSearch = true;
        
        for (auto& d : dirs) {
            int nx = x + d[0], ny = y + d[1];
            if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
            
            // проверка стен
            bool wallBlocked = false;
            if (d[0] == 1 && lab.getCell(x,y).walls[2]) wallBlocked = true;
            if (d[0] == -1 && lab.getCell(x,y).walls[3]) wallBlocked = true;
            if (d[1] == 1 && lab.getCell(x,y).walls[1]) wallBlocked = true;
            if (d[1] == -1 && lab.getCell(x,y).walls[0]) wallBlocked = true;
            if (wallBlocked) continue;
            
            int tentative_g = gScore[{x, y}] + 1;
            if (gScore.find({nx, ny}) == gScore.end() || tentative_g < gScore[{nx, ny}]) {
                prev[{nx, ny}] = {x, y};
                gScore[{nx, ny}] = tentative_g;
                int f = tentative_g + heuristic(nx, ny, fx, fy);
                pq.push({nx, ny, tentative_g, f});
            }
        }
    }
    
    std::vector<std::pair<int,int>> path;
    std::pair<int,int> cur = {fx, fy};
    while (!(cur.first == sx && cur.second == sy)) {
        path.push_back(cur);
        if (prev.find(cur) == prev.end()) break;
        cur = prev[cur];
    }
    path.push_back({sx, sy});
    std::reverse(path.begin(), path.end());
    
    for (auto& p : path) {
        lab.getCell(p.first, p.second).inPath = true;
    }
    return path;
}
