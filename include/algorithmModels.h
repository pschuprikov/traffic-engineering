#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>


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

    // returns the unweighted path
    std::vector<Edge> theShortestPath(const std::string &from, const std::string &to);
private:
    static constexpr double INF = 1.0 * 1000 * 1000 * 1000;
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

    std::vector<std::string> getAllNodes() const;
private:
    std::unordered_map<std::string, std::vector<Edge>> _edges;
};

} // namespace TrafficEngineering
