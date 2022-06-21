#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <optional>


namespace TrafficEngineering {

struct Edge {
    std::string from;
    std::string to;
    double weight;
};


class Graph {
public:
    Graph(int vertex_number, const std::vector<Edge> edges);

    double theShortestPathWeight(const std::string &from, const std::string &to);

    std::vector<Edge> theShortestPath(const std::string &from, const std::string &to);
private:
    std::vector<Edge> theShortestPathImpl(const std::string &from, const std::string &to);
    int checked_vertex_id(const std::string &name) const;

private:
    std::vector<std::string> _names;
    std::unordered_map<std::string, int> _indexes;
    std::vector<std::vector<double>> _distances;
    std::vector<std::vector<int>> _parent;
};


class Tree {
public:
    Tree(const std::string &root);

    void addEdge(const Edge &edge);
    void addBranch(const std::vector<Edge> &branch);

    double theLongestPathWeight(const std::string &node) const;

    std::string getRoot() const { return _root; }
    std::vector<std::string> getAllNodes() const;
    std::vector<Edge> getEdgesDFSOrder() const;
private:
    std::vector<Edge> dfs(const std::string &node) const;
private:
    std::string _root;
    std::unordered_map<std::string, std::vector<Edge>> _edges;
};

} // namespace TrafficEngineering
