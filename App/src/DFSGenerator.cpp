#include "DFSGenerator.h"
#include <stack>
#include <random>
#include <algorithm>

static std::mt19937 rng(std::random_device{}());

void DFSGenerator::generate(Labyrinth& lab) {
    lab.reset();
    int w = lab.getWidth();
    int h = lab.getHeight();
    std::vector<std::vector<bool>> visited(h, std::vector<bool>(w, false));
    std::stack<std::pair<int,int>> st;
    
    int startX = 0, startY = 0;
    visited[startY][startX] = true;
    st.push({startX, startY});
    
    while (!st.empty()) {
        auto [x, y] = st.top();
        std::vector<std::pair<int,int>> neighbors;
        if (x > 0 && !visited[y][x-1]) neighbors.push_back({x-1, y});
        if (x < w-1 && !visited[y][x+1]) neighbors.push_back({x+1, y});
        if (y > 0 && !visited[y-1][x]) neighbors.push_back({x, y-1});
        if (y < h-1 && !visited[y+1][x]) neighbors.push_back({x, y+1});
        
        if (!neighbors.empty()) {
            std::shuffle(neighbors.begin(), neighbors.end(), rng);
            auto [nx, ny] = neighbors[0];
            // remove wall
            if (nx == x-1) { lab.getCell(x,y).walls[3] = false; lab.getCell(nx,ny).walls[2] = false; }
            if (nx == x+1) { lab.getCell(x,y).walls[2] = false; lab.getCell(nx,ny).walls[3] = false; }
            if (ny == y-1) { lab.getCell(x,y).walls[0] = false; lab.getCell(nx,ny).walls[1] = false; }
            if (ny == y+1) { lab.getCell(x,y).walls[1] = false; lab.getCell(nx,ny).walls[0] = false; }
            visited[ny][nx] = true;
            st.push({nx, ny});
        } else {
            st.pop();
        }
    }
    lab.setStart(0,0);
    lab.setFinish(w-1, h-1);
}
