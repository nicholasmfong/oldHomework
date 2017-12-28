#include "graph.h"          //graph.cpp
#include <cassert>
#include <algorithm>
#include <queue>
#include <list>
graph::graph(){
    A = std::vector<std::list<sizetype>>();
}
graph::sizetype graph::n() const{
    return A.size();
}

graph::sizetype graph::m() const{
   sizetype ans(0);
   for (sizetype i = 0; i < n(); ++i)
       ans += A[i].size();
   return ans / 2;
}

bool graph::is_edge(sizetype v, sizetype w) const{
    assert(v < n() && w < n());
    return (std::find(A[v].begin(),
                      A[v].end(),
                      w) != A[v].end());
}
std::list<graph::sizetype> graph::neighbors(sizetype v) const{
    assert(v < n());
    return A[v];
}
void graph::add_vertex(){
    A.push_back(std::list<sizetype>());
}
void graph::add_edge(sizetype v, sizetype w){
    assert(v < n() && w < n());
    if (is_edge(v, w))
        return;
    A[v].push_back(w);
    A[w].push_back(v);
}
void graph::remove_edge(sizetype v, sizetype w){
    assert(v < n() && w < n());
    if (!is_edge(v, w))
        return;
    A[v].erase(std::remove(A[v].begin(),A[v].end(),w), A[v].end());
    A[w].erase(std::remove(A[w].begin(), A[w].end(),v),A[w].end());
}
void graph::bfs(std::vector<int> & generation){
    std::vector<bool> visited(n(), false);
    std::vector<int> parent(n(), -1);
    for (sizetype v = 0; v < n(); ++v){
        if (!visited[v]){
            visited[v] = true;
            bfs1(v, visited, parent, generation);
        }
    }
}
void graph::bfs1(sizetype start,std::vector<bool> & visited,std::vector<int> & parent,std::vector<int> & generation){
    std::queue<sizetype> q;
    q.push(start);
    visited[start] = true;
    parent[start] = start;
    while(!q.empty()){
        sizetype f = q.front();
        q.pop();
        for (auto w : neighbors(f)){
            if(!visited[w]){
                visited[w] = true;
                parent[w] = f;
                generation[w] = (generation[f] + 1);
                q.push(w);
            }
        }
    }
}
bool graph::make_teams(std::list<sizetype> &team1, std::list<sizetype> &team2){
    team1.clear();
    team2.clear();
    std::vector<int> generation(n(), 1);
    bfs(generation);
    for(size_t i = 0; i < n(); i++){
        for(auto e: neighbors(i)){
            if(generation[e] == generation[i]){
                return false;
            }
        }
    }
    for(size_t j = 0; j < generation.size(); j++){
        if(generation[j] % 2 == 1){
            team1.push_back(j);
        }
        else{
            team2.push_back(j);
        }
    }
    return true;
}
std::istream & operator >> (std::istream & is, graph & g){
    size_t filler;
    size_t i = 0;
    size_t v;
    size_t w;
    is>>filler;
    while(i < filler){
        g.add_vertex();
        i++;
    }
    is >> filler;
    i = 0;
    while(is >> v && is >> w && i < filler){
        g.add_edge(v,w);
        i ++;
    }
    assert(filler == i);
    return is;
}
