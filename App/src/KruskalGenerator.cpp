#include "KruskalGenerator.h"
#include <random>
#include <vector>
#include <algorithm>

struct DSU {
    std::vector<int> parent;
    DSU(int n) { parent.resize(n); for(int i=0;i<n;i++) parent[i]=i; }
    int find(int x) { return parent[x]==x ? x : parent[x]=find(parent[x]); }
    void unite(int a, int b) { parent[find(a)]=find(b); }
};

void KruskalGenerator::generate(Labyrinth& lab) {
    lab.reset();
    int w = lab.getWidth(), h = lab.getHeight();
    struct Edge { int x1,y1,x2,y2; };
    std::vector<Edge> edges;
    for(int y=0;y<h;y++)
        for(int x=0;x<w;x++) {
            if(x+1<w) edges.push_back({x,y,x+1,y});
            if(y+1<h) edges.push_back({x,y,x,y+1});
        }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(edges.begin(), edges.end(), g);
    
    DSU dsu(w*h);
    for(auto& e : edges) {
        int id1 = e.y1*w + e.x1;
        int id2 = e.y2*w + e.x2;
        if(dsu.find(id1) != dsu.find(id2)) {
            dsu.unite(id1, id2);
            if(e.x2==e.x1+1) {
                lab.getCell(e.x1,e.y1).walls[2]=false;
                lab.getCell(e.x2,e.y2).walls[3]=false;
            } else if(e.x1==e.x2+1) {
                lab.getCell(e.x1,e.y1).walls[3]=false;
                lab.getCell(e.x2,e.y2).walls[2]=false;
            } else if(e.y2==e.y1+1) {
                lab.getCell(e.x1,e.y1).walls[1]=false;
                lab.getCell(e.x2,e.y2).walls[0]=false;
            } else if(e.y1==e.y2+1) {
                lab.getCell(e.x1,e.y1).walls[0]=false;
                lab.getCell(e.x2,e.y2).walls[1]=false;
            }
        }
    }
    lab.setStart(0,0);
    lab.setFinish(w-1, h-1);
}
