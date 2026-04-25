#include "BFSFinder.h"
#include <queue>
#include <map>

std::vector<std::pair<int,int>> BFSFinder::findPath(Labyrinth& lab) {
    lab.clearSearch();
    int w = lab.getWidth(), h = lab.getHeight();
    auto [sx, sy] = lab.getStart();
    auto [fx, fy] = lab.getFinish();
    std::queue<std::pair<int,int>> q;
    std::map<std::pair<int,int>, std::pair<int,int>> prev;
    q.push({sx,sy});
    lab.getCell(sx,sy).visitedDuringSearch = true;
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    
    while(!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        if(x==fx && y==fy) break;
        for(auto& d : dirs) {
            int nx = x + d[0], ny = y + d[1];
            if(nx<0 || ny<0 || nx>=w || ny>=h) continue;
            bool wallBlocked = false;
            if(d[0]==1 && lab.getCell(x,y).walls[2]) wallBlocked=true;
            if(d[0]==-1 && lab.getCell(x,y).walls[3]) wallBlocked=true;
            if(d[1]==1 && lab.getCell(x,y).walls[1]) wallBlocked=true;
            if(d[1]==-1 && lab.getCell(x,y).walls[0]) wallBlocked=true;
            if(wallBlocked) continue;
            if(!lab.getCell(nx,ny).visitedDuringSearch) {
                lab.getCell(nx,ny).visitedDuringSearch = true;
                prev[{nx,ny}] = {x,y};
                q.push({nx,ny});
            }
        }
    }
    std::vector<std::pair<int,int>> path;
    std::pair<int,int> cur = {fx,fy};
    while(!(cur.first==sx && cur.second==sy)) {
        path.push_back(cur);
        if(prev.find(cur)==prev.end()) break;
        cur = prev[cur];
    }
    path.push_back({sx,sy});
    std::reverse(path.begin(), path.end());
    for(auto& p : path) lab.getCell(p.first,p.second).inPath = true;
    return path;
}
