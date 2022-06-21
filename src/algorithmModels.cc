#include "algorithmModels.h"

#include <cassert>
#include <cmath>
#include <exception>
#include <limits>


namespace TrafficEngineering {

Graph::Graph(int vertex_number, const std::vector<Edge> edges) :
    _names(vertex_number),
    _distances(vertex_number, std::vector<double>(vertex_number, std::numeric_limits<double>::infinity())),
    _parent(vertex_number, std::vector<int>(vertex_number))
{
    for (const auto &edge : edges) {
        if (_indexes.count(edge.from) == 0) {
            auto const vertex_id =_indexes.size();
            _names[vertex_id] = edge.from;
            _indexes[edge.from] = vertex_id;
        }
        if (_indexes.count(edge.to) == 0) {
            auto const vertex_id =_indexes.size();
            _names[vertex_id] = edge.to;
            _indexes[edge.to] = vertex_id;
        }
        if (std::isnan(edge.weight)) {
            throw std::invalid_argument("edge weight can't be NaN");
        }
        if (std::isinf(edge.weight)) {
            throw std::invalid_argument("edge weight can't be infinite");
        }
        if (edge.weight < 0) {
            throw std::invalid_argument("edge weight can't be negative");
        }
        _distances[_indexes[edge.from]][_indexes[edge.to]] = edge.weight;
        _parent[_indexes[edge.from]][_indexes[edge.to]] = _indexes[edge.from];
    }
    for (int i = 0; i < vertex_number; i++) {
        _distances[i][i] = 0;
        _parent[i][i] = i;
    }

    for (int k = 0; k < vertex_number; k++) {
        for (int i = 0; i < vertex_number; i++) {
            for (int j = 0; j < vertex_number; j++) {
                if (_distances[i][j] > _distances[i][k] + _distances[k][j]) {
                    _distances[i][j] = _distances[i][k] + _distances[k][j];
                    _parent[i][j] = k;
                }
            }
        }
    }
}

double Graph::theShortestPathWeight(const std::string &from, const std::string &to) {
    return _distances[checked_vertex_id(from)][checked_vertex_id(to)];
}

int Graph::checked_vertex_id(const std::string &name) const {
    if (_indexes.count(name) == 0) {
        throw std::invalid_argument("unknown vertex " + name);
    }
    return _indexes.at(name);
}

std::vector<Edge> Graph::theShortestPath(const std::string &from, const std::string &to) {
    if (_distances[_indexes.at(from)][_indexes.at(to)] == std::numeric_limits<double>::infinity()) {
        throw std::invalid_argument("no path between " + from + " and " + to);
    }
    return theShortestPathImpl(from, to);
}

std::vector<Edge> Graph::theShortestPathImpl(const std::string &from, const std::string &to) {
    std::string vertex = _names[_parent[_indexes[from]][_indexes[to]]];
    if (from == vertex) {
        return {{from, to, 0}};
    }
    auto left = theShortestPathImpl(from, vertex);
    auto right = theShortestPathImpl(vertex, to);
    left.insert(left.end(), right.begin(), right.end());
    return left;
}


Tree::Tree(const std::string &root) : _root(root) {
    _edges[root] = {};
}

void Tree::addEdge(const Edge &edge) {
    assert(_edges.count(edge.from) != 0);
    assert(_edges.count(edge.to) == 0);
    _edges[edge.from].push_back(edge);
    _edges[edge.to] = {};
}

void Tree::addBranch(const std::vector<Edge> &branch) {
    for (const auto &edge : branch) {
        addEdge(edge);
    }
}

double Tree::theLongestPathWeight(const std::string &node) const {
    assert(_edges.count(node) != 0);
    double result = 0;
    for (const auto &edge : _edges.at(node)) {
        result = std::max(result, edge.weight + theLongestPathWeight(edge.to));
    }
    return result;
}

std::vector<std::string> Tree::getAllNodes() const {
    std::vector<std::string> result;
    for (const auto &entry : _edges) {
        result.push_back(entry.first);
    }
    return result;
}

std::vector<Edge> Tree::getEdgesDFSOrder() const {
    return dfs(_root);
}

std::vector<Edge> Tree::dfs(const std::string &node) const {
    std::vector<Edge> result;
    for (const auto &edge : _edges.at(node)) {
        result.push_back(edge);
        auto others = dfs(edge.to);
        result.insert(result.end(), others.begin(), others.end());
    }
    return result;
}

} // namespace TrafficEngineering
