#ifndef GRAPH_H         //graph.h
#define GRAPH_H
#include <iostream>
#include <vector>
#include <list>
class graph{
public:
    typedef std::size_t sizetype;
    // pre: none
    // post: creates an empty graph
    graph();

    // const member functions
    // pre: none
    // post: returns the number of vertices in this graph
    sizetype n() const;
    // pre: none
    // post: returns the number of edges in this graph
    sizetype m() const;
    // pre: v < n(), w < n()
    // post: returns true iff {v, w} is an edge
    bool is_edge(sizetype v, sizetype w) const;
    // pre: v < n()
    // post: returns a list of vertices adjacent to v
    std::list<sizetype> neighbors(sizetype v) const;

    // nonconst member functions
    // pre: none
    // post: add another vertex to this graph (it has highest label)
    void add_vertex();
    // pre: v < n(), w < n()
    // post: if {v, w} is already an edge, do nothing
    //       else add edge {v, w} to this graph
    void add_edge(sizetype v, sizetype w);
    // pre: v < n(), w < n()
    // post: if {v, w} is not an edge, do nothing
    //       else remove {v, w} from this graph
    void remove_edge(sizetype v, sizetype w);
    // pre: team1 and team2 are lists
    // post: makes 2 teams on team1 and team2 with different vertices so that no 2 connected
    //       vertices are on the same team and returns true. If not possible, returns false
    bool make_teams(std::list<sizetype> &team1, std::list<sizetype> &team2);
private:
    std::vector<std::list<sizetype>> A;
    // invariants:  A is the adjacency list representation of this
    //              simple undirected graph
    //              vertices are numbered 0, ..., n()-1
    //              A[v] is an unordered list of vertices adjacency to v
    //              if {v, w} is an edge, then A[v] contains w, and
    //              A[w] contains v

    //performs a breadth first search and gives each element a generation number
    void bfs(std::vector<int> & generation);
    void bfs1(sizetype, std::vector<bool> &, std::vector<int> &, std::vector<int> &generation);
};
std::istream & operator >> (std::istream & is, graph & g);
#endif // GRAPH_H
